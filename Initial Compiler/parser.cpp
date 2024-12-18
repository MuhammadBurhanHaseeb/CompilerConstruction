#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <stack>
#include <stdexcept>
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

class SymbolTable {
public:

    void declareVariable(const string &name, const string &type) {
        if (symbolTable.find(name) != symbolTable.end()) {
            throw runtime_error("Semantic error: Variable '" + name + "' is already declared.");
        }
        symbolTable[name] = make_pair(type, "undefined");
    }

    string getVariableType(const string &name) {
        if (symbolTable.find(name) == symbolTable.end()) {
            throw runtime_error("Semantic error: Variable '" + name + "' is not declared.");
        }
        return symbolTable[name].first;
    }

    bool isDeclared(const string &name) const {
        return symbolTable.find(name) != symbolTable.end();
    }

    void setMemberAccess(const string& memberName, const string& accessType) {
    if (symbolTable.find(memberName) == symbolTable.end()) {
        cout << "Error: Member '" << memberName << "' is not declared." << endl;
        exit(1);
    }
        symbolTable[memberName].second = accessType;  // Set the access modifier (e.g., public, private, protected)
    }

    void declareStruct(const string& structName) {
    if (structTable.find(structName) != structTable.end()) {
        cout << "Error: Struct '" << structName << "' is already declared." << endl;
        exit(1);
    }
    structTable[structName] = { "struct", {} };  // Add a new entry with type "struct" and an empty member list
    }

    void declareClass(const string& className) {
    if (classTable.find(className) != classTable.end()) {
        cout << "Error: Class '" << className << "' is already declared." << endl;
        exit(1);
    }
    classTable[className] = { "class", {} };  // Add a new entry with type "class" and an empty member list
    }

     // Declare a function
    void declareFunction(const string &funcName, const string &returnType, const vector<string> &paramTypes) {
        if (functionTable.find(funcName) != functionTable.end()) {
            throw runtime_error("Semantic error: Function '" + funcName + "' is already declared.");
        }
        functionTable[funcName] = {returnType, paramTypes};  // Store return type and parameter types
    }

    // Get the function's return type and parameter types
    pair<string, vector<string>> getFunctionInfo(const string &funcName) {
        if (functionTable.find(funcName) == functionTable.end()) {
            throw runtime_error("Error: Function '" + funcName + "' not declared.");
        }
        return functionTable[funcName];
    }

    // Check if a function is declared
    bool isFunctionDeclared(const string &funcName) {
        return functionTable.find(funcName) != functionTable.end();
    }

    // Print the symbol table
    void printSymbolTable() const {
        cout << "Symbol Table (Variables):\n";
        for (const auto &entry : symbolTable) {
            cout << entry.first << " : " << entry.second.first << " (" << entry.second.second << ")\n";
        }

        cout << "\nClasses:\n";
        for (const auto &entry : classTable) {
            cout << entry.first << "\n";
        }

        cout << "\nFunctions:\n";
        for (const auto &entry : functionTable) {
            cout << entry.first << " : " << entry.second.first << "(";
            for (const auto &param : entry.second.second) {
                cout << param << ", ";
            }
            cout << ")\n";
        }
    }
    

private:
    // map<string, string> symbolTable;
    map<string, pair<string, string>> symbolTable;
    unordered_map<string, vector<string>> classTable;
    unordered_map<string, vector<string>> structTable;
    unordered_map<string, pair<string, vector<string>>> functionTable;

};

class IntermediateCodeGnerator {
public:
    vector<string> instructions;
    int tempCount = 0;
    int labelCount = 0 ; 
    stack<string> breakLabelStack;

    string newTemp() {
        return "t" + to_string(tempCount++);
    }
    string newLabel() {
        return "L" + to_string(labelCount++);
    }

    void addInstruction(const string &instr) {
        instructions.push_back(instr);
    }

    void printInstructions() {
        for (const auto &instr : instructions) {
            cout << instr << endl;
        }
    }
    void addLabelInstruction(const string &label) {
        instructions.push_back(label + ":");  // Labels are typically followed by a colon
    }

    // Add a jump instruction (for example, for `goto` statements)
    void addJumpInstruction(const string &label) {
        instructions.push_back("goto " + label);
    }

    // Add conditional jump (e.g., for `if` statements, `break` or `continue`)
    void addConditionalJump(const string &cond, const string &label) {
        instructions.push_back("if " + cond + " goto " + label);
    }
    void pushBreakLabel() {
        string breakLabel = "break_" + to_string(labelCount++);
        breakLabelStack.push(breakLabel);
    }

    // Method to get the current (top) break label.
    string getCurrentBreakLabel() {
        if (breakLabelStack.empty()) {
            throw runtime_error("No active loop or switch statement for break.");
        }
        return breakLabelStack.top();
    }

    // Method to pop the break label from the stack when exiting the loop or switch.
    void popBreakLabel() {
        if (breakLabelStack.empty()) {
            throw runtime_error("No active break label to pop.");
        }
        breakLabelStack.pop();
    }
};



class AssemblyCodeGenerator
{
private:
    vector<string> assemblyCode;
    int labelCounter;
    unordered_map<string, string> variableRegisterMap;
    int registerCounter = 0;

    string allocateRegister(const string &var)
    {
        if (variableRegisterMap.find(var) == variableRegisterMap.end())
        {
            variableRegisterMap[var] = "r" + to_string(registerCounter++);
        }
        return variableRegisterMap[var];
    }

    string generateLabel()
    {
        return "L" + to_string(labelCounter++);
    }

    void addInstruction(const string &instruction)
    {
        assemblyCode.push_back(instruction);
    }

    void processAssignment(const string &line)
    {
        auto eqPos = line.find("=");
        string tVar = line.substr(0, eqPos);
        string value = line.substr(eqPos + 1);

        tVar = trim(tVar);
        value = trim(value);

        string targetRegister = allocateRegister(tVar);

        // Direct assignment
        if (isdigit(value[0]))
        {
            addInstruction("li " + targetRegister + ", " + value);
        }
        else
        {
            string sourceRegister = allocateRegister(value);
            addInstruction("move " + targetRegister + ", " + sourceRegister);
        }
    }

    void processBinaryOperation(const string &line)
    {
        static const unordered_map<string, string> operationMap = {
            {"+", "add"},
            {"-", "sub"},
            {"*", "mul"},
            {"/", "div"}};

        auto eqPos = line.find("=");
        string tVar = line.substr(0, eqPos);
        string expr = line.substr(eqPos + 1);

        string op;
        for (const auto &entry : operationMap)
        {
            if (expr.find(entry.first) != string::npos)
            {
                op = entry.first;
                break;
            }
        }

        auto opPos = expr.find(op);
        string lhs = expr.substr(0, opPos);
        string rhs = expr.substr(opPos + 1);

        tVar = trim(tVar);
        lhs = trim(lhs);
        rhs = trim(rhs);

        string targetRegister = allocateRegister(tVar);
        string lhsRegister = isdigit(lhs[0]) ? allocateRegister(generateTempRegister(lhs)) : allocateRegister(lhs);
        string rhsRegister = isdigit(rhs[0]) ? allocateRegister(generateTempRegister(rhs)) : allocateRegister(rhs);

        if (isdigit(lhs[0]))
            addInstruction("li " + lhsRegister + ", " + lhs);
        if (isdigit(rhs[0]))
            addInstruction("li " + rhsRegister + ", " + rhs);

        addInstruction(operationMap.at(op) + " " + targetRegister + ", " + lhsRegister + ", " + rhsRegister);
    }

    void processRelationalOperation(const string &line)
    {
        auto eqPos = line.find("=");
        string tVar = line.substr(0, eqPos);
        string expr = line.substr(eqPos + 1);

        tVar = trim(tVar);

        string op;
        if (expr.find(">=") != string::npos)
            op = ">=";
        else if (expr.find("<=") != string::npos)
            op = "<=";
        else if (expr.find("==") != string::npos)
            op = "==";
        else if (expr.find("!=") != string::npos)
            op = "!=";
        else if (expr.find(">") != string::npos)
            op = ">";
        else if (expr.find("<") != string::npos)
            op = "<";

        auto opPos = expr.find(op);
        string lhs = expr.substr(0, opPos);
        string rhs = expr.substr(opPos + op.size());

        lhs = trim(lhs);
        rhs = trim(rhs);

        string lhsReg = isdigit(lhs[0]) ? allocateRegister(generateTempRegister(lhs)) : allocateRegister(lhs);
        string rhsReg = isdigit(rhs[0]) ? allocateRegister(generateTempRegister(rhs)) : allocateRegister(rhs);
        string resultReg = allocateRegister(tVar);

        if (isdigit(lhs[0]))
            addInstruction("li " + lhsReg + ", " + lhs);
        if (isdigit(rhs[0]))
            addInstruction("li " + rhsReg + ", " + rhs);

        if (op == ">")
        {
            addInstruction("sgt " + resultReg + ", " + lhsReg + ", " + rhsReg);
        }
        else if (op == "<")
        {
            addInstruction("slt " + resultReg + ", " + lhsReg + ", " + rhsReg);
        }
        else if (op == ">=")
        {
            addInstruction("slt " + resultReg + ", " + lhsReg + ", " + rhsReg);
            addInstruction("seqz " + resultReg + ", " + resultReg);
        }
        else if (op == "<=")
        {
            addInstruction("sgt " + resultReg + ", " + lhsReg + ", " + rhsReg);
            addInstruction("seqz " + resultReg + ", " + resultReg);
        }
        else if (op == "==")
        {
            addInstruction("sub " + resultReg + ", " + lhsReg + ", " + rhsReg);
            addInstruction("seqz " + resultReg + ", " + resultReg);
        }
        else if (op == "!=")
        {
            addInstruction("sub " + resultReg + ", " + lhsReg + ", " + rhsReg);
            addInstruction("snez " + resultReg + ", " + resultReg);
        }
    }

    void processConditional(const string &line)
    {
        auto ifPos = line.find("if");
        auto gotoPos = line.find("goto");
        string condition = line.substr(ifPos + 2, gotoPos - (ifPos + 2));
        string label = line.substr(gotoPos + 4);

        condition = trim(condition);
        label = trim(label);

        string conditionReg = allocateRegister(condition);
        addInstruction("bne " + conditionReg + ", x0, " + label);
    }

    void processGoto(const string &line)
    {
        auto gotoPos = line.find("goto");
        string label = line.substr(gotoPos + 4);
        label = trim(label);

        addInstruction("jmp " + label);
    }

    void processLabel(const string &line)
    {
        addInstruction(line);
    }

    string generateTempRegister(const string &value)
    {
        return "temp_" + value;
    }

    string trim(const string &str)
    {
        auto start = str.find_first_not_of(" \t");
        auto end = str.find_last_not_of(" \t");
        return (start == string::npos) ? "" : str.substr(start, end - start + 1);
    }

public:
    AssemblyCodeGenerator() : labelCounter(0) {}

    void generateAssembly(const vector<string> &intermediateCode)
    {
        for (const auto &line : intermediateCode)
        {
            string Line = trim(line);
            if (Line.empty())
                continue;

            if (Line.find("=") != string::npos)
            {
                if (Line.find(">") != string::npos || Line.find("<") != string::npos ||
                    Line.find("==") != string::npos || Line.find(">=") != string::npos ||
                    Line.find("<=") != string::npos || Line.find("!=") != string::npos)
                {
                    processRelationalOperation(Line);
                }
                else if (Line.find("+") != string::npos ||
                         Line.find("-") != string::npos ||
                         Line.find("*") != string::npos ||
                         Line.find("/") != string::npos)
                {
                    processBinaryOperation(Line);
                }
                else
                {
                    processAssignment(Line);
                }
            }
            else if (Line.find("if") == 0)
            {
                processConditional(Line);
            }
            else if (Line.find("goto") == 0)
            {
                processGoto(Line);
            }
            else if (Line.back() == ':')
            {
                processLabel(Line);
            }
        }
    }

    void printAssemblyCode()
    {
        cout << "\n\n============================="<<endl;
        cout << "ASSEMBLY CODE:" << endl;
        cout << "============================="<<endl;
        for (const auto &instruction : assemblyCode)
        {
            cout << instruction << "\n";
        }
        cout << "\n\n";
    }
};




class Parser {
public:

    //Constructor
    Parser(const vector<Token> &tokens, SymbolTable &symTable, IntermediateCodeGnerator &icg)
        : tokens(tokens), pos(0), symTable(symTable), icg(icg) {}
        //here the private member of this class are being initalized with the arguments passed to this constructor
    // Parser(const vector<Token> &tokens) {
    //     this->tokens = tokens;  
    //     this->pos = 0;          
    // }

    void parseProgram() {
        while (tokens[pos].type != T_EOF) {
            parseStatement();
        }
        cout << "Parsing completed successfully! No Syntax Error" << endl;
    }

private:
    vector<Token> tokens;
    size_t pos;
    SymbolTable &symTable;
    IntermediateCodeGnerator &icg;

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
        // expect(a);
        // expect(T_ID);
        // expect(T_SEMICOLON);

        expect(a);  // Expect and consume the int keyword.
        string varName = expectAndReturnValue(T_ID); // Expect and return the variable name (identifier).
        string b ; 
        if (a == T_INT  )   b = "int";
        else if (a == T_BOOL  )   b = "bool";
        else if (a == T_STRING  )   b = "string";
        else if (a == T_FLOAT  )   b = "float";
        else if (a == T_CHAR  )   b = "char";
        else if (a == T_DOUBLE  )   b = "double";
        symTable.declareVariable(varName, b); // Register the variable in the symbol table with type "int".
        expect(T_SEMICOLON); // Expect the semicolon to end the statement.
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

        string varName = expectAndReturnValue(T_ID);
        symTable.getVariableType(varName);    // Ensure the variable is declared in the symbol table.
        expect(T_ASSIGN);
        string expr = parseExpression();
        icg.addInstruction(varName + " = " + expr);  // Generate intermediate code for the assignment.
        expect(T_SEMICOLON);
    }
    void parseIncrementAssignment( ) {
        // expect(T_ID);
        // expect(T_INCREMENT);
        // expect(T_SEMICOLON);

        string varName = expectAndReturnValue(T_ID);  
        symTable.getVariableType(varName);  

        expect(T_INCREMENT);  
        icg.addInstruction(varName + " = " + varName + " + 1");  

        expect(T_SEMICOLON);
    }
    void parseDecrementAssignment( ) {
        // expect(T_ID);
        // expect(T_DECREMENT);
        // expect(T_SEMICOLON);

        string varName = expectAndReturnValue(T_ID);  
        symTable.getVariableType(varName);
        expect(T_DECREMENT); 
        icg.addInstruction(varName + " = " + varName + " - 1");  
        expect(T_SEMICOLON); 
    }
     void parseDeclarationAssignment(TokenType a ) {
        // expect(a);
        // expect(T_ID);
        // expect(T_ASSIGN);
        // parseExpression();
        // expect(T_SEMICOLON);

         expect(a);
        string varName = expectAndReturnValue(T_ID);  
        symTable.declareVariable(varName, tokenTypeToString(a));  

        expect(T_ASSIGN); 
        string expr = parseExpression();  
        icg.addInstruction(varName + " = " + expr);  
    
        expect(T_SEMICOLON); 
    }

    void parseIfStatement() {
        // expect(T_IF);
        // expect(T_LPAREN);
        // parseExpression();
        // expect(T_RPAREN);
        // parseStatement();  
        // if (tokens[pos].type == T_ELSE) {
        //     expect(T_ELSE);
        //     parseStatement();  
        // }


        expect(T_IF);
        expect(T_LPAREN);               
        string cond = parseExpression(); 
        expect(T_RPAREN);

        string temp = icg.newTemp();    
        icg.addInstruction(temp + " = " + cond);      

        icg.addInstruction("if " + temp + " goto L1");   
        icg.addInstruction("goto L2");                 
        icg.addInstruction("L1:");                    

        parseStatement();

        if (tokens[pos].type == T_ELSE) {           
            icg.addInstruction("goto L3");
            icg.addInstruction("L2:");
            expect(T_ELSE);
            parseStatement();     
            icg.addInstruction("L3:");
        } else {
            icg.addInstruction("L2:");
        }
    }
    void parseAgrStatement() {
        // expect(T_AGR);
        // expect(T_LPAREN);
        // parseExpression();
        // expect(T_RPAREN);
        // parseStatement();  
        // if (tokens[pos].type == T_MAGR) {
        //     expect(T_MAGR);
        //     parseStatement();  
        // }


        expect(T_AGR);
        expect(T_LPAREN);             
        string cond = parseExpression(); 
        expect(T_RPAREN);

        string temp = icg.newTemp();   
        icg.addInstruction(temp + " = " + cond);        

        icg.addInstruction("agr " + temp + " goto L1");  
        icg.addInstruction("goto L2");                  
        icg.addInstruction("L1:");            

        parseStatement();

        if (tokens[pos].type == T_MAGR) {          
            icg.addInstruction("goto L3");
            icg.addInstruction("L2:");
            expect(T_MAGR);
            parseStatement();      
            icg.addInstruction("L3:");
        } else {
            icg.addInstruction("L2:");
        }
    }

    void parseClassStatement()
    {
        // expect(T_CLASS);
        // expect(T_ID);
        // parseBlock();
        // expect(T_SEMICOLON);


        expect(T_CLASS);  
    string className = expectAndReturnValue(T_ID);  
    symTable.declareClass(className); 

    icg.addInstruction("class " + className + " {");  

    parseBlock();  

    icg.addInstruction("}");
    expect(T_SEMICOLON);  
    }
    void parseStructStatement()
    {
        // expect(T_STRUCT);
        // expect(T_ID);
        // parseBlock();
        // expect(T_SEMICOLON);


        expect(T_STRUCT); 
    string structName = expectAndReturnValue(T_ID); 
    symTable.declareStruct(structName);  

    icg.addInstruction("struct " + structName + " {");  

    parseBlock();  

    icg.addInstruction("}");  
    expect(T_SEMICOLON); 

    }

    void parsePublicStatement()
    {
        // expect(T_PUBLIC);
        // expect(T_ID);
        // expect(T_SEMICOLON);

        expect(T_PUBLIC); 
    string memberName = expectAndReturnValue(T_ID);  
    symTable.setMemberAccess(memberName, "public");  

    icg.addInstruction("public " + memberName + ";"); 
    expect(T_SEMICOLON);
    }
     void parsePrivateStatement()
    {
        // expect(T_PRIVATE);
        // expect(T_ID);
        // expect(T_SEMICOLON);

         expect(T_PRIVATE);  
    string memberName = expectAndReturnValue(T_ID);  
    symTable.setMemberAccess(memberName, "private");  

    icg.addInstruction("private " + memberName + ";");  
    expect(T_SEMICOLON);  
    }
     void parseProtectedStatement()
    {
        // expect(T_PROTECTED);
        // expect(T_ID);
        // expect(T_SEMICOLON);

         expect(T_PROTECTED);  
    string memberName = expectAndReturnValue(T_ID);  
    symTable.setMemberAccess(memberName, "protected"); 

    icg.addInstruction("protected " + memberName + ";");  
    expect(T_SEMICOLON);  
    }

    void parseTryCatchStatement ()
    {
        // expect(T_TRY);
        // parseBlock();
        // expect(T_CATCH);
        // expect(T_LPAREN);
        // expect(T_ETARGET);
        // expect(T_RPAREN);
        // parseBlock();

        expect(T_TRY); 

    icg.addInstruction("try {");  
    parseBlock();  
    icg.addInstruction("}");

    expect(T_CATCH);  
    expect(T_LPAREN);  
    string exceptionTarget = expectAndReturnValue(T_ETARGET);  
    symTable.declareVariable(exceptionTarget, "exception");  
    expect(T_RPAREN);  

    icg.addInstruction("catch (" + exceptionTarget + ") {");  
    parseBlock();
    icg.addInstruction("}");
    }


    void parseReturnStatement() {
        // expect(T_RETURN);
        // parseExpression();
        // expect(T_SEMICOLON);

        expect(T_RETURN);
        string expr = parseExpression();
        icg.addInstruction("return " + expr);  
        expect(T_SEMICOLON);
    }

     void parseForStatement() {
        // expect(T_FOR);
        // expect(T_LPAREN);
        // parseDeclarationAssignment(T_INT);
        // parseExpression();
        // expect(T_SEMICOLON);
        // parseIncrementDecrement();
        // expect(T_RPAREN);
        // parseBlock();  

        expect(T_FOR);
        expect(T_LPAREN);
        parseDeclarationAssignment(T_INT);
        string condition = parseExpression();
        string startLabel = icg.newLabel();
        string endLabel = icg.newLabel();
        icg.addInstruction(startLabel + ":");  
        icg.addInstruction("if !" + condition + " goto " + endLabel); 
        expect(T_SEMICOLON);
        string incrementDecrement = parseIncrementDecrement();
        expect(T_RPAREN);
        parseBlock();  
        icg.addInstruction(incrementDecrement);
        icg.addInstruction("goto " + startLabel);
        icg.addInstruction(endLabel + ":");  
    }

   string parseIncrementDecrement() {
    // expect(T_ID); 
    // if (tokens[pos].type == T_INCREMENT) {  
    //     pos++;  
    // } else if (tokens[pos].type == T_DECREMENT) {  
    //     pos++; 
    // } else {
    //     cout << "Syntax error: expected increment (++) or decrement (--) operator at line "
    //          << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
    //     exit(1);
    // }

    string varName = expectAndReturnValue(T_ID);  

    if (tokens[pos].type == T_INCREMENT) {  
        pos++; 
        return varName + " = " + varName + " + 1";  
    } else if (tokens[pos].type == T_DECREMENT) {  
        pos++;  
        return varName + " = " + varName + " - 1";  
    } else {
        cout << "Syntax error: expected increment (++) or decrement (--) operator at line "
             << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}


    void parseWhileStatement() {
        // expect(T_WHILE);
        // expect(T_LPAREN);
        // parseExpression();  
        // expect(T_RPAREN);
        // parseBlock();  


        expect(T_WHILE);
        expect(T_LPAREN);

        string startLabel = icg.newLabel();
        string endLabel = icg.newLabel();
        icg.addInstruction(startLabel + ":");  

        string condition = parseExpression();  
        icg.addInstruction("if !" + condition + " goto " + endLabel);  

        expect(T_RPAREN);
        parseBlock(); 

        icg.addInstruction("goto " + startLabel);  
        icg.addInstruction(endLabel + ":"); 
    }



void parseSwitchStatement() {
    // pos++;
    // expect(T_LPAREN);
    // expect(T_ID); 
    // expect(T_RPAREN);
    // expect(T_LBRACE);

    // // Process cases
    // while (tokens[pos].type == T_CASE || tokens[pos].type == T_DEFAULT) {
    //     if (tokens[pos].type == T_CASE) {
    //         parseCaseStatement();
    //     } else if (tokens[pos].type == T_DEFAULT) {
    //         parseDefaultStatement();
    //     }
    // }

    // expect(T_RBRACE); 


     pos++;
    expect(T_LPAREN);
    string switchVar = expectAndReturnValue(T_ID); 
    expect(T_RPAREN);
    expect(T_LBRACE);

    string endLabel = icg.newLabel();

    while (tokens[pos].type == T_CASE || tokens[pos].type == T_DEFAULT) {
        if (tokens[pos].type == T_CASE) {
            parseCaseStatement(switchVar, endLabel);
        } else if (tokens[pos].type == T_DEFAULT) {
            parseDefaultStatement(endLabel);
        }
    }

    expect(T_RBRACE);
    icg.addInstruction(endLabel + ":");  
}
void parseCaseStatement(const string& switchVar, const string& endLabel) {
    pos++;
    string caseValue = expectAndReturnValue(T_NUM);
    string caseLabel = icg.newLabel();
    icg.addInstruction("if " + switchVar + " == " + caseValue + " goto " + caseLabel);

    expect(T_COLON);

    icg.addInstruction(caseLabel + ":");  
    while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
        parseStatement();  
    }
    icg.addInstruction("goto " + endLabel); 
}


// void parseCaseStatement() {
//     pos++;
//     expect(T_NUM); // Case value (like case 1:)
//     expect(T_COLON);

//     // Parsing the case body: This could be a sequence of statements.
//     while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
//         parseStatement(); // Assume parseStatement handles a single statement
//     }
// }

void parseDefaultStatement(const string& endLabel) {
    pos++;
    expect(T_COLON);

    string defaultLabel = icg.newLabel();
    icg.addInstruction(defaultLabel + ":"); 

    while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
        parseStatement(); 
    }
    icg.addInstruction("goto " + endLabel);
}

// void parseDefaultStatement() {
//     pos++;
//     expect(T_COLON);

//     // Parsing the default body: This could be a sequence of statements.
//     while (tokens[pos].type != T_CASE && tokens[pos].type != T_DEFAULT && tokens[pos].type != T_RBRACE) {
//         parseStatement(); // Parsing a single statement
//     }
// }

void parseFunctionStatement() {
    // 
    // if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
    //     tokens[pos].type == T_VOID || tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || 
    //     tokens[pos].type == T_BOOL) {
        
    //     pos++;  
    // } else {
    //     cout << "Syntax error: expected return type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
    //     exit(1);
    // }

    // // Parse the function name (identifier)
    // expect(T_ID);

    // expect(T_LPAREN);
    // if (tokens[pos].type != T_RPAREN) {  
    //     parseParameterList();
    // }
    // expect(T_RPAREN);

    // parseBlock();  // Assuming parseBlock handles statements within curly braces


// // Parse the return type (e.g., int, void, etc.)
//     string returnType;
//     if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
//         tokens[pos].type == T_VOID || tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || 
//         tokens[pos].type == T_BOOL) {
        
//         returnType = tokens[pos++].value;
//     } else {
//         cout << "Syntax error: expected return type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
//         exit(1);
//     }

//     string functionName = expectAndReturnValue(T_ID); 

//     expect(T_LPAREN);
//     if (tokens[pos].type != T_RPAREN) {
//         parseParameterList();  
//     }
//     expect(T_RPAREN);

//     symTable.declareFunction(functionName, returnType);  

//     icg.addInstruction(returnType + " " + functionName + "();");
//     parseBlock(); 


     string returnType;
    // Parse the return type of the function (e.g., int, void)
    if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
        tokens[pos].type == T_VOID || tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || 
        tokens[pos].type == T_BOOL) {
        
        returnType = tokens[pos++].value;  // Get the return type and move past the token
    } else {
        cout << "Syntax error: expected return type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }

    // Parse the function name (identifier)
    string functionName = expectAndReturnValue(T_ID);

    // Parse the parameter list
    expect(T_LPAREN);
    vector<string> paramTypes;
    if (tokens[pos].type != T_RPAREN) {  // If not immediately closing, parse parameters
        parseParameterList(paramTypes);
    }
    expect(T_RPAREN);

    // Declare the function in the symbol table
    symTable.declareFunction(functionName, returnType, paramTypes);

    // Generate intermediate code for the function signature (just the declaration for now)
    icg.addInstruction(returnType + " " + functionName + "();");

    // Parse the function body (block)
    parseBlock(); 
}

void parseParameterList(vector<string>& paramTypes) {
    // Parse parameters (type and name) and store the parameter types
    while (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT ||
           tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || tokens[pos].type == T_BOOL) {
        string paramType = tokens[pos++].value;  // Get the parameter type and move past the token
        string paramName = expectAndReturnValue(T_ID);  // Get the parameter name
        
        paramTypes.push_back(paramType);  // Store the parameter type

        if (tokens[pos].type == T_COMMA) {
            pos++;  // Skip the comma
        }
    }
}

// void parseParameterList() {
//     // parseParameter();
//     // while (tokens[pos].type == T_COMMA) { 
//     //     pos++;
//     //     parseParameter();
//     // }


//      vector<string> parameters;  


//     parameters.push_back(parseParameter());
//     while (tokens[pos].type == T_COMMA) {  
//         pos++;
//         parameters.push_back(parseParameter());
//     }

//     for (const string& param : parameters) {
//         symTable.declareVariable(param, "parameter"); 
//     }

//     icg.addInstruction("parameters: " + join(parameters, ", ")); 
// }
string parseParameter() {
    string type, name;
    if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
        tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || tokens[pos].type == T_BOOL) {
        
        type = tokens[pos++].value;  
    } else {
        cout << "Syntax error: expected parameter type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
    name = expectAndReturnValue(T_ID);  

    symTable.declareVariable(name, type);  
    icg.addInstruction(type + " " + name);  

    return name;  
}
// void parseParameter() {
//     // Expect a type and identifier for each parameter (e.g., int x)
//     if (tokens[pos].type == T_INT || tokens[pos].type == T_DOUBLE || tokens[pos].type == T_FLOAT || 
//         tokens[pos].type == T_STRING || tokens[pos].type == T_CHAR || tokens[pos].type == T_BOOL) {
        
//         pos++;  // Advance past the type
//     } else {
//         cout << "Syntax error: expected parameter type at line " << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
//         exit(1);
//     }
//     expect(T_ID);  // Expect parameter name
// }
    void parseBreakStatement() {
        // pos++;
        // expect(T_SEMICOLON);

         pos++;
        expect(T_SEMICOLON);

        string breakLabel = icg.getCurrentBreakLabel();  
        if (breakLabel.empty()) {
        cout << "Syntax error: 'break' used outside of loop or switch at line "
             << tokens[pos].lineNo << ", column " << tokens[pos].colNo << endl;
            exit(1);
    }

        icg.addInstruction("goto " + breakLabel); 
    }
    string join(const vector<string>& vec, const string& delimiter) {
    string result;
    for (size_t i = 0; i < vec.size(); ++i) {
        result += vec[i];
        if (i < vec.size() - 1) result += delimiter;
    }
    return result;
}


string parseExpression() {
    string term = parseTerm();

    // Handle addition, subtraction, and logical/relational operators
    while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS || 
           tokens[pos].type == T_GT || tokens[pos].type == T_LT ||
           tokens[pos].type == T_GE || tokens[pos].type == T_LE || 
           tokens[pos].type == T_EQ || tokens[pos].type == T_NEQ || 
           tokens[pos].type == T_AND || tokens[pos].type == T_OR) {
        
        TokenType op = tokens[pos++].type;  // Capture the operator and move forward
        string nextTerm = parseTerm();      // Parse the next term/expression
        string temp = icg.newTemp();        // Generate a temporary variable for intermediate results
        
        // Handle different types of operations
        if (op == T_PLUS) {
            icg.addInstruction(temp + " = " + term + " + " + nextTerm);
        } else if (op == T_MINUS) {
            icg.addInstruction(temp + " = " + term + " - " + nextTerm);
        } else if (op == T_GT) {
            icg.addInstruction(temp + " = " + term + " > " + nextTerm);
        } else if (op == T_LT) {
            icg.addInstruction(temp + " = " + term + " < " + nextTerm);
        } else if (op == T_GE) {
            icg.addInstruction(temp + " = " + term + " >= " + nextTerm);
        } else if (op == T_LE) {
            icg.addInstruction(temp + " = " + term + " <= " + nextTerm);
        } else if (op == T_EQ) {
            icg.addInstruction(temp + " = " + term + " == " + nextTerm);
        } else if (op == T_NEQ) {
            icg.addInstruction(temp + " = " + term + " != " + nextTerm);
        } else if (op == T_AND) {
            icg.addInstruction(temp + " = " + term + " && " + nextTerm);
        } else if (op == T_OR) {
            icg.addInstruction(temp + " = " + term + " || " + nextTerm);
        }

        term = temp;  // Update the term to the new temporary variable
    }

    return term;  // Return the final result of the expression
}
string parseTerm() {
    string factor = parseFactor();  // Parse the first factor

    // Handle multiplication and division operators
    while (tokens[pos].type == T_MUL || tokens[pos].type == T_DIV) {
        TokenType op = tokens[pos++].type;  // Capture the operator and advance
        string nextFactor = parseFactor(); // Parse the next factor
        string temp = icg.newTemp();       // Generate a temporary variable for the result
        
        // Generate intermediate code for the operation
        if (op == T_MUL) {
            icg.addInstruction(temp + " = " + factor + " * " + nextFactor);
        } else if (op == T_DIV) {
            icg.addInstruction(temp + " = " + factor + " / " + nextFactor);
        }
        
        factor = temp;  // Update the factor to the temporary result
    }

    return factor;  // Return the final result of the term
}
string parseFactor() {
    if (tokens[pos].type == T_NUM || tokens[pos].type == T_STRING_LITERAL || tokens[pos].type == T_CHAR_LITERAL) {
        // For numeric, string, or character literals
        return tokens[pos++].value;  // Return the literal value and advance
    } 
    else if (tokens[pos].type == T_ID) {
        string id = tokens[pos++].value;  // Store the identifier name

        // Handle post-increment and post-decrement
        if (tokens[pos].type == T_INCREMENT) {  // If it's increment (id++)
            pos++;  // Advance past the `++`
            string temp = icg.newTemp();  // Generate a temporary variable
            icg.addInstruction(temp + " = " + id);  // Store the current value
            icg.addInstruction(id + " = " + id + " + 1");  // Perform the increment
            return temp;  // Return the old value (for post-increment behavior)
        } 
        else if (tokens[pos].type == T_DECREMENT) {  // If it's decrement (id--)
            pos++;  // Advance past the `--`
            string temp = icg.newTemp();  // Generate a temporary variable
            icg.addInstruction(temp + " = " + id);  // Store the current value
            icg.addInstruction(id + " = " + id + " - 1");  // Perform the decrement
            return temp;  // Return the old value (for post-decrement behavior)
        }

        // If no increment/decrement, just return the identifier
        return id;
    } 
    else if (tokens[pos].type == T_LPAREN) {
        // Handle parenthesized expressions
        expect(T_LPAREN);
        string expr = parseExpression();  // Parse the inner expression
        expect(T_RPAREN);
        return expr;  // Return the result of the expression
    } 
    else if (tokens[pos].type == T_ASSIGN) {
        // Handle assignments
        pos++;  // Move past the assignment operator
        string expr = parseExpression();  // Parse the right-hand side expression
        string temp = icg.newTemp();  // Generate a temporary variable
        icg.addInstruction(temp + " = " + expr);  // Generate code for assignment
        return temp;  // Return the result of the assignment
    } 
    else {
        // Handle unexpected tokens with error reporting
        cout << "Syntax error: unexpected token '" << tokens[pos].value 
        << "' at line " << tokens[pos].lineNo 
        << ", column " << tokens[pos].colNo << endl;
        exit(1);
    }
}
// void parseExpression() {
//     parseTerm();
    
//     // Handle addition, subtraction, and relational operators in expression
//     while (tokens[pos].type == T_PLUS || tokens[pos].type == T_MINUS || 
//            tokens[pos].type == T_GT || tokens[pos].type == T_LT ||
//            tokens[pos].type == T_GE || tokens[pos].type == T_LE || 
//            tokens[pos].type == T_EQ || tokens[pos].type == T_NEQ || 
//            tokens[pos].type == T_AND || tokens[pos].type == T_OR ) {
        
//         pos++;  // Advance past the operator
//         parseTerm();
//     }
// }
// void parseTerm() {
//     parseFactor();
    
//     // Handle multiplication and division operators
//     while (tokens[pos].type == T_MUL || tokens[pos].type == T_DIV) {
//         pos++;
//         parseFactor();
//     }
// }

// void parseFactor() {
//     if (tokens[pos].type == T_NUM || tokens[pos].type == T_ID ||
//         tokens[pos].type == T_STRING_LITERAL || tokens[pos].type == T_CHAR_LITERAL) {
        
//         string id = tokens[pos].value;  // Store the identifier or literal value
//         pos++;  // Advance past literals or identifiers
        
//         // Check for increment (++) and decrement (--) after an identifier
//         if (tokens[pos].type == T_INCREMENT) {  // If it's increment
//             pos++;  // Move past the `++`
//             cout << "Incrementing " << id << endl;  // Handle incrementing logic
//         } else if (tokens[pos].type == T_DECREMENT) {  // If it's decrement
//             pos++;  // Move past the `--`
//             cout << "Decrementing " << id << endl;  // Handle decrementing logic
//         }
//     } else if (tokens[pos].type == T_LPAREN) {
//         expect(T_LPAREN);
//         parseExpression();
//         expect(T_RPAREN);
        
//     } else if (tokens[pos].type == T_ASSIGN) {
//         pos++;  // Move past the assignment
//         parseExpression();  // Expect an expression after `=`

//     } else {
//         cout << "Syntax error: unexpected token '" << tokens[pos].value 
//              << "' at line " << tokens[pos].lineNo 
//              << ", column " << tokens[pos].colNo << endl;
//         exit(1);
//     }
// }


string expectAndReturnValue(TokenType type) {
        string value = tokens[pos].value;
        expect(type);
        return value;
    }

void expect(TokenType type) {
    if (tokens[pos].type == type) {
        pos++;  // Move to the next token if the expected token is found
    } else {
        // Print detailed syntax error message
        cout << "Syntax error: expected '" << tokenTypeToString(type) 
             << "' but found '" << tokens[pos].value 
             << "' at line " << tokens[pos].lineNo 
             << ", column " << tokens[pos].colNo << endl;
        
        // Provide a suggestion for fixing the syntax error
        string suggestion = suggestFix(type);
        if (!suggestion.empty()) {
            cout << "Suggested fix: " << suggestion << endl;
        }
        
        // Exit after showing the error and suggestion
        exit(1);  
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
        int count = 0 ;
        
        }
        class bhb {
        // protected int ajmal = "helloo"; 
        // private  car;
        // public model; 
    };
        struct room {
            // protected studentName ; 
            // private studentCgpa ;
            // public studentRollNo ; 
        };
        // hello burhan butt is here 
        /* hello burhan butt is here */
        
        while (count < 5) {
            count++;
        }
        int bum = 4  ;
        int num = 2 ;
        switch (num) {
        case 1:
            for (int c = 0; c < 5 ; c++) {
                int coun = 0 ;
        
                }
        case 2:
        case 3:
        default:
            
        }
        void printData(){}
        string  printDataa( int a  , char b )
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
    
    // Parser parser(tokens);
    // parser.parseProgram();


    SymbolTable symTable;
    IntermediateCodeGnerator icg;
    Parser parser(tokens, symTable, icg);

    parser.parseProgram();
    icg.printInstructions();

    cout<<""<<endl;
    cout<<""<<endl;
    cout<<""<<endl;
    cout<<""<<endl;
    cout<<""<<endl;
    symTable.printSymbolTable();

    AssemblyCodeGenerator acg ; 
    acg.generateAssembly(icg.instructions);
    acg.printAssemblyCode();

    

    return 0;
}


