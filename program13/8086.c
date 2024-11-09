#include <stdio.h>
#include <string.h>

int main() {
    char icode[10][30], str[20], opr[10];
    int i = 0;

    printf("\nEnter the set of intermediate code (terminated by 'exit'):\n");

    // Reading the input until 'exit' is encountered
    do {
        scanf("%s", icode[i]);
    } while (strcmp(icode[i++], "exit") != 0);
    
    printf("Target code generation\n");

    // Process each instruction
    for (int j = 0; j < i - 1; j++) {  // i - 1 to skip 'exit'
        strcpy(str, icode[j]);
        switch (str[3]) {
            case '+':
                strcpy(opr, "ADD");
                break;
            case '-':
                strcpy(opr, "SUB");
                break;
            case '*':
                strcpy(opr, "MUL");
                break;
            case '/':
                strcpy(opr, "DIV");
                break;
            default:
                strcpy(opr, "UNKNOWN");
                break;
        }

        // Print the assembly code based on the intermediate code format
        if (strcmp(opr, "UNKNOWN") != 0) {
            printf("\n\tMOV %c, R%d", str[0], 0); // Assuming str[0] is the destination
            printf("\n\t%s %c, R%d", opr, str[2], 1); // str[2] is the source operand
            printf("\n\tMOV R%d, %c", 1, str[4]); // Assuming str[4] is the destination
        }
    }

    return 0;
}


