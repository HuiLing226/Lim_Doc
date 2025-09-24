# Signal Processing Pipeline
(PCM → FFT → Mel → quantization)

## 1. Audio capture
- **Microphone**: SPH0645 I²S MEMS microphone
- **Sample rate**: 16 kHz (configured in STM32 I²S1)
- **Data format**: 16-bit samples in a 32-bit I²S frame
- **Buffering**: DMA transfers audio into a circular buffer
  ```c
  #define SAMPLE_RATE   16000        // Hz
  #define FRAME_SIZE    512          // samples per FFT frame
  #define HOP_SIZE      256          // frame stride (overlap 50%)
  ```

## 2. Framing and windowing
Audio is divided into short overlapping frames.
- Frame length: 512 samples (~32 ms)
- Hop size: 256 samples (~16 ms step)
- Each frame is multiplied by a **Hamming window**.
  ```c
  for (int i = 0; i < FRAME_SIZE; i++) {
    float w = 0.54f - 0.46f * cosf(2.0f * M_PI * i / (FRAME_SIZE-1));
    windowed[i] = (float32_t)pcm[i] / 32768.0f * w;
  }
  ```
## 3. FFT and Magnitude Spectrum
- FFT size: 512
- Output bins: 256 (Nyquist)
```c
arm_rfft_fast_f32(&fftInstance, fftInput, fftOutput, 0);
for (int i = 0; i < N_FFT/2; i++) {
    float re = fftOutput[2*i];
    float im = fftOutput[2*i+1];
    magnitude[i] = sqrtf(re*re + im*im);
}
```
## 4. Mel Filter Bank
The linear frequency axis is mapped to the Mel scale to approximate human hearing.
- Mel bands: 16
- Frequency range: 0 – 8 kHz
- Triangular overlapping filters applied to FFT magnitude bins.
```c
for (int m = 0; m < N_MELS; m++) {
    melSpectrum[m] = 0;
    for (int k = 0; k < N_FFT/2; k++) {
        melSpectrum[m] += magnitude[k] * melFilterBank[m][k];
    }
    melSpectrum[m] = (melSpectrum[m] > 0) ? logf(melSpectrum[m]) : -10.0f;
}
```
## 6. Quantization (float32 → INT8)
Since the neural network runs with INT8 inputs, Mel features are quantized.
- Range: [-10, +10] → maps to [-128, 127]
- Normalization → scaling → int8 cast
 ```c
  int8_t quantize_float_to_int8(float32_t x, float32_t min, float32_t max) {
    float norm = (x - min) / (max - min);  // 0..1
    int32_t q = (int32_t)(norm * 255.0f - 128.0f);
    if (q < -128) q = -128;
    if (q > 127) q = 127;
    return (int8_t)q;
  }
```

## 7. Final output format
- Sample count: 16,000 × 3 = 48,000 samples
- Feature matrix: **16 Mel bins × 188 frames = 3008 values**
- Stored in `int8_t melSpecInt8[3008]`
- This Mel spectrogram vector is the input to the neural network.

---

## STM32 Application Setup (with signal processing)
1. Enable CMSIS-DSP library, which can find the tutorial [here](https://community.st.com/t5/stm32cubeide-mcus/cookbook-enabling-arm-math-h-on-stm32h7-dual-core-m7-m4/td-p/205189).



