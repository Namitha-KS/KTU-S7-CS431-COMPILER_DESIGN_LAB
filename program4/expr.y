%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%union {
    int num;
}

%token <num> NUMBER
%token <num> ID
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
expr: expr '+' expr { $$ = $1 + $3; }
    | expr '-' expr { $$ = $1 - $3; }
    | expr '*' expr { $$ = $1 * $3; }
    | expr '/' expr { 
        if ($3 == 0) {
            yyerror("Division by zero");
            YYABORT;
        } else {
            $$ = $1 / $3; 
        }
      }
    | '-' expr %prec UMINUS { $$ = -$2; }
    | '(' expr ')' { $$ = $2; }
    | NUMBER       { $$ = $1; }
    | ID           { $$ = $1; }
    ;

%%
int main()
{
    if (yyparse() == 0)
    {
        printf("Expression is valid\n");
    }
    else
    {
        printf("Expression is invalid\n");
    }
    return 0;
}

void yyerror(const char *s)
{
    printf("Error: %s\n", s);
}

