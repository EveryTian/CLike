#include "ast.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <fstream>

using namespace std;

extern Program* program;
void printAST();

void printAST() {
    int size = 0;
    queue <Node*> *q = new queue<Node*>();
    fstream ast;

    ast.open("AST.txt",ios_base::out);

    // level order travelsal to print the AST tree
    ast << "|" << program->toString() <<"|"<< endl;
    program->pushto(q);
    while(!q->empty()){
        size = q->size();
        ast << "|";
        for(int i = 0; i < size; i++){
            Node* temp = q->front();
            ast << temp->toString()<<"|";
            temp->pushto(q);
            q->pop();
        }
        ast<<endl;
    }
    ast.close();

}


