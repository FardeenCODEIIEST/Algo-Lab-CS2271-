import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

median = pd.read_csv('Observation.csv')

mom = median['MOM'].to_numpy()
dir_median = median['Direct Median'].to_numpy()

x_axis = range(3, 15)

plt.figure(figsize=(10, 10))

plt.title('Median of Median vs Direct median')

plt.plot(x_axis, mom, 'o-', label='MOM')
plt.plot(x_axis, dir_median, 'o-', label='Direct Median')
plt.legend()

plt.ylabel('Obtained Median values', rotation=0, labelpad=40)
plt.xlabel(r'n[array size=$2^n$]')

plt.show()