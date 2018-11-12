%option noyywrap

%{
#include "parser.tab.hpp"

#define YY_DECL yy::parser::symbol_type yylex()
%}

%%

"sin" { return yy::parser::make_SIN(); }
"cos" { return yy::parser::make_COS(); }
"exp" { return yy::parser::make_EXP(); }
"ln" { return yy::parser::make_LN(); }
"(" { return yy::parser::make_LPAREN(); }
")" { return yy::parser::make_RPAREN(); }
"+" { return yy::parser::make_ADD(); }
"-" { return yy::parser::make_SUB(); }
"*" { return yy::parser::make_MUL(); }
"/" { return yy::parser::make_DIV(); }
"^" { return yy::parser::make_POW(); }

";" { return yy::parser::make_SEMICOLON(); }
"=" { return yy::parser::make_EQUALS(); }
"," { return yy::parser::make_COMMA(); }

[a-z] { return yy::parser::make_VAR(yytext); }
([0-9]+)|([0-9]+\.[0-9]+) { return yy::parser::make_NUM(std::stod(yytext)); }

[ \t] { }
. { std::cout << "Ignoring unknown character: " << yytext << std::endl; }

<<EOF>> { return yy::parser::make_END(); }
%%
