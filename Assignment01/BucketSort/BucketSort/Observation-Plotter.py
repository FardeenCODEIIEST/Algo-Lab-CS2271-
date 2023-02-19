import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

uniform_dis = pd.read_csv('bucket_uniform_obs.csv')
normal_dis = pd.read_csv('bucket_normal_obs.csv')

n_uni = uniform_dis['Size'].to_numpy()
comp_uni = uniform_dis['Avg_Comparison'].to_numpy()
time_uni = uniform_dis['Avg_Time'].to_numpy()
comp_ratio_uni = comp_uni / (n_uni)
time_ratio_uni = time_uni / (n_uni)

n_nor = normal_dis['Size'].to_numpy()
comp_nor = normal_dis['Avg_Comparison'].to_numpy()
time_nor = normal_dis['Avg_Time'].to_numpy()
comp_ratio_nor = comp_nor / (n_nor)
time_ratio_nor = time_nor / (n_nor)

fig, axis = plt.subplots(2, 1)
fig.suptitle("Comparisons and Time Ratio for Bucket Sort")

# For comparison(Y)
axis[0].plot(comp_ratio_uni, 'o-', label='Uniform_Dis')
axis[0].plot(comp_ratio_nor, 'o--', label='Normal_Dis')
axis[0].legend()
axis[0].set_ylabel(r'$\frac{Avg Comparisons}{n}$', rotation=0)

# For time(Y)
axis[1].plot(time_ratio_uni, 'o-', label='Uniform_Dis')
axis[1].plot(time_ratio_nor, 'o--', label='Normal_Dis')
axis[1].legend()
axis[1].set_ylabel(r'$\frac{Avg Time}{n}$', rotation=0, labelpad=15)

# For size(X)
plt.xlabel(r'n [array size = $2^n$]')
plt.show()