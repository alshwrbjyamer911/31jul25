#!/usr/bin/python3
import json
import serial
import time

# === USER CONFIGURATION ===
json_path = "/home/amer/Work/Elebel/26jun25/code/as32_lora_addresses.json"
baud_rate = 9600
serial_port_path = "/dev/ttyUSB0"  # Only one port used
command_prefix = 0xC0
state_file = "/home/amer/Work/Elebel/26jun25/code/last_id.txt"

# === LOAD CONFIG FILE ===
with open(json_path, "r") as f:
    data = json.load(f)

config = data["config"]
addresses = data["addresses"]

# === GET CONFIG VALUES ===
speed = int(config["speed_register"], 16)
chan = int(config["chan_register"], 16)
option = int(config["option_register"], 16)

# === LOAD OR INIT LAST INDEX ===
def load_last_index():
    try:
        with open(state_file, "r") as f:
            return int(f.read().strip())
    except FileNotFoundError:
        return 0

def save_last_index(idx):
    with open(state_file, "w") as f:
        f.write(str(idx))

# === SEND CONFIG TO CURRENT MODULE ===
def send_config(serial_port, addr, label=""):
    packet = bytes([
        
        command_prefix,
        int(addr["addh"], 16),
        int(addr["addl"], 16),
        speed,
        chan,
        option
    ])
    serial_port.write(packet)
    print(f"[{label}] Sent: {packet.hex(' ')}")
    time.sleep(0.3)

# === MAIN ===
def main():
    index = load_last_index()
    if index >= len(addresses):
        print("✅ All address blocks configured.")
        return

    addr = addresses[index]

    print(f"\n=== Transmitter Phase ===")
    print(f"Configuring TX device: ID {addr['id']} ADDH={addr['addh']} ADDL={addr['addl']}")
    input("Connect TRANSMITTER to USB and press ENTER...")

    with serial.Serial(serial_port_path, baud_rate, timeout=1) as ser:
        send_config(ser, addr, "TX")

    print(f"\n=== Receiver Phase ===")
    print(f"Configuring RX device: ID {addr['id']} ADDH={addr['addh']} ADDL={addr['addl']}")
    input("Now connect RECEIVER to USB and press ENTER...")

    with serial.Serial(serial_port_path, baud_rate, timeout=1) as ser:
        send_config(ser, addr, "RX")

    # Save progress
    save_last_index(index + 1)
    print(f"\n✅ TX and RX configured with same address. Next ID will be {index + 1}.\n")

if __name__ == "__main__":
    main()
    
