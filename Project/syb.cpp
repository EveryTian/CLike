#include "ast.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>

extern Program* program;
extern int yyparse();
using namespace std;

int main(void) {
    queue<Node*> *q = new queue<Node*>();
    int size = 0;

    yyparse();
    cout << "|" << program->toString() << endl;
    program->pushto(q);
    while(!q->empty()){
        size = q->size();
        cout << "|";
        for(int i = 0; i < size; i++){
            cout << q->front()->toString();
            q->front()->pushto(q);
            q->pop();
        }
        cout<<endl;
    }
    return 0;
}
