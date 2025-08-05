#!/usr/bin/env python3
"""
Production ML inference runner for ARM ML SDK
"""

import os
import sys
import json
import time
import numpy as np
import subprocess
from pathlib import Path

class MLInferenceRunner:
    def __init__(self, sdk_root=None):
        self.sdk_root = sdk_root or Path(__file__).parent.parent
        self.scenario_runner = self.sdk_root / "bin" / "scenario-runner"
        
        # Check environment
        if not self.scenario_runner.exists():
            raise RuntimeError(f"Scenario runner not found at {self.scenario_runner}")
    
    def run_inference(self, model_path, input_data, output_path=None):
        """Run ML inference on input data"""
        print(f"\n=== Running ML Inference ===")
        print(f"Model: {model_path}")
        print(f"Input shape: {input_data.shape if hasattr(input_data, 'shape') else 'Unknown'}")
        
        # Create scenario for model
        scenario = self._create_inference_scenario(model_path, input_data)
        scenario_path = "/tmp/ml_inference_scenario.json"
        
        with open(scenario_path, 'w') as f:
            json.dump(scenario, f, indent=2)
        
        # Run inference
        start_time = time.time()
        
        env = os.environ.copy()
        env["DYLD_LIBRARY_PATH"] = "/usr/local/lib"
        
        result = subprocess.run([
            str(self.scenario_runner),
            "--scenario", scenario_path,
            "--output", output_path or "/tmp/ml_output"
        ], capture_output=True, text=True, env=env)
        
        inference_time = time.time() - start_time
        
        if result.returncode == 0:
            print(f"✓ Inference completed in {inference_time:.3f} seconds")
            return True
        else:
            print(f"✗ Inference failed: {result.stderr}")
            return False
    
    def _create_inference_scenario(self, model_path, input_data):
        """Create Vulkan scenario for inference"""
        # This is a simplified version - real implementation would
        # parse the model and create appropriate pipeline
        
        scenario = {
            "name": "ml_inference",
            "commands": [],
            "resources": []
        }
        
        # Add input buffer
        if isinstance(input_data, np.ndarray):
            input_path = "/tmp/ml_input.npy"
            np.save(input_path, input_data)
            
            scenario["resources"].append({
                "buffer": {
                    "uid": "input",
                    "shader_access": "readonly",
                    "size": input_data.nbytes,
                    "src": input_path
                }
            })
        
        # Add model-specific pipeline stages
        model_name = os.path.basename(model_path).replace('.tflite', '')
        
        # For style transfer models
        if "style" in model_name.lower() or model_name in ["la_muse", "udnie", "wave_crop"]:
            self._add_style_transfer_pipeline(scenario)
        else:
            self._add_generic_pipeline(scenario)
        
        return scenario
    
    def _add_style_transfer_pipeline(self, scenario):
        """Add style transfer pipeline stages"""
        stages = [
            ("conv1", "conv2d.spv", [256, 256, 1]),
            ("relu1", "relu.spv", [65536]),
            ("conv2", "conv2d.spv", [128, 128, 1]),
            ("relu2", "relu.spv", [16384])
        ]
        
        for i, (name, shader, dispatch) in enumerate(stages):
            # Add shader resource
            scenario["resources"].append({
                "shader": {
                    "uid": f"{name}_shader",
                    "type": "SPIR-V",
                    "src": f"../shaders/{shader}",
                    "entry": "main"
                }
            })
            
            # Add dispatch command
            scenario["commands"].append({
                "dispatch_compute": {
                    "shader_ref": f"{name}_shader",
                    "rangeND": dispatch,
                    "bindings": [{
                        "id": 0,
                        "set": 0,
                        "resource_ref": "input" if i == 0 else f"stage_{i-1}_output"
                    }]
                }
            })
            
            # Add intermediate buffers
            if i < len(stages) - 1:
                scenario["resources"].append({
                    "buffer": {
                        "uid": f"stage_{i}_output",
                        "shader_access": "readwrite",
                        "size": 4 * np.prod(dispatch)  # float32
                    }
                })
    
    def _add_generic_pipeline(self, scenario):
        """Add generic ML pipeline"""
        # Simple convolution + activation pipeline
        scenario["resources"].append({
            "shader": {
                "uid": "generic_ml",
                "type": "SPIR-V",
                "src": "../shaders/conv2d.spv",
                "entry": "main"
            }
        })
        
        scenario["commands"].append({
            "dispatch_compute": {
                "shader_ref": "generic_ml",
                "rangeND": [256, 256, 1],
                "bindings": [{
                    "id": 0,
                    "set": 0,
                    "resource_ref": "input"
                }]
            }
        })

def main():
    import argparse
    parser = argparse.ArgumentParser(description="Production ML Inference")
    parser.add_argument("model", help="Path to ML model")
    parser.add_argument("--input", help="Input data (numpy file or image)")
    parser.add_argument("--output", help="Output path")
    parser.add_argument("--benchmark", action="store_true", help="Run benchmark")
    
    args = parser.parse_args()
    
    runner = MLInferenceRunner()
    
    # Load or create input data
    if args.input and args.input.endswith('.npy'):
        input_data = np.load(args.input)
    else:
        # Create random input for testing
        input_data = np.random.randn(1, 256, 256, 3).astype(np.float32)
        print("Note: Using random input data for testing")
    
    # Run inference
    if args.benchmark:
        print("\nRunning benchmark...")
        times = []
        for i in range(10):
            start = time.time()
            runner.run_inference(args.model, input_data, args.output)
            times.append(time.time() - start)
        
        print(f"\nBenchmark Results:")
        print(f"  Average: {np.mean(times):.3f}s")
        print(f"  Min: {np.min(times):.3f}s")
        print(f"  Max: {np.max(times):.3f}s")
    else:
        runner.run_inference(args.model, input_data, args.output)

if __name__ == "__main__":
    main()
