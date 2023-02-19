import numpy as np  # for arrays
import matplotlib.pyplot as plt  # for plotting
import pandas as pd

df = pd.read_csv('normalized_uniform_distribution.csv')

plt.figure(figsize=(10, 10))
plt.xlabel("Number")
plt.ylabel("Frequency")
plt.hist(df['value'].to_numpy(), bins=101)
plt.title("Histogram of Normalised-Uniform Dataset")
plt.show()
