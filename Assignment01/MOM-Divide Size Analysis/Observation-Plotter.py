import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

obs = pd.read_csv('Observation.csv')

Div_Size = obs['Divide Size'].to_numpy()
Avg_Time = obs['Avg Time'].to_numpy()

plt.figure(figsize=(10, 10))
plt.plot(Div_Size, Avg_Time, '.-')
plt.xlabel('Divide Size')
plt.ylabel('Average Time Taken in ms', labelpad=40)
plt.title('MOM Divide Size Analysis')
plt.show()