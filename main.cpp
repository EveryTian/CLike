#include "ast.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include "syb.h"
#include <fstream>

extern int yyparse();
extern void printAST();
extern void semanticAnalysis();
extern void createStackFrame();
extern void translate();

using namespace std;

int main(void) {
    yyparse();
    printAST();
    semanticAnalysis();
    createStackFrame();
    //translate();
    return 0;
}

