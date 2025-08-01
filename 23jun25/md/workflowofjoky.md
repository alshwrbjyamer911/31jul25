### structure of Joky code
---

### 🔧 **Tec Joky Embedded Software Workflow**

| **Type**       | **Step**                      | **Description**                                               |
| -------------- | ----------------------------- | ------------------------------------------------------------- |
| **Start**      | System Init                   | Initialize peripherals, timers, LoRa, and system state        |
| **Foreground** | Timer Interrupt (every 5 sec) | Periodic interrupt for battery monitoring                     |
|                | → Read ADC                    | Read voltage data from ADC pin                                |
|                | → Analyze SoC                 | Estimate State of Charge (SoC) based on ADC reading           |
|                | → Send SoC to RC              | Transmit SoC value to remote controller (e.g., via LoRa/UART) |
| **Background** | Main Loop                     | Runs continuously in the background                           |
|                | → Receive LoRa Cmds           | Listen for incoming commands from the remote controller       |
|                | → Control DC Motors           | Decode command and drive motors accordingly                   |
| **End**        | Loop / End                    | System loops or waits for next interrupt or command           |

---

**notes**

 - ### two channals adc with two analog data from current sensor and Voltage 
    - to estimate soc 
---
 - ### the cmd receied "lora over UART " 
    - "1" for one hit 
    - "2" for continous hitting 
    - "3" for stop motot 
---
 - ### the data sent from **joky** to **RC**
    - It will only a number sent as a string 
    - in **RC** the data sored in an uint8_t arr[2]; 
 ---

  - ### NOTE it may be a version of model a code 
     - may be edited in optimization 