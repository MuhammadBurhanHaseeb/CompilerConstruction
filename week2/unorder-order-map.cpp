#include <iostream>
#include <unordered_map>
#include <map>
#include <sstream>
#include <string>

using namespace std;

void countWordFrequencyUnordered(const string& text) {
    unordered_map<string, int> wordCount;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        wordCount[word]++;
    }

    cout << "\nWord Frequencies using unordered_map:\n";
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

void countWordFrequencyOrdered(const string& text) {
    map<string, int> wordCount;
    stringstream ss(text);
    string word;

    while (ss >> word) {
        wordCount[word]++;
    }

    cout << "\nWord Frequencies using map:\n";
    for (const auto& pair : wordCount) {
        cout << pair.first << ": " << pair.second << endl;
    }
}

int main() {
    string text = "hello world hello hello map unordered map hello unordered";

    countWordFrequencyUnordered(text);

    countWordFrequencyOrdered(text);

    return 0;
}
