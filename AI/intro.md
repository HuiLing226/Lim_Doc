# AI introduction

## Traditional Programming vs Machine Learning vs Deep Learning

### Traditional Programming
- Humans explicitly write the rules.
- Program follows: **IF condition → THEN action**.
- Works well for simple, well-defined problems.
- Example: “If temperature > 30°C, turn on fan.”

---

### Machine Learning (ML)
- Humans provide **examples (data + labels)** instead of rules.
- Algorithm learns patterns and rules by itself.
- Needs **feature engineering** (humans decide which features are important).
- Example: Feed a classifier features like *beak length, feather color* → predicts bird species.

---

### Deep Learning (DL)
- Subset of ML using **multi-layer neural networks**.
- Learns features **automatically from raw data**.
- Handles very complex data (images, audio, text).
- Needs more data and computation.
- Example: Input raw bird images → CNN automatically detects edges, shapes, feathers → predicts species.

---

### Quick Comparison Table

| Aspect              | Traditional Programming            | Machine Learning                        | Deep Learning                          |
|---------------------|------------------------------------|-----------------------------------------|----------------------------------------|
| **Rules**           | Written by humans                  | Learned from data (with labels)          | Learned from raw data                   |
| **Feature extraction** | Not needed (rules coded)           | Manual (handcrafted by humans)           | Automatic (learned by network)          |
| **Data needs**      | Low                                | Moderate                                 | Very high (big data)                   |
| **Computation**     | Lightweight                        | Moderate                                 | Heavy (needs GPU/optimized hardware)    |
| **Best for**        | Simple, rule-based tasks           | Structured data with clear features      | Complex data (images, speech, audio)    |
