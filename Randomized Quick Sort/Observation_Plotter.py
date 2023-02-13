import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

uni_dis = pd.read_csv('uniform_distribution_obs_quick.csv')
ran_uni_dis = pd.read_csv('uniform_distribution_obs_quick_random.csv')
ran_nor_dis = pd.read_csv('normal_distribution_obs_quick_random.csv')
nor_dis = pd.read_csv('normal_distribution_obs_quick.csv')

#Uniform
n_uni = uni_dis['Size'].to_numpy()
comp_n_uni = uni_dis['Avg_Comparisons'].to_numpy()
time_n_uni = uni_dis['Avg_Time_Taken'].to_numpy()
ratio_time_n_uni = time_n_uni / (n_uni * np.log2(n_uni))
ratio_comp_n_uni = comp_n_uni / (n_uni * np.log2(n_uni))

#Random-Uniform
ran_n_uni = ran_uni_dis['Size'].to_numpy()
ran_comp_n_uni = ran_uni_dis['Avg_Comparisons'].to_numpy()
ran_time_n_uni = ran_uni_dis['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_uni = ran_time_n_uni / (ran_n_uni * np.log2(ran_n_uni))
ratio_ran_comp_n_uni = ran_comp_n_uni / (ran_n_uni * np.log2(ran_n_uni))

#Normal
n_nor = nor_dis['Size'].to_numpy()
comp_n_nor = nor_dis['Avg_Comparisons'].to_numpy()
time_n_nor = nor_dis['Avg_Time_Taken'].to_numpy()
ratio_time_n_nor = time_n_nor / (n_nor * np.log2(n_nor))
ratio_comp_n_nor = comp_n_nor / (n_nor * np.log2(n_nor))

#Random Normal
ran_n_nor = ran_nor_dis['Size'].to_numpy()
ran_comp_n_nor = ran_nor_dis['Avg_Comparisons'].to_numpy()
ran_time_n_nor = ran_nor_dis['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_nor = ran_time_n_nor / (ran_n_nor * np.log2(ran_n_nor))
ratio_ran_comp_n_nor = ran_comp_n_nor / (ran_n_nor * np.log2(ran_n_nor))

fig, axis = plt.subplots(2, 1, figsize=(10, 10))

fig.suptitle("Comparison and Time Ratio for Quick Sort Randomized Partitions")

axis[0].plot(ratio_comp_n_uni, 'o-', label='Uniform')
axis[0].plot(ratio_ran_comp_n_uni, 'o--', label='Random Uniform')
axis[0].plot(ratio_comp_n_nor, 'o-', label='Normal')
axis[0].plot(ratio_ran_comp_n_nor, 'o--', label='Random Normal')
axis[0].legend()
axis[0].set_ylabel(r'$\frac{Avg. Comparisons}{n*lgn}$',
                   rotation=0,
                   labelpad=30)

axis[1].plot(ratio_time_n_uni, 'o-', label='Uniform')
axis[1].plot(ratio_ran_time_n_uni, 'o--', label='Random Uniform')
axis[1].plot(ratio_time_n_nor, 'o-', label='Normal')
axis[1].plot(ratio_ran_time_n_nor, 'o--', label='Random Normal')
axis[1].legend()
axis[1].set_ylabel(r'$\frac{Avg.Time}{n*lgn}$', rotation=0, labelpad=16)

plt.xlabel(r'n [array size = $2^n$]')

plt.show()
