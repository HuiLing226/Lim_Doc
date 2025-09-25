# Dual-Core STM32 Project Documentation
**Project**: Real-Time Bird Sound Detection (Simulation with Button & LEDs)
The goal was to use STM32’s **dual-core architecture (Cortex-M7 + Cortex-M4)** with **HSEM (Hardware Semaphores)** to coordinate tasks:
- **M4 core**: Simulates **Bird Activity Detection (BAD)** by monitoring a **button press**.
- **M7 core**: Identifies the **bird species** (simulated) and provides feedback using LEDs.

##This setup is a simplified demonstration of real-time bird sound detection, where:
- Button press = detected bird activity.
- M7 response = species identification (LED on + message).
---
## 1. Concept of HSEM
- Hardware Semaphore (HSEM) is a hardware unit inside STM32H7 dual-core devices.
- It allows synchronization between M7 and M4 without memory corruption.
- Works like a lock system:
  - Core A **locks** (take semaphore) → Core B **waits**.
  - Core A **releases** → Core B can **proceed**.
I found the tutorial on [YouTube video](https://www.youtube.com/watch?v=QzICJz-xRzk&t=233s)

--- 
## 2. System design
### M7
- At startup: Print `M7 Ready`.
- Red LED on (means no bird)
- Send signal to M4 to start.
- Enter loop:
  - Wait for signal (HSEM release).
  - Turn the **Red LED off** and **Green LED ON**.
  - Print  `Got bird` (simulated species detected).

### M4
- Continuously check Button.
  - If button not pressed(no bird, Red LED remains on, because M7 not receive the signal to proceed) → continue to check the state.
  - If button pressed(detected bird) → Release HSEM lock to M7.

### Issue Encountered:
- M7 could not be kept in idle state while waiting for M4 → caused conflicts.
- Board sometimes became undetectable (STM32 target not found, while the ST-link debug is connected) as shown below.<img width="1491" height="858" alt="image" src="https://github.com/user-attachments/assets/72f33ca3-d717-4869-a704-583cdc49cc15" /><img width="567" height="332" alt="image" src="https://github.com/user-attachments/assets/ae125cd3-1ac2-4cee-ab28-d4a2240d1012" />

### Recovery required:
  - Set BOOT0 = HIGH (boot in System Memory / ST Bootloader) → Forces the MCU to **boot from system memory (ST’s built-in bootloader)** instead of your Flash..
  - Erase Flash memory to clear faulty firmware.
  - Re-flash a working project.

!! This shows a risk of putting M7 into deep idle while M4 still active.


