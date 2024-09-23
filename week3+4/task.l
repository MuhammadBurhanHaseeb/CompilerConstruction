%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylval;  

#define INTEGER 258
#define IDENTIFIER 259
#define PLUS 260
#define MINUS 261
#define MULTIPLY 262
#define DIVIDE 263
#define LPAREN 264
#define RPAREN 265
#define LBRACE 266
#define RBRACE 267
#define SEMICOLON 268
#define RETURN 269
#define IF 270
#define ELSE 271
%}

%%

[ \t\n]+        ;   

"return"        { printf("Special Character: %s\n", yytext); }
"if"           { printf("Special Character: %s\n", yytext); }
"else"         { printf("Special Character: %s\n", yytext); }

[a-zA-Z_][a-zA-Z0-9_]* { printf("IDENTIFIER: %s\n", yytext); }

[0-9]+          { printf("NUMBER: %s\n", yytext); }

"+"             { printf("PLUS: %s\n", yytext); }
"-"             { printf("MINUS: %s\n", yytext); }
"*"             { printf("MULTIPLY: %s\n", yytext); }
"/"             { printf("DIVIDE: %s\n", yytext); }

"("             { printf("Open Brracket: %s\n", yytext); }
")"             { printf("Close Brracket: %s\n", yytext); }
"{"             { printf("Open Curly Brracket: %s\n", yytext); }
"}"             { printf("Close Curly Brracket: %s\n", yytext); }
";"             { printf("SEMICOLON: %s\n", yytext); }

.               { printf("UNKNOWN TOKEN: %s\n", yytext); }

%%

int main() {
    char input[1024]; 

    printf("Enter C++ code (press Enter on an empty line to exit):\n");

    while (1) {
        fgets(input, sizeof(input), stdin);

        if (strcmp(input, "\n") == 0) {
            break;
        }

        YY_BUFFER_STATE buffer = yy_scan_string(input);
        yylex(); 

        yy_delete_buffer(buffer);
    }

    return 0;
}

int yywrap() {
    return 1;
}
