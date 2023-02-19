import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

uni_dis = pd.read_csv('MOM_uniform_part_5_obs.csv')
nor_dis = pd.read_csv('MOM_normal_part_5_obs.csv')

n_uni = uni_dis['Size'].to_numpy()
parti_uni = uni_dis['Avg Partition Size'].to_numpy()

n_nor = nor_dis['Size'].to_numpy()
parti_nor = nor_dis['Avg Partition Size'].to_numpy()

plt.figure(figsize=(10, 10))
plt.plot(n_uni, parti_uni / n_uni, '.', label='Uniform')
plt.plot(n_nor, parti_nor / n_nor, '.', label='Normal')
plt.legend()
plt.xlabel('Array Size(n)')
plt.ylabel(r'$\frac{Partitions}{n}$', labelpad=20)
plt.title('Partition Size vs Array Size in MOM with divide size 5')
plt.show()
