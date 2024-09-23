#include<iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<vector>
using namespace std;
int main(int argc, char* argv[])
{
    vector<string> tokens;

    if (argc < 2) {
        cerr << "Usage: mycompiler <Burhan.cpp>" << endl;
        return 1;
    }
    
    ifstream file(argv[1]);
    
    
    if (!file.is_open()) {
        
        cerr << "Could not open the file " << argv[1] << endl;
        return 1;
    }

    string line;
    while (getline(file, line)) {

        string token;
        stringstream ss(line);
        while (ss >> token) 
        {
            tokens.push_back(token);           // Add each token to the vector
        }
    }
    file.close();

    for (const string& token : tokens) {
            cout << " " << token << " "<<endl;
        }
        cout << std::endl;

    return 0;
}