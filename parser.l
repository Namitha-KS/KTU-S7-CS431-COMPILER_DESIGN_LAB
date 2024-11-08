// LEX FILE - parser.l
%{
#include "y.tab.h"  
%}

%option noyywrap

%%
[ \t\n]+              ; 
"while"              { return WHILE; }
"<="                 { return LE; }
">="                 { return GE; }
"=="                 { return EQ; }
"!="                 { return NE; }
"&&"                 { return AND; }
"||"                 { return OR; }
"("                  { return '('; }
")"                  { return ')'; }
"{"                  { return '{'; }
"}"                  { return '}'; }
";"                  { return ';'; }
[0-9]+               { yylval = atoi(yytext); return NUM; } 
[a-zA-Z_][a-zA-Z0-9_]* { yylval = strdup(yytext); return ID; } 
"<"                  { return '<'; }
">"                  { return '>'; }
"+"                  { return '+'; }
"-"                  { return '-'; }
"*"                  { return '*'; }
"/"                  { return '/'; }
.                    { return yytext[0]; }
%%

int yyerror(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    return 0;
}
