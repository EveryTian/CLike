bison -d clike.yy
flex clike.l
g++ lex.yy.c clike.tab.cc -lfl
