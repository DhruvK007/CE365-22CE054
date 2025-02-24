%option noyywrap
%{
    #include <stdio.h>
    int l=0, w=0, c=0;
%}
%%
\n     { l++; c++; }     
[ \t]+ { c += yyleng; }   
[a-zA-Z]+ { w++; c += yyleng; } 
. { c++; }  
%%

int main() {
    printf("Enter a string: ");
    yylex();
    printf("Lines: %d\nWords: %d\nCharacters: %d\n", l, w, c);
    return 0;
}
