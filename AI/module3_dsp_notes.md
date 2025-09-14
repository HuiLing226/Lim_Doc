# Module 3: DSP for Audio

## Learning Objectives
By the end of this module, you should be able to:
- Understand the fundamentals of digital audio signals.
- Apply DSP techniques to extract features from raw microphone input.
- Compute STFT, Mel spectrograms, and MFCCs for audio analysis.
- Prepare audio features suitable for TinyML models on microcontrollers.

---

## 1. Audio Signal Basics
- **Digitization**: Microphone captures sound → converted to digital samples via ADC or I2S (commonly 16 kHz).
- **Time-domain signal**: Raw waveform with amplitude vs. time.
- Raw audio is too large and noisy → needs transformation into compact, meaningful features.

---

## 2. Windowing
- Audio is split into **frames** (e.g., 25 ms each, ~400 samples at 16 kHz).
- Frames overlap (e.g., 10 ms hop).
- Apply a **window function** (Hann or Hamming) to reduce spectral leakage.

---

## 3. Short-Time Fourier Transform (STFT)
- For each frame, apply **FFT** → frequency representation.
- Produces a **spectrogram** (time × frequency × magnitude).
- Still large in size, but shows frequency evolution over time.

---

## 4. Mel Filter Bank
- Human/bird hearing is non-linear: better resolution at low frequencies.
- Apply **Mel filter bank** to spectrogram:
  - Compress frequency axis into Mel scale.
  - Output: **Mel spectrogram** (time × Mel bands).
- Example: 40 Mel bands instead of 257 FFT bins.

---

## 5. Log Scaling
- Convert Mel spectrogram to **log scale** (dB).  
- Makes features more stable and closer to human perception.

---

## 6. MFCC (Optional)
- Apply **Discrete Cosine Transform (DCT)** to log-Mel spectrogram.
- Produces **Mel-Frequency Cepstral Coefficients (MFCCs)**.
- Compact (e.g., 13 coefficients per frame).
- Often used in speech tasks; optional for CNN-based bird detection.

---

## 7. DSP on STM32 Nucleo H755
- **Real-time requirement**: Process each frame before next arrives.
- Use **CMSIS-DSP** library:
  - `arm_rfft_fast_f32()` for FFT.
  - `arm_mat_mult_f32()` for Mel filter bank and DCT.
- **Precompute**:
  - Mel filter bank weights in Python → store in C arrays.
  - DCT matrix for MFCC → store in C arrays.

---

## 8. Example DSP Flow
1. Microphone → 16 kHz audio stream.
2. Frame 25 ms, hop 10 ms, apply Hann window.
3. FFT (512-point) → Power spectrum.
4. Multiply by Mel filter bank (40 bands).
5. Take log → Mel spectrogram.
6. (Optional) DCT → 13 MFCCs.
7. Pass Mel spectrogram or MFCCs into TinyML model.

---

## Key Notes
- **Mel spectrogram** = main feature for CNN models on MCU.
- **MFCC** = optional, more compact, but may lose detail.
- DSP reduces raw audio → efficient, informative features.
- Essential step before deploying any audio TinyML application.

---

## Reflection
- Why do we use overlapping windows for STFT?  
- Why is Mel scaling better than raw FFT for bird/audio detection?  
- When would MFCCs be preferred over Mel spectrograms?  
