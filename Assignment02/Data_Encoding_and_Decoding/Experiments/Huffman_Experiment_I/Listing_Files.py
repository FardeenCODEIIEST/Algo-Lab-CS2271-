import os
import unicodedata

# Define the directory where the text files are located
directory = "C:/Users/joyab/Documents/Programming/College/4th Sem/Algorithm/Assignment2/Assignment2_Part2/Huffman_Experiment_I"

# Create an empty dictionary to store the frequency of each character
char_freq = {}

def replace_non_english_symbols(file_path):
    with open(file_path, "r") as f:
        contents = f.read()

    normalized = unicodedata.normalize("NFKD", contents)
    ascii_string = normalized.encode("ascii", "ignore").decode("ascii")
    
    with open(file_path, "w") as f:
        f.write(ascii_string)

# Loop through all the files in the directory
for filename in os.listdir(directory):
    if filename.endswith(".txt") and filename not in ["Original_File_List.txt", "Frequency_Distribution.txt"]:
        # Replace non-English symbols with English equivalents
        replace_non_english_symbols(os.path.join(directory, filename))
        # Open the file and read its contents character by character
        with open(os.path.join(directory, filename)) as f:
            for char in f.read():
                # Update the frequency count for this character
                char_freq[ord(char)] = char_freq.get(ord(char), 0) + 1

# Write the character frequency data to a new text file in the same directory
output_file = os.path.join(directory, "Frequency_Distribution.txt")
with open(output_file, "w") as f:
    for char, freq in sorted(char_freq.items(), key=lambda x: x[1], reverse=True):
        f.write(f"{char} {freq}\n")

# Write the list of files to a new text file in the same directory
file_list_file = os.path.join(directory, "Original_File_List.txt")
with open(file_list_file, "w") as f:
    for filename in os.listdir(directory):
        if filename.endswith(".txt") and filename not in ["Original_File_List.txt", "Frequency_Distribution.txt", "Encoded_File_List.txt", "Decoded_File_List.txt", "Results.txt"]:
            f.write(f"{filename}\n")

# Create a new list of encoded file names based on the original file list
encoded_file_list = [f"Encoded_{filename}" for filename in os.listdir(directory) if filename.endswith(".txt") and filename not in ["Original_File_List.txt", "Frequency_Distribution.txt", "Encoded_File_List.txt", "Decoded_File_List.txt", "Results.txt"]]

# Write the encoded file list to a new text file in the same directory
encoded_file_list_file = os.path.join(directory, "Encoded_File_List.txt")
with open(encoded_file_list_file, "w") as f:
    for filename in encoded_file_list:
        f.write(f"{filename}\n")

# Create a new list of decoded file names based on the original file list
encoded_file_list = [f"Decoded_{filename}" for filename in os.listdir(directory) if filename.endswith(".txt") and filename not in ["Original_File_List.txt", "Frequency_Distribution.txt", "Encoded_File_List.txt", "Decoded_File_List.txt", "Results.txt"]]

# Write the encoded file list to a new text file in the same directory
encoded_file_list_file = os.path.join(directory, "Decoded_File_List.txt")
with open(encoded_file_list_file, "w") as f:
    for filename in encoded_file_list:
        f.write(f"{filename}\n")

print("End of program")
