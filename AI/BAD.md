# Training a Bird Activity Detection (BAD) Model

## Exercises
### 1. Replace freefield1010 with warblrb to train the CNN. Is the accuracy improved or worsened?
  #### freefield1010<img width="1036" height="391" alt="image" src="https://github.com/user-attachments/assets/9e630625-ce23-47c5-afe9-c82fb279af44" />
  - Size: 7,690 excerpts.
  - Source: Extracted from Freesound community recordings.
  - Scope: Worldwide — many countries, diverse environments.
  - Annotation: Binary (bird present / not).
  - Noise: Less structured, more general field recordings.
  - DATASET_URL = "https://archive.org/download/ff1010bird/ff1010bird_wav.zip"
  - METADATA_URL = "https://ndownloader.figshare.com/files/10853303"
  #### warblrb <img width="1037" height="393" alt="image" src="https://github.com/user-attachments/assets/c33f6b2a-c8a9-4ec8-a808-fc1e19a33369" />
  - Size: 8,000 smartphone recordings.
  - Source: Uploaded by Warblr app users.
  - Scope: UK-specific.
  - Noise: Includes weather, traffic, human speech, and even bird imitations.
  - Annotation: Bird present / not.
  - DATASET_URL = "https://archive.org/download/warblrb10k_public/warblrb10k_public_wav.zip"
  - METADATA_URL = "https://ndownloader.figshare.com/files/6035817"

  ### 2. Use the TinyChirp dataset to train the CNN. This dataset has fixed train/validate/test splits. What kind of modifications are needed to properly train your CNN? <img width="1704" height="369" alt="image" src="https://github.com/user-attachments/assets/7d9ade28-3cb3-4cbb-933b-edd7c9481258" />

- **Modify the dataset source**. Replace FreeField1010 with the TinyChirp dataset, which can be downloaded using:
  
```python
import kagglehub

# Download latest version
path = kagglehub.dataset_download("zhaolanhuang/tinychirp")

print("Path to dataset files:", path)
```
  - **Use fixed splits**. TinyChirp already provides `training/`, `validation/`, and `testing/` folders with `target/` (bird) and `non_target/` (no-bird), so `train_test_split` is not needed.

- **Label assignment**. Labels are determined directly from the folder structure (`target = 1`, `non_target = 0`) instead of using a metadata CSV file.
- **Result**: The TinyChirp dataset gives higher accuracy compared to FreeField1010 because of its cleaner recordings and standardized splits.

### 3. Load a few audio files and plot their waveforms and Mel spectrograms side by side. Describe what differences you observe between bird and non-bird clips.
#### Bird clips
<img width="495" height="295" alt="image" src="https://github.com/user-attachments/assets/01533739-8e05-4626-bd63-fa1e0921a9d1" />

- Short, sharp bursts of sound with noticeable peaks (chirps, whistles).
- Clear vertical structures (harmonics) and strong energy concentrated in specific frequency bands (often 2–8 kHz).
  
#### Non-bird clips
<img width="495" height="295" alt="image" src="https://github.com/user-attachments/assets/a8f4e5e5-2eb6-4bc9-a3e6-4d4eb75ab207" />

- More continuous or flat signals (wind, background noise, silence).
- More diffuse energy, spread across frequencies, often without a clear harmonic structure.

### 4. Add another convolutional layer to the CNN. What happens the accuracy? Can we keep on adding layers?
#### Original<img width="1003" height="391" alt="image" src="https://github.com/user-attachments/assets/638d086d-7616-4a98-a0d7-d294655fdf2b" />

#### Add a third Conv2D<img width="1146" height="437" alt="image" src="https://github.com/user-attachments/assets/514e101d-fdb2-445f-8df5-6256c29537f1" />

- Accuracy increases because the model can capture more complex patterns from the audio features.
- Not always necessary to keep adding layers – while accuracy can increase, each new layer also increases model size, training time, and the risk of overfitting.
- Beyond a certain point, validation accuracy may even drop due to overfitting.
