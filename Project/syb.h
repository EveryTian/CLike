#ifndef SYB_H
#define SYB_H

#include <string>
#include "ast.hpp"
#include <vector>

class Symbol;

class Symbol{
    public:
        std::string identifier;
        VariableType* type;
        ParameterList* paraList;
        int address;

    Symbol(std::string identifier, VariableType* type, ParameterList* paraList, int address){
        this->identifier = identifier;
        this->type = type;
	this->paraList = paraList;
        this->address = address;
    }
    std::string toString(){
	std::string* str = new std::string();
	
	str->append(identifier + "  " + type->toString() + "  ");
	if(paraList != nullptr)
		for(int i = 0; i < paraList->size(); i++){
		    str->append(((*paraList)[i])->variableType->toString() + " ");
		}
	str->append(std::to_string(address));
        return *str;
    }
};

#endif
