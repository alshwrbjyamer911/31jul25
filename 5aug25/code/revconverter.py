#!/usr/bin/env python3
import re
import sys
from PIL import Image

def rgb565_to_rgb888(value):
    """Convert RGB565 (16-bit) to RGB888 (24-bit)"""
    r = ((value >> 11) & 0x1F) << 3
    g = ((value >> 5) & 0x3F) << 2
    b = (value & 0x1F) << 3
    return (r, g, b)

def extract_array_from_header(header_file):
    """Extract uint16_t array values from a .h file"""
    with open(header_file, 'r') as f:
        content = f.read()
    
    # Match array contents between braces { ... }
    match = re.search(r'\{([^}]*)\}', content, re.S)
    if not match:
        raise ValueError("No array found in the header file.")
    
    array_text = match.group(1)
    # Extract all hex or decimal numbers
    values = re.findall(r'0x[0-9A-Fa-f]+|\d+', array_text)
    return [int(v, 0) for v in values]

def main(header_file, width, height, output_file):
    data = extract_array_from_header(header_file)
    
    if len(data) != width * height:
        print(f"Warning: data size {len(data)} does not match {width}x{height} ({width*height}).")

    img = Image.new('RGB', (width, height))
    pixels = img.load()
    
    for y in range(height):
        for x in range(width):
            idx = y * width + x
            if idx < len(data):
                rgb = rgb565_to_rgb888(data[idx])
                pixels[x, y] = rgb

    img.save(output_file)
    print(f"Image saved as {output_file}")

if __name__ == "__main__":
    if len(sys.argv) != 5:
        print(f"Usage: {sys.argv[0]} <input.h> <width> <height> <output.png>")
        sys.exit(1)
    main(sys.argv[1], int(sys.argv[2]), int(sys.argv[3]), sys.argv[4])

