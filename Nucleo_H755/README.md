# STM32 NUCLEO-H755ZI 

---

## Overview
The **STM32 Nucleo-144** board provides a flexible and affordable platform for prototyping with the STM32H755 series microcontrollers.  
It integrates:
- **ST Zio connector** (extends Arduino™ Uno V3 compatibility)  
- **ST morpho connectors** (full pin access)  
- **On-board ST-LINK debugger/programmer** (no external probe needed)  

The overview of the board layout is as below:
<img width="398" height="454" alt="image" src="https://github.com/user-attachments/assets/1362dfea-e6f4-4376-9a12-fd1d4d4dcb55" />


---

## MCU Specifications (STM32H755ZI - Q)
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

## Peripherals & Features
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

## Power & Clock
- Supply: 1.62 V – 3.6 V  
- Backup supply: 1.2 – 3.6 V (VBAT)  
- Low-power modes: Sleep, Stop, Standby, VBAT  
- Internal oscillators: HSI (64 MHz), HSI48, CSI (4 MHz), LSI (32 kHz)  
- External oscillators: HSE (4–48 MHz), LSE (32.768 kHz)  

---

## Debugging
- SWD + JTAG  
- Embedded trace buffer (4 KB)  
- Integrated ST-LINK (STLINK-V3E or V3EC)  

---

## I/O Capabilities
- Up to **168 GPIOs** with interrupts  
- Many 5V-tolerant pins  
- ST Zio (Arduino Uno V3 compatibility)  
- ST morpho (full MCU pin access)  

---

## On-board Components
- **3× User LEDs**  
- **1× User Button (B1)**  
- **1× Reset Button**  
- **32.768 kHz LSE crystal oscillator**  

---
## Reference
- [Data sheet](https://www.st.com/en/evaluation-tools/nucleo-h755zi-q.html)
- [Schematics](https://www.st.com/resource/en/schematic_pack/mb1363-h755ziq-d01_schematic.pdf)
- [Reference Manual](https://www.st.com/resource/en/reference_manual/rm0399-stm32h745755-and-stm32h747757-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [User Manual](https://www.st.com/resource/en/user_manual/um1721-developing-applications-on-stm32cube-with-fatfs-stmicroelectronics.pdf)



---

