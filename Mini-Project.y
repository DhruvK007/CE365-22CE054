%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int yylex();
void yyerror(char *s);
int valid = 1; // Flag to track if expression is valid
%}

%union {
    double val;
}

%token <val> NUMBER
%token PLUS MINUS MUL DIV LPAREN RPAREN MOD POWER FLOOR_DIV
%token UMINUS  /* Define UMINUS as a token */

%type <val> expression term factor

%left PLUS MINUS
%left MUL DIV MOD FLOOR_DIV
%right POWER
%right UMINUS  /* Precedence for unary minus */

%%
input:
    /* empty */
    | input line
    ;

line:
    expression '\n'      { 
                          if(valid) {
                              printf("Valid\n");
                              printf("Result: %.6g\n", $1);
                          } else {
                              printf("Invalid\n");
                          }
                          valid = 1; // Reset for next expression
                        }
    | error '\n'         { 
                          printf("Invalid\n");
                          valid = 1; // Reset for next expression
                          yyerrok; 
                        }
    ;

expression:
    term                         { $$ = $1; }
    | expression PLUS term       { $$ = $1 + $3; }
    | expression MINUS term      { $$ = $1 - $3; }
    ;

term:
    factor                       { $$ = $1; }
    | term MUL factor            { $$ = $1 * $3; }
    | term DIV factor            { 
                                   if($3 == 0) {
                                       yyerror("Division by zero");
                                       valid = 0;
                                       $$ = 0;
                                   } else {
                                       $$ = $1 / $3;
                                   }
                                 }
    | term MOD factor            { 
                                   if($3 == 0) {
                                       yyerror("Modulo by zero");
                                       valid = 0;
                                       $$ = 0;
                                   } else {
                                       $$ = fmod($1, $3);
                                   }
                                 }
    | term FLOOR_DIV factor      { 
                                   if($3 == 0) {
                                       yyerror("Division by zero");
                                       valid = 0;
                                       $$ = 0;
                                   } else {
                                       $$ = floor($1 / $3);
                                   }
                                 }
    ;

factor:
    NUMBER                       { $$ = $1; }
    | LPAREN expression RPAREN   { $$ = $2; }
    | MINUS factor %prec UMINUS  { $$ = -$2; }  /* Handle unary minus */
    | factor POWER factor        { $$ = pow($1, $3); }
    ;
%%

void yyerror(char *s) {
    printf("Syntax Error: %s\n", s);
    valid = 0;
}

int main() {
    printf("Enter arithmetic expressions (Ctrl+D to exit):\n");
    yyparse();
    return 0;
}