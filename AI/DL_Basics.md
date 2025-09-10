# Deep Learning Basics

## CHAP 1: TinyML (Tiny Machine Learning)

### What is TinyML?
According to [tinyml.org](https://www.tinyml.org/):  
> “Tiny machine learning is broadly defined as a fast-growing field of machine learning technologies and applications including hardware, algorithms, and software capable of performing on-device sensor data analytics at extremely low power (typically in the mW range and below), and hence enabling a variety of always-on use cases targeting battery operated devices.”

TinyML = **AI at the edge**, running on **low-power microcontrollers**.

---

### Benefits of TinyML
- **Low Latency:** Inference runs on-device → no internet delays.
- **Energy Savings:** MCUs consume very little power, often running for months/years on batteries.
- **Reduced Bandwidth:** No need to stream raw sensor data to the cloud.
- **Data Privacy:** Data stays on-device → higher privacy.

---

### Why is TinyML Important?
TinyML enables us to **do more with less**:  
- Bring AI to billions of low-cost IoT devices.  
- Enable **always-on sensing** without draining batteries.  
- Complement cloud AI (train in the cloud, deploy at the edge).  


---

## CHAP 2: Neural Networks Fundamentals
### How a Neuron Works

A neuron is the fundamental building block of a neural network.  
It receives inputs, applies weights and biases, and passes the result through an activation function.

### What are Neural Networks?
Neural networks (also called **Artificial Neural Networks, ANNs**) form the foundation of **deep learning**.  
They are inspired by the structure and function of the human brain, where neurons signal to one another.

- Neural networks are a **subfield of Machine Learning**.
- They consist of **layers of artificial neurons** that transform inputs into outputs.
- By adjusting weights and biases, they learn complex patterns from data.

---

### Mathematical Model
For inputs [x₁, x₂, ..., xₙ] with weights [w₁, w₂, ..., wₙ] and bias [b]:

$$z = \sum_{i=1}^n w_i x_i + b$$

The output of the neuron is:

$$y = f(z)$$

where:
- $w_i$ = weight (importance of each input)  
- $b$ = bias (adjusts the output threshold)  
- $f(\cdot)$ = activation function (introduces nonlinearity)  

#### Activation Functions

- **Sigmoid:** $f(x) = \frac{1}{1+e^{-x}}$ → squashes output between (0,1)
- **ReLU:** $f(x) = \max(0, x)$ → passes positive values, blocks negatives
- **tanh:** outputs values between (-1,1), centered at 0

These functions allow the network to model complex, non-linear relationships.

---

### From Neuron to Neural Network

A single neuron is limited. To solve real problems, neurons are connected into layers:

1. **Input Layer**
   - First layer, takes raw data (e.g., pixel values of an image).  
   - Example: MNIST image (28 × 28 = 784 inputs).  

2. **Hidden Layers**
   - Each neuron receives outputs from previous neurons.
   - They apply weights, biases, and activations to build higher-level features.  
   - Example: first hidden layer detects edges, later layers combine edges into shapes.  

3. **Output Layer**
   - Final predictions (e.g., 10 neurons for digits 0–9).
   - The neuron with the highest activation = network’s decision.  

<img width="400" height="267" alt="image" src="https://github.com/user-attachments/assets/b7c873b2-d9f4-4fe3-bb03-bd2459878b30" />

### Forward Pass (Information Flow)
1. Input → multiplied by weights → summed with bias.  
2. Result passes through an activation function.  
3. Output flows to the next layer.
   
### Backpropagation (Learning)
- After a forward pass, compare prediction with the true label → compute **loss**.  
- Send the error backward → update weights and biases.  
- Repeat over many **epochs** until the model improves.
  
##An **epoch** means **one full pass through the entire training dataset**.

- If you have 60,000 training images (like MNIST),  
  then **1 epoch = the model sees all 60,000 images once**.  
- Training usually requires **multiple epochs** (e.g., 5, 10, 20).  
- With each epoch, the model improves by adjusting weights and biases using backpropagation.

---

## CHAP 3: Practical Implementation
### Google Colab

- Free cloud Jupyter environment from Google.
- Preinstalled with TensorFlow, NumPy.
- Free GPU acceleration.
- Runs in a browser, no setup required.

**Steps:**
1. Go to [Google Colab](https://colab.research.google.com)  
2. Sign in → New Notebook  
3. Run Python/TensorFlow code directly  
4. Saves automatically to Google Drive  

Enable GPU:  
- Runtime → Change runtime type → GPU  

### TensorFlow

- Open-source ML library by Google.
- `tf.keras`: High-level API for building and training networks.  
- `tf.lite`: For deploying lightweight models on embedded devices.

### MNIST Dataset
- 70,000 grayscale images of handwritten digits (0–9).
- 60,000 training + 10,000 testing samples.
- Each image: 28 × 28 pixels.
- Considered the "Hello World" of Deep Learning.
  
---

### Your First Neural Network in Code
#### Step 1: Import Libraries
```python
import tensorflow as tf
from tensorflow import keras
```

#### Step 2: Preprocess Data
```python
x_train = x_train.reshape(-1,784).astype("float32")/255
x_test = x_test.reshape(-1,784).astype("float32")/255
```

#### Step 3: Define the Model
```python
model = keras.Sequential([
    keras.layers.Dense(128, activation="relu", input_shape=(784,)),
    keras.layers.Dense(10, activation="softmax")
])
```

#### Step 4: Compile the Model
```python
model.compile(optimizer="adam",
              loss="sparse_categorical_crossentropy",
              metrics=["accuracy"])
```

#### Step 5: Train the Model
```python
model.fit(x_train, y_train, epochs=5, batch_size=32)
```

#### Step 6: Evaluate the Model
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
