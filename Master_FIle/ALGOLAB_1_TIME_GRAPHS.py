import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("/Users/anishbanerjee/Desktop/master_time_graph_results.txt", sep=" ")

fig, axs = plt.subplots(2, 2, figsize=(10, 8))

axs[0][0].plot(df.iloc[:, 0], df.iloc[:, 1], label="UNIFORM")
axs[0][0].plot(df.iloc[:, 0], df.iloc[:, 2], label="NORMAL")
axs[0][0].legend()
axs[0][0].set_title("GRAPH FOR MERGE SORT")
axs[0][0].set_xlabel("NUMBER OF ELEMENTS (N)")
axs[0][0].set_ylabel("CONSTANT = TIME / N LOG2 N")

axs[0][1].plot(df.iloc[:, 0], df.iloc[:, 3], label="UNIFORM")
axs[0][1].plot(df.iloc[:, 0], df.iloc[:, 4], label="NORMAL")
axs[0][1].legend()
axs[0][1].set_title("GRAPH FOR RANDOMIZED QUICK SORT")
axs[0][1].set_xlabel("NUMBER OF ELEMENTS (N)")
axs[0][1].set_ylabel("CONSTANT = TIME / N LOG2 N")

axs[1][0].plot(df.iloc[:, 0], df.iloc[:, 5], label="UNIFORM")
axs[1][0].plot(df.iloc[:, 0], df.iloc[:, 6], label="NORMAL")
axs[1][0].legend()
axs[1][0].set_title("GRAPH FOR QUICK SORT")
axs[1][0].set_xlabel("NUMBER OF ELEMENTS (N)")
axs[1][0].set_ylabel("CONSTANT = TIME / N LOG2 N")

axs[1][1].plot(df.iloc[:, 0], df.iloc[:, 7], label="UNIFORM")
axs[1][1].plot(df.iloc[:, 0], df.iloc[:, 8], label="NORMAL")
axs[1][1].legend()
axs[1][1].set_title("GRAPH FOR BUCKET SORT")
axs[1][1].set_xlabel("NUMBER OF ELEMENTS (N)")
axs[1][1].set_ylabel("CONSTANT = TIME / N")

fig.tight_layout()
plt.show()
