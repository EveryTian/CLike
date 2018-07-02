#include "ast.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <unordered_map>
#include "syb.h"

extern Program* program;
extern int yyparse();
using namespace std;
void addId(string identifier, string type ,int address, unordered_map<string, Symbol*>* hashList);
void typeCheck(string id1, string id2,unordered_map<string, Symbol*>* hashList);

int main(void) {
    queue<Node*> *q = new queue<Node*>();
    vector <unordered_map<string, Symbol*>*> *funcEnv = new vector <unordered_map<string, Symbol*>*>();
    vector <unordered_map<string, Symbol*>*> *varEnv = new vector <unordered_map<string, Symbol*>*>();
    int size = 0;

    yyparse();
    // level order travelsal to print the AST tree
    cout << "|" << program->toString() <<"|"<< endl;
    program->pushto(q);
    while(!q->empty()){
        size = q->size();
        cout << "|";
        for(int i = 0; i < size; i++){
            Node* temp = q->front();
            cout << temp->toString()<<"|";
            temp->pushto(q);
            q->pop();
        }
        cout<<endl;
    }

    program->pushto(q);
    while(!q->empty()){
        Node* temp = q->back();
	q->pop();
cout << temp->toString()<<endl;
        if(temp->isFuncDec){
        funcEnv->push_back(new unordered_map<string, Symbol*> ());
        varEnv->push_back(new unordered_map<string, Symbol*> ());
            if(temp->variableType)
                addId(temp->identifier->toString(), temp->variableType->toString(),funcEnv->size(),funcEnv->back());
            else
                addId(temp->identifier->toString(), "void",funcEnv->size(),funcEnv->back());
        }
        if(temp->isVarDec){
            if(temp->variableType)
                addId(temp->variable->identifier->toString(), temp->variableType->toString(),funcEnv->size(),varEnv->back());
            else
                addId(temp->variable->identifier->toString(), "void",funcEnv->size(),varEnv->back());
        }
        /*if(temp->isNeedTypeCheck){
            typeCheck(temp->expression1->)
        }*/
        temp->pushto(q);

    }


    cout << "function symbol table contains:"<<endl;
    cout << "function name   return type    location"<<endl;
    for(int i = 0; i < funcEnv->size(); ++i)
        for(auto it = funcEnv->at(i)->begin(); it != funcEnv->at(i)->end(); ++it)
            cout << it->second->toString() << endl;

    cout << "variable symbol table contains:"<<endl;
    cout << "variable name   type    location"<<endl;
    for(int i = 0; i < varEnv->size(); ++i)
        for(auto it = varEnv->at(i)->begin(); it != varEnv->at(i)->end(); ++it)
            cout << it->second->toString() << endl;
    return 0;
}

void addId(string identifier, string type ,int address, unordered_map<string, Symbol*>* hashList){
    Symbol* temp = new Symbol(identifier,type, address);
    pair<string,Symbol*> kvPair(identifier,temp);

    if(hashList->find(identifier) == hashList->end()){
        hashList->insert(kvPair);
    }
    else{
        cout<<endl<<identifier<<" is redefined!"<<endl;
        exit(-1);
    }
}

void typeCheck(string id1, string id2,unordered_map<string, Symbol*>* hashList){
    if(hashList->find(id1) == hashList->end()){
        cout<<id1<<" is undefined!"<<endl;
    }
    else if(hashList->find(id2) == hashList->end()){
        cout<<id2<<" is undefined!"<<endl;
    }
    else{
        if((*hashList)[id1]->type != (*hashList)[id2]->type)
            cout<<id1<<" and "<<id2<<" cause a type conflict"<<endl;
    }
}
