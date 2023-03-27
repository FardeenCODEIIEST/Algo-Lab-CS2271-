#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <math.h>

using namespace std;

string original_file = "Text_Sample3.txt";
string encoded_file  = "Text_Sample3_Huffman_Encoded.txt";
string decoded_file  = "Text_Sample3_Huffman_Decoded.txt";
string codebook_file = "Text_Sample3_Huffman_Codebook.txt";

// Data structure to store an ASCII character, its frequency, and Huffman code
struct Node
{
    char ch;
    int freq;
    string code;
    Node* left, * right;

    Node(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

/*-------------------------------------------------------------------------------------------------------------------------------------------*/
void traverse(Node* root, string code, unordered_map<char, string>& map);
void sortByCodeLengthFreqAndCode(vector<pair<char, int>>& code_lengths, unordered_map<char, int>& freq_map, unordered_map<char, string>& map);
void storeCodebook(unordered_map<char, int>& map, unordered_map<char, string>& codeMap);
void displayCodes(unordered_map<char, int>& freq_map, unordered_map<char, string>& map);
Node* buildHuffmanTree(unordered_map<char, int>& freq_map);
void encodeFile(Node*& start);
void decodeFile(Node* root);
bool are_files_identical();
/*-------------------------------------------------------------------------------------------------------------------------------------------*/

// Function to traverse the Huffman Tree and store the Huffman codes in a map
void traverse(Node* root, string code, unordered_map<char, string>& map)
{
    if (!root) return;
    if (root->ch != '\0')
        map[root->ch] = code;

    traverse(root->left, code + "0", map);
    traverse(root->right, code + "1", map);
}

double calculateLowerBound(unordered_map<char, int>& freq_map)
{
    double lower_bound = 0;
    int total_freq = 0;

    // Calculate the total frequency of all characters
    for (auto& pair : freq_map)
        total_freq += pair.second;

    // Calculate the lower bound using the formula
    for (auto& pair : freq_map)
    {
        double p = (double) pair.second / total_freq;
        lower_bound += p * log2(1 / p);
    }

    return total_freq*lower_bound;
}

int huffmanCodeLength(const unordered_map<char, int>& freqMap, const unordered_map<char, string>& codeMap)
{
    int totalBits = 0;
    for (auto it = freqMap.begin(); it != freqMap.end(); it++)
        totalBits += it->second * codeMap.at(it->first).length();

    return totalBits;
}

// Function to sort the characters by code length, frequency, and code
void sortByCodeLengthFreqAndCode(vector<pair<char, int>>& code_lengths, unordered_map<char, int>& freq_map, unordered_map<char, string>& map)
{
    // Sort the vector in increasing order of code lengths
    sort(code_lengths.begin(), code_lengths.end(), [](const pair<char, int>& a, const pair<char, int>& b)
    {
        return a.second < b.second;
    });

    // Sort the subgroups of characters with equal code lengths
    int i = 0, n = code_lengths.size();
    while (i < n)
    {
        int j = i + 1;
        while (j < n && code_lengths[j].second == code_lengths[i].second)
            j++;

        // Sort the subgroup in decreasing order of frequencies
        sort(code_lengths.begin() + i, code_lengths.begin() + j, [&](const pair<char, int>& a, const pair<char, int>& b)
        {
            if (freq_map[a.first] != freq_map[b.first])
                return freq_map[a.first] > freq_map[b.first];
            else
                return map[a.first] < map[b.first];
        });

        i = j;
    }
}

void storeCodebook(unordered_map<char, int>& freq_map, unordered_map<char, string>& codeMap)
{
    // Open the codebook file for writing
    ofstream fout(codebook_file);

    // Write the ASCII value and Huffman code for each character to the file
    for (auto& pair : freq_map)
    {
        char ch = pair.first;
        fout << int(ch) << " " << codeMap[ch] << endl;
    }

    // Close the file
    fout.close();
}

// Function to display the ASCII character, frequency, and Huffman code for each character
void displayCodes(unordered_map<char, int>& freq_map, unordered_map<char, string>& codeMap)
{
    // Create a vector of pairs to store the characters and their code length
    vector<pair<char, int>> code_lengths;

    // Calculate the code lengths for each character and store them in the vector
    for (auto& pair : freq_map)
        code_lengths.push_back(make_pair(pair.first, codeMap[pair.first].length()));

    // Sort the characters by code length, frequency, and code
    sortByCodeLengthFreqAndCode(code_lengths, freq_map, codeMap);

    // Display the ASCII character, frequency, and Huffman code for each character in a table format
    cout << setw(10) << "Character" << setw(10) << "Frequency" << setw(15) << "Huffman Code" << endl;
    cout << setfill('-') << setw(35) << "-" << setfill(' ') << endl;
    for (auto& pair : code_lengths)
    {
        char ch = pair.first;
        if (ch == ' ')
            cout << setw(10) << "<space>" << setw(10) << freq_map[ch] << setw(15) << codeMap[ch] << endl;
        else if (ch == '\n')
            cout << setw(10) << "<enter>" << setw(10) << freq_map[ch] << setw(15) << codeMap[ch] << endl;
        else
            cout << setw(10) << ch << setw(10) << freq_map[ch] << setw(15) << codeMap[ch] << endl;
    }

    storeCodebook(freq_map,codeMap);

    double lb = calculateLowerBound(freq_map);
    double hf = huffmanCodeLength(freq_map,codeMap);

    cout<<"deviation = "<< (hf-lb)/lb * 100;
}

// Function to build the Huffman Tree
Node* buildHuffmanTree(unordered_map<char, int>& freq_map)
{
    // Create an array of node pointers to store the nodes of the Huffman Tree
    Node* nodes[freq_map.size()];
    int i = 0;
    for (auto& pair : freq_map)
    {
        nodes[i] = new Node(pair.first, pair.second);
        i++;
    }

    // Build the Huffman Tree using a heap
    while (i > 1)
    {
        int min1 = 0, min2 = 1;     //min1 for smallest frequency and min2 for second smallest

        // If nodes have equal frequency, break tie based on ASCII value of characters
        if (nodes[min1]->freq == nodes[min2]->freq)
        {
            if (nodes[min1]->ch > nodes[min2]->ch)
                swap(min1, min2);
        }

        if (nodes[min1]->freq > nodes[min2]->freq)
            swap(min1, min2);

        for (int j = 2; j < i; j++)
            if (nodes[j]->freq < nodes[min1]->freq)
            {
                min2 = min1;
                min1 = j;
            }
            else if (nodes[j]->freq < nodes[min2]->freq)
            {
                min2 = j;

                // If nodes have equal frequency, break tie based on ASCII value of characters
                if (nodes[min1]->freq == nodes[min2]->freq)
                {
                    if (nodes[min1]->ch > nodes[min2]->ch)
                        swap(min1, min2);
                }
            }

        // Create a new node with the sum of the frequencies of the two smallest nodes
        Node* parent = new Node('\0', nodes[min1]->freq + nodes[min2]->freq);
        parent->left = nodes[min1];
        parent->right = nodes[min2];

        // Remove the two smallest nodes from the array and add the new node
        nodes[min1] = parent;
        nodes[min2] = nodes[i - 1];
        i--;
    }

    // Return the root of the Huffman Tree
    return nodes[0];
}

// Function to encode the input file and write the encoded data to output file
void encodeFile(Node*& start)
{
    // Count the frequency of each character in the input file
    unordered_map<char, int> freq_map;
    char ch;
    ifstream infile(original_file);
    while (infile >> noskipws >> ch)
        freq_map[ch]++;

    infile.close();

    // Build the Huffman Tree using the frequency map
    Node* root = buildHuffmanTree(freq_map);
    start = root;

    // Traverse the Huffman Tree and store the Huffman codes in a map
    unordered_map<char, string> Codemap;
    traverse(root, "", Codemap);

    // Display the ASCII character, frequency, and Huffman code for each character
    displayCodes(freq_map, Codemap);

    // Encode the input file using the Huffman codes and write the encoded data to output file
    ofstream outfile(encoded_file);
    infile.open(original_file);
    while (infile >> noskipws >> ch)
        outfile << Codemap[ch];
    
    infile.close();
    outfile.close();
}

// Traverse the Huffman tree to decode the input string
void decodeFile(Node* root)
{
    // Open the input and output files
    ifstream inFile(encoded_file, ios::binary);
    ofstream outFile(decoded_file, ios::binary);

    // Traverse the Huffman tree for each character in the input file
    Node* current = root;
    char c;
    while (inFile.get(c))
    {
        if (c == '0')
            current = current->left;
        else
            current = current->right;

        if (current->left == nullptr && current->right == nullptr)
        {
            outFile.put(current->ch);
            current = root;
        }
    }

    // Close the input and output files
    inFile.close();
    outFile.close();
}

// Check if original text and decoded text are identical
bool are_files_identical()
{
    ifstream file1(original_file), file2(decoded_file);
    char c1, c2;
    while (file1.get(c1) && file2.get(c2))
        if (c1 != c2)
            return false;
    return !file1.eof() || !file2.eof();
}

// Driver code
int main()
{
    Node * Huffman_root = nullptr;

    // Encode the input file and write the encoded data to output file
    encodeFile(Huffman_root);
    decodeFile(Huffman_root);
    if(are_files_identical())
        cout<<"\nSuccess";

    return 0;
}