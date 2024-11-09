%{
#include <stdio.h>
#include <stdlib.h>

// Function declarations
int yylex(void);
void yyerror(char* msg);
%}

// Define tokens for YACC
%token ID NUM WHILE FOR IF LE GE EQ NE OR AND

// Precedence and associativity
%left '+' '-'
%left '*' '/'
%right UMINUS
%nonassoc '<' '>' LE GE EQ NE
%nonassoc AND OR

%%

// Define the grammar rules
S: ST { printf("Input accepted\n"); exit(0); }
  ;

ST: ST ';'                        // Sequence of statements separated by semicolons
   | WHILE '(' E ')' '{' ST '}'    // while loop: while(expression) { statement }
   | FOR '(' E ';' E ';' E ')' '{' ST '}' // for loop: for(expression; expression; expression) { statement }
   | IF '(' E ')' '{' ST '}'       // if statement: if(expression) { statement }
   | ID '=' E ';'                 // assignment: variable = expression;
   ;

E: E '+' E
  | E '-' E
  | E '*' E
  | E '/' E
  | '-' E %prec UMINUS  // Unary minus
  | ID
  | NUM
  | '(' E ')'
  | E '<' E
  | E '>' E
  | E LE E
  | E GE E
  | E EQ E
  | E NE E
  | E OR E
  | E AND E
  ;

%%

// Main function to start parsing
int main() {
    printf("Enter the expression: ");
    yyparse();
    return 0;
}

// Error handling function
void yyerror(char* msg) {
    fprintf(stderr, "Invalid input: %s\n", msg);
}

