#!/usr/bin/python3
import serial
import time

# === USER CONFIGURATION ===
serial_port = "/dev/ttyUSB0"
baud_rate = 9600

def read_module_config():
    try:
        with serial.Serial(serial_port, baud_rate, timeout=1) as ser:
            # Send 0xC1 0xC1 0xC1
            cmd = bytes([0xC1, 0xC1, 0xC1])
            ser.write(cmd)
            print(f"Sent: {cmd.hex(' ')}")

            # Wait and read 6-byte response
            time.sleep(0.3)
            response = ser.read(6)

            if len(response) == 6 and response[0] == 0xC0:
                print(f"✅ Config Response: {response.hex(' ')}")
                print("Parsed:")
                print(f"  ADDH   = 0x{response[1]:02X}")
                print(f"  ADDL   = 0x{response[2]:02X}")
                print(f"  SPEED  = 0x{response[3]:02X}")
                print(f"  CHAN   = 0x{response[4]:02X}")
                print(f"  OPTION = 0x{response[5]:02X}")
            else:
                print("❌ Invalid or no response received.")
    except Exception as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    read_module_config()
