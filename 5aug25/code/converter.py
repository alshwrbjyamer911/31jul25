#!/usr/bin/python3
import sys
import os
from PIL import Image

def rgb_to_rgb565(r, g, b):
    """Convert 8-bit R,G,B to 16-bit RGB565"""
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)

def image_to_rgb565(image_path, size_arg):
    # Check if 'x' (color) or 'X' (bw)
    if 'x' in size_arg:
        color_mode = 'color'
        w_str, h_str = size_arg.split('x')
    elif 'X' in size_arg:
        color_mode = 'bw'
        w_str, h_str = size_arg.split('X')
    else:
        raise ValueError("Size must contain 'x' (color) or 'X' (bw)")

    width, height = int(w_str), int(h_str)

    # Open and resize image
    img = Image.open(image_path)
    img = img.resize((width, height), Image.LANCZOS)

    # If black and white, convert first
    if color_mode == 'bw':
        img = img.convert("L").convert("RGB")  # grayscale then back to RGB
    else:
        img = img.convert("RGB")

    # Process pixels
    rgb565_data = []
    for y in range(height):
        for x in range(width):
            r, g, b = img.getpixel((x, y))
            pixel565 = rgb_to_rgb565(r, g, b)
            rgb565_data.append(pixel565)

    return rgb565_data, width, height

def save_as_c_array(data, width, height, var_name="image_data"):
    lines = []
    lines.append(f"const uint16_t {var_name}[{width*height}] = {{")
    # Format as hex values
    for i in range(0, len(data), 12):
        chunk = data[i:i+12]
        hex_values = ", ".join(f"0x{val:04X}" for val in chunk)
        lines.append("    " + hex_values + ",")
    lines.append("};")
    return "\n".join(lines)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python convert.py input_image WIDTHxHEIGHT(or WIDTHXHEIGHT)")
        sys.exit(1)

    image_path = sys.argv[1]
    size_arg = sys.argv[2]

    # Get base name (without extension)
    base_name = os.path.splitext(os.path.basename(image_path))[0]

    data, w, h = image_to_rgb565(image_path, size_arg)
    c_array_str = save_as_c_array(data, w, h, var_name=base_name)

    # Save to .h file
    header_file = f"{base_name}.h"
    with open(header_file, "w") as f:
        f.write(c_array_str + "\n")

    print(f"Header file '{header_file}' generated successfully.")
