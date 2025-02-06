%option noyywrap
%{
    #include <stdio.h>  
%}
%%
[0-9]+ {printf("%s\n", yytext);}
[a-zA-Z]+ {;}
[\t\n] {yyterminate();}
%%

int main(){
    printf("Enter a string: ");
    yylex();
    return 0;
}