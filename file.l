%option noyywrap
%{
    #include <stdio.h>
    int v=0, c=0;
%}
%%
[aAeEiIoOuU] { v++; }
[a-zA-Z] { c++; }
. {;}
[\t\n] {yyterminate();}
%%

int main(){
    printf("Enter a string: ");
    yylex();
    printf("Vowels: %d\nConsonants: %d\n", v, c);
    return 0;
}