In **Dubai (UAE)**, the **legal LoRa frequency band** is regulated by the **Telecommunications and Digital Government Regulatory Authority (TDRA)**.

---

### ✅ Allowed LoRa BAND in Dubai:

**`868 MHz`**

* Specifically, **863–870 MHz** is the **ISM band** approved for LoRa use in the UAE.
* The **`433 MHz` band is not officially permitted** for LoRa applications in UAE.

> 🔴 **Do NOT use `433 MHz`** in Dubai — it may be **illegal** or interfere with other services.

---

### 🔹 So, updated values to use in Dubai:

| Parameter   | Suggested Value | Reason                    |
| ----------- | --------------- | ------------------------- |
| `BAND`      | `868`           | Legal and standard in UAE |
| `NETWORKID` | `12`            | Rare, non-default value   |
| `ADDRESS`   | `in its range`  | High, uncommon address    |

---

### ✅ AT Commands Example for RYLR896:

```plaintext
AT+BAND=868000000
AT+NETWORKID=12
AT+ADDRESS=<range>
```

* Make sure to set the same `NETWORKID` on all devices in the same network.
* Each device should have a **unique** `ADDRESS`.

To **initialize the RYLR896 LoRa module** properly, you only need a few essential **AT commands** to set up the module for communication. Below is a minimal and **correct initialization sequence** that ensures the module is ready to send and receive data.

---

## ✅ Necessary AT Commands to Initialize RYLR896

### 🔹 1. **Reset the Module** (Optional but recommended)

```plaintext
AT+RESET
```

* Reboots the module.
* Wait \~1 second after this before sending the next command.

---

### 🔹 2. **Set the BAND** (Frequency in Hz)

For **Dubai**, use `868 MHz`:

```plaintext
AT+BAND=868000000
```

> ⚠️ This sets the operating frequency. Must match on all devices.

---

### 🔹 3. **Set the NETWORKID**

Example:

```plaintext
AT+NETWORKID=57342
```

> This groups devices logically — must be the same across your devices.

---

### 🔹 4. **Set the DEVICE ADDRESS**

Each device must have a unique address:

```plaintext
AT+ADDRESS=45963
```

> For another device, use a different address like `45964`.

---

### 🔹 5. **Set UART Baud Rate** (Optional; default is `115200`)

```plaintext
AT+IPR=115200
```

> Only needed if you're changing the baud rate.

---

### 🔹 6. **Set Spreading Factor, Bandwidth, and Coding Rate** (Optional but recommended for tuning)

```plaintext
AT+PARAMETER=12,7,1,4
```

**Format:** `AT+PARAMETER=SF,BW,CR,PreambleLen`

| Field                 | Value | Meaning                       |
| --------------------- | ----- | ----------------------------- |
| SF (Spreading Factor) | 12    | Higher range, lower data rate |
| BW (Bandwidth)        | 7     | 125 kHz                       |
| CR (Coding Rate)      | 1     | 4/5                           |
| PreambleLen           | 4     | Default preamble              |

---

### 🔹 7. **Enable or Disable Acknowledgement (ACK)**

If you want the module to **expect ACKs** (reliable delivery):

```plaintext
AT+CRFOP=1
```

To **disable ACK**:

```plaintext
AT+CRFOP=0
```

---

## ✅ Example Full Initialization Script:

```plaintext
AT+RESET
<wait 1 sec>
AT+BAND=868000000
AT+NETWORKID=12
AT+ADDRESS=45963
AT+PARAMETER=12,7,1,4
AT+CRFOP=1
```

---

## ✅ Check Module is Ready

You can send:

```plaintext
AT
```

And you should get:

```plaintext
OK
```

---

## ✅ Sending a Message

To send a message to another device:

```plaintext
AT+SEND=45964,5,HELLO
```

> Format: `AT+SEND=<address>,<length>,<data>`

---


