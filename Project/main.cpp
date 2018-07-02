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
extern void printAST(void);
extern void semanticAnalysis(void);

using namespace std;

int main(void) {
    yyparse();
    printAST();
    semanticAnalysis();
    return 0;
}

