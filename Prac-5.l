/*Code for lexical Analyzer using lex */
%option noyywrap
%{
    #include <stdio.h>
%}
%%
\/\/.*[\n] {}
\/\*([^*]|\*[^/])*\*\/ {}
(auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while) {printf("Keyword: %s\n",yytext);}
[a-zA-Z_][a-zA-Z_0-9]* {printf("Identifier: %s\n",yytext);}
['"'].*['"'] {printf("String: %s\n",yytext);}
'\'([^\\']|\\[abfnrtv\\'"]|\\[0-7]{1,3}|\\x[0-9A-Fa-f]+)\'' { printf("String: %s\n", yytext); }
[0-9]+ {printf("Constant: %s\n",yytext);}
[0-9]+[.][0-9]+ {printf("Constant: %s\n",yytext);}
[0-9]+[eE][+-]?[0-9]+ {printf("Constant: %s\n",yytext);}
[0-9]+[.][0-9]+[eE][+-]?[0-9]+ {printf("Constant: %s\n",yytext);}
['=='|'!='|'<'|'>'|'<=|'>='|'+'|'-'|'*'|'/'|'%'|'&'|'^'|'|'|'~'|'!'|'<<'|'>>'] {printf("Operator: %s\n",yytext);}
[=,;:.!?(){}] {printf("Punctuation: %s\n", yytext);}
[\t ] {}
[\n] {}
. {yyterminate();}
%%
int main(){
    yyin = fopen("demo.c", "r");
    yylex();
    return 0;
}


