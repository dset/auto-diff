%option noyywrap

%{
#include "parser.tab.h"

void yyerror(const char* s);
%}

%%

"sin" { return SIN; }
"cos" { return COS; }
"exp" { return EXP; }
"ln" { return LN; }
"(" { return LPAREN; }
")" { return RPAREN; }
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"^" { return POW; }

[a-z] { return VAR; }
[0-9]+ { return NUM; }

[ \t] { }
. { yyerror("bad input char"); }

%%
