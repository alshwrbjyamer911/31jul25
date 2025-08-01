import json

# PMR446 frequencies (446.00625 MHz to 446.19375 MHz, 12.5 kHz spacing)
pmr446_frequencies = [446.00625 + (i * 0.0125) for i in range(16)]  # 16 channels

# CTCSS codes (0001–0038, from Appendix 3)
ctcss_codes = [f"{i:04d}" for i in range(1, 39)]  # 0001 to 0038

# CDCSS codes (I codes from Appendix 2, excluding N codes)
cdcss_codes = [
    "023I", "025I", "026I", "031I", "032I", "043I", "047I", "051I", "054I", "065I",
    "071I", "072I", "073I", "074I", "114I", "115I", "116I", "125I", "131I", "132I",
    "134I", "143I", "152I", "155I", "156I", "162I", "165I", "172I", "174I", "205I",
    "223I", "226I", "243I", "244I", "245I", "251I", "261I", "263I", "265I", "271I",
    "306I", "311I", "315I", "331I", "343I", "346I", "351I", "364I", "365I", "371I",
    "411I", "412I", "413I", "423I", "431I", "432I", "445I", "464I", "465I", "466I",
    "503I", "506I", "516I", "532I", "546I", "565I", "606I", "612I", "624I", "627I",
    "631I", "632I", "654I", "662I", "664I", "703I", "712I", "723I", "731I", "732I",
    "734I", "743I", "754I"
]  # 83 codes

# Combine CXCSS codes
cxcss_codes = ["0000"] + ctcss_codes + cdcss_codes  # 1 + 38 + 83 = 122

# Dummy values for unused parameters
DUMMY_FREQ = "400.0000"  # Outside PMR446
DUMMY_CXCSS = "0000"     # No coding

# Generate initialization commands
def generate_initialization():
    return {
        "initialization": {
            "transmitter": [
                "AT+DMOCONNECT\r\n",
                "AT+SETFILTER=0,0,0\r\n",
                "AT+SETTAIL=0\r\n"
            ],
            "receiver": [
                "AT+DMOCONNECT\r\n",
                "AT+DMOSETVOLUME=4\r\n",
                "AT+SETFILTER=0,0,0\r\n"
            ]
        }
    }

# Generate AT+DMOSETGROUP configurations
def generate_dmosetgroup_configs():
    configs = []
    config_id = 1
    gbw = "0"  # 12.5 kHz
    sq = "4"   # Fixed squelch level

    for freq in pmr446_frequencies:
        freq_str = f"{freq:.4f}"  # e.g., 446.0063
        for cxcss in cxcss_codes:
            # Determine type
            if cxcss == "0000":
                cxcss_type = "NONE"
            elif cxcss in ctcss_codes:
                cxcss_type = "CTCSS"
            else:
                cxcss_type = "CDCSS"
            
            # Transmitter command (only TFV and Tx_CXCSS relevant)
            tx_cmd = f"AT+DMOSETGROUP={gbw},{freq_str},{DUMMY_FREQ},{cxcss},{sq},{DUMMY_CXCSS}\r\n"
            # Receiver command (only RFV, Rx_CXCSS, and SQ relevant)
            rx_cmd = f"AT+DMOSETGROUP={gbw},{DUMMY_FREQ},{freq_str},{DUMMY_CXCSS},{sq},{cxcss}\r\n"
            
            configs.append({
                "id": config_id,
                "type": cxcss_type,
                "frequency": freq_str,
                "at_tx_cmd": tx_cmd,
                "at_rx_cmd": rx_cmd
            })
            config_id += 1
    
    return configs

# Main function to generate JSON
def generate_at_commands_json():
    # Generate initialization and configurations
    init_block = generate_initialization()
    configs_block = generate_dmosetgroup_configs()

    # Combine into final JSON structure
    output = {
        **init_block,
        "configurations": configs_block,
        "metadata": {
            "frequency_band": "PMR446 (446.0–446.2 MHz)",
            "total_configurations": len(configs_block),
            "note": "Transmitter only uses TFV and Tx_CXCSS; Receiver only uses RFV, Rx_CXCSS, and SQ. Dummy values (400.0000 MHz, 0000) used for unused parameters. Squelch fixed at 4."
        }
    }

    # Save to JSON file
    with open("sa818s_at_commandsV2.json", "w") as f:
        json.dump(output, f, indent=4)

    print(f"Generated JSON file 'sa818s_at_commandsV2.json' with {len(configs_block)} configurations.")

if __name__ == "__main__":
    generate_at_commands_json()