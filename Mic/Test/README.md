## 4. Signal Processing Pipeline
1.  Enabling `arm_math.h`, which can find the tutorial [here](https://community.st.com/t5/stm32cubeide-mcus/cookbook-enabling-arm-math-h-on-stm32h7-dual-core-m7-m4/td-p/205189).
   
1. **Sampling**
   - Configure I²S1 at **32 kHz** sample rate  
   - DMA buffer size: `FRAME_SIZE * 2` (e.g., 512 × 2)

2. **Pre-processing**
   - Convert raw audio → floating point
   - Apply **Hamming window**

3. **FFT**
   - Use CMSIS-DSP `arm_rfft_fast_f32`
   - Compute magnitude spectrum

4. **Mel Filterbank**
   - Pre-compute filter bank (e.g., 40 mel bins, FFT size 512)
   - Apply triangular filters → log-scaled mel spectrum

5. **Spectrogram**
   - Store mel features in a 2D circular buffer `melSpectrogram[N_FRAMES][N_MELS]`

---

