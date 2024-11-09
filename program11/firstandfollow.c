#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10];

void follow(char c);
void first(char c);

int main() {
    int i, z;
    char c, ch;
    
    // Clear input buffer before reading a character for 'c'
    printf("Enter the number of productions: \n");
    scanf("%d", &n);
    getchar();  // To consume the newline character left by scanf

    printf("Enter the productions:\n");
    for (i = 0; i < n; i++) {
        // Take input in the format like "E=TR"
        fgets(a[i], sizeof(a[i]), stdin);
        a[i][strlen(a[i]) - 1] = '\0';  // Remove the newline character
    }

    do {
        m = 0;
        printf("Enter a variable whose first & follow is to be found: ");
        scanf("%c", &c);
        getchar();  // Consume the newline after character input

        first(c);
        printf("First(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        strcpy(f, " ");
        m = 0;
        follow(c);
        printf("Follow(%c)={", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        printf("Want to continue or not(1/0)? ");
        scanf("%d%c", &z, &ch);
        getchar();  // Consume the newline character after input
    }
    while (z == 1);
    return 0;
}

void first(char c) {
    int k;
    if (!isupper(c)) {
        f[m++] = c;  // If the character is a terminal, add it to FIRST set
    }

    // Go through all productions
    for (k = 0; k < n; k++) {
        if (a[k][0] == c) {  // Check if the production starts with 'c'
            if (a[k][2] == '$') {  // If production is of the form A->$
                follow(a[k][0]);
            } else if (islower(a[k][2])) {  // If the next symbol is a terminal
                f[m++] = a[k][2];
            } else {  // If the next symbol is a non-terminal, compute FIRST recursively
                first(a[k][2]);
            }
        }
    }
}

void follow(char c) {
    if (a[0][0] == c) {
        f[m++] = '$';  // If 'c' is the start symbol, add '$' to its FOLLOW set
    }

    // Go through all productions to find where 'c' appears
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) {  // Starting from 2 to skip left-hand side
            if (a[i][j] == c) {  // Check if 'c' appears at position j
                if (a[i][j + 1] != '\0') {
                    first(a[i][j + 1]);  // If the next symbol is available, calculate its FIRST set
                }
                if (a[i][j + 1] == '\0' && c != a[i][0]) {  // If it’s the end of the production, call follow recursively
                    follow(a[i][0]);
                }
            }
        }
    }
}

