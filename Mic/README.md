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

## SPH0645LM4H-B Digital MEMS Microphone
For this project, we select the **SPH0645LM4H-B** digital MEMS microphone. 
- **Type:** Digital MEMS microphone
- **Interface:** I²S → compatible with STM32 Nucleo-H755 boards
- **Frequency Response:** 50 Hz – 15 kHz → Suitable for **bird calls**, which are mainly in the **1 kHz – 8 kHz** range.
- **Voltage Supply:** 1.6 – 3.6 V → works with Nucleo-64’s 3.3 V supply.
- **Power Consumption:** Low, suitable for continuous outdoor monitoring.

#### Advantages: 
- No need for ADC → direct I²S connection to STM32.
- Compact and robust MEMS design.
- High sensitivity and reliability for bird detection applications.
- suitable for high performance like aiads/2015/02/INMP441.pdf)
  
**Datasheet:** [SPH0645LM4H-B Datasheet (PDF)](https://cdn-shop.adafruit.com/product-files/3421/i2S+Datasheet.PDF)
