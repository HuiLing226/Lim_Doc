# Deploying a Neural Network to an MCU (STM32)

This guide explains how to deploy a trained neural network onto an STM32 Nucleo board using **TensorFlow Lite (TFLite)** and **X-CUBE-AI**.

---

### Step 1: Convert model to TFLite
Neural networks trained on desktops or cloud servers (e.g., TensorFlow, PyTorch) are often too large and computationally expensive for microcontrollers.   
- **Storage**: Hundreds of MBs (vs. <256 KB on many MCUs).  
- **Operations**: FP32 floating-point (vs. INT8 on low-end MCUs).  
- **Memory bandwidth**: High (vs. limited SRAM/Flash on embedded devices).  

TFLite optimizes models for microcontrollers:  
- Smaller (via **quantization** and pruning).  
- Faster inference (optimized kernels for ARM Cortex-M).  
- Low memory footprint (<16 KB RAM).  
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

  ###### !! If you want to download the model from Google Colab
```python

from google.colab import files
files.download("/content/mnist_model_float32.tflite")

```

---
### Step 2: Quantization
The model size is in 32-bit floating-point (FP32) which is still too big for MCUs, thus we need to convert it into 8-bit integers (INT8). 

#### 2.1 Post-Training Quantization (PTQ)
- Simplest method.
- Converts trained FP32 → INT8.
- Usually <1% accuracy loss (if calibration data is good).

```python
converter.optimizations = [tf.lite.Optimize.DEFAULT]
```

#### 2.2 Quantization-Aware Training (QAT)
- Simulates INT8 quantization during training.
- Minimizes accuracy loss.
- Best for critical applications (e.g., medical, industrial).

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
### Step 4: Deploying on STM32 with Cube.AI

#### 4.1 Create a project in STM32CubeMX
- Open CubeMX and select the target board (ie, **Nucleo-H755ZI-Q**).<img width="1879" height="1022" alt="image" src="https://github.com/user-attachments/assets/340b599b-5fe5-484f-a551-5d19e54550d9" />
- Configure PD8 → USART3_TX and PD9 → USART3_RX for debugging.
- Enable USART3 *Asynchronous* mode.<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/73fe83be-c1b5-419a-bfac-cf9c00e9026d" />

#### 4.2 Configure X-CUBE_AI
- Under *Middleware* → *X-CUBE-AI*, set as below:<img width="1711" height="962" alt="image" src="https://github.com/user-attachments/assets/7bd29c8e-bee1-4fac-8f69-417a534a77dc" />
  ##### !! Important: Use Cortex-M7

- Add Network → Change the *model* to *TFLite*
- Import Model (can get from [here](https://github.com/HuiLing226/Lim_Doc/blob/main/AI/mnist_portenta.tflite)). <img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/88de3103-33f3-4db4-859a-374e3f1a30a0" />
- → Click *Analyse* to check resource usage.
  
#### 4.3 Check resource usage <img width="808" height="272" alt="image" src="https://github.com/user-attachments/assets/57d81c07-9fd2-4d2e-98e7-a8561d618c29" />

#### 4.4 Generate code
- Go to *Project Manager* → set *Toolchain* to **STM32CubeIDE**<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/e48802c2-5497-4d02-9559-4628d63815d2" />
- Generate code. CubeMX produces files such as:
  - `app_ai.c/h` or `app_x-cube_ai.c/h` (for new ver)
  - `network.c/h`
  - `network_data.c/h`
  - <img width="172" height="303" alt="image" src="https://github.com/user-attachments/assets/56f3b7b9-c995-441d-add7-6cb07f84c388" />

#### 4.5 Integrate test digits
- Generate sample digits (1-5) using Python ([mnist_digits.py](https://github.com/HuiLing226/Lim_Doc/blob/main/AI/mnist_digits.py)) → export to [digits.h]. 
- Copy `digits.h` file into (Project)_CM7/Core/Inc.

    <img width="199.5" height="157.5" alt="image" src="https://github.com/user-attachments/assets/4163140f-24af-49ca-8c21-c401829cf4dd" />


### Step 5: Running inference
Modify  `MX_X_CUBE_AI_Process()` in *app_x-cube_ai.c*:
```c
void MX_X_CUBE_AI_Process(void)
{
    /* USER CODE BEGIN 6 */

	ai_i8 input_data [28*28];
	ai_i8 output_data [10];

	// Load test digit ( change to digit1 .. digit5 )
	memcpy ( input_data , digit1 , sizeof ( input_data ) );


	// Initialize AI buffers
	ai_buffer ai_input[AI_NETWORK_IN_NUM] = {
	    AI_BUFFER_INIT(
	        AI_FLAG_NONE,                    // flags
	        AI_BUFFER_FORMAT_S8,             // format
	        AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 1, 28, 28), // shape (batch, channels, width, height)
	        784,                             // size (28 * 28 * 1)
	        NULL,                            // meta_info
	        input_data                       // data
	    )
	};

	ai_buffer ai_output[AI_NETWORK_OUT_NUM] = {
	    AI_BUFFER_INIT(
	        AI_FLAG_NONE,                    // flags
	        AI_BUFFER_FORMAT_S8,             // format
	        AI_BUFFER_SHAPE_INIT(AI_SHAPE_BCWH, 4, 1, 10, 1, 1), // shape (batch, channels, width, height)
	        10,                              // size (10 classes)
	        NULL,                            // meta_info
	        output_data                      // data
	    )
	};

	// Run inference
	if ( ai_network_run ( network , ai_input , ai_output ) != 1) {
		HAL_UART_Transmit(&huart3, (uint8_t*)err_msg, strlen(err_msg), HAL_MAX_DELAY);
		return ;
	}

	// Find predicted digit
	int max_idx = 0;
	int8_t max_val = output_data [0];
	for (int i = 1; i < 10; i ++) {
		if ( output_data [i ] > max_val ) {
			max_val = output_data [i ];
			max_idx = i;
		}
	}
	sprintf(msg, "Predicted digit : %d\r\n", max_idx);
		HAL_UART_Transmit(&huart3, (uint8_t*)msg, strlen(msg), HAL_MAX_DELAY);

    /* USER CODE END 6 */
}
```
The whole project can be found [here]

### Step 6: Testing
#### 1. Build and flash the CubeIDE project.
#### 2. Open TeraTerm, choose the correct serial, and set the baud rate to 115200.
#### 3. Results:
- using `digit1`<img width="541" height="376" alt="image" src="https://github.com/user-attachments/assets/6bb8798a-1b15-4252-921c-6676b659a3cf" />

- using `digit2`<img width="541" height="376" alt="image" src="https://github.com/user-attachments/assets/b31c1b54-1bf8-4bf3-be26-a85a02a275b0" />

- using `digit3`<img width="541" height="376" alt="image" src="https://github.com/user-attachments/assets/c3f17fe8-5a8f-4056-918d-05bc7709868b" />

- using `digit4`<img width="541" height="376" alt="image" src="https://github.com/user-attachments/assets/44bc44a0-db70-417a-8bb2-8376da921d55" />

- using `digit5`<img width="541" height="376" alt="image" src="https://github.com/user-attachments/assets/8c56ad46-3718-4c94-bd4b-87d04b0e7685" />

  

 
