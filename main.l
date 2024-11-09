#include <stdio.h>
#include <string.h>
#include <ctype.h>

int lines = 0;
int words = 0;
int characters = 0;
int vowels = 0;
int consonants = 0;
char substring[] = "println";

// Function to convert a string to uppercase
void convert_to_uppercase(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
}

// Lex rules
%{
#include "y.tab.h"
%}

%%
\n              { lines++; characters++; }
[[:space:]]+   { /* ignore whitespace */ }
[a-zA-Z]+      { 
                    int len = strlen(yytext);
                    characters += len; 
                    words++;

                    // Count vowels and consonants
                    for (int i = 0; i < len; i++) {
                        char c = tolower(yytext[i]);
                        if (strchr("aeiou", c)) {
                            vowels++;
                        } else if (isalpha(c)) {
                            consonants++;
                        }
                    }

                    // Check for the substring "println"
                    if (strcmp(yytext, substring) == 0) {
                        printf("Substring '%s' exists.\n", yytext);
                        convert_to_uppercase(yytext);
                        printf("Converted substring: %s\n", yytext);
                    }
                }
.               { characters++; }  // Count other characters
%%

// Main function
int main(int argc, char *argv[]) {
    yylex();
    printf("Lines: %d\n", lines);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    printf("Vowels: %d\n", vowels);
    printf("Consonants: %d\n", consonants);
    return 0;
}
