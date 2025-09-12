
### Download bird sound and view waveform
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

### Removing the noise using high pass FIR
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


### Generating a spectrogram with Librosa
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
plt.colorbar (format ="%+2.0 f dB")
plt.title ("Spectrogram of Bird Sound")
plt.tight_layout ()
plt.show ()
```
<img width="957" height="390" alt="image" src="https://github.com/user-attachments/assets/ee392ce8-71d2-41ce-9783-66b6c6b50418" />

### Mel spec
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
plt.colorbar (format ="%+2.0 f dB")
plt.title ("Mel Spectrogram of Bird Sound")
plt.tight_layout ()
plt.show ()
```
<img width="957" height="390" alt="image" src="https://github.com/user-attachments/assets/07f5c520-e691-4884-a360-84663588e2f9" />

### MFCC
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
   ##### FFT 256
   ##### FFT 512
   ##### FFT 1024
  -
  
2. Compare the resolution of Mel filters in the low-frequency range versus the high-frequency range. Why does the Mel scale emphasize low frequencies more?

3. Extract MFCCs from the same bird sound using 13 coefficients and then 20 coefficients. Compare the feature sets.
   ##### 13 coefficients
   ##### 20 coefficients
   - 
4. Try different colormaps (gray_r, magma, viridis) for spectrogram visualization. Which one makes the patterns easiest to see?
   ##### gray_r
   ##### magma
   ##### viridis

----

## Reflection
1. Why does increasing FFT size improve frequency resolution but worsen time resolution?
2. Why are Mel spectrograms better aligned with human hearing than linear spectrograms?
3. Why are MFCCs popular in speech recognition, but sometimes less effective in bird sound analysis?
4. How might the choice of features (spectrogram vs. Mel vs. MFCC) affect neural network performance?
