%{
#include <stdio.h>
#include <string.h>

// Enum for token types
enum TokenType {
    NOUN,
    VERB,
    PRONOUN,
    PROPER_NOUN,
    DETERMINER,
    PREPOSITION,
    UNKNOWN
};

// Function to print token
void print_token(enum TokenType type, char* lexeme) {
    char* token_names[] = {"NOUN", "VERB", "PRONOUN", "PROPER_NOUN", "DETERMINER", "PREPOSITION", "UNKNOWN"};
    printf("Token: %-12s Lexeme: %s\n", token_names[type], lexeme);
}
%}

%%

championship|ball|toss    { print_token(NOUN, yytext); }
is|want|won|played        { print_token(VERB, yytext); }
me|I|you                  { print_token(PRONOUN, yytext); }
India|Australia|Steve|John { print_token(PROPER_NOUN, yytext); }
the|a|an                  { print_token(DETERMINER, yytext); }
on|of                     { print_token(PREPOSITION, yytext); }
[a-zA-Z]+                 { print_token(UNKNOWN, yytext); }
[ \t\n]                   ; /* Ignore whitespace */
.                         { printf("Unexpected character: %s\n", yytext); }

%%

int main(int argc, char** argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (yyin == NULL) {
            printf("Error opening file: %s\n", argv[1]);
            return 1;
        }
    } else {
        yyin = stdin;
    }

    yylex();

    if (argc > 1) {
        fclose(yyin);
    }

    return 0;
}

int yywrap() {
    return 1;
}