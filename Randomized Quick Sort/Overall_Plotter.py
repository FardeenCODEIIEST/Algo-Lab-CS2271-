import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

ran_uni_dis = pd.read_csv('uniform_distribution_obs_quick_random.csv')
ran_uni_dis_1000 = pd.read_csv('uniform_distribution_obs_quick_1_1000.csv')
ran_uni_dis_5000 = pd.read_csv('uniform_distribution_obs_quick_1_5000.csv')
ran_uni_dis_10000 = pd.read_csv('uniform_distribution_obs_quick_1_10000.csv')
ran_nor_dis = pd.read_csv('normal_distribution_obs_quick_random.csv')
ran_nor_dis_1000 = pd.read_csv('normal_distribution_obs_quick_1_1000.csv')
ran_nor_dis_5000 = pd.read_csv('normal_distribution_obs_quick_1_5000.csv')
ran_nor_dis_10000 = pd.read_csv('normal_distribution_obs_quick_1_10000.csv')

#Random-Uniform
ran_n_uni = ran_uni_dis['Size'].to_numpy()
ran_comp_n_uni = ran_uni_dis['Avg_Comparisons'].to_numpy()
ran_time_n_uni = ran_uni_dis['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_uni = ran_time_n_uni / (ran_n_uni * np.log2(ran_n_uni))
ratio_ran_comp_n_uni = ran_comp_n_uni / (ran_n_uni * np.log2(ran_n_uni))

# 1:1000 partition
ran_n_uni_1000 = ran_uni_dis_1000['Size'].to_numpy()
ran_comp_n_uni_1000 = ran_uni_dis_1000['Avg_Comparisons'].to_numpy()
ran_time_n_uni_1000 = ran_uni_dis_1000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_uni_1000 = ran_time_n_uni_1000 / (ran_n_uni_1000 *
                                                   np.log2(ran_n_uni_1000))
ratio_ran_comp_n_uni_1000 = ran_comp_n_uni_1000 / (ran_n_uni_1000 *
                                                   np.log2(ran_n_uni_1000))

# 1:5000 partition
ran_n_uni_5000 = ran_uni_dis_5000['Size'].to_numpy()
ran_comp_n_uni_5000 = ran_uni_dis_5000['Avg_Comparisons'].to_numpy()
ran_time_n_uni_5000 = ran_uni_dis_5000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_uni_5000 = ran_time_n_uni_5000 / (ran_n_uni_5000 *
                                                   np.log2(ran_n_uni_5000))
ratio_ran_comp_n_uni_5000 = ran_comp_n_uni_5000 / (ran_n_uni_5000 *
                                                   np.log2(ran_n_uni_5000))

# 1:10000 partition
ran_n_uni_10000 = ran_uni_dis_10000['Size'].to_numpy()
ran_comp_n_uni_10000 = ran_uni_dis_10000['Avg_Comparisons'].to_numpy()
ran_time_n_uni_10000 = ran_uni_dis_10000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_uni_10000 = ran_time_n_uni_10000 / (ran_n_uni_10000 *
                                                     np.log2(ran_n_uni_10000))
ratio_ran_comp_n_uni_10000 = ran_comp_n_uni_10000 / (ran_n_uni_10000 *
                                                     np.log2(ran_n_uni_10000))

#Random Normal
ran_n_nor = ran_nor_dis['Size'].to_numpy()
ran_comp_n_nor = ran_nor_dis['Avg_Comparisons'].to_numpy()
ran_time_n_nor = ran_nor_dis['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_nor = ran_time_n_nor / (ran_n_nor * np.log2(ran_n_nor))
ratio_ran_comp_n_nor = ran_comp_n_nor / (ran_n_nor * np.log2(ran_n_nor))

# 1:1000 partition
ran_n_nor_1000 = ran_nor_dis_1000['Size'].to_numpy()
ran_comp_n_nor_1000 = ran_nor_dis_1000['Avg_Comparisons'].to_numpy()
ran_time_n_nor_1000 = ran_nor_dis_1000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_nor_1000 = ran_time_n_nor_1000 / (ran_n_nor_1000 *
                                                   np.log2(ran_n_nor_1000))
ratio_ran_comp_n_nor_1000 = ran_comp_n_nor_1000 / (ran_n_nor_1000 *
                                                   np.log2(ran_n_nor_1000))

# 1:5000 partition

ran_n_nor_5000 = ran_nor_dis_5000['Size'].to_numpy()
ran_comp_n_nor_5000 = ran_nor_dis_5000['Avg_Comparisons'].to_numpy()
ran_time_n_nor_5000 = ran_nor_dis_5000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_nor_5000 = ran_time_n_nor_5000 / (ran_n_nor_5000 *
                                                   np.log2(ran_n_nor_5000))
ratio_ran_comp_n_nor_5000 = ran_comp_n_nor_5000 / (ran_n_nor_5000 *
                                                   np.log2(ran_n_nor_5000))

# 1:10000 partition
ran_n_nor_10000 = ran_nor_dis_10000['Size'].to_numpy()
ran_comp_n_nor_10000 = ran_nor_dis_10000['Avg_Comparisons'].to_numpy()
ran_time_n_nor_10000 = ran_nor_dis_10000['Avg_Time_Taken'].to_numpy()
ratio_ran_time_n_nor_10000 = ran_time_n_nor_10000 / (ran_n_nor_10000 *
                                                     np.log2(ran_n_nor_10000))
ratio_ran_comp_n_nor_10000 = ran_comp_n_nor_10000 / (ran_n_nor_10000 *
                                                     np.log2(ran_n_nor_10000))

fig, axis = plt.subplots(2, 1, figsize=(20, 20))

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
