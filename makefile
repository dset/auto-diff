fad: lex.yy.c parser.tab.cpp main.cpp
	g++ -std=c++14 -Wno-deprecated-register lex.yy.c parser.tab.cpp main.cpp -o fad

lex.yy.c: lexer.l
	flex lexer.l

parser.tab.cpp: parser.ypp
	bison -d parser.ypp

clean:
	rm fad lex.yy.c parser.tab.cpp parser.tab.hpp *~
