import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

# Reading the respective observation files
uniform_dis = pd.read_csv('uniform_distribution_obs_quick_maxsize.csv')
normal_dis = pd.read_csv('normal_distribution_obs_quick_maxsize.csv')

#For uniform
n_uniform = uniform_dis['Size'].to_numpy()
comparison_uniform = uniform_dis['Avg_Comparisons'].to_numpy()
time_uniform = uniform_dis['Avg_Time_Taken'].to_numpy()
comp_uni_ratio = 10 * comparison_uniform / (n_uniform * np.log2(n_uniform))
time_uni_ratio = 10 * time_uniform / (n_uniform * np.log2(n_uniform))

#For Normal
n_normal = normal_dis['Size'].to_numpy()
comparison_normal = normal_dis['Avg_Comparisons'].to_numpy()
time_normal = normal_dis['Avg_Time_Taken'].to_numpy()
comp_nor_ratio = 10 * comparison_normal / (n_normal * np.log2(n_normal))
time_nor_ratio = 10 * time_normal / (n_normal * np.log2(n_normal))

fig, axis = plt.subplots(2, 1, figsize=(8, 5))
fig.suptitle(
    "Comparisons and Time Ratio for Quick Sort (Taking Max. size first)")

# For comparison(Y)
axis[0].plot(comp_uni_ratio, 'o-', label='Uniform_Dis')
axis[0].plot(comp_nor_ratio, 'o--', label='Normal_Dis')
axis[0].legend()
axis[0].set_ylabel(r'$\frac{Avg Comparisons}{n*logn}$',
                   rotation=0,
                   labelpad=28)

# For time(Y)
axis[1].plot(time_uni_ratio, 'o-', label='Uniform_Dis')
axis[1].plot(time_nor_ratio, 'o--', label='Normal_Dis')
axis[1].legend()
axis[1].set_ylabel(r'$\frac{Avg Time}{n*logn}$', rotation=0, labelpad=18)

# For size(X)
plt.xlabel(r'n [array size = $2^n$]')
plt.show()