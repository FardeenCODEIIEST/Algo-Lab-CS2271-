import matplotlib.pyplot as plt
import pandas as pd
import math

# Read in the data for DPQS_Result1.csv
df1 = pd.read_csv('C:/Users/joyab/Documents/Programming/4th Sem/Algorithm/Final/Experiments/DPQS/DPQS_Result1.csv',
                  header=None, names=['data_size', 'num_comparisons', 'num_swaps', 'partition_ratio', 'time_required'])
df1.columns = ['data_size', 'num_comparisons', 'num_swaps', 'partition_ratio', 'time']

# Filter out data with partition_ratio of 5 or 50 or 500
mask = ((df1['partition_ratio'] == 5) | (df1['partition_ratio'] == 50) | (df1['partition_ratio'] == 500))
df1 = df1[~mask]

# Group the dataframe by partition_ratio and data_size
grouped = df1.groupby(['partition_ratio', 'data_size'])

# Calculate the mean of num_comparisons for each group
grouped_mean = grouped['num_comparisons'].mean().reset_index()

# Create a figure and axis object for the first plot
fig1, ax1 = plt.subplots()

# Plot num_comparisons vs data_size for each partition ratio in the first plot
for name, group in grouped_mean.groupby('partition_ratio'):
    ax1.plot(group['data_size'], group['num_comparisons'], label='Partition Ratio 1:{}'.format(name))

# Set the axis labels and legend for the first plot
#ax1.set_xlabel('Data Size')
#ax1.set_ylabel('Number of Comparisons')
ax1.set_xscale('log')
#ax1.set_yscale('log')
ax1.legend()

# Read in the data for DPQS_Result2.csv
df2 = pd.read_csv('C:/Users/joyab/Documents/Programming/4th Sem/Algorithm/Final/Experiments/DPQS/DPQS_Result2.csv',
                  header=None, names=['data_size', 'num_comparisons', 'num_swaps', 'partition_ratio', 'time_required'])
df2.columns = ['data_size', 'num_comparisons', 'num_swaps', 'partition_ratio', 'time']

# Filter out data with partition_ratio of 5 or 50 or 500
mask = ((df2['partition_ratio'] == 5) | (df2['partition_ratio'] == 50) | (df2['partition_ratio'] == 500))
df2 = df2[~mask]

# Group the dataframe by partition_ratio and data_size
grouped = df2.groupby(['partition_ratio', 'data_size'])

# Calculate the mean of num_comparisons for each group
grouped_mean = grouped['num_comparisons'].mean().reset_index()

# Create a figure and axis object for the second plot
fig2, ax2 = plt.subplots()

# Plot num_comparisons vs data_size for each partition ratio in the second plot
for name, group in grouped_mean.groupby('partition_ratio'):
    ax2.plot(group['data_size'], group['num_comparisons'], label='Partition Ratio 1:{}'.format(name))

# Set the axis labels and legend for the second plot
#ax2.set_xlabel('Data Size')
#ax2.set_ylabel('Number of Comparisons')
ax2.set_xscale('log')
#ax2.set_yscale('log')
ax2.legend()

# Show the plots
plt.show()

print(df1)
print(df2)