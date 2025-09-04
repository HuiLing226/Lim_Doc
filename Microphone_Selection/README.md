# Microphone Selection
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

--- 

## INMP441 Digital MEMS Microphone
For this project, we use the **INMP441** digital MEMS microphone as the audio input device. It is a simple, reliable, and widely supported I²S microphone that works well with the STM32H755 dual-core MCU.

---

## Advantages
- **Simple Hardware Setup:**
  - Operates from a single **3.3 V supply**, no need for extra regulators.
  - Standard **6-pin breakout pinout**:  
    **VDD, GND, SD (data), WS (word select), SCK (bit clock), L/R (channel select)**
  - No external components required  
- **Direct Digital Output(I²S):**
  - No ADC needed (unlike analog microphones).
  - **24-bit output** → fits well with H755’s DSP and AI capabilities.
  - Fully supported by STM32 HAL and STM32CubeIDE. 
- **Frequency Response:** 60 Hz – 15 kHz
  - suitable for **bird calls** (1–8 kHz range).
- **Low Power Consumption:** Low, enabling continuous outdoor monitoring  

### Development Ease
- Works seamlessly with **STM32CubeMX** (configure I²S peripheral)  
- Many STM32 + INMP441 code examples available online  
- Simple 4-wire I²S connection (plus power)  
- Immediate audio capture without complex initialization  

---

## Basic Connection (Nucleo-H755ZI)

INMP441 -> Nucleo-H755ZI

VDD -> 3.3V

GND -> GND

SD -> I2S_SD pin

WS -> I2S_WS pin

SCK -> I2S_CK pin

L/R -> GND (left channel) or 3.3V (right channel)


---






## Reference
- **Datasheet:** [INMP441 PDF](https://invensense.tdk.com/wp-content/uploads/2015/02/INMP441.pdf)  
