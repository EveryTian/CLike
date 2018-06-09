bison -d clike.yy
flex clike.l
g++ -o lex.yy.c clike.tab.cc -lfl
