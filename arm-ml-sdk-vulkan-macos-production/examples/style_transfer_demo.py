#!/usr/bin/env python3
"""
Style Transfer Demo using ARM ML SDK
"""

import sys
import os
sys.path.append(os.path.join(os.path.dirname(__file__), '..', 'tools'))

from run_ml_inference import MLInferenceRunner
import numpy as np
from PIL import Image

def preprocess_image(image_path, target_size=(256, 256)):
    """Preprocess image for style transfer"""
    img = Image.open(image_path).convert('RGB')
    img = img.resize(target_size, Image.LANCZOS)
    
    # Convert to numpy array and normalize
    img_array = np.array(img, dtype=np.float32)
    img_array = img_array / 255.0
    img_array = np.expand_dims(img_array, axis=0)  # Add batch dimension
    
    return img_array

def postprocess_output(output_array, output_path):
    """Convert model output back to image"""
    # Remove batch dimension and denormalize
    output = output_array.squeeze(0)
    output = (output * 255.0).clip(0, 255).astype(np.uint8)
    
    # Save image
    img = Image.fromarray(output)
    img.save(output_path)
    print(f"Stylized image saved to: {output_path}")

def main():
    if len(sys.argv) < 3:
        print("Usage: python style_transfer_demo.py <model.tflite> <input_image>")
        print("\nAvailable models:")
        print("  - models/la_muse.tflite")
        print("  - models/udnie.tflite")
        print("  - models/wave_crop.tflite")
        return
    
    model_path = sys.argv[1]
    image_path = sys.argv[2]
    
    print(f"=== Style Transfer Demo ===")
    print(f"Model: {model_path}")
    print(f"Input: {image_path}")
    
    # Initialize runner
    runner = MLInferenceRunner()
    
    # Preprocess image
    input_data = preprocess_image(image_path)
    print(f"Input shape: {input_data.shape}")
    
    # Run inference
    success = runner.run_inference(model_path, input_data, "output")
    
    if success:
        print("\nStyle transfer completed successfully!")
        # In a real implementation, we would load and postprocess the output
    else:
        print("\nStyle transfer failed!")

if __name__ == "__main__":
    main()
