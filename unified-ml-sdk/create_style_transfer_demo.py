#!/usr/bin/env python3
"""
Create a style transfer demo using the unified ML SDK
"""

import numpy as np
import json
import os
from PIL import Image

class StyleTransferDemo:
    def __init__(self, model_path):
        self.model_path = model_path
        self.model_name = os.path.basename(model_path).replace('.tflite', '')
        
    def preprocess_image(self, image_path, target_size=(256, 256)):
        """Preprocess image for style transfer"""
        img = Image.open(image_path).convert('RGB')
        img = img.resize(target_size, Image.LANCZOS)
        
        # Convert to numpy array and normalize
        img_array = np.array(img, dtype=np.float32)
        img_array = img_array / 255.0  # Normalize to [0, 1]
        
        # Add batch dimension
        img_array = np.expand_dims(img_array, axis=0)
        
        # Save as numpy file
        np.save('input_image.npy', img_array)
        print(f"Preprocessed image: {img_array.shape}")
        return img_array
    
    def create_style_transfer_scenario(self):
        """Create Vulkan scenario for style transfer"""
        scenario = {
            "commands": [],
            "resources": []
        }
        
        # Style transfer typically has these layers:
        # 1. Initial convolutions
        # 2. Residual blocks
        # 3. Upsampling convolutions
        # 4. Final convolution to RGB
        
        # For demo, we'll create a simplified pipeline
        operations = [
            {
                "name": "conv1",
                "type": "conv2d",
                "input_shape": [1, 256, 256, 3],
                "output_shape": [1, 256, 256, 32],
                "kernel_size": [9, 9],
                "stride": 1
            },
            {
                "name": "relu1",
                "type": "relu",
                "shape": [1, 256, 256, 32]
            },
            {
                "name": "conv2",
                "type": "conv2d", 
                "input_shape": [1, 256, 256, 32],
                "output_shape": [1, 256, 256, 64],
                "kernel_size": [3, 3],
                "stride": 2
            },
            {
                "name": "conv3",
                "type": "conv2d",
                "input_shape": [1, 128, 128, 64],
                "output_shape": [1, 128, 128, 128],
                "kernel_size": [3, 3],
                "stride": 2
            }
        ]
        
        # Add initial input buffer
        scenario["resources"].append({
            "buffer": {
                "shader_access": "readonly",
                "size": 1 * 256 * 256 * 3 * 4,  # NHWC * float32
                "src": "input_image.npy",
                "uid": "input_image"
            }
        })
        
        # Create buffers and operations
        buffer_id = 0
        for i, op in enumerate(operations):
            if op["type"] == "conv2d":
                # Add convolution shader
                scenario["resources"].append({
                    "shader": {
                        "entry": "main",
                        "src": f"shaders/conv2d.spv",
                        "type": "SPIR-V",
                        "uid": f"{op['name']}_shader"
                    }
                })
                
                # Add weight buffer
                weight_size = (op["kernel_size"][0] * op["kernel_size"][1] * 
                              op["input_shape"][3] * op["output_shape"][3] * 4)
                scenario["resources"].append({
                    "buffer": {
                        "shader_access": "readonly",
                        "size": int(weight_size),
                        "uid": f"{op['name']}_weights"
                    }
                })
                
                # Add output buffer
                output_size = np.prod(op["output_shape"]) * 4
                scenario["resources"].append({
                    "buffer": {
                        "shader_access": "writeonly",
                        "size": int(output_size),
                        "uid": f"{op['name']}_output"
                    }
                })
                
                # Add dispatch command
                scenario["commands"].append({
                    "dispatch_compute": {
                        "bindings": [
                            {"id": 0, "set": 0, "resource_ref": "input_image" if i == 0 else f"{operations[i-1]['name']}_output"},
                            {"id": 1, "set": 0, "resource_ref": f"{op['name']}_weights"},
                            {"id": 2, "set": 0, "resource_ref": f"{op['name']}_output"}
                        ],
                        "rangeND": [op["output_shape"][2], op["output_shape"][1], 1],
                        "shader_ref": f"{op['name']}_shader"
                    }
                })
                
            elif op["type"] == "relu":
                # Add ReLU shader
                scenario["resources"].append({
                    "shader": {
                        "entry": "main",
                        "src": "shaders/relu.spv",
                        "type": "SPIR-V",
                        "uid": f"{op['name']}_shader"
                    }
                })
                
                # ReLU operates in-place
                scenario["commands"].append({
                    "dispatch_compute": {
                        "bindings": [
                            {"id": 0, "set": 0, "resource_ref": f"{operations[i-1]['name']}_output"}
                        ],
                        "rangeND": [np.prod(op["shape"])],
                        "shader_ref": f"{op['name']}_shader"
                    }
                })
        
        # Save scenario
        with open(f"scenarios/style_transfer_{self.model_name}.json", 'w') as f:
            json.dump(scenario, f, indent=2)
        
        print(f"Created scenario: scenarios/style_transfer_{self.model_name}.json")
        
    def run_inference(self):
        """Run style transfer inference"""
        print(f"\nRunning style transfer with {self.model_name}...")
        
        # In a real implementation, we would:
        # 1. Load the actual TFLite model weights
        # 2. Convert them to Vulkan buffers
        # 3. Run the full inference pipeline
        # 4. Post-process the output
        
        # For demo, we'll show the structure
        print("Pipeline stages:")
        print("1. Convolution + Instance Norm + ReLU")
        print("2. Residual blocks (5-9 blocks)")
        print("3. Transposed convolution for upsampling")
        print("4. Final convolution to RGB")
        print("5. Tanh activation for output")
        
    def postprocess_output(self, output_path):
        """Convert output back to image"""
        # Load output tensor
        if os.path.exists(output_path):
            output = np.load(output_path)
            
            # Remove batch dimension
            output = output.squeeze(0)
            
            # Denormalize from [-1, 1] to [0, 255]
            output = (output + 1.0) * 127.5
            output = np.clip(output, 0, 255).astype(np.uint8)
            
            # Save as image
            img = Image.fromarray(output)
            img.save(f"stylized_{self.model_name}.jpg")
            print(f"Saved stylized image: stylized_{self.model_name}.jpg")

def main():
    import argparse
    parser = argparse.ArgumentParser(description="Style Transfer Demo")
    parser.add_argument("--model", default="models/la_muse.tflite", help="Style model path")
    parser.add_argument("--image", default="test_image.jpg", help="Input image path")
    
    args = parser.parse_args()
    
    # Check if model exists
    if not os.path.exists(args.model):
        print(f"Model not found: {args.model}")
        print("Available models:")
        for model in os.listdir("models"):
            if model.endswith(".tflite"):
                print(f"  - models/{model}")
        return
    
    demo = StyleTransferDemo(args.model)
    
    # Create test image if needed
    if not os.path.exists(args.image):
        print("Creating test image...")
        test_img = np.random.rand(256, 256, 3) * 255
        Image.fromarray(test_img.astype(np.uint8)).save(args.image)
    
    # Run demo
    demo.preprocess_image(args.image)
    demo.create_style_transfer_scenario()
    demo.run_inference()
    
    print("\nStyle transfer demo complete!")
    print("Note: This is a demonstration of the pipeline structure.")
    print("Full implementation would require weight extraction from TFLite.")

if __name__ == "__main__":
    main()