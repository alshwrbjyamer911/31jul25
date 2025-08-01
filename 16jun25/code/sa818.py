#! /usr/bin/python3
import json
import os

# /home/amer/Work/Elebel/16jun25/sa818s_at_commandsV2.json
INPUT_JSON = "/home/amer/Work/Elebel/16jun25/sa818s_at_commandsV2.json"
STATE_JSON = "/home/amer/Work/Elebel/16jun25/state.json"

# Total number of configurations (from previous script)
TOTAL_CONFIGS = 1952

def load_json_data():
    """Load the sa818s_at_commands.json file."""
    try:
        with open(INPUT_JSON, "r") as f:
            return json.load(f)
    except FileNotFoundError:
        print(f"Error: {INPUT_JSON} not found. Please generate it first.")
        exit(1)
    except json.JSONDecodeError:
        print(f"Error: {INPUT_JSON} is invalid JSON.")
        exit(1)

def load_state():
    """Load the last configuration ID from state.json, or return 0 if not found."""
    try:
        with open(STATE_JSON, "r") as f:
            state = json.load(f)
            return state.get("last_config_id", 0)
    except (FileNotFoundError, json.JSONDecodeError):
        return 0

def save_state(config_id):
    """Save the current configuration ID to state.json."""
    with open(STATE_JSON, "w") as f:
        json.dump({"last_config_id": config_id}, f, indent=4)

def get_next_config_id(last_id):
    """Get the next configuration ID, cycling back to 1 if needed."""
    next_id = last_id + 1
    if next_id > TOTAL_CONFIGS:
        next_id = 1
    return next_id

def print_commands(data, config_id):
    """Print initialization and configuration commands for the given ID."""
    # Get initialization commands
    init = data.get("initialization", {})
    tx_init = init.get("transmitter", [])
    rx_init = init.get("receiver", [])

    # Get configuration
    configs = data.get("configurations", [])
    config = next((c for c in configs if c["id"] == config_id), None)
    if not config:
        print(f"Error: Configuration ID {config_id} not found.")
        return

    # Print initialization commands
    print("\n=== Initialization Commands ===")
    print("Transmitter:")
    for cmd in tx_init:
        print(f"  {cmd.strip()}")
    print("Receiver:")
    for cmd in rx_init:
        print(f"  {cmd.strip()}")

    # Print configuration commands
    print("\n=== Configuration Commands ===")
    print(f"ID: {config['id']}")
    print(f"Type: {config['type']}")
    print(f"Frequency: {config['frequency']} MHz")
    print(f"Transmitter Command: {config['at_tx_cmd'].strip()}")
    print(f"Receiver Command: {config['at_rx_cmd'].strip()}")

def main():
    # Load JSON data
    data = load_json_data()

    # Load last configuration ID
    last_id = load_state()
    config_id = get_next_config_id(last_id)

    # Print commands
    print_commands(data, config_id)

    # Save new state
    save_state(config_id)
    print(f"\nState saved: Next run will use configuration ID {get_next_config_id(config_id)}")

if __name__ == "__main__":
    main()