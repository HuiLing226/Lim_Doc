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
