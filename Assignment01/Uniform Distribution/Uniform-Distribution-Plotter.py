import numpy as np # For Handling Arrays
import csv # For reading .csv files
import matplotlib.pyplot as pyp # For plotting the Dataset

# Our .csv File has total 10e7 samples of numbers
samples=np.zeros(int(10e7))

# As long as the csv file is open
with open("uniform_distribution.csv") as file:
  reader=csv.reader(file,delimiter=',') # Defining the file reader
  count=0 # Keeping track of the array indices
  for it in reader:
    samples[count]=it[0]
    count=count+1
  print("Processed",count,"Lines")

#Plotting Part
pyp.figure("Histogram of Uniformly Distributed Dataset") 
pyp.title("Histogram-Uniform-Distribution-Dataset")
pyp.xlabel("Number Values")
pyp.ylabel("Frequency")
pyp.hist(samples,bins=range(201))
pyp.show()



