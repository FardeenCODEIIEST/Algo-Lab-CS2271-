import pandas as pd
import matplotlib.pyplot as plt

# Function to read CSV file, sort by original size, and compute compression ratio and original file size
def process_results_csv(file_path):
    df = pd.read_csv(file_path)
    df = df.sort_values(by='Original Size')
    df["Compression Ratio"] = df["Encoded Size"] / df["Original Size"]
    df["OG_File(bytes)"] = df["Original Size"]/8
    avg_compression_ratio = round(df["Compression Ratio"].mean(), 5)
    return df, avg_compression_ratio

#-----------------------------------------------------------------------------------------------------------------------------------#

# Read the CSV files and process results
df1, avg_compression_ratio_1 = process_results_csv('C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Huffman_Experiment_I/Result_Record.csv')
df2, avg_compression_ratio_2 = process_results_csv('C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Huffman_Experiment_II/Result_Record.csv')

# Scatter plot of compression ratio vs original size
fig, ax = plt.subplots()
ax.scatter(df1["OG_File(bytes)"], df1["Compression Ratio"], label='Huffman_Experiment_I')
ax.scatter(df2["OG_File(bytes)"], df2["Compression Ratio"], label='Huffman_Experiment_II')

ax.set_xlabel("Original File Size")
ax.set_ylabel("Compression Ratio")

# Add horizontal lines for the average compression ratio of each dataset
ax.axhline(y=avg_compression_ratio_1, color="red")
ax.axhline(y=avg_compression_ratio_2, color="green")

# Add text labels for the average compression ratios
trans = ax.get_yaxis_transform()
ax.text(1.01, avg_compression_ratio_1, f"{avg_compression_ratio_1:.5f}", color="red",
        horizontalalignment="left", verticalalignment="center", transform=trans)
ax.text(1.01, avg_compression_ratio_2, f"{avg_compression_ratio_2:.5f}", color="green",
        horizontalalignment="left", verticalalignment="center", transform=trans)

# Add legend to the upper right corner
ax.legend(loc='upper right')

# Set the x-axis label and plot title for the second plot
fig, ax1 = plt.subplots()
ax1.set_xlabel("Original File Size")
plt.title("Variation of Entropy and Avg. Huffman Code Len with Original File Size")

# Plot the lines for entropy and average code length
ax1.plot(df1["OG_File(bytes)"], df1["Entropy"], color="red", label="Entropy", alpha = 0.5)
ax1.plot(df1["OG_File(bytes)"], df1["Avg Code Len"], color="blue", label="Averaged-out Huffman Code Length", alpha = 0.5)
ax1.plot(df2["OG_File(bytes)"], df2["Avg Code Len"], color="green", label="File Specific Huffman Code Length", alpha = 0.5)

# Set the y-axis labels and colors
ax1.set_ylabel("bits/character")
ax1.tick_params(axis='y', labelcolor="red")

# Add legend to show which line stands for what
ax1.legend(loc="upper right")

# Show the plot
plt.show()
