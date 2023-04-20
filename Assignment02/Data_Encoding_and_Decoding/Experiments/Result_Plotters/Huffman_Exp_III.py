import pandas as pd
import matplotlib.pyplot as plt

# Read the CSV file into a pandas dataframe
df= pd.read_csv('C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Huffman_Experiment_III/Result_Record.csv')
df = df.sort_values(by='Original Size')
# Compute the compression ratio and add it to the dataframe
df["Compression Ratio"] = df["Encoded Size"] / df["Original Size"]
df["OG_File(bytes)"] = df["Original Size"]/8

# Compute the average compression ratio
avg_compression_ratio = round(df["Compression Ratio"].mean(), 5)

# Scatter plot of compression ratio vs original size
fig, ax = plt.subplots()
ax.scatter(df["OG_File(bytes)"], df["Compression Ratio"])

# Add a horizontal line for the average compression ratio
ax.axhline(y=avg_compression_ratio, color="red")
trans = ax.get_yaxis_transform()
ax.text(1.01, avg_compression_ratio, f"{avg_compression_ratio:.5f}", color="red",
        horizontalalignment="left", verticalalignment="center", transform=trans)


# Set the x-axis and y-axis labels and plot title
ax.set_xlabel("Original File Size")
ax.set_ylabel("Compression Ratio")
plt.title("Compression Ratio vs Original File Size")

# Set the x-axis label and plot title for the second plot
fig, ax1 = plt.subplots()
ax1.set_xlabel("Original File Size")
plt.title("Variation of Entropy and Avg. Huffman Code Len with Original File Size")

# Plot the lines for entropy and average code length
ax1.plot(df["OG_File(bytes)"], df["Entropy"], color="red", label="Entropy")
ax1.plot(df["OG_File(bytes)"], df["Avg Code Len"], color="blue", label="Avg. Huffman Code Len")

# Plot the points for entropy and average code length
#ax1.scatter(df["Original Size"], df["Entropy"], color="red")
#ax1.scatter(df["Original Size"], df["Avg Code Len"], color="blue")

# Set the y-axis labels and colors
ax1.set_ylabel("bits/character")
ax1.tick_params(axis='y', labelcolor="red")

# Add legend to show which line stands for what
ax1.legend(loc="upper right")

# Show the plot
plt.show()