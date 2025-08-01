#!/usr/bin/python3
import serial
import time

# === CONFIGURATION ===
serial_port = "/dev/ttyACM0"
baud_rate = 115200
timeout = 1  # seconds

def main():
    try:
        with serial.Serial(serial_port, baud_rate, timeout=timeout) as ser:
            print(f"📡 Listening on {serial_port} at {baud_rate} baud...")
            print("🕰 Waiting for data...\n(Press Ctrl+C to exit)")

            while True:
                data = ser.read_all()

                if data:
                    try:
                        text = data.decode('utf-8')
                        print(f"<<< {text}")
                    except UnicodeDecodeError:
                        print(f"<<< [binary] {data.hex(' ')}")

                time.sleep(0.1)

    except KeyboardInterrupt:
        print("\n🚪 Exiting receiver.")
    except Exception as e:
        print(f"❌ Error: {e}")

if __name__ == "__main__":
    main()
