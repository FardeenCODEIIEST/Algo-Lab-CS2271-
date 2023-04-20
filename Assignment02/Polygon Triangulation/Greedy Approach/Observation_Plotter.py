import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

dis1 = pd.read_csv('ObservationDP.csv')
dis2 = pd.read_csv('ObservationGreedy.csv')

gr = dis2['Avg.Time Taken'].to_numpy()
dp = dis1['Avg.Time Taken'].to_numpy()
n1 = dis1['Vertices'].to_numpy()
n2 = dis2['Vertices'].to_numpy()

plt.figure(figsize=(10, 25))

plt.title('Greedy vs Dynamic Programming')

plt.plot(n1, gr, 'o-', label='Greedy')
plt.plot(n2, dp, 'o-', label='DP')
plt.legend()

plt.xlabel('Number of vertices')
plt.ylabel('Avg Time Taken in ms', labelpad=40, rotation=0)

plt.show()