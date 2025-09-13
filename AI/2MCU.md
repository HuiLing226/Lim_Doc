# Deploying a Neural Network to an MCU (STM32)

Once you have trained a neural network, the next step is to **deploy it on a microcontroller**.  

---

### Step 1: Convert to TFLite
Neural networks trained on desktops or cloud servers are often too large for microcontrollers. Neural networks trained on desktops or cloud servers (e.g., using TensorFlow or PyTorch) are typically too large and computationally expensive for microcontrollers. A typical pre-trained CNN (e.g., MobileNet) may require:
- Hundreds of MBs of storage (vs. <256 KB on many MCUs).
- Floating-point operations (FP32) (vs. 8-bit integer (INT8) ops on low-end MCUs).
- High memory bandwidth (vs. limited SRAM/Flash on embedded devices)

Thus, the network trained is needed to convert into TensorFlow Lite (TFLite):
- Smaller models (via quantization & pruning).
- Faster inference (optimized kernels for ARM Cortex-M).
- Low memory footprint (works with <16 KB RAM).
- Cross-platform support (STM32, Arduino, ESP32, RP2040).

```python
# Create a TFLite Converter
converter = tf.lite.TFLiteConverter.from_keras_model (model)
# Convert
tflite_model = converter.convert ()

# Save the model
with open ("mnist_model_float32.tflite", "wb") as f:
  f.write(tflite_model)
```
---
### Step 2: Quantization
The model size is in 32-bit floating-point (FP32) which is still too big for MCUs, thus we need to convert it into 8-bit integers (INT8). 
There are two ways of quantization:
#### Post-Training Quantization (PTQ)
PTQ converts a trained model to INT8 without retraining. It’s the simplest way to optimize for microcontrollers, typically with < 1% accuracy loss if well-calibrated.

```python
converter.optimizations = [tf.lite.Optimize.DEFAULT]
```

#### Quantization-Aware Training (QAT)
QAT simulates INT8 quantization during training to minimize accuracy loss. Ideal for
critical applications (e.g., medical, industrial).

```python
import tensorflow as tf
import tensorflow_model_optimization as tfmot

model = tf.keras.Sequential([...])
model.compile(...)

# Apply quantization-aware training
quant_aware_model = tfmot.quantization.keras.quantize_model(model)
quant_aware_model.fit(x_train, y_train, epochs=5)

# Convert to TFLite
converter = tf.lite.TFLiteConverter.from_keras_model(quant_aware_model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()
```
---
### Step 3(Optional): Check compatibility
``` python
interpreter = tf.lite.Interpreter(model_content=tflite_model)
print ("Supported ops:", interpreter.get_tensor_details ())
```
---
### Step 4: MNIST Classifier on STM32 Nucleo Boards with Cube.AI

#### 1. Create a project in STM32CubeMX. Select the target board (ie, Nucleo-H755ZI-Q).
<img width="1879" height="1022" alt="image" src="https://github.com/user-attachments/assets/340b599b-5fe5-484f-a551-5d19e54550d9" />

#### 2. Configure PD8 as USART3_TX and PD9 as USART3_RX for debugging. In the Pinout & Configuration tab, enable USART3 *Asynchronous*.
<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/73fe83be-c1b5-419a-bfac-cf9c00e9026d" />

#### 3. Under *Middleware*, open *X-CUBE-AI* and set as below:
<img width="1711" height="963" alt="image" src="https://github.com/user-attachments/assets/73d5f297-0df7-48b8-b019-8ec21da4109e" />

#### 4. Import the quantized model. In the AI configuration window, click Add Network → Change the *model* to *TFLite* → Import Model (can get from [here](https://github.com/HuiLing226/Lim_Doc/blob/main/AI/mnist_portenta.tflite)) → Click *Analyse*.
<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/88de3103-33f3-4db4-859a-374e3f1a30a0" />

#### 5. Check resource usage Cube.AI. Analyzer reports RAM, Flash, and MACs required.
<img width="1309" height="617" alt="image" src="https://github.com/user-attachments/assets/d602aacd-a815-4f81-a304-69741f36e78c" />

#### 6. Under *Project Manager*, change the *Toolchain* to STM32CubeIDE and generate the code. 
<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/e48802c2-5497-4d02-9559-4628d63815d2" />
- CubeMX produces files such as: app_ai.c/h or app_x-cube_ai.c/h (for new ver), network.c/h, network_data.c/h.
<img width="172" height="303" alt="image" src="https://github.com/user-attachments/assets/56f3b7b9-c995-441d-add7-6cb07f84c388" />

#### 7. Integrate test digits. Copy digits.h (sample digits 1–5) into Core/Inc.
<img width="486" height="339" alt="image" src="https://github.com/user-attachments/assets/07e26a4e-9e0b-4f8a-bdb5-0572fb49a905" />

```h
# ifndef DIGITS_H
# define DIGITS_H
# include <stdint.h>

extern const int8_t digit1 [28*28];
extern const int8_t digit2 [28*28];
extern const int8_t digit3 [28*28];
extern const int8_t digit4 [28*28];
extern const int8_t digit5 [28*28];

# endif // DIGITS_H
```
---

### Step 5: Running inference
Under *app_x-cube_ai.c*, modify the n MX_X_CUBE_AI_Process() to load a test digit and print the prediction.
