#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>
#include <unordered_map>
#include <math.h>

typedef unsigned int ui;
using namespace std;

class Node
{
public:
    int ascii;
    int frequency;
    Node* left;
    Node* right;

    Node(int ascii, int frequency)
    {
        this->ascii = ascii;
        this->frequency = frequency;
        this->left = nullptr;
        this->right = nullptr;
    }
};

// Comparison function for the priority queue
struct Compare
{
    bool operator()(Node* n1, Node* n2)
    {
        return n1->frequency > n2->frequency;
    }
};


/*--------------------------------------------------------------------------------------------------------*/
void read_input(string filename, vector<Node*>& nodes);
Node* build_tree(vector<Node*>& nodes);
void assign_Huffman_codes(Node* root, string code, map<int, string>& codes);
void print_codes(map<int, string>& codes);
void read_file_list(vector<string>& file_list, const string file_name);
void encode_file(string original_file, string encoded_file, map<int, string>& codes, int &codelength, double &avgcodelen);
/*--------------------------------------------------------------------------------------------------------*/


// Reads the input file and populates the vector of nodes
void read_input(string filename, vector<Node*>& nodes)
{
    ifstream file(filename);

    int ascii, frequency;
    
    while (file >> ascii >> frequency)
        nodes.push_back(new Node(ascii, frequency));
    
    file.close();
}

// Builds the Huffman tree from the vector of nodes
Node* build_tree(vector<Node*>& nodes)
{
    // Sort nodes in ascending order of frequency
    sort(nodes.begin(), nodes.end(), Compare());

    // Create a priority queue of nodes using the sorted vector
    priority_queue<Node*, vector<Node*>, Compare> pq(nodes.begin(), nodes.end());

    // Merge nodes until only one remains, which is the root of the Huffman tree
    while (pq.size() > 1)
    {
        Node* left = pq.top();
        pq.pop();
        Node* right = pq.top();
        pq.pop();
        
        Node* parent = new Node(-1, left->frequency + right->frequency);
        
        parent->left = left;
        parent->right = right;
        
        pq.push(parent);
    }

    return pq.top();
}

// Recursively assigns Huffman codes to each leaf node of the Huffman tree
void assign_Huffman_codes(Node* root, string code, map<int, string>& codes)
{
    if (root == nullptr)
        return;

    if (root->ascii != -1)
        codes[root->ascii] = code;

    assign_Huffman_codes(root->left, code + "0", codes);
    assign_Huffman_codes(root->right, code + "1", codes);
}

// Prints the assigned Huffman codes for each ASCII value
void print_codes(map<int, string>& codes)
{
    for (auto it : codes)
        cout << it.first << " " << it.second << endl;
}

void read_file_list(vector<string>& file_list, const string file_name)
{
    ifstream file(file_name);

    if (!file.is_open())
    {
        cerr << "Error: could not open file" << endl;
        return;
    }

    string filename;
    while (getline(file, filename))
        file_list.push_back(filename);

    file.close();
}

void encode_file(string original_file, string encoded_file, map<int, string>& codes, int &codelength, double &avgcodelen)
{
    ifstream infile(original_file);
    ofstream outfile(encoded_file);

    char c;
    int charcount = 0; // Counter for the total number of characters in the file

    while (infile.get(c))
    {
        // Encode the character using the Huffman code
        string code = codes[c];

        // Write the encoded code to the output file
        outfile << code;

        codelength += code.length();
        charcount++;
    }

    infile.close();
    outfile.close();

    avgcodelen = static_cast<double>(codelength) / charcount; // Calculate the average code length
}

void length_calc(string original_file, double &entropy)
{
    // Count the frequency of each character in the input file
    unordered_map<char, int> freq_map;
    char ch;
    ifstream infile(original_file);
    while (infile >> noskipws >> ch)
        freq_map[ch]++;
    infile.close();

    // Calculate the entropy of the data
    ui freq_sum = 0;
    for (auto& pair : freq_map)
        freq_sum += pair.second;
    
    for (auto& pair : freq_map)
    {
        double p = (double) pair.second / freq_sum;
        entropy += p * log2(1 / p);
    }
}

void decode_file(string encoded_file, string decoded_file, Node* root)
{
    ifstream infile(encoded_file);
    ofstream outfile(decoded_file);

    Node* current = root;
    char c;
    while (infile.get(c))
    {
        // Traverse the Huffman tree
        if (c == '0')
            current = current->left;
        else if (c == '1')
            current = current->right;

        // If a leaf node is reached, write the corresponding character to the output file
        if (current->left == nullptr && current->right == nullptr)
        {
            outfile << (char) current->ascii;
            current = root;  // Reset to the root node for the next character
        }
    }

    infile.close();
    outfile.close();
}

bool compare_files(string original_file, string decoded_file)
{
    ifstream infile1(original_file);
    ifstream infile2(decoded_file);

    if (!infile1.is_open() || !infile2.is_open())
    {
        cerr << "Error: could not open file" << endl;
        return false;
    }

    char c1, c2;
    while (infile1.get(c1) && infile2.get(c2))
    {
        if (c1 != c2)
            return false;
    }

    return true;
}

void compression_ratio(string original_file, int& size)
{
    // Calculate size of original file
    ifstream orig(original_file);
    if (orig.is_open())
    {
        int count = 0;
        char c;
        while (orig.get(c))
            count++;
        orig.close();
        size = count * 8; // Size in bytes
    }
    else
    {
        cout << "Error: Unable to open original file" << endl;
        return;
    }
}

void write_in_csv(const vector<int> original_files_lengths, const vector<int> encoded_files_lengths, const vector<double> entropy_list, const vector<double> avg_Huff_len, const string& filename)
{
    ofstream outfile(filename);

    if (outfile.is_open())
    {
        // Write header row
        outfile << "Original Size,Encoded Size,Entropy,Avg Code Len" << endl;

        // Write data rows
        for (int i = 0; i < original_files_lengths.size(); ++i)
            outfile << original_files_lengths[i] << "," << encoded_files_lengths[i] << "," << entropy_list[i] << "," << avg_Huff_len[i] << endl;

        outfile.close();
    }
    else
        cerr << "Error: Unable to some file" << endl;
}

int main()
{
    // Read the input file and populate the vector of nodes
    vector<Node*> nodes;
    read_input("Frequency_Distribution.txt", nodes);

    // Build the Huffman tree from the vector of nodes
    Node* root = build_tree(nodes);

    // Assign Huffman codes to each leaf node of the Huffman tree
    map<int, string> codes;
    assign_Huffman_codes(root, "", codes);

    // Print the assigned Huffman codes for each ASCII value
    //print_codes(codes);

    // declare a vector to store the filenames
    vector<string> original_files_list;
    vector<string> encoded_files_list;
    vector<string> decoded_files_list;

    // call the read_file_list function to populate the vector
    read_file_list(original_files_list, "Original_File_List.txt");
    read_file_list(encoded_files_list, "Encoded_File_List.txt");
    read_file_list(decoded_files_list, "Decoded_File_List.txt");

    vector<int> original_files_lengths;
    vector<int> encoded_files_lengths;
    vector<double> avg_Huff_lengths;
    vector<double> entropy_list;

    original_files_lengths.assign(original_files_list.size(), 0);
    encoded_files_lengths.assign(original_files_list.size(), 0);
    avg_Huff_lengths.assign(original_files_list.size(),0);
    entropy_list.assign(original_files_list.size(),0);

    for (int i = 0; i < original_files_list.size(); i++)
    {
        length_calc(original_files_list[i], entropy_list[i]);
        encode_file(original_files_list[i], encoded_files_list[i], codes, encoded_files_lengths[i], avg_Huff_lengths[i]);
        decode_file(encoded_files_list[i], decoded_files_list[i], root);

        if(compare_files(original_files_list[i],decoded_files_list[i])==false)
            cerr << "\nFailure for File: "<< original_files_list[i];

        compression_ratio(original_files_list[i],original_files_lengths[i]);
    }

    write_in_csv(original_files_lengths,encoded_files_lengths,entropy_list,avg_Huff_lengths,"Result_Record.csv");
    cout<<"\nEnd of program";
    return 0;
}
