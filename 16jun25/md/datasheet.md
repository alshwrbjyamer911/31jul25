**SA818S communication protocol summary**, now clearly showing which settings are **optional**, as requested:

---

## 📡 SA818S Serial Protocol (Simplified & Labeled)

### ⚙️ Serial Port Settings

| Setting     | Value                                |
| ----------- | ------------------------------------ |
| Baud Rate   | `9600 bps`                           |
| Data Bits   | `8`                                  |
| Stop Bit    | `1`                                  |
| Parity      | `None`                               |
| Line Ending | `\r\n` (Carriage Return + Line Feed) |

---

## 🔧 Command Reference

---

### 1. ✅ `AT+DMOCONNECT`

**Required.**
🔹 Purpose: Handshake to confirm communication.
🔹 Response: `+DMOCONNECT:0`
📌 Send after power-on or reset.

---

### 2. ✅ `AT+DMOSETGROUP=GBW, TFV, RFV, Tx_CXCSS, SQ, Rx_CXCSS`

**Required.**
🔹 Purpose: Set radio parameters.

| Parameter  | Description                                                       | Required  |
| ---------- | ----------------------------------------------------------------- | --------  |
| `GBW`      | Bandwidth: `0` = 12.5 kHz, `1` = 25 kHz                           | ✅ Yes    |
| `TFV`      | TX Frequency: `446-446.2 MHz`                                     | ✅ Yes    |
| `RFV`      | RX Frequency: same range                                          | ✅ Yes    |
| `Tx_CXCSS` | TX Tone: `0000` = none, or CTCSS (0001–0038), CDCSS (e.g. `223I`) | ✅ Yes    |
| `SQ`       | Squelch Level: `0–8` (0 = open squelch)                           | ✅ Yes    |
| `Rx_CXCSS` | RX Tone: same format as `Tx_CXCSS`                                | ✅ Yes    |



✅ Example:

```text
AT+DMOSETGROUP=0,446.0250,446.0250,0013,4,0013\r\n
```

---

### 3. 🟡 `AT+DMOSETVOLUME=X`

**Optional.**
🔹 Purpose: Set volume level (1–8).
🔹 Default: Unspecified in datasheet.

✅ Example:

```text
AT+DMOSETVOLUME=4\r\n
```

---

### 4. 🟡 `AT+SETFILTER=PRE,HPF,LPF`

**Optional.**
🔹 Purpose: Enable/disable audio filters.

| Param | Description                        | Value    |
| ----- | ---------------------------------- | -------- |
| `PRE` | Pre-emphasis (0 = ON, 1 = OFF)     | Optional |
| `HPF` | High-pass filter (0 = ON, 1 = OFF) | Optional |
| `LPF` | Low-pass filter (0 = ON, 1 = OFF)  | Optional |


---
✅ Example (enable all filters):

```text
AT+SETFILTER=0,0,0\r\n
```

---

### 5. 🟡 `AT+SETTAIL=X`

**Optional.**
🔹 Purpose: Enable/disable end-of-transmission tail tone.
🔹 Values: `0` = Off, `1` = On

✅ Example:

```text
AT+SETTAIL=0\r\n
```

---

### 6. 🟡 `AT+DMOREADGROUP`

**Optional.**
🔹 Purpose: Read current radio configuration.

✅ Response:

```text
+DMOREADGROUP=GBW,TFV,RFV,Tx_CXCSS,SQ,Rx_CXCSS
```

---

### 7. 🟡 `AT+VERSION`

**Optional.**
🔹 Purpose: Read firmware version.
✅ Response:

```text
+VERSION:SA818_V5.0
```

---

### 8. 🟡 `RSSI?`

**Optional.**
🔹 Purpose: Read signal strength.
✅ Response:

```text
RSSI:010
```

---

### 9. 🟡 `S+<frequency>`

**Optional.**
🔹 Purpose: Frequency scan (detect signal presence).
✅ Response:

* `S=0` → signal detected
* `S=1` → no signal

✅ Example:

```text
S+446.0250\r\n
```

---

## ✅ Example Sequences

### 🔊 Transmitter

```text
AT+DMOCONNECT\r\n
AT+SETFILTER=0,0,0\r\n         ; optional
AT+SETTAIL=0\r\n               ; optional
AT+DMOSETGROUP=0,446.0250,400.0000,0012,4,0000\r\n
```

### 🔈 Receiver

```text
AT+DMOCONNECT\r\n
AT+DMOSETVOLUME=4\r\n          ; optional
AT+SETFILTER=0,0,0\r\n         ; optional
AT+DMOSETGROUP=0,400.0000,446.0250,0000,4,0012\r\n
```

---
### NOTE 📌 📌 📌 📌 📌 📌 📌 📌 
 This module dosent have EEPROM 
 then all cmd will initalized in init function 