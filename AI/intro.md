# Introduction


## Traditional Programming
- Humans explicitly write the rules.
- Program follows: **IF condition → THEN action**.
- Works well for simple, well-defined problems.
- Example: “If temperature > 30°C, turn on fan.”

---

## Machine Learning (ML)
- Humans provide **examples (data + labels)** instead of rules.
- Algorithm learns patterns and rules by itself to make predictions.
- Needs **feature engineering** (humans decide which features are important).
- Suitable when rules are too complex to define manually.
- Example: Train a classifier on labeled images of cats vs dogs.

---

## Deep Learning (DL)
- Subset of ML using **multi-layer neural networks**.
- Learns features **automatically from raw data**.
- Handles very complex data (images, audio, text).
- Needs more data and computation.
- Example: Input raw bird images → CNN automatically detects edges, shapes, feathers → predicts species.

---

## Comparison Table
 

| Aspect               | Traditional Programming                               | Machine Learning                                               | Deep Learning                                      |
|-----------------------|-------------------------------------------------------|----------------------------------------------------------------|---------------------------------------------------|
| **Approach**          | Explicit rules written by humans                      | Learns from data with labeled examples                         | Learns features automatically from raw data        |
| **Data dependency**   | Low – depends on programmer’s logic                   | High – quality/quantity of data determines performance         | Very high – requires large datasets to generalize  |
| **Flexibility**       | Low – code must be updated manually                   | Moderate – retrain model with new data                         | High – retrain large models, can adapt automatically |
| **Problem complexity**| Best for simple, deterministic logic                  | Good for complex patterns (NLP, analytics)                     | Best for highly complex data (vision, speech, audio)|
| **Development**       | Linear & predictable (design → code → debug)          | Iterative (train → evaluate → tune)                            | Iterative, compute-intensive, experimental          |
| **Outcome**           | Predictable if inputs + rules are known               | May be less interpretable (depends on algorithm)                | Often “black box” – low interpretability            |**Best for**        | Simple, rule-based tasks           | Structured data with clear features      | Complex data (images, speech, audio)    |

