# Chapter 0: Introduction — Arduino Portenta H7

The **Arduino Portenta H7** is a high-performance development board designed for **AI, IoT, and edge computing** applications.  

Its main processor is the **dual-core STM32H747**, which includes:  
- **Cortex® M7** running at **480 MHz**  
- **Cortex® M4** running at **240 MHz**  

The two cores communicate via a **Remote Procedure Call (RPC)** mechanism, which allows one core to call functions on the other seamlessly. Both processors share all in-chip peripherals and can run independently or cooperatively.

---

## Key Features
- Designed for **AI, IoT, edge computing**  
- Compatible with both **Arduino IDE** and **STM32CubeIDE**

---

## Why Use Portenta H7 for This Project?
- Supports **AI** via **STM32 AI Developer Cloud**  
- High performance for **real-time tasks** (e.g., bird sound detection)  
- **Industrial-grade reliability** for robust deployment  

---

## Pinout Configuration
The full pinout diagram of the Arduino Portenta H7 can be found here:  

[📄 View Pinout PDF](https://content.arduino.cc/assets/Pinout-PortentaH7_latest.pdf)  


---

# Chapter 1: Installation

In this chapter, we will install and set up the required software to work with the Arduino Portenta H7.  
We will start with the **Arduino IDE** for quick testing, and then move to **STM32CubeIDE** for more advanced development.

---

## 1.1 Arduino IDE Setup

The **Arduino IDE** is the easiest way to start programming the Portenta H7.  
It allows you to quickly upload code and verify the board is functioning.

### Steps:
1. Download the **Arduino IDE** from the official website:  
   👉 [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)

2. Install the IDE and launch it.

3. Go to **Tools > Board > Board Manager**.  
   - Search for **Arduino Mbed OS Boards**.  
   - Install the package that includes **Portenta H7**.

4. Connect your Portenta H7 via **USB-C cable**.

5. Select your board and port:  
   - **Tools > Board > Arduino Portenta H7**  
   - **Tools > Port > [Select the correct COM/tty port]**

6. Upload the **Blink** example to test the board:  
   - Go to **File > Examples > Basics > Blink**  
   - Modify the LED pin if needed (use `LEDR`, `LEDG`, `LEDB`)  
   - Click **Upload**

---

## 1.2 STM32CubeIDE Setup

The **STM32CubeIDE** provides a professional development environment for the Portenta H7, offering full access to the STM32H747 microcontroller.

### Steps:
1. Download **STM32CubeIDE** from STMicroelectronics:  
   👉 [https://www.st.com/en/development-tools/stm32cubeide.html](https://www.st.com/en/development-tools/stm32cubeide.html)

2. Install the IDE and required USB drivers:  
   - **ST-LINK / DFU drivers** from ST website.  

3. Connect your Portenta H7 via **USB-C cable**.

4. Create a new project:  
   - Go to **File > New > STM32 Project**  
   - Select the MCU **STM32H747** (dual-core)  
   - Configure project name and settings  

5. Open **CubeMX configuration** (built into CubeIDE)  
   - Enable GPIO pins for LEDs (`LEDR`, `LEDG`, `LEDB`)  
   - Generate initialization code  

6. Write your first LED toggle program inside `main.c`.  
   Example:  
   ```c
   HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0); // Example LED pin
   HAL_Delay(500);

