#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Data structure to hold the frequency and code for each symbol
struct SymbolData {
    char symbol;
    int frequency;
    string code;
};

// Function to calculate the Shannon-Fano code for a set of symbols
void ShannonCoding(vector<SymbolData>& symbols, int start, int end, string code) {
    // Base case: if there is only one symbol, assign the code and return
    if (start == end) {
        symbols[start].code = code;
        return;
    }

    // Calculate the total frequency of symbols in the range
    int totalFrequency = 0;
    for (int i = start; i <= end; i++) {
        totalFrequency += symbols[i].frequency;
    }

    // Calculate the midpoint of the range
    int midpoint = start;
    int midpointFrequency = symbols[start].frequency;
    while (midpointFrequency * 2 < totalFrequency && midpoint < end) {
        midpoint++;
        midpointFrequency += symbols[midpoint].frequency;
    }

    // Assign codes to the left and right halves of the range
    ShannonCoding(symbols, start, midpoint, code + "0");
    ShannonCoding(symbols, midpoint + 1, end, code + "1");
}

int main() {
    // Input symbols and their frequencies
    vector<SymbolData> symbols = {
        {'a', 7},
        {'b', 5},
        {'c', 2},
        {'d', 4},
        {'e', 8}
    };

    // Sort the symbols by frequency in descending order
    sort(symbols.begin(), symbols.end(), [](const SymbolData& s1, const SymbolData& s2) {
        return s1.frequency > s2.frequency;
    });

    // Calculate the Shannon-Fano codes for each symbol
    ShannonCoding(symbols, 0, symbols.size() - 1, "");

    // Output the results
    for (const auto& symbol : symbols) {
        cout << symbol.symbol << " " << symbol.frequency << " " << symbol.code << endl;
    }

    return 0;
}
