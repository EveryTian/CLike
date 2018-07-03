LEX = flex
YACC = bison
CC = g++
OBJECT=clike

$(OBJECT): lex.yy.c  $(OBJECT).tab.hh ast.hpp $(OBJECT).tab.cc semantic.cpp ast.cpp frame.cpp irtree.cpp main.cpp
	$(CC) lex.yy.c $(OBJECT).tab.cc semantic.cpp ast.cpp frame.cpp irtree.cpp main.cpp -o $(OBJECT) -lfl -std=c++11

$(OBJECT).tab.cc  $(OBJECT).tab.hh: $(OBJECT).yy
	$(YACC) -d $(OBJECT).yy

lex.yy.c: $(OBJECT).l
	$(LEX) $(OBJECT).l

clean:
	@rm -f $(OBJECT).tab.cc  $(OBJECT).tab.hh lex.yy.c $(OBJECT) SymbolTable.txt AST.txt StackFrame.txt
