#!/usr/bin/python3
import re
import sys

def process_rgb565_array(header_path):
    # Read file
    with open(header_path, "r") as f:
        content = f.read()

    # Regex to match all 0xHHHH values
    hex_values = re.findall(r"0x[0-9A-Fa-f]{4}", content)

    if not hex_values:
        print("No 0xHHHH values found in file.")
        return

    # Convert and update
    updated_values = []
    for val in hex_values:
        num = int(val, 16)
        if num < 0x00FF:
            updated_values.append("0x0000")
        else:
            updated_values.append("0xFFFF")

    # Replace values back in the file
    def replacement(match_iter=iter(updated_values)):
        return next(match_iter)

    new_content = re.sub(r"0x[0-9A-Fa-f]{4}", lambda _: replacement(), content)

    # Write updated file
    with open(header_path, "w") as f:
        f.write(new_content)

    print(f"Updated {header_path} successfully.")

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python update_array.py <file.h>")
        sys.exit(1)

    process_rgb565_array(sys.argv[1])

