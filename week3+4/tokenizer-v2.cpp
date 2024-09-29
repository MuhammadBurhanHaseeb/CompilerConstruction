#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_set>

enum class TokenType {
    KEYWORD,
    IDENTIFIER,
    NUMBER,
    OPERATOR,
    PUNCTUATION,
    UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;

    Token(TokenType t, const std::string &v) : type(t), value(v) {}
};

std::unordered_set<std::string> keywords = {"if", "else", "for", "while", "return", "int", "float", "char", "void", "double"};
std::unordered_set<char> operators = {'+', '-', '*', '/', '=', '>', '<', '&', '|', '!'};
std::unordered_set<char> punctuation = {',', ';', '(', ')', '{', '}'}; 

bool isKeyword(const std::string &str) {
    return keywords.find(str) != keywords.end();
}

std::vector<Token> tokenize(const std::string &input) {
    std::vector<Token> tokens;
    int i = 0;

    while (i < input.size()) {
        if (isspace(input[i])) {
            ++i;
            continue;
        } else if (isalpha(input[i])) {
            std::string word;
            while (i < input.size() && isalnum(input[i])) {
                word += input[i++];
            }
            if (isKeyword(word)) {
                tokens.emplace_back(TokenType::KEYWORD, word);
            } else {
                tokens.emplace_back(TokenType::IDENTIFIER, word);
            }
        } else if (isdigit(input[i])) {
            std::string number;
            while (i < input.size() && isdigit(input[i])) {
                number += input[i++];
            }
            tokens.emplace_back(TokenType::NUMBER, number);
        } else if (operators.find(input[i]) != operators.end()) {
            tokens.emplace_back(TokenType::OPERATOR, std::string(1, input[i++]));
        } else if (punctuation.find(input[i]) != punctuation.end()) {
            tokens.emplace_back(TokenType::PUNCTUATION, std::string(1, input[i++]));
        } else {
            tokens.emplace_back(TokenType::UNKNOWN, std::string(1, input[i++]));
        }
    }

    return tokens;
}

void printTokens(const std::vector<Token>& tokens) {
    for (const auto& token : tokens) {
        std::cout << "Token: " << token.value << ", Type: ";
        switch (token.type) {
            case TokenType::KEYWORD:
                std::cout << "Keyword";
                break;
            case TokenType::IDENTIFIER:
                std::cout << "Identifier";
                break;
            case TokenType::NUMBER:
                std::cout << "Number";
                break;
            case TokenType::OPERATOR:
                std::cout << "Operator";
                break;
            case TokenType::PUNCTUATION:
                std::cout << "Punctuation";
                break;
            case TokenType::UNKNOWN:
                std::cout << "Unknown";
                break;
        }
        std::cout << std::endl;
    }
}

int main() {
    std::string input = "if (x << 10) return x +20 ;";
    std::vector<Token> tokens = tokenize(input);
    printTokens(tokens);
    return 0;
}
