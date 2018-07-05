#include <vector>
#include <string>
#include "syb.h"
#include <queue>
#include "ast.hpp"
#include <unordered_map>
#include <iostream>
#include <fstream>

using namespace std;

extern Program* program;

class Frame{
public:
    Symbol* label;
    vector<Symbol*>* localVars;
    Frame* returnAddr;
    vector<Symbol*>* arguments;
    Frame(Symbol* funcLabel){
        this->label = funcLabel;
        this->localVars = new vector<Symbol*>();
        this->returnAddr = nullptr;
        this->arguments = new vector<Symbol*>();
    }
    void print(fstream *s){
        *s << this->label->identifier<<endl;
        if(localVars != nullptr)
            for(int i = 0; i < localVars->size(); i++){
                *s<<"  "<<to_string(i)<<"     "<<((*localVars)[i])->identifier<<endl;
            }
        if(returnAddr != nullptr)
            *s<<"Return: "<<returnAddr->label->identifier<<endl;
        else
            *s<<"Return: null"<<endl;
        if(arguments != nullptr)
            for(int i = 0; i < arguments->size(); i++){
                *s<<"  "<<to_string(i)<<"     "<<((*arguments)[i])->identifier<<endl;
            }

    }
    Frame* duplicate(){
        Frame* temp = new Frame(this->label);
        vector<Symbol*>* vars(this->localVars);
        vector<Symbol*>* args(this->arguments);
        temp->arguments = args;
        temp->localVars = vars;
        temp->returnAddr = this->returnAddr;
        return temp;
    }
};
void createStackFrame();
void _createStackFrame(Node * n);
