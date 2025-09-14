# Module 3: Model Deployment on MCUs

## Learning Objectives
By the end of this module, you should be able to:
- Deploy a trained neural network model onto an STM32 Nucleo board.
- Understand how to convert models into TensorFlow Lite (TFLite) format.
- Perform quantization to optimize models for microcontroller use.
- Integrate microphone input with TinyML firmware in STM32CubeIDE.
- Flash the firmware and run real-time inference on the Nucleo H755.

---

## Workflow Overview
1. **Train Model in Colab**
   - Train using Python (TensorFlow/Keras).
   - Input features: **Mel spectrogram** from microphone audio.
   - Save as a `.tflite` model.

2. **Convert Model to C Header**
   - Use `xxd -i` or STM32Cube.AI tools to convert the `.tflite` file into a C array (`model_data.h`).
   - This embeds the model inside MCU firmware.

3. **Setup Microphone on Nucleo H755**
   - Connect MEMS microphone or I2S mic to the board.
   - Configure sampling rate (commonly 16 kHz).
   - Use DMA + interrupts to collect audio frames.

4. **Compute Mel Filterbank on MCU**
   - Precompute Mel filterbank weights (in Python) and include as C arrays.
   - On MCU:
     - Apply STFT on audio frames (FFT → power spectrum).
     - Multiply with Mel filterbank → **Mel spectrogram features**.

5. **Run Inference with TFLite Micro**
   - Load the model into MCU RAM/Flash.
   - Feed extracted Mel spectrogram features into the model.
   - Model outputs: probability of bird sound (active vs inactive).

6. **Integrate with STM32CubeIDE**
   - Create a project with STM32CubeIDE.
   - Add `model_data.h`, preprocessing code, and inference loop.
   - Compile and flash firmware.

7. **Test and Verify**
   - Run inference in real-time with live microphone input.
   - Check predictions via UART/serial logs or onboard LEDs.

---

## Key Notes
- **STFT**: Required to transform raw audio into frequency domain.
- **Mel Spectrogram**: Main input feature for CNN model.
- **MFCC**: Optional (compressed version of Mel spectrogram), but not required here.
- **Quantization**: Reduces model size (e.g., FP32 → INT8) to fit MCU memory and speed up inference.
- **Memory Constraints**: Ensure model < RAM/Flash capacity of Nucleo H755.

---

## Example: Bird Activity Detection (BAD)
1. Train CNN on bird/no-bird dataset (using Mel spectrogram features).
2. Convert trained model → `.tflite` → `.h` C header.
3. Implement microphone streaming + STFT + Mel filterbank on MCU.
4. Deploy and test: board lights up LED when bird sound is detected.

---

## Reflection
- Why is quantization essential for MCU deployment?
- Why do we prefer Mel spectrograms over MFCCs in CNN-based detection?
- How can you balance model accuracy vs latency on the Nucleo H755?
