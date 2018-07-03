#ifndef SYB_H
#define SYB_H

#include <string>
#include "ast.hpp"
#include <vector>
#include <fstream>

using namespace std;

class Symbol;

class Symbol{
    public:
        string identifier;
        VariableType* type;
        ParameterList* paraList;
        int address;

    Symbol(string identifier, VariableType* type, ParameterList* paraList, int address){
        this->identifier = identifier;
        this->type = type;
	this->paraList = paraList;
        this->address = address;
    }
    void print(fstream* f){
	string* str = new string();

	(*f).setf(ios::left);
	(*f).width(7);
	(*f)<<to_string(address);
	(*f).width(16);
	(*f)<<identifier;
	(*f).width(15);
	(*f)<<type->toString();
	if(paraList != nullptr)
		for(int i = 0; i < paraList->size(); i++){
		    (*f)<<((*paraList)[i])->variableType->toString()<< " ";
		}
	(*f)<<endl;

    }
};

#endif
