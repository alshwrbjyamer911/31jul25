# 📡 Embedded Voice & LoRa Communication Project Timeline

**Role**: Embedded Software Team Leader  
**Company**: Elebel  
**Target MCU**: STM32F405RGT6  
**Modules Used**:
- **LoRa**: RYLR898
- **Voice**: SA818SU Audio Module

**Goal**:  
Send **commands via LoRa** and **voice via walkie-talkie module** from one STM32F405 to another.

---

## 🕒 Work Schedule
- **Days/Week**: 5  
- **Hours/Day**: 8  
- **Total**: 40 hours/week  

---

## 🔧 Project Duration & Phases
**Estimated Duration**: 6–7 Weeks

---

## ✅ Week 1 – Project Planning & Initial Setup

**Tasks**:
- Requirements analysis and protocol planning.
- Study RYLR898 and SA818SU datasheets.
- Setup STM32 project using STM32CubeMX (HAL/LL drivers).
- Initialize UARTs for LoRa and Audio modules.
- Prepare development tools (e.g., serial terminal, logic analyzer, test audio).

**Deliverables**:
- STM32 environment ready.
- Basic UART communication established.

---

## ✅ Week 2 – LoRa (RYLR898) Communication

**Tasks**:
- Implement AT command-based UART communication with RYLR898.
- Establish two-way communication between two STM32 boards.
- Add error handling and acknowledgment protocol.
- Design simple command structure (JSON or byte packet).

**Deliverables**:
- Reliable LoRa command exchange working.

---

## ✅ Week 3 – SA818SU Voice Module Integration

**Tasks**:
- Understand and control TX/RX modes using GPIO.
- Connect headset/mic and test with another SA818SU.
- Implement GPIO-based PTT (push-to-talk) control.
- Verify audio transmission quality.

**Deliverables**:
- Full-duplex voice transmission working under STM32 control.

---

## ✅ Week 4 – Command Protocol Implementation

**Tasks**:
- Design command structure (control, status, request types).
- Implement command parser and dispatcher on STM32.
- Add retries, CRC, and basic protocol features.
- Create abstraction layer for easier extension/testing.

**Deliverables**:
- Fully working structured command protocol.

---

## ✅ Week 5 – System Integration

**Tasks**:
- Combine LoRa and voice functionality.
- Implement task switching/state machine for both modules.
- Add indicators for system status (LEDs, serial debug).
- Ensure coordination between command and voice modes.

**Deliverables**:
- Integrated system with command + voice capabilities.

---

## ✅ Week 6 – Testing, Optimization, Documentation

**Tasks**:
- Field test communication range and quality.
- Add UART DMA or IRQ to optimize performance.
- Add fault recovery and watchdogs.
- Document code structure, usage, and test cases.

**Deliverables**:
- Fully validated and documented firmware.

---

## 🛠️ Week 7 (Optional) – Future-Proofing

**Tasks**:
- Add command-line interface (CLI) for debugging.
- Add RTOS (FreeRTOS) for modular task handling.
- Add OTA or debug bootloader (if needed).

**Deliverables**:
- Production-ready system with advanced features.

---

## 📊 Summary Table

| Week | Tasks | Deliverables |
|------|-------|--------------|
| 1 | Planning, setup, UART init | Environment & drivers ready |
| 2 | LoRa module | Basic LoRa comm |
| 3 | Voice module | SA818 voice works |
| 4 | Protocol design | Structured LoRa commands |
| 5 | Integration | LoRa + voice coordination |
| 6 | Testing, docs | Final testable product |
| 7 | (Optional) Additions | CLI, RTOS, UI |

---

## 📎 Notes
- Use UART-based AT commands for RYLR898 and SA818SU.
- Use GPIOs for TX/RX (PTT) control for SA818SU.
- Start simple, then refactor and add abstraction/RTOS if time allows.

---
