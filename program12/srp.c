#include <stdio.h>
#include <string.h>

int k = 0, z = 0, i = 0, j = 0;
char a[16], ac[20], stk[15], act[10];

void check();

int main() {
    printf("GRAMMAR: E -> E+E | E*E | (E) | id\n");
    printf("Enter input string: ");
    fgets(a, sizeof(a), stdin);  // Use fgets for safer input
    a[strcspn(a, "\n")] = 0;     // Remove newline character
    
    strcpy(act, "SHIFT");
    printf("Stack\tInput\tAction\n");

    for (k = 0, i = 0, j = 0; j < strlen(a); k++, i++, j++) {
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];
            stk[i + 1] = a[j + 1];
            stk[i + 2] = '\0';
            a[j] = ' ';
            a[j + 1] = ' ';
            printf("\n$%s\t%s$\t%s id", stk, a, act);
            check();
        } else {
            stk[i] = a[j];
            stk[i + 1] = '\0';
            a[j] = ' ';
            printf("\n$%s\t%s$\t%s symbols", stk, a, act);
            check();
        }
    }
    check();  // Final check after the loop for any remaining reductions
    return 0;
}

void check() {
    strcpy(ac, "REDUCE TO E");
    for (z = 0; z < strlen(stk); z++) {
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i--;
        }
    }
    
   
 for (z = 0; z < strlen(stk); z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2;
        }
    }

    for (z = 0; z < strlen(stk); z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2;
        }
    }

    for (z = 0; z < strlen(stk); z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';
            stk[z + 1] = '\0';
            stk[z + 2] = '\0';
            printf("\n$%s\t%s$\t%s", stk, a, ac);
            i -= 2;
        }
    }
}







