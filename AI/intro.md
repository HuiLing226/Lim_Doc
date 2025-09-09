# AI introduction

## Machine Learning (ML) vs Deep Learning (DL)

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


## Deep Learning vs Convolutional Neural Networks (CNN)

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
