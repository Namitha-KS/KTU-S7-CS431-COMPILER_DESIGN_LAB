
//YACC FILE - parser.y
%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(char* msg);
%}

%token ID NUM WHILE LE GE EQ NE OR AND

%left '+' '-'
%left '*' '/'
%right UMINUS
%nonassoc '<' '>' LE GE EQ NE
%nonassoc AND OR

%%
S: ST { printf("Input accepted\n"); exit(0); }
  ;

ST: ST ';'
   | WHILE '(' E ')' '{' ST '}'
   | ID '=' E ';'
   ;

E: E '+' E
 | E '-' E
 | E '*' E
 | E '/' E
 | '-' E %prec UMINUS
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

int main() {
    printf("Enter the expression: ");
    yyparse();
    return 0;
}

void yyerror(char* msg) {
    fprintf(stderr, "Invalid input: %s\n", msg);
}

