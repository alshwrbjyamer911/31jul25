# AS32-TTL-100 Module Configuration Details

The following table describes the configuration parameters for the AS32-TTL-100 LoRa module as specified: `ADDH=0x00`, `ADDL=0x00`, `SPEED=0x1A`, `CHAN=0x17`, `OPTION=0xC0`.

| **Register** | **Value (Hex)** | **Parameter** | **Details** | **Description** |
|--------------|-----------------|---------------|-------------|-----------------|
| **ADDH**     | 0x00            | Module Address High Byte | 8-bit high byte of module address | Sets the high byte of the 16-bit module address to 0x00. Combined with ADDL, the full address is 0x0000 (factory default). Used for point-to-point or broadcast communication to identify the module. |
| **ADDL**     | 0x00            | Module Address Low Byte | 8-bit low byte of module address | Sets the low byte of the 16-bit module address to 0x00. The address 0x0000 allows the module to operate in transparent or point-to-point mode, or as a broadcast receiver if paired with specific settings. |
| **SPEED**    | 0x1A (Binary: 00011010) | UART Parity (Bits [7:6]) | 00: 8N1 | Configures UART to 8 data bits, no parity, 1 stop bit (8N1). This is the default parity setting, ensuring compatibility with standard serial communication. |
| | | UART Baud Rate (Bits [5:3]) | 011: 9600 bps | Sets the UART baud rate to 9600 bps, suitable for most microcontrollers. Supported baud rates range from 1200 to 115200 bps. |
| | | Air Speed (Bits [2:0]) | 010: 2.4 kbps | Sets the wireless air data rate to 2.4 kbps (default). This balances range and data rate. Supported air speeds: 0.3, 1.2, 2.4, 4.8, 9.6, 19.2 kbps. Must match between TX and RX. |
| **CHAN**     | 0x17            | Channel | 23 (433 MHz) | Sets the operating frequency to 433 MHz (calculated as 410 MHz + CHAN * 1 MHz = 410 + 23 = 433 MHz). The module supports 32 channels (410–441 MHz). This is the default frequency, a license-free band in many regions. |
| **OPTION**   | 0xC0 (Binary: 11000000) | FixedTransmitEn (Bit 7) | 1: Point-to-Point | Enables point-to-point transmission mode. Data sent must include the receiver’s address (ADDH, ADDL) and channel (CHAN) as a header (e.g., `[ADDH_RX] [ADDL_RX] [CHAN_RX] [Data]`). |
| | | IOType (Bit 6) | 1: Push-pull/pull-up | Configures TXD and AUX as push-pull outputs and RXD as pull-up input. This ensures robust signal levels for UART communication. Alternative is open-drain/open input (0). |
| | | WakeTime (Bits [5:3]) | 000: 250 ms | Sets the wireless wake-up time to 250 ms (default). For TX, this is the duration of the wake-up code in Wake-Up mode; for RX, it’s the monitoring interval in Power-Saving mode. Options: 250–2000 ms. |
| | | Reserved (Bit 2) | 0 | Reserved bit, set to 0. No functional impact. |
| | | SendPower (Bits [1:0]) | 00: 20 dBm | Sets the transmit power to 20 dBm (100 mW), the maximum for this module. Options: 20 dBm, 17 dBm, 14 dBm, 11 dBm. Higher power increases range but requires stable VCC (≥3.6V). |

## Notes
- **Configuration Command**: To apply this configuration, enter Sleep Mode (MD0=1, MD1=1) and send the command `0xC0 0x00 0x00 0x1A 0x17 0xC0` via UART. The module responds with `OK` (ASCII) on success or `ERROR` on failure.
- **Operation Mode**: This configuration is optimized for point-to-point communication in General Mode (MD0=0, MD1=0) or Wake-Up Mode (MD0=1, MD1=0). For point-to-point, the TX data must include the receiver’s address and channel.
- **Compatibility**: The air speed (2.4 kbps) and baud rate (9600 bps) combination supports transmission of infinite data packets (Table 6-6).
- **Power Supply**: Ensure VCC is 2.5–5.5V, ideally ≥3.6V to maintain 20 dBm TX power. Ripple should be <100 mV, and instantaneous current >200 mA.