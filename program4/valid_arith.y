%{
        int yylex();
        int yyerror(char *);
        #include<stdio.h>
%}
%token id num NL
%left '+' '-'
%left '*' '%'
%%
ln : e NL {printf("Expression Valid\n"); return 0;}
e: e '+' e {}
| e '-' e {}
| e '*' e {}
| e '%' e {}
| '(' e ')' {}
| num {}
| id {}
%%
int main()
{
        yyparse();
        return 0;
}
int yyerror(char *m)
{
        printf("%s: Invalid Expression\n",m);

}
