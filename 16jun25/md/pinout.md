![Alt text](image.png)
Here is an **organized and detailed pinout description** for the **SA818S embedded walkie-talkie module**, based on your provided table:

---

## 📌 SA818S Pin Description (18 Pins)

| **Pin No.** | **Pin Name** | **Function** | **Detailed Description**                                                                                                                                                                             |
| ----------- | ------------ | ------------ | ---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| 1           | **Audio ON** | Output       | Controls external audio amplifier. Outputs **low level** when module is active (turns amplifier **ON**) and **high level** when idle (amplifier **OFF**).                                            |
| 2           | **NC**       | —            | Not connected (internally unconnected).                                                                                                                                                              |
| 3           | **AF\_OUT**  | Output       | Audio output pin. Connect to speaker or amplifier input.                                                                                                                                             |
| 4           | **NC**       | —            | Not connected.                                                                                                                                                                                       |
| 5           | **PTT**      | Input        | Push-to-Talk control: <br>• `0` (Low) = **Transmit mode (TX)** <br>• `1` (High) = **Receive mode (RX)**                                                                                              |
| 6           | **PD**       | Input        | Power Down control: <br>• `0` = Sleep mode <br>• `1` = Normal operation                                                                                                                              |
| 7           | **H/L**      | Input        | High/Low output power control: <br>• **Leave open** = **High Power** (default) <br>• **Pull Low** = **Low Power** (e.g., PMR446 legal 500 mW) <br>⚠️ Do **NOT** connect to VDD or high logic levels. |
| 8           | **VBAT**     | Power Input  | Connect to **positive power supply** (e.g., 3.7–4.2 V Li-ion battery).                                                                                                                               |
| 9           | **GND**      | Ground       | Connect to ground.                                                                                                                                                                                   |
| 10          | **GND**      | Ground       | Additional ground pin.                                                                                                                                                                               |
| 11          | **NC**       | —            | Not connected.                                                                                                                                                                                       |
| 12          | **ANT**      | RF I/O       | Connect a **50-ohm antenna** (e.g., whip, SMA). Critical for operation.                                                                                                                              |
| 13, 14, 15  | **NC**       | —            | Not connected.                                                                                                                                                                                       |
| 16          | **RXD**      | Input        | Serial receive pin (connect to external TX). <br>**Note**: Before entering sleep mode, pull this **LOW** to avoid current leakage or wakeup issues.                                                  |
| 17          | **TXD**      | Output       | Serial transmit pin (connect to external RX).                                                                                                                                                        |
| 18          | **MIC\_IN**  | Input        | Microphone or line-in input. Connect electret mic or audio source.                                                                                                                                   |

---

## ⚠️ Important Usage Notes

* **PTT** (`Pin 5`): Controls transmit/receive state. Keep it LOW for TX, HIGH for RX. For fixed transmitter/receiver modules, tie this pin to GND (TX) or VCC (RX).
* **H/L** (`Pin 7`): Pull LOW for **low-power** transmission (complies with PMR446 500 mW limit).
* **PD** (`Pin 6`): Pull HIGH for normal use. Pull LOW to power down the module.
* **RXD (Pin 16)**: Must be pulled LOW before sleep mode to avoid issues on wake-up.
* **Audio ON (Pin 1)**: Use to switch an external audio amplifier depending on module activity.

---
