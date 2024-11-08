#include<stdio.h>
#include<stdlib.h>

struct node {
    int st;
    struct node *Link;
};

int set[20], nostate, noalpha, notransition, s, r, buffer[20];
char alphabet[20], c;
struct node *transition[20][20] = {NULL};
int eclosure[20][20] = {0};

// Find the index of a given alphabet character in the alphabet array
int findalpha(char c) {
    int i;
    for (i = 0; i < noalpha; i++) {
        if (alphabet[i] == c)
            return i;
    }
    return 999;
}

// Insert a transition from state r to state s on symbol c
void inserttrans(int r, char c, int s) {
    int j;
    struct node *temp;
    j = findalpha(c);
    if (j == 999) {
        printf("\nError\n");
        exit(0);
    }
    temp = (struct node *) malloc(sizeof(struct node));
    temp->st = s;
    temp->Link = transition[r][j];
    transition[r][j] = temp;
}

// Print epsilon closure for a given state
void printeclosure(int i) {
    int j;
    printf("{");
    for (j = 0; eclosure[i][j] != 0; j++) {
        printf("q%d ", eclosure[i][j]);
    }
    printf("}");
}

// Recursive function to find epsilon closure of a state
void findclosure(int x, int sta) {
    struct node *temp;
    int i;
    if (buffer[x])
        return;
    eclosure[sta][c++] = x;
    buffer[x] = 1;
    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->st, sta);
            temp = temp->Link;
        }
    }
}

// Generate epsilon-NFA based on epsilon closures
void generate_epsilon_nfa() {
    struct node *temp;
    int i, j, k;

    for (i = 1; i <= nostate; i++) {
        for (j = 0; eclosure[i][j] != 0; j++) {
            int state = eclosure[i][j];
            for (k = 0; k < noalpha - 1; k++) { // For each input symbol except epsilon
                temp = transition[state][k];
                while (temp != NULL) {
                    inserttrans(i, alphabet[k], temp->st);
                    temp = temp->Link;
                }
            }
        }
    }
}

int main() {
    int i, j, k, t, n;
    struct node *temp;

    printf("Enter the number of alphabets:");
    scanf("%d", &noalpha);
    getchar();

    printf("Enter the alphabets:\n");
    for (i = 0; i < noalpha; i++) {
        alphabet[i] = getchar();
        getchar();
    }

    printf("\nEnter the number of states:");
    scanf("%d", &nostate);

    printf("\nEnter the number of transitions:");
    scanf("%d", &notransition);

    printf("Enter the transitions:\n");
    for (i = 0; i < notransition; i++) {
        scanf("%d %c %d", &r, &c, &s);
        inserttrans(r, c, s);
    }

    // Calculate epsilon closures for each state
    printf("\nE-Closure:\n");
    printf("--------------\n\n");
    for (i = 1; i <= nostate; i++) {
        c = 0;
        for (j = 0; j < 20; j++) {
            buffer[j] = 0;
            eclosure[i][j] = 0;
        }
        findclosure(i, i);
        printf("\nE-Closure(q%d):", i);
        printeclosure(i);
    }

    // Generate epsilon-NFA transitions using epsilon closures
    generate_epsilon_nfa();

    // Print the resulting epsilon-NFA transitions
    printf("\n\nTransitions in Epsilon-NFA:\n");
    for (i = 1; i <= nostate; i++) {
        for (j = 0; j < noalpha - 1; j++) { // Exclude epsilon from printing transitions
            temp = transition[i][j];
            while (temp != NULL) {
                printf("q%d -- %c --> q%d\n", i, alphabet[j], temp->st);
                temp = temp->Link;
            }
        }
    }

    printf("\n");
    return 0;
}
