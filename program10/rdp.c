#include <stdio.h>
#include <ctype.h>
#include <string.h>

void E();         // Forward declaration for E
void Eprime();    // Forward declaration for E'
void T();         // Forward declaration for T
void Tprime();    // Forward declaration for T'
void check();     // Function to check if character is alphanumeric or '('

char expression[10];
int count, flag;

int main() {
    count = 0;
    flag = 0;

    printf("\nEnter an Algebraic Expression: ");
    scanf("%s", expression);  // Read expression as string

    E();  // Start with the non-terminal 'E'

    if ((strlen(expression) == count) && (flag == 0)) {
        printf("\nThe Expression %s is Valid\n", expression);
    } else {
        printf("\nThe Expression %s is Invalid\n", expression);
    }

    return 0;
}

void E() {
    T();        // E -> T E'
    Eprime();   // Continue with E'
}

void Eprime() {
    if (expression[count] == '+') {
        count++;     // Consume '+'
        T();         // Parse T
        Eprime();    // Parse E' recursively
    }
}

void T() {
    check();    // T -> check T'
    Tprime();   // Continue with T'
}



void Tprime() {
    if (expression[count] == '*') {
        count++;     // Consume '*'
        check();     // Parse factor (alphanumeric or parenthesis)
        Tprime();    // Parse T' recursively
    }
}

void check() {
    if (isalnum(expression[count])) {
        count++;     // Consume alphanumeric character
    } else if (expression[count] == '(') {
        count++;     // Consume '('
        E();         // Parse sub-expression
        if (expression[count] == ')') {
            count++; // Consume ')'
        } else {
            flag = 1; // Set flag for invalid expression
        }
    } else {
        flag = 1;     // Set flag for invalid expression
    }
}





