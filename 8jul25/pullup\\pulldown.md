
### 📌 Should I use **Pull-up** or **Pull-down**?

✅ **It depends on the nature of the signal you expect on the pin**:

| **Switch Wiring / Signal Behavior**                   | **GPIO Configuration** |
| ----------------------------------------------------- | ---------------------- |
| Switch connects to **GND** when pressed (active low)  | **Pull-up**            |
| Switch connects to **VCC** when pressed (active high) | **Pull-down**          |

### Example:

* If you have a **button between GPIO and GND**, use:

  * **GPIO: Input with Pull-up**
  * EXTI triggers on **falling edge** when button is pressed.

* If you have a **button between GPIO and VCC**, use:

  * **GPIO: Input with Pull-down**
  * EXTI triggers on **rising edge** when button is pressed.

---

### ⚡ How Pull-up / Pull-down Impacts EXTI:

1. **Prevents Floating Inputs:**

   * Without pull-up/pull-down, the pin is **floating** when unconnected or the button is unpressed → random EXTI triggers (false interrupts).

2. **Defines Idle State:**

   * Pull-up → Pin is normally **high**.
   * Pull-down → Pin is normally **low**.

3. **Affects Edge Selection:**

   * You choose **rising** or **falling** edge in EXTI depending on the idle state:

     * Pull-up → use **falling edge**.
     * Pull-down → use **rising edge**.

---

### 🚦 Practical Rule:

* If you **don’t have external resistors**, enable the **internal pull-up or pull-down** in CubeMX (in GPIO settings).
* If you **do have external resistors**, disable the internal pull resistors.

---

✅ **Example CubeMX Setup for Button on PC13:**

| Setting                | Value                          |
| ---------------------- | ------------------------------ |
| GPIO Mode              | **GPIO\_EXTI13**               |
| GPIO Pull-up/Pull-down | **Pull-up** (if button to GND) |
| EXTI Trigger           | **Falling edge**               |

---

