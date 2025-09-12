# Deploying a Neural Network to an MCU (STM32)

Once you have trained a neural network (e.g., MNIST in Google Colab), the next step is to **deploy it on a microcontroller**.  

---

## Step 1: Train and Export Your Model
- Train your model in Google Colab or locally using TensorFlow/Keras.  
- Save it in the `.h5` format:

```python
model.save("mnist_model.h5")
```

<img width="1879" height="1022" alt="image" src="https://github.com/user-attachments/assets/a6af3f08-c91b-4b17-8f80-5c3f3173a08f" />

<img width="1571" height="867" alt="image" src="https://github.com/user-attachments/assets/4a955311-3abf-47d0-bcaa-38dda6820475" />

<img width="984" height="717" alt="image" src="https://github.com/user-attachments/assets/b639dd52-9c34-4eab-aa8c-c7b08347b23c" />
<img width="1879" height="1022" alt="image" src="https://github.com/user-attachments/assets/637a598e-70a9-4fbf-bae0-6332d85d92d0" />
<img width="1879" height="1022" alt="image" src="https://github.com/user-attachments/assets/b62d2235-40bf-489c-bf6b-be2a29d2f2d7" />

<img width="1306" height="113" alt="image" src="https://github.com/user-attachments/assets/87e1a7ae-dcb4-4ace-88a9-05c90ca30db2" />
<img width="1309" height="617" alt="image" src="https://github.com/user-attachments/assets/f4d433a7-780b-460f-88bd-8281fab21604" />
