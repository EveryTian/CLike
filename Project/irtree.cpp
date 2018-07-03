#include "irtree.h"
#include <iostream>
#include <typeinfo>
#include "ast.hpp"

using namespace std;

extern Program* program;
queue <TreeNode*> *tempNode = new queue<TreeNode*>();
queue <TreeExp*> *tempExp = new queue<TreeExp*>();
vector<TreeExp*> *tempExpList = new vector<TreeExp*>();
TreeNode* root;

void translate();
void _translate(Node * n);

void translate(){
    _translate(program);
}

void _translate(Node * n){
    queue <Node*> *q = new queue<Node*>();

    n->pushto(q);
    int size = q->size();
    for(int i = 0; i < size; i++){
        Node* temp = q->front();
        q->pop();
        _translate(temp);
    }
    string nodeId = typeid(*n).name();
    for(auto it = nodeId.begin(); it != nodeId.end();){
        if(*it >= '0' && *it <= '9'){
            nodeId.erase(it);
        }
        else{
            ++it;
        }
    }
    if(nodeId == "IntValue"){
        tempExp->push(new ConstExp(n->value));
    }
    else if (nodeId == "Identifier"){
        tempExp->push(new NameExp(n->toString()));
    }
    else if (nodeId == "Variable"){
        tempExp->push(new MemExp(tempExp->front()));
        tempExp->pop();
    }
    else if (nodeId == "Argument"){
        int size = tempExp->size();
        for(int i = 0; i < size; i++){
            tempExpList->push_back(tempExp->front());
            tempExp->pop();
        }
    }
    else if (nodeId == "FunctionCallExpression"){
        tempExp->push(new CallExp(n->identifier->toString(), tempExpList));
        tempExpList->clear();
    }
    else if (nodeId == "NotExpression"){
        tempExp->push(new SinopExp(NOT, tempExp->front()));
        tempExp->pop();
    }
    else if (nodeId == "UnaryExpression"){
        tempExp->push(new SinopExp(UMINUS, tempExp->front()));
        tempExp->pop();
    }
    else if (nodeId == "DivExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(DIV,left,right));
    }
    else if (nodeId == "MulExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(MUL,left,right));
    }
    else if (nodeId == "SubExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(SUB,left,right));
    }
    else if (nodeId == "AddExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(ADD,left,right));
    }
    else if (nodeId == "AndExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(AND,left,right));
    }
    else if (nodeId == "OrExpression"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempExp->push(new BinopExp(OR,left,right));
    }
    else if (nodeId == "AssignExpression"||nodeId == "VariableDeclarationStatement"){
        TreeExp* left = tempExp->front();
        tempExp->pop();
        TreeExp* right = tempExp->front();
        tempExp->pop();

        tempNode->push(new MoveNode(left,right));
    }
    else if (nodeId == "ExpressionStatement"){
        tempNode->push(new ExpNode(tempExp->front()));
        tempExp->pop();
    }
    else if (nodeId == "Block"){
        TreeNode* block;
        int size = tempNode->size();

        if(size >= 2){
            TreeNode* left = tempNode->front();
            tempNode->pop();
            TreeNode* right = tempNode->front();
            tempNode->pop();
            block = new SeqNode(left,right);
            for(int i = 0; i < size-2; i++){
                block = new SeqNode(block,tempNode->front());
                tempNode->pop();
            }
            tempNode->push(block);
        }
    }
    else if (nodeId == "Program"){
        int size = tempNode->size();

        if(size >= 2){
            TreeNode* left = tempNode->front();
            tempNode->pop();
            TreeNode* right = tempNode->front();
            tempNode->pop();
            root = new SeqNode(left,right);
            for(int i = 0; i < size-2; i++){
                root = new SeqNode(root,tempNode->front());
                tempNode->pop();
            }
        }
    }
    else if (nodeId == "IntValue"){
        tempExp->push(new ConstExp(n->value));
    }
    else if (nodeId == "IntValue"){
        tempExp->push(new ConstExp(n->value));
    }
    else if (nodeId == "IntValue"){
        tempExp->push(new ConstExp(n->value));
    }
    else if (nodeId == "IntValue"){
        tempExp->push(new ConstExp(n->value));
    }
}
