#!/usr/bin/python3
import json
import os

NODES_FILE = "/home/amer/Work/Elebel/lora_nodes.json"
STATE_FILE = "/home/amer/Work/Elebel/state.json"

def load_nodes():
    if not os.path.exists(NODES_FILE):
        print(f"❌ ERROR: {NODES_FILE} not found.")
        return []
    with open(NODES_FILE, "r") as f:
        return json.load(f)

def load_state():
    if os.path.exists(STATE_FILE):
        with open(STATE_FILE, "r") as f:
            return json.load(f)
    else:
        return {"current_index": 0}

def save_state(state):
    with open(STATE_FILE, "w") as f:
        json.dump(state, f)

def generate_at_commands(device):
    return [
        f"AT+BAND={device['band']}",
        f"AT+NETWORKID={device['network_id']}",
        f"AT+ADDRESS={device['address']}",
        f"AT+CPIN=\"{device['password']}\""
    ]

def print_device_info(label, device):
    print(f"\n🔹 {label} Info:")
    print(json.dumps(device, indent=2))

    print(f"\n🛠️ {label} AT Commands:")
    commands = generate_at_commands(device)
    for cmd in commands:
        print(cmd)

def main():
    nodes = load_nodes()
    state = load_state()
    index = state["current_index"]

    if index + 1 >= len(nodes):
        print("✅ All device pairs have been processed.")
        return

    tx = nodes[index]
    rx = nodes[index + 1]

    print("\n📡 Next Device Pair:")
    print("-" * 40)

    print_device_info("Transmitter", tx)
    print_device_info("Receiver", rx)

    print("-" * 40)

    # Save state
    state["current_index"] = index + 2
    save_state(state)

if __name__ == "__main__":
    main()
