# Training a Species Classifier

The initial implementation (using the code inside the module) attempted to load the entire dataset into memory before training. Each `.wav` audio file was converted into a Mel-spectrogram and stored inside NumPy arrays, as shown below:
```python
X.append(mel_image)
y.append(class_idx)
...
return np.array(X), np.array(y)
```
- While this approach is straightforward, it quickly becomes inefficient when dealing with large datasets. 
- In this case, the dataset contained over 8,000 audio samples, each converted to a spectrogram of size `(224, 224, 3)` using the float32 data type, this required more than 4.6 GB of RAM just to hold the data in memory. 
- On typical laptops with 8–16 GB of RAM, this caused `MemoryError` crashes and made the training process fail before it could even start.

#### Solution: using `tf.data.Dataset` API to create an on-the-fly data pipeline
Instead of precomputing all spectrograms, each audio file is:
- Read from disk only when needed.
- Converted to a Mel-spectrogram on the fly.
- Fed into the model in small batches (e.g. 32 samples).
  ##### Example
  ```python
  dataset = tf.data.Dataset.from_tensor_slices((paths, labels))
  dataset = dataset.map(preprocess_file, num_parallel_calls=tf.data.AUTOTUNE)
  dataset = dataset.batch(batch_size).prefetch(tf.data.AUTOTUNE)
  ```
- This ensures that only **a single batch is kept in memory at any time**, reducing RAM usage drastically and enabling training to start immediately without waiting to load the entire dataset.

#### ## The full modified Python script implementing this memory-efficient data loading approach can be found [here](https://github.com/HuiLing226/Lim_Doc/blob/da058006d96ac7d6283e28457b0bb8b18b7ced84/AI/.py/species_modified.py).
---

## Exercises
  1. Replace the SEAbird dataset with Putra dataset from UPM: https://drive.google.com/drive/folders/1HvR_sbEx5rzWjgTWkyjplUXgzsQkEgzH?usp=sharing.
  2. Copy the code and dataset to your laptop, convert script to regular Python (.py) and run locally.
  3. Convert the trained model to TensorFlow Lite (.tflite format)
  4. Experiment with different pre-trained models (VGG16, ResNet50, EfficientNet) instead of MobileNetV3 and compare their performance on the seabird classification task.
  5. Implement audio data augmentation techniques (pitch shifting, time stretching, background noise addition) and measure the impact on model generalization and test accuracy.
