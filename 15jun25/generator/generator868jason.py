import os
import json

JSON_FILE = "lora_nodes.json"
BAND = "868000000"
CPIN_PASSWORD = "LoRaSecure1234"
NETWORKID_START = 1
NETWORKID_END = 16
MAX_ADDRESS = 65534

def load_existing_nodes():
    if os.path.exists(JSON_FILE):
        with open(JSON_FILE, "r") as f:
            return json.load(f)
    else:
        return []

def get_used_addresses_by_network(nodes):
    used = {}
    for node in nodes:
        net_id = node["network_id"]
        addr = node["address"]
        if net_id not in used:
            used[net_id] = set()
        used[net_id].add(addr)
    return used

def main():
    nodes = load_existing_nodes()
    used_addresses = get_used_addresses_by_network(nodes)
    device_id = max([n["device_id"] for n in nodes], default=0) + 1

    for netid in range(NETWORKID_START, NETWORKID_END + 1):
        used = used_addresses.get(netid, set())
        available = [a for a in range(1, MAX_ADDRESS + 1) if a not in used]

        if not available:
            print(f"All addresses used for NETWORKID={netid}, skipping.")
            continue

        for i in range(0, len(available), 2):  # Pair transmitter & receiver
            if i + 1 >= len(available):
                break
            tx_addr = available[i]
            rx_addr = available[i + 1]

            nodes.append({
                "device_id": device_id,
                "role": "transmitter",
                "network_id": netid,
                "address": tx_addr,
                "password": CPIN_PASSWORD,
                "band": BAND
            })
            device_id += 1

            nodes.append({
                "device_id": device_id,
                "role": "receiver",
                "network_id": netid,
                "address": rx_addr,
                "password": CPIN_PASSWORD,
                "band": BAND
            })
            device_id += 1

            print(f"NETWORKID {netid}: TX={tx_addr}, RX={rx_addr}")

        # Save after each networkid to persist progress
        with open(JSON_FILE, "w") as f:
            json.dump(nodes, f, indent=2)

    print(f"\n✅ All configurations saved to {JSON_FILE}")

if __name__ == "__main__":
    main()
