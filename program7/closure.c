#include<stdio.h>
#include<stdlib.h>

struct node {
    int st;
    struct node *link;
};

void findclosure(int, int);
void insert_trantbl(int, char, int);
int findalpha(char);
void print_e_closure(int);

static int set[20], nostate, noalpha, s, notransition, c, r, buffer[20];
char alphabet[20];
static int e_closure[20][20] = {0};
struct node *transition[20][20] = {NULL};

int main() {
    int i, j, k, m, t, n;
    struct node *temp;

    printf("Enter the number of input symbols?\n");
    scanf("%d", &noalpha);
    getchar();

    printf("NOTE: [ use letter e as epsilon]\n");
    printf("NOTE: [e must be last character, if it is present]\n");
    printf("\nEnter symbols?\n");
    for(i = 0; i < noalpha; i++) {
        alphabet[i] = getchar();
        getchar();
    }

    printf("\nEnter the number of states?\n");
    scanf("%d", &nostate);
    printf("\nEnter the number of transitions?\n");
    scanf("%d", &notransition);

    printf("NOTE: [Transition is in the form–> qno alphabet qno]\n");
    printf("NOTE: [States number must be greater than zero]\n");
    printf("\nEnter transitions?\n");
    for(i = 0; i < notransition; i++) {
        char ch;
        int from, to;
        scanf("%d %c %d", &from, &ch, &to);
        insert_trantbl(from, ch, to);
    }

    printf("\ne-closure of states……\n");
    printf("-----------------------\n");
    for(i = 1; i <= nostate; i++) {
        c = 0;
        for(j = 0; j < 20; j++) {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }
        findclosure(i, i);
        printf("\ne-closure(q%d): ", i);
        print_e_closure(i);
    }
    return 0;
}

void findclosure(int x, int sta) {
    struct node *temp;
    int i;

    if (buffer[x])
        return;

    e_closure[sta][c++] = x;
    buffer[x] = 1;

    if (alphabet[noalpha - 1] == 'e' && transition[x][noalpha - 1] != NULL) {
        temp = transition[x][noalpha - 1];
        while (temp != NULL) {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

void insert_trantbl(int r, char c, int s) {
    int j = findalpha(c);
    if (j == 999) {
        printf("Error: Invalid alphabet.\n");
        exit(0);
    }

    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];
    transition[r][j] = temp;
}

int findalpha(char c) {
    for(int i = 0; i < noalpha; i++) {
        if(alphabet[i] == c)
            return i;
    }
    return 999;
}

void print_e_closure(int i) {
    printf("{");
    int j = 0;
    while (e_closure[i][j] != 0) {
        printf("q%d", e_closure[i][j]);
        if (e_closure[i][j+1] != 0) printf(", ");
        j++;
    }
    printf("}");
}

