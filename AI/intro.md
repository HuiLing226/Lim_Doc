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
### Comparison Table
 

| Aspect               | Traditional Programming                               | Machine Learning                                                                           |
|-----------------------|-------------------------------------------------------|----------------------------------------------------------------|
| **Approach**          | Explicit rules written by humans                      | Learns from data with labeled examples                         |
| **Data dependency**   | Low – depends on programmer’s logic                   | High – quality/quantity of data determines performance          |
| **Flexibility**       | Low – code must be updated manually                   | Moderate – retrain model with new data                          |
| **Problem complexity**| Best for simple, deterministic logic                  | Good for complex patterns (NLP, analytics)                    |
| **Development**       | Linear & predictable (design → code → debug)          | Iterative (train → evaluate → tune)                               |
| **Outcome**           | Predictable if inputs + rules are known               | May be less interpretable (depends on algorithm)                    |**Best for**        | Simple, rule-based tasks           | Structured data with clear features      | 
<img width="425" height="316" alt="image" src="https://github.com/user-attachments/assets/ef08ebfc-e318-4f3b-a22a-b1f5608d825f" />

--- 

## Deep Learning (DL)
- Subset of ML using **multi-layer neural networks**.
- Learns features **automatically from raw data**.
- Handles very complex data (images, audio, text).
- Needs more data and computation.
- Example: Input raw bird images → CNN automatically detects edges, shapes, feathers → predicts species.

---

The hierarchy relationship is shown below, which will be discussed in the next chapter:
<img width="537.6" height="472.5" alt="image" src="https://github.com/user-attachments/assets/37fb05cd-1772-4471-a0f5-bcbc2f0399e5" />
