## Structure of a Simple Neural Network

### Layers
1. **Input Layer** – Takes input values (e.g., 28×28 pixel image → 784 neurons).
2. **Hidden Layer(s)** – Processes inputs using weights, bias, and activation functions.
3. **Output Layer** – Produces the final prediction (e.g., digits 0–9).

### Flow
- Input → Hidden layer(s) → Output.
- Each connection has a **weight** that scales importance.
- Each neuron has a **bias** to shift activation.
- Activation functions (ReLU, Sigmoid, etc.) introduce non-linearity.

  ---

## How a Neuron Works

### Step 1: Input
- Each pixel (0–1 grayscale value) enters as activation.
- Example: MNIST digit → 28×28 = 784 input neurons.

### Step 2: Weighted Sum + Bias
Each hidden neuron computes:
\[
z = \sum (w_i \cdot x_i) + b
\]

- \(w_i\): weight
- \(x_i\): input activation
- \(b\): bias

### Step 3: Activation Function
\[
a = f(z)
\]
- Converts weighted sum into nonlinear output.
- Common functions: ReLU, Sigmoid, Tanh.

### Step 4: Output Decision
- Output layer has 10 neurons (0–9).
- Neuron with highest activation = prediction.

### Step 5: Backpropagation
- Forward pass: input → output prediction.
- Compute loss (error).
- Backward pass: gradients flow backward to adjust weights and bias.
- Repeat until error minimized.

--- 

## What is TinyML?

- Fusion of ML and embedded systems.
- Models compressed (GB → KB).
- Optimized for low-power devices.
- Applications:
  - Keyword spotting (“Hey Arduino”).
  - Gesture recognition.
  - Environmental monitoring (bird sounds).
  - Healthcare devices.

**Key Benefits:**
- Long battery life.
- Real-time response.
- Cost-efficient.

---

## TinyML vs Cloud AI

**Cloud AI:**
- Runs on servers/GPUs.
- High compute power.
- Requires internet.
- Latency & privacy concerns.

**TinyML:**
- Runs on microcontrollers (e.g., STM32).
- Low power (milliwatts).
- Offline, real-time.
- Private (data stays on device).

**Partnership:**
- Cloud: train big models, manage data.
- TinyML: deploy small optimized models locally.

--- 

## Google Colab

- Free cloud Jupyter environment from Google.
- Preinstalled with TensorFlow, NumPy.
- Free GPU acceleration.
- Runs in browser, no setup.

**Steps:**
1. Go to https://colab.research.google.com
2. Sign in → New Notebook.
3. Run Python/TensorFlow code directly.
4. Save automatically to Google Drive.

Enable GPU: Runtime → Change runtime type → GPU.

---

## TensorFlow

- Open-source ML library by Google.
- `tf.keras`: easy API for building networks.
- `tf.lite`: lightweight models for embedded.

**Example:**
```python
from tensorflow.keras import layers, models
model = models.Sequential([
    layers.Dense(128, activation='relu', input_shape=(784,)),
    layers.Dense(10, activation='softmax')
])
```

---

## MNIST Dataset

- 70,000 handwritten digits (0–9).
- 60k training, 10k testing.
- Each image: 28×28 pixels grayscale.
- Classic "Hello World" of DL.

**Load in TensorFlow:**
```python
from tensorflow import keras
(x_train, y_train), (x_test, y_test) = keras.datasets.mnist.load_data()
x_train, x_test = x_train/255.0, x_test/255.0
```
---

## Your First Neural Network in Code

**Step 1: Import**
```python
import tensorflow as tf
from tensorflow import keras
x_train = x_train.reshape(-1,784).astype("float32")/255
x_test = x_test.reshape(-1,784).astype("float32")/255
```

**Step 2: Preprocess**
```python
x_train = x_train.reshape(-1,784).astype("float32")/255
x_test = x_test.reshape(-1,784).astype("float32")/255
```

**Step 3: Model**
```python
model = keras.Sequential([
    keras.layers.Dense(128, activation="relu", input_shape=(784,)),
    keras.layers.Dense(10, activation="softmax")
])
```

**Step 4: Compile**
```python
model.compile(optimizer="adam",
              loss="sparse_categorical_crossentropy",
              metrics=["accuracy"])
```

**Step 5: Train**
```python
model.fit(x_train, y_train, epochs=5, batch_size=32)
```

**Step 6: Evaluate**
```python
test_loss, test_acc = model.evaluate(x_test, y_test)
print("Accuracy:", test_acc)
```

---

## QNA

### Why do smaller models train faster but may have lower accuracy?
- Fewer parameters → faster computation.
- But limited capacity → may underfit.

### Why does accuracy sometimes stop improving after many epochs?
- Overfitting: memorizing training data, not generalizing.
- Learning rate too high/low.
- Fix: early stopping, regularization, dropout.

### How do these trade-offs matter for microcontrollers?
- MCUs have limited memory & compute.
- Must balance model size vs accuracy.
- Often better to use a slightly smaller model that fits in RAM/Flash and runs in real-time.
