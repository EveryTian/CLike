#ifndef SYB_H
#define SYB_H

#include <string>
 
class Symbol;

class Symbol{
    public:
        std::string identifier;
        std::string type;
        int address;
    Symbol(std::string identifier, std::string type, int address){
        this->identifier = identifier;
        this->type = type;
        this->address = address;
    }
    std::string toString(){
        return identifier + "  " + type + "  " + std::to_string(address);
    }
};

#endif
