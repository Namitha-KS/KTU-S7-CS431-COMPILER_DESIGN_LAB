%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
[0-9]+    { yylval = atoi(yytext); return NUMBER; }
"+"       { return PLUS; }
"-"       { return MINUS; }
"*"       { return TIMES; }
"/"       { return DIVIDE; }
"("       { return LPAREN; }
")"       { return RPAREN; }
[ \t\n]   { /* skip whitespace */ }
.         { /* ignore unrecognized characters */ }

%% 

int yywrap(void) {
    return 1;
}

