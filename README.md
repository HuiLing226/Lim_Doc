# STM32 Audio AI Project  

This repository documents the development of an **STM32-based Audio AI Project**, focusing on sound detection and bird species classification using digital MEMS microphones and machine learning.  

## Executive Summary
- **Project Overview:** Brief description of the dual-chip bird sound detection and species classification system
- **Key Features:** Real-time detection, species identification, embedded AI implementation
- **Hardware Platform:** STM32H755ZI dual-core microcontroller with SPH0645LM4H microphone
- **Development Environment:** STM32CubeIDE + STM32 AI toolkit

## Table of Contents  

| Chapter / Topic        | Description |
|-------------------------|-------------|
| [Nucleo_H755](Nucleo_H755/README.md) | Notes and datasheets using the **Nucleo-H755 development board** |
| [Getting_Start](STM32/StartUp) | General STM32 tutorials (CubeIDE setup, GPIO, blinking LED, etc.) |
| [Microphone_Selection](Mic/README.md) | Study of **analog vs. digital microphones** and chosen MEMS microphone (SPH0645LM4H) |

---

## Project Goal
Develop an embedded system capable of detecting and classifying bird sounds.
### Technical Objectives:
- Implement real-time audio processing
- Deploy AI models on embedded hardware
- Achieve acceptable accuracy for bird detection and species classification

