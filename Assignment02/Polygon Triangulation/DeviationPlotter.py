import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

dis = pd.read_csv('DeviationObs.csv')

n = dis['Vertices'].to_numpy()
dev = dis['Avg. Deviation'].to_numpy()

plt.figure(figsize=(10, 25))

plt.title('Greedy and DP Offset')

plt.plot(n, dev, 'o-', label='Offset')
plt.legend()

plt.xlabel('Number of vertices')
plt.ylabel('Greedy result offset', labelpad=40, rotation=0)

plt.show()