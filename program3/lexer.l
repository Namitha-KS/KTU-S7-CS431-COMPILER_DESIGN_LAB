%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Counter variables
int chars = 0;
int words = 0;
int lines = 0;
int spaces = 0;
int special_chars = 0;
int printlnCount = 0;

// Function to update counters
void count() {
    chars += yyleng;
}
%}

%%

\n              { lines++; chars++; }                         // Newline increments line and character count
[a-zA-Z]+       { words++; count(); printf("Word: %s\n", yytext); } // Match words
" "             { spaces++; chars++; }                       // Count spaces and characters
[,\.\?!;:]      { special_chars++; count(); printf("Special Character: %s\n", yytext); } // Special characters
\"[^\"]*\"      {                                            // Quoted strings
                    count();
                    printf("Quoted String: %s\n", yytext);
                    // Check for "println" in quoted strings
                    if(strstr(yytext, "println") != NULL) {
                        printlnCount++;
                    }
                }
println         { printlnCount++; printf("Found 'println'\n"); } // Detect standalone "println"
.               { count(); }                                      // Any other character increments the character count

%%

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if(!file) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    yyin = file;
    
    printf("\nBeginning Analysis of file: %s\n", argv[1]);
    printf("----------------------------------------\n\n");
    
    yylex(); // Begin lexical analysis
    
    // Display summary results
    printf("\n----------------------------------------\n");
    printf("Analysis Results:\n");
    printf("----------------------------------------\n");
    printf("Total Characters: %d\n", chars);
    printf("Total Words: %d\n", words);
    printf("Total Lines: %d\n", lines + 1); // +1 for the last line if it doesn't end with \n
    printf("Total Spaces: %d\n", spaces);
    printf("Total Special Characters: %d\n", special_chars);
    printf("Occurrences of 'println': %d\n", printlnCount);
    
    fclose(file);
    return 0;
}

int yywrap() {
    return 1;
}
