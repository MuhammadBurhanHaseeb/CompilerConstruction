#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <unordered_map>

using namespace std;

enum TokenType {
    T_CHAR_LITERAL , T_STRING_LITERAL,
    T_STRING, T_FLOAT, T_DOUBLE, T_CHAR, T_VOID, T_BOOL, T_INT,
     T_FOR, T_WHILE, T_SWITCH, T_CASE, T_BREAK,T_DEFAULT,
    T_ID, T_NUM, T_IF, T_ELSE, T_RETURN, 
    T_ASSIGN, T_PLUS, T_MINUS, T_MUL, T_DIV, 
    T_LPAREN, T_RPAREN, T_LBRACE, T_RBRACE,  
    T_SEMICOLON, T_GT,T_LT,T_LE,T_GE,T_NEQ,T_EQ ,T_EOF, T_COLON,T_COMMA,
    T_AGR , T_MAGR,
    T_INCREMENT,T_DECREMENT,  
    T_AND , T_OR ,
    T_PRIVATE , T_PUBLIC , T_PROTECTED,
    T_STRUCT , T_CLASS ,
    T_TRY , T_CATCH, T_ETARGET   
      
};

struct Token {
    TokenType type;
    string value;
    int lineNo;
    int colNo;
};

class Lexer {

    char peek() const {
    return (pos + 1 < src.size()) ? src[pos + 1] : '\0';
    }
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

            // Handle single-line comments starting with "//"
        if (current == '/' && peek() == '/') {
            pos += 2;  // Skip the "//"
            while (pos < src.size() && src[pos] != '\n') {
                pos++;  // Skip until end of line
            }
            continue;  // Ignore the comment and move to the next character
        }

        // Handle multi-line comments starting with "/*"
        if (current == '/' && peek() == '*') {
            pos += 2;  // Skip the "/*"
            while (pos < src.size() - 1 && !(src[pos] == '*' && peek() == '/')) {
                pos++;  // Skip until "*/" is found
            }
            pos += 2;  // Skip the closing "*/"
            continue;  // Ignore the comment and move to the next character
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

                else if (word == "agr") tokens.push_back(Token{T_AGR, word, lineNo, colNo});
                else if (word == "magr") tokens.push_back(Token{T_MAGR, word, lineNo, colNo});

                else if (word == "for") tokens.push_back(Token{T_FOR, word, lineNo, colNo});       
                else if (word == "while") tokens.push_back(Token{T_WHILE, word, lineNo, colNo});   
                else if (word == "switch") tokens.push_back(Token{T_SWITCH, word, lineNo, colNo});
                else if (word == "default") tokens.push_back(Token{T_DEFAULT, word, lineNo, colNo}); 
                else if (word == "case") tokens.push_back(Token{T_CASE, word, lineNo, colNo});  
                else if (word == "break") tokens.push_back(Token{T_BREAK, word, lineNo, colNo});  

                else if (word == "private") tokens.push_back(Token{T_PRIVATE, word, lineNo, colNo});       
                else if (word == "public") tokens.push_back(Token{T_PUBLIC, word, lineNo, colNo});   
                else if (word == "protected") tokens.push_back(Token{T_PROTECTED, word, lineNo, colNo});
                else if (word == "struct") tokens.push_back(Token{T_STRUCT, word, lineNo, colNo}); 
                else if (word == "class") tokens.push_back(Token{T_CLASS, word, lineNo, colNo}); 
                else if (word == "try") tokens.push_back(Token{T_TRY, word, lineNo, colNo});
                else if (word == "catch") tokens.push_back(Token{T_CATCH, word, lineNo, colNo}); 
                else if (word == "e") tokens.push_back(Token{T_ETARGET, word, lineNo, colNo});   

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
                case ',': tokens.push_back(Token{T_COMMA, ",", lineNo, colNo}); break;
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
                case '&':
                    current = src[pos+1];
                    if (current == '&') {
                        tokens.push_back(Token{T_AND, "&&", lineNo, colNo});
                        pos++; colNo++;
                    }
                    break;
                case '|':
                    current = src[pos+1];
                    if (current == '|') {
                        tokens.push_back(Token{T_OR, "||", lineNo, colNo});
                        pos++; colNo++;
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


        if (tokens[pos].type == T_INT  && tokens[pos+2].type == T_ASSIGN) {
            parseDeclarationAssignment( T_INT );
        }
        else if (tokens[pos].type == T_INT) {
            parseDeclaration( T_INT );
        }
        else  if (tokens[pos].type == T_DOUBLE && tokens[pos+2].type == T_ASSIGN ) {
            parseDeclarationAssignment( T_DOUBLE );
        }
        else  if (tokens[pos].type == T_DOUBLE) {
            parseDeclaration( T_DOUBLE );
        }
        else if (tokens[pos].type == T_FLOAT  && tokens[pos+2].type == T_ASSIGN ) {
            parseDeclarationAssignment( T_FLOAT );
        }
        else if (tokens[pos].type == T_FLOAT ) {
            parseDeclaration( T_FLOAT );
        }
        else if ((tokens[pos].type == T_VOID  || tokens[pos].type == T_INT ||
                 tokens[pos].type == T_STRING  || tokens[pos].type == T_BOOL ||
                 tokens[pos].type == T_FLOAT  || tokens[pos].type == T_DOUBLE  ||
                 tokens[pos].type == T_CHAR) && tokens[pos+2 ].type == T_LPAREN ) {

                parseFunctionStatement();
        }
        else if (tokens[pos].type == T_STRING && tokens[pos+2].type == T_ASSIGN  ) {
            parseDeclarationAssignment( T_STRING );
        }
        else if (tokens[pos].type == T_STRING  ) {
            parseDeclaration( T_STRING );
        }
          else if (tokens[pos].type == T_CHAR && tokens[pos+2].type == T_ASSIGN ) {
            parseDeclarationAssignment( T_CHAR );
        }
         else if (tokens[pos].type == T_CHAR  ) {
            parseDeclaration( T_CHAR );
        }
        else if (tokens[pos].type == T_BOOL  && tokens[pos+2].type == T_ASSIGN) {
            parseDeclarationAssignment( T_BOOL );
        }
        else if (tokens[pos].type == T_BOOL  ) {
            parseDeclaration( T_BOOL );
        }
        else if (tokens[pos].type == T_ID) {
            if(tokens[pos+1].type == T_INCREMENT )
            {
                parseIncrementAssignment();
            }
            else if (tokens[pos +1].type == T_DECREMENT )
            {
                parseDecrementAssignment();
            }
            else{
                parseAssignment();
            }
        } else if (tokens[pos].type == T_IF) {
            parseIfStatement();
        }
        else if (tokens[pos].type == T_AGR) {
            parseAgrStatement();
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
        }else if (tokens[pos].type == T_CLASS) { 
            parseClassStatement();
        }else if (tokens[pos].type == T_STRUCT) { 
            parseStructStatement();
        } else if (tokens[pos].type == T_PROTECTED) { 
            parseProtectedStatement();
        } else if (tokens[pos].type == T_PRIVATE) { 
            parsePrivateStatement();
        }else if (tokens[pos].type == T_PUBLIC) { 
            parsePublicStatement();
        }
        else if (tokens[pos].type == T_TRY) { 
            parseTryCatchStatement();
        }
         else {
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

    void VoidFunctionDeclaration()
    {
        expect(T_VOID);
        expect(T_ID);

    }

    void parseAssignment( ) {
        expect(T_ID);
        expect(T_ASSIGN);
        parseExpression();
        expect(T_SEMICOLON);
    }
    void parseIncrementAssignment( ) {
        expect(T_ID);
        expect(T_INCREMENT);
        expect(T_SEMICOLON);
    }
    void parseDecrementAssignment( ) {
        expect(T_ID);
        expect(T_DECREMENT);
        expect(T_SEMICOLON);
    }
     void parseDeclarationAssignment(TokenType a ) {
        expect(a);
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
    void parseAgrStatement() {
        expect(T_AGR);
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        parseStatement();  
        if (tokens[pos].type == T_MAGR) {
            expect(T_MAGR);
            parseStatement();  
        }
    }

    void parseClassStatement()
    {
        expect(T_CLASS);
        expect(T_ID);
        parseBlock();
        expect(T_SEMICOLON);
    }
    void parseStructStatement()
    {
        expect(T_STRUCT);
        expect(T_ID);
        parseBlock();
        expect(T_SEMICOLON);

    }

    void parsePublicStatement()
    {
        expect(T_PUBLIC);
        expect(T_ID);
        expect(T_SEMICOLON);
    }
     void parsePrivateStatement()
    {
        expect(T_PRIVATE);
        expect(T_ID);
        expect(T_SEMICOLON);
    }
     void parseProtectedStatement()
    {
        expect(T_PROTECTED);
        expect(T_ID);
        expect(T_SEMICOLON);
    }

    void parseTryCatchStatement ()
    {
        expect(T_TRY);
        parseBlock();
        expect(T_CATCH);
        expect(T_LPAREN);
        expect(T_ETARGET);
        expect(T_RPAREN);
        parseBlock();
    }


    void parseReturnStatement() {
        expect(T_RETURN);
        parseExpression();
        expect(T_SEMICOLON);
    }

     void parseForStatement() {
        expect(T_FOR);
        expect(T_LPAREN);
    
        // Parse the initialization statement (e.g., int i = 0)
        parseDeclarationAssignment(T_INT);
        // Parse the condition (e.g., i < 5)
        parseExpression();
        expect(T_SEMICOLON);

        // Parse the increment or decrement part (e.g., i++, i--)
        parseIncrementDecrement();
        expect(T_RPAREN);

        parseBlock();  // Parse the body of the `for` loop
    }

   void parseIncrementDecrement() {
    expect(T_ID);  // Expect the iterator variable (e.g., i)

    if (tokens[pos].type == T_INCREMENT) {  // Check for `++`
        pos++;  // Move past the `++` token
    } else if (tokens[pos].type == T_DECREMENT) {  // Check for `--`
        pos++;  // Move past the `--` token
    } else {
        cout << "Syntax error: expected increment (++) or decrement (--) operator at line "
             << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}


    void parseWhileStatement() {
        expect(T_WHILE);
        expect(T_LPAREN);
        parseExpression();  // Parse the condition inside parentheses
        expect(T_RPAREN);
        parseBlock();  // Parse the body of the while loop
    }



void parseSwitchStatement() {
    pos++;
    expect(T_LPAREN);
    expect(T_ID); // Switch variable (or expression)
    expect(T_RPAREN);
    expect(T_LBRACE);

    // Process cases
    while (tokens[pos].type == T_CASE || tokens[pos].type == T_DEFAULT) {
        if (tokens[pos].type == T_CASE) {
            parseCaseStatement();
        } else if (tokens[pos].type == T_DEFAULT) {
            parseDefaultStatement();
        }
    }

    expect(T_RBRACE); // End of switch block
}

void parseCaseStatement() {
    pos++;
    expect(T_NUM); // Case value (like case 1:)
    expect(T_COLON);

    // Parsing the case body: This could be a sequence of statements.
    while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
        parseStatement(); // Assume parseStatement handles a single statement
    }
}

void parseDefaultStatement() {
    pos++;
    expect(T_COLON);

    // Parsing the default body: This could be a sequence of statements.
    while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
        parseStatement(); // Parsing a single statement
    }
}

void parseFunctionStatement() {
    // Parse the return type (e.g., int, void, etc.)
    if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
        tokens[pos].type == T_VOID || tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || 
        tokens[pos].type == T_BOOL) {
        
        pos++;  // Advance past the return type
    } else {
        cout << "Syntax error: expected return type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }

    // Parse the function name (identifier)
    expect(T_ID);

    // Parse the parameter list
    expect(T_LPAREN);
    if (tokens[pos].type != T_RPAREN) {  // If not immediately closing, parse parameters
        parseParameterList();
    }
    expect(T_RPAREN);

    // Parse the function body
    parseBlock();  // Assuming parseBlock handles statements within curly braces
}

void parseParameterList() {
    // Parse parameter type and identifier (e.g., int x, float y)
    parseParameter();
    while (tokens[pos].type == T_COMMA) {  // Support for multiple parameters separated by commas
        pos++;
        parseParameter();
    }
}

void parseParameter() {
    // Expect a type and identifier for each parameter (e.g., int x)
    if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
        tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || tokens[pos].type == T_BOOL) {
        
        pos++;  // Advance past the type
    } else {
        cout << "Syntax error: expected parameter type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
    expect(T_ID);  // Expect parameter name
}
    void parseBreakStatement() {
        pos++;
        expect(T_SEMICOLON);
    }

void parseExpression() {
    parseTerm();
    
    // Handle addition, subtraction, and relational operators in expression
    while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS || 
           tokens[pos].type == T_GT || tokens[pos].type == T_LT ||
           tokens[pos].type == T_GE || tokens[pos].type == T_LE || 
           tokens[pos].type == T_EQ || tokens[pos].type == T_NEQ || 
           tokens[pos].type == T_AND || tokens[pos].type == T_OR ) {
        
        pos++;  // Advance past the operator
        parseTerm();
    }
}
void parseTerm() {
    parseFactor();
    
    // Handle multiplication and division operators
    while (tokens[pos].type == T_MUL || tokens[pos].type == T_DIV) {
        pos++;
        parseFactor();
    }
}

void parseFactor() {
    if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID ||
        tokens[pos].type == T_STRING_LITERAL || tokens[pos].type == T_CHAR_LITERAL) {
        
        string id = tokens[pos].value;  // Store the identifier or literal value
        pos++;  // Advance past literals or identifiers
        
        // Check for increment (++) and decrement (--) after an identifier
        if (tokens[pos].type == T_INCREMENT) {  // If it's increment
            pos++;  // Move past the `++`
            cout << "Incrementing " << id << endl;  // Handle incrementing logic
        } else if (tokens[pos].type == T_DECREMENT) {  // If it's decrement
            pos++;  // Move past the `--`
            cout << "Decrementing " << id << endl;  // Handle decrementing logic
        }
    } else if (tokens[pos].type == T_LPAREN) {
        expect(T_LPAREN);
        parseExpression();
        expect(T_RPAREN);
        
    } else if (tokens[pos].type == T_ASSIGN) {
        pos++;  // Move past the assignment
        parseExpression();  // Expect an expression after `=`

    } else {
        cout << "Syntax error: unexpected token '" << tokens[pos].value 
             << "' at line " << tokens[pos].lineNo 
             << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}





void expect(TokenType type) {
    if (tokens[pos].type == type) {
        pos++;  // Move to the next token if the expected token is found
    } else {
        cout << "Syntax error: expected '" << tokenTypeToString(type) 
             << "' but found '" << tokens[pos].value 
             << "' at line " << tokens[pos].lineNo 
             << ", column " << tokens[pos].colNo << endl;
        
        // Suggest a possible fix
        string suggestion = suggestFix(type);
        if (!suggestion.empty()) {
            cout << "Suggested fix: " << suggestion << endl;
        }
        
        exit(1);  // Exit after showing the error and suggestion
    }
}

string suggestFix(TokenType expectedType) {
    string suggestion = "";

    switch (expectedType) {
        case T_SEMICOLON:
            suggestion = "add a semicolon at the end of the statement.";
            break;
        case T_LPAREN:
            suggestion = "add a '(' before the expression.";
            break;
        case T_RPAREN:
            suggestion = "add a ')' after the expression.";
            break;
        case T_LBRACE:
            suggestion = "add a '{' to begin the block.";
            break;
        case T_RBRACE:
            suggestion = "add a '}' to close the block.";
            break;
        case T_ID:
            suggestion = "check if you missed defining the identifier.";
            break;
        case T_ASSIGN:
            suggestion = "add an '=' to assign a value.";
            break;
        case T_RETURN:
            suggestion = "make sure 'return' is followed by an expression (if applicable).";
            break;
        case T_IF:
            suggestion = "ensure that 'if' is followed by a condition and block.";
            break;
        case T_ELSE:
            suggestion = "make sure 'else' is followed by a block.";
            break;
        default:
            suggestion = "check the syntax near this token.";
            break;
    }

    return suggestion;
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
        case T_AGR: return "T_AGR";
        case T_MAGR: return "T_MAGR";
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

        agr (b && 10) {
            return b;
        } magr {
            return 0;
        }
        for (int i = 0; i < 5 ; i++) {
        int count ;
        count = 0 ; 

        }
        class bhb {
            protected ajmal ; 
            private car ;
            public model ; 
        };
        struct room {
            protected studentName ; 
            private studentCgpa ;
            public studentRollNo ; 
        };
        // hello burhan butt is here 
        /* hello burhan butt is here */
        int count;
        count = 0;
        while (count < 5) {
            count++;
        }
        int bum = 4  ;
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
            break ;
            
        }
        void printData()
        {

        }
        string  printData( int a  , char b )
        {
            if (a < b  )
            {
            }
            return a ;
        }
        try {
        }
        catch (e)
        {
        }

    )";

    Lexer lexer(input);
    vector<Token> tokens = lexer.tokenize();
    
    Parser parser(tokens);
    parser.parseProgram();

    return 0;
}


