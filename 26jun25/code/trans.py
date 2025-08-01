#!/usr/bin/python3
import serial
import time

# === CONFIG ===
serial_port = "/dev/ttyUSB0"
baud_rate = 115200  # Set to match your device
timeout = 1  # seconds

def main():
    try:
        with serial.Serial(serial_port, baud_rate, timeout=timeout) as ser:
            print(f"✅ Connected to {serial_port} at {baud_rate} baud.")
            print("🔁 Type and press ENTER to send. Press Ctrl+C to quit.\n")

            while True:
                # Get user input from terminal
                user_input = input(">>> ")

                if not user_input:
                    continue

                # Send user input as bytes (with newline if needed)
                ser.write(user_input.encode())

                # Wait for device to respond
                time.sleep(0.2)
                response = ser.read_all()

                # Show result
                if response:
                    try:
                        text = response.decode('utf-8')
                    except UnicodeDecodeError:
                        text = response.hex(' ')
                    print(f"<<< {text}")
                else:
                    print("<<< (no response)")

    except KeyboardInterrupt:
        print("\n🚪 Exiting.")
    except Exception as e:
        print(f"❌ Error: {e}")

if __name__ == "__main__":
    main()
