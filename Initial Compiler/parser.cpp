#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

enum TokenType {
    T_CHAR_LITERAL , T_STRING_LITERAL,
    T_STRING, T_FLOAT, T_DOUBLE, T_CHAR, T_VOID, T_BOOL, T_INT,
     T_FOR, T_WHILE, T_SWITCH, T_CASE, T_BREAK,
    T_ID, T_NUM, T_IF, T_ELSE, T_RETURN, 
    T_ASSIGN, T_PLUS, T_MINUS, T_MUL, T_DIV, 
    T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE,  
    T_SEMICOLON, T_GT,T_LT,T_LE,T_GE,T_NEQ,T_EQ ,T_EOF, T_COLON,
    T_AGAR , T_MAGAR,
    T_INCREMENT,T_DECREMENT,   
      
};

struct Token {
    TokenType type;
    string value;
    int lineNo;
    int colNo;
};
class Lexer {
private:
    string src;
    size_t pos;
    int lineNo;
    int colNo;

public:
    Lexer(const string &src) {
        this->src = src;
        this->pos = 0;
        this->lineNo = 1;  // Start from the first line
        this->colNo = 1;   // Start from the first column
    }

    vector<Token> tokenize() {
        vector<Token> tokens;
        while (pos < src.size()) {
            char current = src[pos];
            
            if (isspace(current)) {
                handleWhitespace(current);
                continue;
            }
            if (isdigit(current)) {
                tokens.push_back(Token{T_NUM, consumeNumber(), lineNo, colNo});
                continue;
            }
            if (isalpha(current)) {
                string word = consumeWord();
                if (word == "int") tokens.push_back(Token{T_INT, word, lineNo, colNo});
                else if (word == "bool") tokens.push_back(Token{T_BOOL, word, lineNo, colNo});
                else if (word == "float") tokens.push_back(Token{T_FLOAT, word, lineNo, colNo});
                else if (word == "double") tokens.push_back(Token{T_DOUBLE, word, lineNo, colNo});
                else if (word == "char") tokens.push_back(Token{T_CHAR, word, lineNo, colNo});
                else if (word == "void") tokens.push_back(Token{T_VOID, word, lineNo, colNo});
                else if (word == "string") tokens.push_back(Token{T_STRING, word, lineNo, colNo});

                else if (word == "if") tokens.push_back(Token{T_IF, word, lineNo, colNo});
                else if (word == "else") tokens.push_back(Token{T_ELSE, word, lineNo, colNo});
                else if (word == "return") tokens.push_back(Token{T_RETURN, word, lineNo, colNo});

                else if (word == "agr") tokens.push_back(Token{T_AGAR, word, lineNo, colNo});
                else if (word == "magr") tokens.push_back(Token{T_MAGAR, word, lineNo, colNo});

                else if (word == "for") tokens.push_back(Token{T_FOR, word, lineNo, colNo});       
                else if (word == "while") tokens.push_back(Token{T_WHILE, word, lineNo, colNo});   
                else if (word == "switch") tokens.push_back(Token{T_SWITCH, word, lineNo, colNo}); 
                else if (word == "case") tokens.push_back(Token{T_CASE, word, lineNo, colNo});    
                else if (word == "break") tokens.push_back(Token{T_BREAK, word, lineNo, colNo});   

                else tokens.push_back(Token{T_ID, word, lineNo, colNo});
                continue;
            }
             if (current == '"') {
                tokens.push_back(Token{T_STRING_LITERAL, consumeStringLiteral(), lineNo, colNo});
                continue;
            }
            if (current == '\'') {
                tokens.push_back(Token{T_CHAR_LITERAL, consumeCharLiteral(), lineNo, colNo});
                continue;
            }

            switch (current) {
                case '*': tokens.push_back(Token{T_MUL, "*", lineNo, colNo}); break;
                case '/': tokens.push_back(Token{T_DIV, "/", lineNo, colNo}); break;
                case '(': tokens.push_back(Token{T_LPAREN, "(", lineNo, colNo}); break;
                case ')': tokens.push_back(Token{T_RPAREN, ")", lineNo, colNo}); break;
                case '{': tokens.push_back(Token{T_LBRACE, "{", lineNo, colNo}); break;
                case '}': tokens.push_back(Token{T_RBRACE, "}", lineNo, colNo}); break;
                case ';': tokens.push_back(Token{T_SEMICOLON, ";", lineNo, colNo}); break;
                case ':': tokens.push_back(Token{T_COLON, ":", lineNo, colNo}); break;
                case '=':
                    current = src[pos+1];
                    if (current == '=') {
                        tokens.push_back(Token{T_EQ, "==", lineNo, colNo});
                        pos++; colNo++;
                    } else {
                        tokens.push_back(Token{T_ASSIGN, "=", lineNo, colNo});
                    }
                    break;
                case '<':
                    current = src[pos+1];
                    if (current == '=') {
                        tokens.push_back(Token{T_LE, "<=", lineNo, colNo});
                        pos++; colNo++;
                    } else {
                        tokens.push_back(Token{T_LT, "<", lineNo, colNo});
                    }
                    break;
                case '>':
                    current = src[pos+1];
                    if (current == '=') {
                        tokens.push_back(Token{T_GE, ">=", lineNo, colNo});
                        pos++; colNo++;
                    } else {
                        tokens.push_back(Token{T_GT, ">", lineNo, colNo});
                    }
                    break;
                case '!':
                    current = src[pos+1];
                    if (current == '=') {
                        tokens.push_back(Token{T_NEQ, "!=", lineNo, colNo});
                        pos++; colNo++;
                    }
                    break;
                case '+':
                    current = src[pos+1];
                    if (current == '+') {
                        tokens.push_back(Token{T_INCREMENT, "++", lineNo, colNo});
                        pos++; colNo++;
                    } else {
                        tokens.push_back(Token{T_PLUS, "+", lineNo, colNo});
                    }
                    break;
                case '-':
                    current = src[pos+1];
                    if (current == '-') {
                        tokens.push_back(Token{T_DECREMENT, "--", lineNo, colNo});
                        pos++; colNo++;
                    } else {
                        tokens.push_back(Token{T_MINUS, "-", lineNo, colNo});
                    }
                    break;
                default: 
                    cout << "Unexpected character: " << current << " at line " 
                         << lineNo << ", column " << colNo << endl; 
                    exit(1);
            }
            pos++;
            colNo++;
        }
        tokens.push_back(Token{T_EOF, "", lineNo, colNo});
        return tokens;
    }

private:
    void handleWhitespace(char current) {
        if (current == '\n') {
            lineNo++;
            colNo = 1;  // Reset column to 1 at the beginning of a new line
        } else {
            colNo++;
        }
        pos++;
    }

    string consumeNumber() {
        size_t start = pos;
        bool dotFlag = false;
        while (pos < src.size() && isdigit(src[pos]) || (src[pos] == '.' && !dotFlag)) {
            if(src[pos] == '.'){
                dotFlag = true;
            }
            pos++;
        }
        return src.substr(start, pos -start);
}

    string consumeWord() {
        size_t start = pos;
        while (pos < src.size() && isalnum(src[pos])) {
            pos++;
            colNo++;
        }
        return src.substr(start, pos - start);
    }

    string consumeStringLiteral() {
        pos++;  // Skip the opening quote
        size_t start = pos;
        while (pos < src.size() && src[pos] != '"') {
            pos++;
            colNo++;
        }
        pos++;  // Skip the closing quote
        return src.substr(start, pos - start);
    }
     string consumeCharLiteral() {
        pos++;  // Skip the opening single quote
        char charValue = src[pos];  // Grab the char (e.g., 'a')
        pos++;  // Move past the character
        if (src[pos] != '\'') {  // Ensure closing single quote
            cout << "Syntax error: unclosed character literal at line " << lineNo << ", column " << colNo << endl;
            exit(1);
        }
        pos++;  // Skip the closing single quote
        return string(1, charValue);  // Return the char as a string
    }
};

class Parser {
public:
    Parser(const vector<Token> &tokens) {
        this->tokens = tokens;  
        this->pos = 0;          
    }

    void parseProgram() {
        while (tokens[pos].type != T_EOF) {
            parseStatement();
        }
        cout << "Parsing completed successfully! No Syntax Error" << endl;
    }

private:
    vector<Token> tokens;
    size_t pos;

    void parseStatement() {


        if (tokens[pos].type == T_INT 
            ) {
            parseDeclaration( T_INT );
        }
        else  if (tokens[pos].type == T_DOUBLE) {
            parseDeclaration( T_DOUBLE );
        }
        else if (tokens[pos].type == T_FLOAT ) {
            parseDeclaration( T_FLOAT );
        }
        else if (tokens[pos].type == T_VOID  ) {
            parseDeclaration( T_VOID );
        }
        else if (tokens[pos].type == T_STRING  ) {
            parseDeclaration( T_STRING );
        }
          else if (tokens[pos].type == T_CHAR  ) {
            parseDeclaration( T_CHAR );
        }
        else if (tokens[pos].type == T_BOOL  ) {
            parseDeclaration( T_BOOL );
        }
        else if (tokens[pos].type == T_ID) {
            parseAssignment();
        } else if (tokens[pos].type == T_IF) {
            parseIfStatement();
        }
        else if (tokens[pos].type == T_AGAR) {
            parseAgarStatement();
        } else if (tokens[pos].type == T_RETURN) {
            parseReturnStatement();
        } else if (tokens[pos].type == T_LBRACE) {  
            parseBlock();
        }else if (tokens[pos].type == T_FOR) { 
            parseForStatement();
        } else if (tokens[pos].type == T_WHILE) { 
            parseWhileStatement();
        } else if (tokens[pos].type == T_SWITCH) { 
            parseSwitchStatement();
        } else if (tokens[pos].type == T_BREAK) { 
            parseBreakStatement();
        } else {
            cout << "Syntax error: unexpected token '" << tokens[pos].value 
                 << "' at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
            exit(1);
        }
    }

    void parseBlock() {
        expect(T_LBRACE);  
        while (tokens[pos].type != T_RBRACE && tokens[pos].type != T_EOF) {
            parseStatement();
        }
        expect(T_RBRACE);  
    }

    void parseDeclaration(TokenType a) {
        expect(a);
        expect(T_ID);
        expect(T_SEMICOLON);
    }

    void parseAssignment( ) {
        expect(T_ID);
        expect(T_ASSIGN);
        parseExpression();
        expect(T_SEMICOLON);
    }

    void parseIfStatement() {
        expect(T_IF);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        parseStatement();  
        if (tokens[pos].type == T_ELSE) {
            expect(T_ELSE);
            parseStatement();  
        }
    }
    void parseAgarStatement() {
        expect(T_AGAR);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        parseStatement();  
        if (tokens[pos].type == T_MAGAR) {
            expect(T_MAGAR);
            parseStatement();  
        }
    }

    void parseReturnStatement() {
        expect(T_RETURN);
        parseExpression();
        expect(T_SEMICOLON);
    }

     void parseForStatement() {
        cout << "Parsing for statement" << endl;
        expect(T_FOR);
        expect(T_LPAREN);
    
        // Parse the initialization statement (e.g., int i = 0)
        parseDeclaration(T_INT);  // Assumes an `int` variable declaration, can extend if needed

        // Parse the condition (e.g., i < 5)
        parseExpression();
        expect(T_SEMICOLON);

        // Parse the increment or decrement part (e.g., i++, i--)
        parseIncrementDecrement();
        expect(T_RPAREN);

        parseBlock();  // Parse the body of the `for` loop
    }

    void parseIncrementDecrement() {
        expect(T_ID);  // The iterator variable (e.g., i)
        if (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS) {
            TokenType op = tokens[pos].type;
            pos++;
            if (tokens[pos].type == op) {  // Expect `++` or `--`
                pos++;
            } else {
                cout << "Syntax error: expected '++' or '--' at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
                exit(1);
            }
        } else {
            cout << "Syntax error: expected increment/decrement operator at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
            exit(1);
        }
    }

    void parseWhileStatement() {
        cout << "Parsing while statement" << endl;
        pos++;
        expect(T_LPAREN);
        expect(T_ID); // Placeholder for condition
        expect(T_RPAREN);
        expect(T_LBRACE);
        expect(T_RBRACE);
    }

    void parseSwitchStatement() {
        cout << "Parsing switch statement" << endl;
        pos++;
        expect(T_LPAREN);
        expect(T_ID); // Placeholder for switch variable
        expect(T_RPAREN);
        expect(T_LBRACE);
        // Process cases
        while (tokens[pos].type == T_CASE) {
            parseCaseStatement();
        }
        expect(T_RBRACE);
    }

    void parseCaseStatement() {
        cout << "Parsing case statement" << endl;
        pos++;
        expect(T_NUM); // Placeholder for case value
        expect(T_COLON); // Assuming a colon token type
        expect(T_ID); // Placeholder for case body
        expect(T_SEMICOLON);
    }

    void parseBreakStatement() {
        cout << "Parsing break statement" << endl;
        pos++;
        expect(T_SEMICOLON);
    }


    void parseExpression() {
        parseTerm();
        while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS) {
            pos++;
            parseTerm();
        }
        if (tokens[pos].type == T_GT) {
            pos++;
            parseExpression();  // After relational operator, parse the next expression
        }
    }

    void parseTerm() {
        parseFactor();
        while (tokens[pos].type == T_MUL || tokens[pos].type == T_DIV) {
            pos++;
            parseFactor();
        }
    }

   
    void parseFactor() {
    if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID ||
     tokens[pos].type == T_STRING_LITERAL || tokens[pos].type == T_CHAR_LITERAL ) {
        pos++;
    } else if (tokens[pos].type == T_LPAREN) {
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
    } else {
        cout << "Syntax error: unexpected token '" << tokens[pos].value 
             << "' at line " << tokens[pos].lineNo 
             << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}
void expect(TokenType type) {
    if (tokens[pos].type == type) {
        pos++;
    } else {
        cout << "Syntax error: expected '" << tokenTypeToString(type) 
             << "' but found '" << tokens[pos].value 
             << "' at line " << tokens[pos].lineNo 
             << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}


string tokenTypeToString(TokenType type) {
    switch (type) {
        case T_BOOL: return "T_BOOL";
        case T_CHAR: return "T_CHAR";
        case T_STRING: return "T_STRING";
        case T_FLOAT: return "T_FLOAT";
        case T_DOUBLE: return "T_DOUBLE";
        case T_VOID: return "T_VOID";
        case T_INT: return "T_INT";
        case T_ID: return "T_ID";
        case T_NUM: return "T_NUM";
        case T_IF: return "T_IF";
        case T_ELSE: return "T_ELSE";
        case T_RETURN: return "T_RETURN";
        case T_ASSIGN: return "T_ASSIGN";
        case T_PLUS: return "T_PLUS";
        case T_MINUS: return "T_MINUS";
        case T_MUL: return "T_MUL";
        case T_DIV: return "T_DIV";
        case T_LPAREN: return "T_LPAREN";
        case T_RPAREN: return "T_RPAREN";
        case T_LBRACE: return "T_LBRACE";
        case T_RBRACE: return "T_RBRACE";
        case T_SEMICOLON: return "T_SEMICOLON";
        case T_GT: return "T_GT";
        case T_EOF: return "T_EOF";
        default: return "UNKNOWN_TOKEN";
    }
}


};

int main() {
    string input = R"(
        int b ;
        string naseeb ;
        char ammad  ; 
        float dd;
        dd = 2.5 ; 
        void a ;
        double ajmal ; 
        bool hello ; 
        char ammad  ; 
        ammad = 'b';
        naseeb = "burhan";
        a = 5;
        int b;
        b = a + 10;
        if (b > 10) {
            return b;
        } else {
            return 0;
        }
        agar (b > 10) {
            return b;
        } magar {
            return 0;
        }


        for (int i = 0; i < 5 ; i++) {
        int count ;
        count = 0 ; 

        }
        int count;
        count = 0;

        while (count < 5) {
            count++;
        }
        int num ;
        num = 2;
        switch (num) {
        case 1:
            
            break;
        case 2:
            
            break;
        case 3:
            
            break;
        default:
            
        }

        void printData()
        {
        
        }



    )";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    
    // Parser parser(tokens);
    // parser.parseProgram();

    return 0;
}
