%option noyywrap
%{
        #include "valid_arith.tab.h"
%}
%%
[0-9]+(\.[0-9]+)?  { return num;}
[a-aA-Z_][a-zA-Z0-9_]* {return id;}
[\t] ;
\n {return NL;}
. {return yytext[0];}
%%
