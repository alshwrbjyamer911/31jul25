**Key Notes on LoRa AT Command Guide for RYLR896 Module**

1. **Module Compatibility**:
   - The guide applies to **RYLR896** LoRa modules, supporting network architectures like Point-to-Point, Point-to-Multipoint, or Multipoint-to-Multipoint.

2. **Network Configuration**:
   - **NETWORKID**: Modules must share the same NETWORKID (1–15 recommended) **ZERO is not safe** to communicate. Different NETWORKIDs prevent communication.
   - **ADDRESS**: Unique identifier for each module **(0–65535)**. Used to specify the transmitter or receiver.

3. **AT Command Sequence**:
   - **AT+ADDRESS**: Set module address (stored in EEPROM).
   - **AT+NETWORKID**: Set network ID (stored in EEPROM, **avoid 0** as it’s the public LoRa ID).
   - **AT+BAND**: Set RF frequency (e.g. 915 MHz for RYLR89x, **not stored in EEPROM**).
   - **AT+PARAMETER**: Configure RF parameters (Spreading Factor, Bandwidth, Coding Rate, Preamble Length, **not** stored in EEPROM):
     - **Spreading Factor (7–12)**: Higher values improve sensitivity but increase transmission time.
     - **Bandwidth (7.8–500 kHz)**: Lower bandwidth improves sensitivity but extends transmission time.
     - **Coding Rate (1–4)**: 1 is fastest.
     - **Preamble Length (4–7)**: Higher values reduce data loss risk.
     - Recommended settings:
       - **Within 3 km: `AT+PARAMETER=10,7,1,7`**
       - Beyond 3 km: `AT+PARAMETER=12,4,1,7`
   - **AT+SEND**: Send data to a specific address (max **240** bytes, adds 8 bytes overhead).

4. **Key AT Commands**:
   - **AT**: Test module response (`+OK`).
   - **AT+RESET**: Software reset (`+RESET`, `+READY`).
   - **AT+MODE**: Set mode (0: Transmit/Receive, 1: Sleep, **wakes** on RX pin input).
   - **AT+IPR**: Set UART baud rate (300–115200, default 115200, **stored in EEPROM**).
   - **AT+CPIN**: Set 32-character AES128 password for network encryption.**Not stored in EEPROM**
   - **AT+CRFOP**: Set RF output power (0–22 dBm, stored in EEPROM).
   - **AT+VER?**: Query firmware version.
   - **AT+UID?**: Query *12-byte* unique ID.
   - **AT+FACTORY**: Reset to defaults (e.g., BAND: 915 MHz, UART: 115200, Address: 0).

5. **Data Transmission**:
   - **AT+SEND=<Address>,<Payload Length>,<Data>**: Sends data to specified address. Address 0 broadcasts to all (0–65535).
   - **+RCV**: Displays received data with Address, Length, Data, RSSI, and SNR (e.g., `+RCV=50,5,HELLO,-99,40`).

6. **Error Handling**:
   - Common errors include missing enter (`+ERR=1`), invalid command (`+ERR=4`), or payload exceeding 240 bytes (`+ERR=13`).

7. **Important Notes**:
   - Add `\r\n` (enter) to all AT commands.
   - Use `?` to query current settings (e.g., `AT+ADDRESS?`).
   - Wait for `+OK` before sending the next command.
   - Use the LoRa Modem Calculator Tool to estimate transmission time.
   - Non-EEPROM settings (BAND, PARAMETER) must be reset after power cycle.

8. **Manufacturer Contact**:
   - Email: alshwrbjyamer@gmail.com
   - Company: ELEBEL Company

