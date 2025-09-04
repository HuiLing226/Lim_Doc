# STM32 NUCLEO-H755ZI 

---

## Chap 00: Introduction

### Overview
The **STM32 Nucleo-144** board provides a flexible and affordable platform for prototyping with the STM32H755 series microcontrollers.  
It integrates:
- **ST Zio connector** (extends Arduino™ Uno V3 compatibility)  
- **ST morpho connectors** (full pin access)  
- **On-board ST-LINK debugger/programmer** (no external probe needed)  

This board is suitable for high-performance applications like **audio signal processing** and **AI-based detection systems**.

---

### MCU Specifications (STM32H755xI)
- **Dual-core architecture**  
  - Cortex®-M7 @ 480 MHz (with L1 cache, double-precision FPU, DSP instructions)  
  - Cortex®-M4 @ 240 MHz (with FPU, DSP instructions)  
- **Performance**  
  - 1027 DMIPS (M7), 300 DMIPS (M4)  
- **Memory**  
  - 2 MB Flash (dual bank, read-while-write)  
  - 1 MB RAM (192 KB TCM RAM, 864 KB user SRAM, 4 KB backup SRAM)  
- **External memory support**  
  - Quad-SPI up to 133 MHz  
  - Flexible memory controller (SRAM, SDRAM, NOR/NAND, PSRAM)  

---

### Peripherals & Features
- **ADC/DAC**  
  - 3 × 16-bit ADCs (36 channels, up to 3.6 MSPS)  
  - 2 × 12-bit DACs  
- **Timers**  
  - 22 total (includes motor-control, general-purpose, low-power, watchdogs)  
  - High-resolution timer (2.1 ns resolution)  
- **Communication interfaces**  
  - 4 × I²C (FM+)  
  - 8 × USART/UART + 1 × LPUART  
  - 6 × SPI (3 with I²S), 4 × SAI  
  - SPDIF-Rx, MDIO, SWPMI  
  - 2 × CAN FD + TT-CAN  
  - 2 × USB OTG (FS + HS with ULPI)  
  - Ethernet MAC with DMA  
  - SD/SDIO/MMC (2×)  
- **Graphics**  
  - LCD-TFT controller (up to XGA)  
  - Chrom-ART Accelerator™ (DMA2D)  
  - JPEG hardware codec  
- **Crypto & Security**  
  - AES, TDES, HASH, HMAC, TRNG  
  - Secure firmware upgrade support  

---

### Power & Clock
- Supply: 1.62 V – 3.6 V  
- Backup supply: 1.2 – 3.6 V (VBAT)  
- Low-power modes: Sleep, Stop, Standby, VBAT  
- Internal oscillators: HSI (64 MHz), HSI48, CSI (4 MHz), LSI (32 kHz)  
- External oscillators: HSE (4–48 MHz), LSE (32.768 kHz)  

---

### Debugging
- SWD + JTAG  
- Embedded trace buffer (4 KB)  
- Integrated ST-LINK (STLINK-V3E or V3EC)  

---

### I/O Capabilities
- Up to **168 GPIOs** with interrupts  
- Many 5V-tolerant pins  
- ST Zio (Arduino Uno V3 compatibility)  
- ST morpho (full MCU pin access)  

---

### On-board Components
- **3× User LEDs**  
- **1× User Button (B1)**  
- **1× Reset Button**  
- **32.768 kHz LSE crystal oscillator**  

---

## Chap 01: Pinout and Expansion

The **NUCLEO-H755ZI** provides two expansion systems:

1. **Arduino™ Uno V3-compatible (Zio) headers**  
   - Allow shields and easy prototyping.  

2. **ST morpho connectors (CN11, CN12, CN13, CN14)**  
   - Expose nearly all MCU pins for advanced usage.  

📌 This dual system lets you choose between **Arduino shields** (easy add-ons) and **direct STM32 GPIO access** for complex designs.  

![Nucleo-H755ZI Pinout](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_h755zi_zio.png)  
![Nucleo-H755ZI Morpho](https://os.mbed.com/media/uploads/jeromecoutant/nucleo_h755zi_morpho.png)  

---

## Chap 02: Getting Started with STM32CubeIDE

### 1. Install STM32CubeIDE
- Download: [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html)  
- Supports Windows, Linux, macOS  

### 2. Create a New Project
1. Open CubeIDE → **File > New > STM32 Project**  
2. Search **NUCLEO-H755ZI** (or STM32H755ZIT6) in board selector  
3. Configure `.ioc` (pinout & middleware)  

### 3. First Example – Blink LED
- **LD1/LD2/LD3** are available user LEDs.  
- Example (toggle LED on port `PB0`):

```c
#include "main.h"

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  while (1)
  {
    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
    HAL_Delay(500);  // 500 ms
  }
}
