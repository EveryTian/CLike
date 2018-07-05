#include "frame.h"

unordered_map<string, vector<Frame*>*>* frameTable = new unordered_map<string, vector<Frame*>*>();
vector<Frame*> *stackFrame = new vector<Frame*>();
Frame* currentFrame = nullptr;

void createStackFrame(){
    fstream actRec;

    actRec.open("StackFrame.txt", ios_base::out);
    _createStackFrame(program);
    for(auto it = stackFrame->begin(); it != stackFrame->end(); ++it){
        (*it)->print(&actRec);
    }
    actRec.close();
}

void _createStackFrame(Node * n){
    queue <Node*> *q = new queue<Node*>();

    n->pushto(q);
    if(n->isFuncDec){
        vector<Frame*> *frameList = new vector<Frame*>();
        Symbol* newFunc = new Symbol(n->identifier->toString(),nullptr,nullptr, stackFrame->size());
        Frame* newFrame = new Frame(newFunc);

        frameList->push_back(newFrame);
        pair<string,vector<Frame*>*> kvPair(n->identifier->toString(), frameList);

        frameTable->insert(kvPair);
        currentFrame = newFrame;
        if(currentFrame->label->identifier == "main"){
            stackFrame->push_back(newFrame->duplicate());
        }
    }
    if(n->isVarDec){
        vector<Symbol*>* currentLocalVars = currentFrame->localVars;
        Symbol* newVar = new Symbol("Local Variable: "+n->variable->identifier->toString(),n->variableType,nullptr, currentLocalVars->size());

        currentLocalVars->push_back(newVar);
    }
    //function call
    if(n->isNeedFuncDeclareCheck){
        string id1 = n->identifier->toString();
        string id2 = currentFrame->label->identifier;
        vector<Frame*> * calleeFrames = (*frameTable)[id1];
        vector<Frame*> * callerFrames = (*frameTable)[id2];

        if(id1 != id2){
             calleeFrames->front()->returnAddr = currentFrame;
            if(currentFrame->label->identifier == "main"){
                for(auto it = calleeFrames->begin(); it != calleeFrames->end(); ++it){
                    stackFrame->push_back((*it)->duplicate());
                }
            }
            else{
                for(auto it = calleeFrames->begin(); it != calleeFrames->end(); ++it){
                    callerFrames->push_back((*it)->duplicate());
                }
            }
            if(n->argumentList != nullptr){
                for(int i = 0; i < n->argumentList->size(); i++){
                    currentFrame->arguments->push_back(new Symbol("Argument "+ to_string(i)+" for " + id1,nullptr,nullptr, currentFrame->arguments->size()));
                }
            }
        }
    }
    int size = q->size();
    for(int i = 0; i < size; i++){
        Node* temp = q->front();
        q->pop();
        _createStackFrame(temp);
    }
}
