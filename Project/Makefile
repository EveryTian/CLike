LEX = flex
YACC = bison
CC = g++
OBJECT=clike

$(OBJECT): lex.yy.c  $(OBJECT).tab.hh ast.hpp $(OBJECT).tab.cc syb.cpp
	$(CC) lex.yy.c $(OBJECT).tab.cc syb.cpp -o $(OBJECT) -lfl -std=c++11

$(OBJECT).tab.o: 
	$(CC) -c $(OBJECT).tab.c -lm

$(OBJECT).tab.cc  $(OBJECT).tab.hh: $(OBJECT).yy
	$(YACC) -d $(OBJECT).yy

lex.yy.c: $(OBJECT).l
	$(LEX) $(OBJECT).l

clean:
	@rm -f $(OBJECT).tab.cc  $(OBJECT).tab.hh lex.yy.c $(OBJECT)
