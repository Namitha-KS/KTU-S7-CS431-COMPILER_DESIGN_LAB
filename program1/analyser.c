#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Function prototypes
bool isDelimiter(char ch);
bool isOperator(char ch);
bool isValidIdentifier(char* str);
bool isKeyword(char* str);
bool isInteger(char* str);
bool isRealNumber(char* str);
char* substring(char* str, int left, int right);
void parse(char* str);

// Main function to read from file and parse its contents
int main() {
    FILE *file = fopen("input.txt", "r"); // Open input.txt in read mode
    if (file == NULL) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }
    
    char str[1000]; // Buffer to store the contents of the file
    printf("Reading from input.txt:\n");
    while (fgets(str, sizeof(str), file) != NULL) { // Read the file line by line
        printf("%s", str); // Display the contents (optional)
        parse(str); // Analyze each line
    }
    fclose(file); // Close the file
    return 0;
}

// Check if the character is a delimiter
bool isDelimiter(char ch) {
    return (ch == ' ' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || 
            ch == ',' || ch == ';' || ch == '>' || ch == '<' || ch == '=' || 
            ch == '(' || ch == ')' || ch == '[' || ch == ']' || 
            ch == '{' || ch == '}');
}

// Check if the character is an operator (including multi-character)
bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '>' || 
            ch == '<' || ch == '=' || ch == '%');
}

// Check if the string is a valid identifier
bool isValidIdentifier(char* str) {
    if (!isalpha(str[0]) && str[0] != '_') {
        return false;
    }
    for (int i = 1; i < strlen(str); i++) {
        if (!isalnum(str[i]) && str[i] != '_') {
            return false;
        }
    }
    return true;
}

// Check if the string is a keyword
bool isKeyword(char* str) {
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue", "int", "double",
        "float", "return", "char", "case", "sizeof", "long", "short",
        "typedef", "switch", "unsigned", "void", "static", "struct", "goto"
    };
    for (int i = 0; i < 22; ++i) {
        if (strcmp(str, keywords[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Check if the string is an integer
bool isInteger(char* str) {
    int len = strlen(str);
    if (len == 0) return false;
    for (int i = 0; i < len; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

// Check if the string is a real number
bool isRealNumber(char* str) {
    int len = strlen(str);
    bool hasDecimal = false;
    for (int i = 0; i < len; i++) {
        if (str[i] == '.') {
            if (hasDecimal) return false; // More than one decimal point
            hasDecimal = true;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return hasDecimal;
}

// Extract a substring from the input string
char* substring(char* str, int left, int right) {
    char* subStr = (char*)malloc((right - left + 2) * sizeof(char));
    for (int i = left; i <= right; i++) {
        subStr[i - left] = str[i];
    }
    subStr[right - left + 1] = '\0';
    return subStr;
}

// Parse the input string and identify tokens
void parse(char* str) {
    int left = 0, right = 0;
    int len = strlen(str);

    while (right <= len) {
        // Skip whitespace
        while (right < len && isspace(str[right])) {
            right++;
        }
        left = right;

        // If the line starts with a comment, skip it
        if (str[left] == '/' && str[left + 1] == '/') {
            printf("// this is a comment (ignored)\n");
            break; // Stop processing this line
        }

        // Move `right` to find the end of the current token
        while (right < len && !isDelimiter(str[right])) {
            right++;
        }

        // Extract the current token
        if (left < right) {
            char* subStr = substring(str, left, right - 1);

            // Strip trailing whitespace from the token
            size_t tokenLen = strlen(subStr);
            if (tokenLen > 0 && isspace(subStr[tokenLen - 1])) {
                subStr[tokenLen - 1] = '\0';
            }

            if (isKeyword(subStr)) {
                printf("'%s' is a keyword\n", subStr);
            } else if (isInteger(subStr)) {
                printf("'%s' is an integer\n", subStr);
            } else if (isRealNumber(subStr)) {
                printf("'%s' is a real number\n", subStr);
            } else if (isValidIdentifier(subStr)) {
                printf("'%s' is a valid identifier\n", subStr);
            } else {
                printf("'%s' is not a valid identifier\n", subStr);
            }
            free(subStr);
        }

        // If the delimiter is an operator, print it
        if (isOperator(str[right])) {
            printf("'%c' is an operator\n", str[right]);
        }

        // Move to the next token
        right++;
    }
}
