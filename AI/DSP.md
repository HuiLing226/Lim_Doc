# DSP for Audio


## Chap 1: Audio Signal Basics
- An audio signal is a continuous pressure wave in air.
- To process digitally, it is converted into numbers through **sampling** and **quantization**.
- **Sampling rate** = number of samples per second.
  - Example: 16 kHz → 16,000 samples/sec.
- **Bit depth** = number of bits per sample.
  - Example: 16-bit → values from −32768 to +32767.
- **Nyquist theorem**: sampling rate ≥ 2 × maximum frequency of interest.
  - For bird sounds (approx around 1k - 8kHz):
  - Common: 16 kHz or 22.05 kHz.

#### Download bird sound and view waveform
```python
import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import requests

# Download bird sound from Xeno - Canto
url = "https://xeno-canto.org/175830/download"
filename = "xc175830.mp3"

r = requests.get(url)
with open (filename, "wb") as f:
  f.write (r.content)

# Load audio with librosa
y , sr = librosa.load (filename , sr =16000)

# Plot waveform (time domain)
plt.figure (figsize =(10 , 3))
librosa.display . waveshow (y , sr = sr)
plt.title ("Waveform in Time Domain (Bird Sound)")
plt.xlabel ("Time (s)")
plt.ylabel ("Amplitude")
plt.show ()
```
The output is shown below: <img width="505" height="188" alt="image" src="https://github.com/user-attachments/assets/035ea055-4704-48b3-95ea-1860dbb3d70b" />

---
## Chap 2: Fundamental DSP Algorithms

Before extracting features from audio, we need to understand basic DSP concepts such as **filtering** and **convolution**.  These operations help remove noise, emphasize relevant signal components, and prepare the audio for feature extraction.


#### Removing the noise using high pass FIR
```python
import requests
import librosa
import numpy as np
import matplotlib.pyplot as plt
import scipy.signal as signal

# --- Step 1: Download audio ---
url = "https://xeno-canto.org/175830/download"
filename = "xc175830.mp3"

try :
  with open (filename,"rb") as f:
    print (f"{filename} already exists , skipping download .")
except FileNotFoundError :
  print (f" Downloading {filename}... ")
r = requests.get(url)
with open (filename , "wb") as f:
  f.write (r.content)
print (" Download complete.")

# --- Step 2: Load audio ---
y , sr = librosa.load (filename , sr =16000)
print (f"Audio loaded : {y.shape [0]} samples at {sr} Hz")

# --- Step 3: Apply FIR band - pass filter (300 Hz - 5000 Hz) ---
nyquist = sr / 2
low_cut = 300 / nyquist
high_cut = 5000 / nyquist
numtaps = 101 # number of FIR coefficients
fir_coeff = signal.firwin(numtaps, [low_cut, high_cut], pass_zero=False )
y_filtered = signal.lfilter(fir_coeff, [1.0], y)

# --- Step 4: Plot original and filtered waveform ---
plt.figure ( figsize =(12 , 4) )
plt.subplot (2 , 1 , 1)
plt.plot ( y)
plt.title (" Original Bird Sound Waveform ")
plt.ylabel (" Amplitude ")
plt.subplot (2 , 1 , 2)
plt.plot ( y_filtered )
plt.title (" Filtered Bird Sound (300 -5000 Hz)")
plt.xlabel (" Sample ")
plt.ylabel (" Amplitude ")
plt.tight_layout ()
plt.show ()
```
<img width="765" height="312" alt="image" src="https://github.com/user-attachments/assets/e0127741-6e0d-402a-b370-7440ed062514" />


---
## Chap 3: Fourier Transform and Spectrograms
After digital audio signals and basic filtering, the next step is analyzing audio in the frequency domain using Fourier transforms. 

#### **Fourier Transform**: Converts audio from time domain → frequency domain.
  - **DFT (Discrete Fourier Transform)**:  
  Formula:  
  $$X[k] = \sum_{n=0}^{N-1} x[n] e^{-j2πkn/N}, \quad k = 0,1,...,N-1$$
  - **FFT (Fast Fourier Transform)**: Efficient algorithm for computing DFT.

#### Windowing and STFT
- Audio is **non-stationary** (frequency changes over time).  
- Split signal into overlapping frames + apply FFT.  
- This is the **Short-Time Fourier Transform (STFT) (standard spectrogram)**.  

#### Spectrogram
- A 2D map built by stacking STFT frames.  
  - **X-axis**: Time  
  - **Y-axis**: Frequency  
  - **Color/Intensity**: Energy of frequencies  
- Spectrograms = image-like representation of sound.  
  - Useful for CNNs → can detect **harmonics, chirps, bird calls**.  
- Visualization uses colormaps (e.g., `gray_r`, `magma`, `viridis`).

#### Generating code for STFT spectrogram 
```python
import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np
import requests

# Download and save the bird sound (Xeno - Canto )
url = "https://xeno-canto.org/175830/download"
filename = "xc175830.mp3"
r = requests.get(url)
with open (filename , "wb") as f:
  f.write (r.content)

# Load the audio
y , sr = librosa.load (filename , sr =16000)

# Compute STFT
D = librosa.stft (y, n_fft =1024, hop_length =512)
S_db = librosa.amplitude_to_db(abs (D), ref=np.max)

# Plot spectrogram
plt.figure(figsize=(10, 4))
librosa.display.specshow(S_db, sr =sr , hop_length =512 ,
x_axis ='time', y_axis ='hz', cmap ='viridis')
plt.colorbar (format ="%+2.0f dB")
plt.title ("Spectrogram of Bird Sound")
plt.tight_layout ()
plt.show ()
```
<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/2d592888-c139-489a-9d36-7a5dce7c951a" />



---

## Chap 4: Mel Filter Bank
- Human/bird hearing is non-linear: better resolution at low frequencies.
- Apply **Mel filter bank** to spectrogram:
  - Apply triangular filters on FFT bins, spaced by Mel scale.
    - Lower frequencies → **narrower bands**
    - Higher frequencies → **wider bands**  
  - Each filter sums energy from its band → **Mel spectrogram**.  

#### Conversions
- **Hz → Mel**:  
  $$m = 2595 \cdot \log_{10}\left(1 + \frac{f}{700}\right)$$
- **Mel → Hz**:  
  $$f = 700 \cdot \left(10^{m/2595} - 1\right)$$

#### Why Mel Spectrograms Matter
- Compact and perceptually meaningful representation.  
- Lower dimensionality vs raw FFT spectrograms.  
- Retains patterns crucial for **speech and bird sound classification**.  


#### Generating code for Mel spectrogram
```python
import librosa
import librosa.display
import matplotlib.pyplot as plt
import numpy as np

# Load the audio
y , sr = librosa.load ("xc175830.mp3", sr =16000)

# Compute Mel spectrogram (Librosa >=0.10 requires keyword arguments)
S = librosa.feature.melspectrogram (y=y, sr =sr, n_fft=1024, hop_length=512,
n_mels=64, fmin=300, fmax=8000)
S_db = librosa.power_to_db (S , ref=np.max)

# Plot Mel spectrogram
plt.figure(figsize=(10, 4))
librosa.display.specshow(S_db, sr =sr , hop_length =512 , x_axis ='time', y_axis ='hz', cmap ='viridis')
plt.colorbar (format ="%+2.0f dB")
plt.title ("Mel Spectrogram of Bird Sound")
plt.tight_layout ()
plt.show ()
```
<img width="957" height="390" alt="image" src="https://github.com/user-attachments/assets/07f5c520-e691-4884-a360-84663588e2f9" />

---
## Chap 5: Feature Extraction with MFCCs

- **MFCCs (Mel-Frequency Cepstral Coefficients)**:  
  - Compact representation of sound.  
  - Capture **timbre** (spectral shape) rather than raw frequency detail.  

#### Step-by-Step Computation
1. Compute **STFT** → magnitude spectrum.  
2. Apply **Mel filter bank** → Mel energies.  
3. Take **logarithm** of Mel energies.  
4. Apply **DCT** → keep 12–13 coefficients per frame. 


#### Generating code for MFCCs
```python
import librosa
import librosa.display
import matplotlib.pyplot as plt

y , sr = librosa.load ("xc175830.mp3", sr =16000)

# Compute MFCCs
mfccs = librosa.feature.mfcc (y=y, sr=sr, n_mfcc=13, n_fft=1024, hop_length=512)

# Plot MFFCs
plt.figure(figsize=(10, 4))
librosa.display.specshow(mfccs, x_axis ='time', sr =sr, hop_length=512, cmap='coolwarm')
plt.colorbar ()
plt.title ("MFCCs of Bird Sound")
plt.tight_layout ()
plt.show ()
```
<img width="907" height="390" alt="image" src="https://github.com/user-attachments/assets/2efd3306-b07b-452f-9a4d-ab09fc76c536" />


--- 
## Exercises
1. Generate a spectrogram of a bird sound with different FFT sizes (e.g., 256, 512,
1024). Compare the time–frequency resolution.
   ##### FFT 256<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/8505850d-9180-4ed6-9f78-6c93bf0d0f0c" />

   ##### FFT 512<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/95643020-bdee-4c64-9885-5bcf4549ad3c" />

   ##### FFT 1024<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/e1ddccd8-eb30-4648-bcad-7712682b23f6" />

   ##### Time–Frequency Resolution Comparison

  | Window Size | Time Resolution | Frequency Resolution | Characteristics |
|----------------------|-----------------|----------------------|-----------------|
  | Short (fft 256)      | High (sharp in time, good for onsets) | Low (blurry frequency bands) | Clear timing of syllables, but pitch/harmonics less precise |
  | Medium (fft 512)     | Moderate        | Moderate             | Balanced view of time and frequency |
  | Long (fft 1024)      | Low (harder to detect fast syllables) | High (clear frequency details, harmonics visible) | Good pitch/harmonic resolution, but temporal smearing |


2. Compare the resolution of Mel filters in the low-frequency range versus the high-frequency range. Why does the Mel scale emphasize low frequencies more?
  - Low frequency → more filters → higher resolution → can distinguish small pitch differences.
  - High frequency → fewer filters → lower resolution → details are “compressed” together.
  - Mel scale emphasizes low frequencies because:
    - Human ears are more sensitive to pitch changes at low frequencies (below ~1 kHz).
    - At high frequencies, our perception is less precise — we can’t distinguish small differences as well.

    
3. Extract MFCCs from the same bird sound using 13 coefficients and then 20 coefficients. Compare the feature sets.
   ##### 13 coefficients<img width="907" height="390" alt="image" src="https://github.com/user-attachments/assets/02462b46-46f1-4f04-89bf-4e82d26200a8" />

   ##### 20 coefficients<img width="907" height="390" alt="image" src="https://github.com/user-attachments/assets/ca3ae1f4-26f2-4ff7-a0a3-5403bb0a38b0" />

   ##### Comparison of MFCC Feature Sets

| Aspect                  | First MFCC Set                               | Second MFCC Set                              |
|--------------------------|-----------------------------------------------|-----------------------------------------------|
| **Low-frequency bands** | Stronger variation, intense negative values (−400 to −450), more irregular patterns | Still strong, but smoother and more consistent |
| **High-frequency bands**| Noisier, less distinct structure              | More stable, clearer separation                |
| **Temporal consistency**| Fluctuates erratically, irregular patches     | Smoother, with clearer band-like patterns      |
| **Noise level**         | Higher noise, possibly less pre-processing    | Lower noise, may include filtering or normalization |
| **Overall structure**   | Appears chaotic, less interpretable features  | More structured and interpretable features     |



  
4. Try different colormaps (gray_r, magma, viridis) for spectrogram visualization. Which one makes the patterns easiest to see?
   ##### gray_r<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/4edc25b4-c8c5-481b-81ad-8d69574708f2" />

   ##### magma<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/be8e36ea-6a95-428f-a995-14e0b584cfb6" />

   ##### viridis<img width="924" height="390" alt="image" src="https://github.com/user-attachments/assets/e1ddccd8-eb30-4648-bcad-7712682b23f6" />

   ##### Colormap Comparison for Spectrogram Visualization

| Colormap   | Characteristics                                                                 | Ease of Seeing Patterns |
|------------|---------------------------------------------------------------------------------|--------------------------|
| **gray_r** | Reversed grayscale. Dark = strong energy, light = weak. Standard in audio work. | Clear and familiar, good for quick interpretation. |
| **magma**  | Perceptually uniform. Dark purple → yellow. Highlights subtle intensity changes. | Excellent for fine detail, great for distinguishing harmonics. |
| **viridis**| Perceptually uniform and colorblind-friendly. Dark blue → green → yellow.        | Strong contrast, good separation of frequency bands and intensities. |


