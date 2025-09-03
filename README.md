<img width="960" height="720" alt="image" src="https://github.com/user-attachments/assets/15863e95-498e-4dc7-aa11-224f933a7bf9" />
## Chap 00: Introduction

### MCU Overview
- **Core**: Arm® 32-bit Cortex®-M4 CPU with FPU  
  - Adaptive real-time accelerator (ART Accelerator)  
  - 0-wait state execution from Flash memory  
  - Frequency: up to 180 MHz  
  - Memory Protection Unit (MPU)  
  - Performance: 225 DMIPS / 1.25 DMIPS/MHz (Dhrystone 2.1)  
  - DSP instructions supported  

### Memories
- 512 Kbytes Flash memory  
- 128 Kbytes SRAM  
- Flexible external memory controller (up to 16-bit data bus): supports SRAM, PSRAM, SDRAM/LPSDR SDRAM, NOR/NAND Flash  
- Dual-mode QuadSPI interface  

### Interfaces & Peripherals
- LCD parallel interface (8080/6800 modes)  
- Clock, reset and supply management:  
  - Supply range: 1.7 V to 3.6 V  
  - POR, PDR, PVD and BOR  
  - 4 to 26 MHz crystal oscillator  
  - Internal 16 MHz RC (1% accuracy)  
  - 32 kHz RTC oscillator + calibration  
  - Internal 32 kHz RC + calibration  
- Low power modes: Sleep, Stop, Standby  
- VBAT supply for RTC, 20×32-bit backup registers, optional 4 KB backup SRAM  
- ADC: 3×12-bit, up to 2.4 MSPS, 24 channels, 7.2 MSPS in triple interleaved mode  
- DAC: 2×12-bit D/A converters  
- DMA: 16-stream DMA controller with FIFO and burst support  
- Timers: 17 total  
  - 2 watchdogs  
  - 1 SysTick  
  - 12×16-bit timers  
  - 2×32-bit timers  
  - Up to 180 MHz operation, each with up to 4 IC/OC/PWM  

### Debug
- SWD and JTAG support  
- Cortex-M4 Trace Macrocell™  

### I/O Capabilities
- Up to 114 I/O ports with interrupt capability  
- Up to 111 fast I/Os (90 MHz)  
- Up to 112 5 V-tolerant I/Os  

### Communication Interfaces
- Up to 20 interfaces, including:  
  - SPDIF-Rx  
  - 4 × I²C (SMBus/PMBus)  
  - 4 × USART + 2 × UART (11.25 Mbit/s, ISO7816, LIN, IrDA, modem control)  
  - 4 × SPI (45 Mbit/s), 3 muxed with I²S  
  - 2 × SAI (serial audio interface)  
  - 2 × CAN (2.0B Active)  
  - SDIO interface  
  - Consumer Electronics Control (CEC) interface 

### Advanced Connectivity
- USB 2.0 FS OTG controller with on-chip PHY  
- USB 2.0 HS/FS OTG controller with DMA, ULPI, and PHY  
- Dedicated USB power rail supports full-speed PHY across MCU voltage range  
- 8–14 bit parallel camera interface (54 MB/s)  

### Other Features
- CRC calculation unit  
- RTC with subsecond accuracy, hardware calendar  
- 96-bit unique ID  

---

### Pinout and Board Layout 

The **NUCLEO-F446RE** are designed with **dual pinout compatibility**:

1. **Arduino™ Uno R3 headers (female pin sockets)**  
   - Allow direct plug-in of Arduino shields.  
   - Pins are arranged as **D0–D15** (digital) and **A0–A5** (analog).  
![alt text](http://url/to/https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f446re_arduino_left_2021_10_26.png
)
2. **ST morpho headers (male pin headers, CN7 & CN10)**  
   - Provide **full access to nearly all STM32 pins**.  
   - Enable advanced use cases beyond Arduino compatibility.  


---

## Chap 01: Install STM32 and Get Started

### 1. Install STM32CubeIDE
1. Download STM32CubeIDE from: [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html).  
2. Install on your system (Windows, Linux, or macOS).  
3. Launch the IDE.

### 2. Setup a New Project
1. Open **STM32CubeIDE**.  
2. Go to **File > New > STM32 Project**.  
3. In the MCU/Board selector:  
   - Search for **NUCLEO-F446RE** or **STM32F446RE**.  
4. Select the board and click **Next**.  
5. Name your project (e.g., `led_blink_test`).  
6. Finish and let CubeIDE generate the project files.

### 3. Configure Clock & Peripherals
- By default, NUCLEO-F446RE uses **HSE oscillator (8 MHz)** and can be configured up to **180 MHz** with PLL.  
- For basic LED blink test, no special clock configuration is required.  

### 4. Compile and Run Project
1. Connect NUCLEO-F446RE via USB.  
2. Select **Run > Debug** in CubeIDE.  
3. IDE will flash the program onto the board using the built-in ST-LINK debugger.  
4. The board will reset and run the program.

---

## Chap 02: First Program – Blink the LED

> To be continued: GPIO configuration and example code for LED blinking (using LD2 at pin `PA5`).
