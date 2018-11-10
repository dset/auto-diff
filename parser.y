%{
#include <stdio.h>

int yylex (void);
void yyerror(const char* s);
%}

%token NUM VAR
%token LPAREN RPAREN
%token ADD SUB MUL DIV POW
%token SIN COS EXP LN

%left ADD SUB
%left MUL DIV
%left POW

%%

exp: NUM
| VAR
| LPAREN exp RPAREN
| exp ADD exp
| exp SUB exp
| exp MUL exp
| exp DIV exp
| exp POW exp
| SIN LPAREN exp RPAREN
| COS LPAREN exp RPAREN
| EXP LPAREN exp RPAREN
| LN LPAREN exp RPAREN
%%

int main(int argc, char** argv) {
  yyparse();
  return 0;
}

void yyerror(const char* s) {
  fprintf(stderr, "error: %s\n", s);
}
