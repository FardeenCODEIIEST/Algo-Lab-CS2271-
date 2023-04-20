import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV files into pandas dataframes
df_huffman = pd.read_csv('C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Huffman_Experiment_II/Result_Record.csv')
df_shannon_fano = pd.read_csv('C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Shannon_Fano/Result_Record.csv')

# Sort the dataframes by original file size
df_huffman = df_huffman.sort_values(by='Original Size')
df_shannon_fano = df_shannon_fano.sort_values(by='Original Size')

# Compute the compression ratios and add them to the dataframes
df_huffman["Compression Ratio"] = df_huffman["Encoded Size"] / df_huffman["Original Size"]
df_huffman["OG_File(bytes)"] = df_huffman["Original Size"] / 8
df_shannon_fano["Compression Ratio"] = df_shannon_fano["Encoded Size"] / df_shannon_fano["Original Size"]
df_shannon_fano["OG_File(bytes)"] = df_shannon_fano["Original Size"] / 8

# Compute the average compression ratios
avg_compression_ratio_huffman = round(df_huffman["Compression Ratio"].mean(), 5)
avg_compression_ratio_shannon_fano = round(df_shannon_fano["Compression Ratio"].mean(), 6)

# Create the first plot
fig1, ax1 = plt.subplots(1, 1, figsize=(8, 6))

# Plot the compression ratios vs original file size
ax1.scatter(df_huffman["OG_File(bytes)"], df_huffman["Compression Ratio"], label="Huffman")
ax1.scatter(df_shannon_fano["OG_File(bytes)"], df_shannon_fano["Compression Ratio"], label="Shannon-Fano")
ax1.axhline(y=avg_compression_ratio_huffman, color="red")
ax1.axhline(y=avg_compression_ratio_shannon_fano, color="green")
trans1 = ax1.get_yaxis_transform()
ax1.text(1.01, avg_compression_ratio_huffman, f"{avg_compression_ratio_huffman:.5f}", color="red",
         horizontalalignment="left", verticalalignment="center", transform=trans1)
ax1.text(1.01, avg_compression_ratio_shannon_fano, f"{avg_compression_ratio_shannon_fano:.5f}", color="green",
         horizontalalignment="left", verticalalignment="center", transform=trans1)
ax1.set_xlabel("Original File Size")
ax1.set_ylabel("Compression Ratio")
ax1.set_title("Compression Ratio vs Original File Size")
ax1.legend()

# Create the second plot
fig2, ax2 = plt.subplots(1, 1, figsize=(8, 6))

# Plot the entropy, average Huffman code length, and average Shannon-Fano code length vs original file size
ax2.plot(df_huffman["OG_File(bytes)"], df_huffman["Entropy"], color="red", label="Entropy (Huffman)")
ax2.plot(df_huffman["OG_File(bytes)"], df_huffman["Avg Code Len"], color="blue", label="Avg. Huffman Code Len")
ax2.plot(df_shannon_fano["OG_File(bytes)"], df_shannon_fano["Avg Code Len"], color="green", label="Avg. Shannon-Fano Code Len")
ax2.set_xlabel("Original File Size")
ax2.set_ylabel("Value")
ax2.set_title("Entropy, Avg. Code Length vs Original File Size")
ax2.legend()

# Show the first plot
plt.show()
