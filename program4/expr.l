%{
#include "y.tab.h"
#include <ctype.h>
#include <stdlib.h>
%}

%%
[0-9]+       { yylval.num = atoi(yytext); return NUMBER; }
[a-zA-Z]+    { yylval.num = 0; return ID; }  // Assuming ID has a default value of 0
[\t\n ]+     { /* ignore whitespace */ }
.            { return yytext[0]; }
%%

int yywrap() { return 1; }
