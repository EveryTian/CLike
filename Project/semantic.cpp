#include "ast.hpp"
#include <string>
#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <unordered_map>
#include "syb.h"
#include <fstream>

using namespace std;

extern Program* program;

void addId(string identifier, VariableType* type ,ParameterList* paraList,int address, unordered_map<string, Symbol*>* hashList);
VariableType* typeCheck(Expression* exp1, Expression* exp2,unordered_map<string, Symbol*>* hashList);
void declareCheck(string id, unordered_map<string, Symbol*>* hashList, string kind);
void _semanticAnalysis(Node * n);
void semanticAnalysis(void);

unordered_map<string, Symbol*>* funcTable = new unordered_map<string, Symbol*>();
vector <unordered_map<string, Symbol*>*> *varEnv = new vector <unordered_map<string, Symbol*>*>();

void semanticAnalysis(void) {
    fstream syb;

    syb.open("SymbolTable.txt", ios_base::out);

    _semanticAnalysis(program);

    syb << "Function Symbol Table:"<<endl;
    syb << "Function Name   Return Type    Param Type    Environment"<<endl;
    for(auto it = funcTable->begin(); it != funcTable->end(); ++it)
        syb << it->second->toString() << endl;

    syb <<endl<<endl<< "Variable Symbol Table:"<<endl;
    syb << "Variable Name   Type    Environment"<<endl;
    for(int i = 0; i < varEnv->size(); ++i)
        for(auto it = varEnv->at(i)->begin(); it != varEnv->at(i)->end(); ++it)
            syb << it->second->toString() << endl;
    syb.close();
}

void _semanticAnalysis(Node * n){
    queue <Node*> *q = new queue<Node*>();

    n->pushto(q);
    if(n->isFuncDec){
        varEnv->push_back(new unordered_map<string, Symbol*> ());
        if(n->variableType)
            addId(n->identifier->toString(), n->variableType, n->parameterList, funcTable->size()+1,funcTable);
        else
            addId(n->identifier->toString(), new VariableType(4), n->parameterList,funcTable->size()+1,funcTable);
        if(n->parameterList != nullptr){
            for(auto it = n->parameterList->begin(); it != n->parameterList->end(); ++it)
                addId((*it)->identifier->toString(), (*it)->variableType,nullptr, varEnv->size(), varEnv->back());
        }
    }
    if(n->isVarDec){
        if(n->variableType)
            addId(n->variable->identifier->toString(), n->variableType,nullptr,varEnv->size(),varEnv->back());
        else
            addId(n->variable->identifier->toString(), new VariableType(4), nullptr,varEnv->size(),varEnv->back());
    }
    if(n->isNeedFuncDeclareCheck){
        declareCheck(n->identifier->toString(), funcTable, "Function");
    }
    if(n->isNeedVarDeclareCheck){
        declareCheck(n->identifier->toString(), varEnv->back(), "Variable");
    }
    int size = q->size();
    for(int i = 0; i < size; i++){
        Node* temp = q->front();
        q->pop();
        _semanticAnalysis(temp);
    }
    if(n->isNeedTypeCheck){
        n->type = typeCheck(n->expression1, n->expression2, varEnv->back());
    }
    if(n->isNeedFuncDeclareCheck){
        if(n->argumentList != nullptr){
            string id = n->identifier->toString();
            ParameterList* paraList = (*funcTable)[id]->paraList;
            if(paraList->size() < n->argumentList->size()){
                cout<<"Too many arguments for "<<id<<endl;
                exit(-1);
            }
            if(paraList->size() > n->argumentList->size()){
                cout<<"Too few arguments for "<<id<<endl;
                exit(-1);
            }
            for(int i = 0; i < paraList->size(); i++){
                typeCheck((Expression*)((*paraList)[i]), (*(n->argumentList))[i]->expression,varEnv->back());
            }
        }
    }
}
void addId(string identifier, VariableType* type ,ParameterList* paraList, int address, unordered_map<string, Symbol*>* hashList){
    Symbol* temp = new Symbol(identifier,type,paraList, address);
    pair<string,Symbol*> kvPair(identifier,temp);

    if(hashList->find(identifier) == hashList->end()){
        hashList->insert(kvPair);
    }
    else{
        cout<<endl<<identifier<<" is redefined!"<<endl;
        exit(-1);
    }
}

VariableType* typeCheck(Expression* exp1, Expression* exp2,unordered_map<string, Symbol*>* hashList){
    if(exp1->isNeedVarDeclareCheck){
        string id1 = exp1->identifier->toString();
        if(exp2->isNeedVarDeclareCheck){
            string id2 = exp2->identifier->toString();

            if((*hashList)[id1]->type->toString() != (*hashList)[id2]->type->toString()){
                cout<<id1<<" and "<<id2<<" cause a type conflict"<<endl;
                exit(-1);
            }
        }
        else if (exp2->isNeedFuncDeclareCheck){
            string id2 = exp2->identifier->toString();

            if((*hashList)[id1]->type->toString() != (*funcTable)[id2]->type->toString()){
                cout<<id1<<" and "<<id2<<" cause a type conflict"<<endl;
                exit(-1);
            }
        }
        else{
            if((*hashList)[id1]->type->toString() != exp2->type->toString()){
                cout<<id1<<" causes a type conflict"<<endl;
                exit(-1);
            }
        }
        return (*hashList)[id1]->type;
    }
    else if(exp1->isNeedFuncDeclareCheck){
        string id1 = exp1->identifier->toString();
        if(exp2->isNeedVarDeclareCheck){
            string id2 = exp2->identifier->toString();

            if((*funcTable)[id1]->type->toString() != (*hashList)[id2]->type->toString()){
                cout<<id1<<" and "<<id2<<" cause a type conflict"<<endl;
                exit(-1);
            }
        }
        else if (exp2->isNeedFuncDeclareCheck){
            string id2 = exp2->identifier->toString();

            if((*funcTable)[id1]->type->toString() != (*funcTable)[id2]->type->toString()){
                cout<<id1<<" and "<<id2<<" cause a type conflict"<<endl;
                exit(-1);
            }
        }
        else{
            if((*funcTable)[id1]->type->toString() != exp2->type->toString()){
                cout<<id1<<" causes a type conflict"<<endl;
                exit(-1);
            }
        }
        return (*funcTable)[id1]->type;
    }
    else{
        if(exp2->isNeedVarDeclareCheck){
            string id2 = exp2->identifier->toString();

            if(exp1->type->toString() != (*hashList)[id2]->type->toString()){
                cout<<id2<<" causes a type conflict"<<endl;
                exit(-1);
            }
        }
        else if (exp2->isNeedFuncDeclareCheck){
            string id2 = exp2->identifier->toString();

            if(exp1->type->toString() != (*funcTable)[id2]->type->toString()){
                cout<<id2<<" causes a type conflict"<<endl;
                exit(-1);
            }
        }
        else{
            if(exp1->type->toString() != exp2->type->toString()){
                cout<<"Expressions cause a type conflict"<<endl;
                exit(-1);
            }
        }
        return exp1->type;
    }
}

void declareCheck(string id, unordered_map<string, Symbol*>* hashList, string kind){
    if(hashList->find(id) == hashList->end()){
        cout<<kind<<" "<<id<<" is undefined!"<<endl;
        exit(-1);
    }
}
