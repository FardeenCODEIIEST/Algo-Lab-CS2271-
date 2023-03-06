import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

dis = pd.read_csv('ObservationBruteForce.csv')

time = dis['Avg.Time Taken'].to_numpy()
n = dis['Vertices'].to_numpy()

plt.figure(figsize=(10, 20))

plt.title('Average Time Taken Brute Force')

plt.plot(n, time, 'o-', label='Brute Force')
plt.legend()

plt.xlabel('Number of vertices')
plt.ylabel('Average Time Taken in ms', rotation=0, labelpad=40)

plt.show()