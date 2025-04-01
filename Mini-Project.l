%{
#include <stdlib.h>
#include "Mini-Project.tab.h"
%}

%%

"**"       { return POWER; }
"//"       { return FLOOR_DIV; }
"+"        { return PLUS; }
"-"        { return MINUS; }
"*"        { return MUL; }
"/"        { return DIV; }
"%"        { return MOD; }
"("        { return LPAREN; }
")"        { return RPAREN; }
[0-9]+(\.[0-9]+)?  { yylval.val = atof(yytext); return NUMBER; }
[ \t]+     { /* ignore whitespace */ }
\n         { return '\n'; }
.          { return yytext[0]; }

%%

int yywrap() { return 1; }