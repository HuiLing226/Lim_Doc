# Lim_Doc – STM32 Audio AI Project  

This repository documents the development of an **STM32-based Audio AI Project**, focusing on sound detection and bird species classification using digital MEMS microphones and machine learning.  

The notes are organized by topics into separate folders for clarity.  

---

## 📚 Table of Contents  

| Chapter / Topic        | Description |
|-------------------------|-------------|
| [Nucleo_H755](Nucleo_H755/README.md) | Notes and experiments using the **Nucleo-H755 development board** |
| [STM32](STM32/README.md) | General STM32 tutorials (CubeIDE setup, GPIO, interrupts, etc.) |
| [Microphone_Selection](Microphone_Selection/README.md) | Study of **analog vs. digital microphones** and chosen MEMS microphone (SPH0645LM4H-B) |

---

## 🚀 Project Goal  

- Detect sounds using MEMS microphones.  
- Identify if the sound comes from a **bird**.  
- Classify the **bird species** using lightweight AI on STM32.  

This repo will continue to grow with more detailed chapters covering:  
- I²S audio input  
- Feature extraction (MFCC, FFT)  
- TinyML / TensorFlow Lite for Microcontrollers (TFLM)  
- Deployment and testing on STM32 hardware  
