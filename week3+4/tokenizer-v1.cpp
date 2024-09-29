#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

bool isSpecialToken(char c) {
    return (c == '!' || c == '@' || c == '#' || c == '$' || c == '%' || c == '^' || c == '&' || 
            c == '*' || c == '(' || c == ')' || c == '-' || c == '_' || c == '=' || c == '+' || 
            c == '[' || c == ']' || c == '{' || c == '}' || c == ';' || c == ':' || c == '\'' || 
            c == ',' || c == '.' || c == '<' || c == '>' || c == '/' || c == '?' || c == '\\' || 
            c == '|' || c == '`' || c == '~') && c != '"';
}

bool isspace(char c) {
    return c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f';
}

int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        cerr << "Use command like this: " << argv[0] << " <Burhan.cpp>\n";
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "File: " << argv[1] << " is not readable or there is no such file with this name\n";
        return 1;
    }

    string line;
    vector<string> tokens;
    bool insideQuotes = false;
    while (getline(file, line)) {
        string token = "";
        for (int i = 0; i < line.length(); i++) {
            char c = line[i];

            if (c == '"') {
                if (insideQuotes) {
                    token += c;
                    tokens.push_back(token);
                    token = "";
                    insideQuotes = false;
                } else {
                    if (!token.empty()) {
                        tokens.push_back(token);
                        token = "";
                    }
                    token += c;
                    insideQuotes = true;
                }
            } else if (insideQuotes) {
                token += c;
            } else if (isspace(c) || isSpecialToken(c)) {
                if (!token.empty()) {
                    tokens.push_back(token); 
                    token = "";              
                } 
                if (isSpecialToken(c)) {
                    string specialToken(1, c);  
                    if ((c == '<' || c == '>') && (i + 1 < line.length()) && line[i + 1] == c) {
                        specialToken += line[i + 1];  
                        i++;  
                    }
                    tokens.push_back(specialToken);  
                }
            } else {
                token += c; 
            }
        }
        if (!token.empty()) {
            tokens.push_back(token); 
        }
    }

    for (const auto& t : tokens) {
        cout << t << endl; 
    }

    return 0;
}
