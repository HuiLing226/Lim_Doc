## Chap 00: Introduction

### Overview
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
   ![alt text](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f446re_arduino_left_2021_10_26.png)
 ![alt text](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f446re_arduino_right_2021_10_26.png)

2. **ST morpho headers (male pin headers, CN7 & CN10)**  
   - Provide **full access to nearly all STM32 pins**.  
   - Enable advanced use cases beyond Arduino compatibility.  
![alt text](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f446re_morpho_right_2021_10_26.png)
![alt text](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_f446re_morpho_left_2021_10_26.png)


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
   - Search for **STM32F446RET6**.  
4. Select the board and click **Next**.  
5. Name your project.  
6. Finish and let CubeIDE generate the project files.

   
---

## Chap 02: First Program – Blink the LED

### 1. Configure Pin in STM32CubeIDE
1. In the **.ioc file**, go to **Pinout & Configuration**.  
2. Select pin **PA5** and set it as **GPIO_Output**.  
  - On the NUCLEO-F446RE board, the **LD2 (user LED)** is connected to **PA5**.
  - Reference: [NUCLEO-F446RE Schematic Diagram](https://github.com/HuiLing226/Lim_Doc/blob/main/NUCLEO_F446RE_SCHEMATICS.pdf)
3. CubeIDE will automatically add it under `GPIO`.  

### 2. Generate Code
- Select **Project > Generate Code** (or press **Alt+K**).  
- CubeIDE will generate `main.c` file along with the necessary HAL drivers.

### 3. Write Code in `main.c`in under while loop
Inside the **while loop**, add the following code:

```
while (1)
  {
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);  // Toggle LED on PA5
    HAL_Delay(500);                         // Delay 500 ms
  }
}
```

### 4. Build and Flash the program
1. Go to **Project > Build Project** to compile the code.
2. Connect the NUCLEO-F446RE board via USB.
3. Select **Run > Run As > STM32 C/C++ Application**.
4. The LED (LD2) on pin **PA5** will start blinking at 1 Hz (on/off every 500 ms).


---

## Chap 03: Microphone Selection  

For STM32 audio projects, there are mainly **two categories** of microphones to consider:  

### 1. Analog Microphones  
#### How they work:  
- Convert acoustic pressure waves into a continuous electrical signal (voltage waveform).  
- STM32 requires an **ADC (Analog-to-Digital Converter)** to digitize the signal.

### 2. Digital Microphones  
#### How they work:  
- Convert sound directly into a **digital signal** before transmission.  
- Common output formats:  
  - **PDM (Pulse Density Modulation)** → supported on STM32 with libraries.  
  - **I²S (Inter-IC Sound)** → common and natively supported by STM32 peripherals.  


For this project, we select the **SPH0645LM4H-B** digital MEMS(Micro-Electro Mechanical Systems) microphone.  

- **Interface:** I²S → compatible with STM32 Nucleo-64 boards  
- **Frequency Response:** 50 Hz – 15 kHz  → Suitable for **bird calls (1 – 8 kHz)**.    
- **Voltage Supply:** 1.6 – 3.6 V → works with Nucleo-64’s 3.3 V supply.  
- **Power Consumption:** Low, suitable for continuous outdoor monitoring.  

#### Advantages:  
- No need for ADC → direct I²S connection to STM32.  
- Compact and robust MEMS design.  
- High sensitivity and reliability for use.
- Optimized for high-performance applications such as AI/ML audio processing.

📄 **Datasheet:** [SPH0645LM4H-B Datasheet (PDF)](https://cdn-shop.adafruit.com/product-files/3421/i2S+Datasheet.PDF)  


---

## Chap 04: Sound input via I<sup>2</sup>S
