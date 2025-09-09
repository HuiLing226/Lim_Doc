# AI introduction

## Chap 1: Machine Learning (ML) vs Deep Learning (DL)

### Machine Learning (ML)
- Human extracts features (color, shape, texture).
- Algorithm (e.g., SVM, Decision Tree) learns from features.
- Works well with smaller datasets.
- Example: Classify food if it’s *burger* or *fried chicken* based on manually chosen features.

### Deep Learning (DL)
- Uses neural networks with many hidden layers.
- Learns features automatically from raw data.
- Requires large datasets and compute power.
- Example: Input raw food images → CNN automatically learns buns, chicken texture, etc.

### Key Differences

| Aspect              | Machine Learning             | Deep Learning                      |
|---------------------|------------------------------|------------------------------------|
| Feature extraction  | Manual, human-designed       | Automatic, learned by the network  |
| Complexity          | Simple models, small data    | Complex models, large data         |
| Interpretability    | Easy to understand           | More like a “black box”            |
| Use cases           | Spam detection, regression   | Image/audio recognition, NLP       |

---

## Chap 2: Structure of a Simple Neural Network

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

## Chap 3: How a Neuron Works

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

## Chap 4: Deep Learning vs Convolutional Neural Networks (CNN)

### Deep Learning (DL)
- General term for using deep (multi-layer) neural networks.
- Fully connected layers: every input neuron connects to every neuron in next layer.
- Works but becomes inefficient for large images.

### Convolutional Neural Networks (CNN)
- Special type of DL designed for image/audio data.
- Uses **convolutions** instead of full connections.
- Convolutional filters detect local patterns (edges, textures, shapes).
- Pooling layers reduce size while keeping features.
- Final dense layer does classification.

### Why CNN for Audio (Spectrograms)?
- Spectrograms are like images (time vs frequency).
- CNN can learn:
  - Low-level features (edges, harmonics).
  - Mid-level features (chirps, patterns).
  - High-level features (bird species).
