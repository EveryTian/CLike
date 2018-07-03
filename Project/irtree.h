#include <vector>
#include <string>
#include <queue>

using namespace std;

enum relOP{
    GT,LT,GE,LE,EQ,NE
};

enum sinOP{
    UMINUS,NOT
};

enum binOP{
    ADD,SUB,MUL,DIV,AND,OR
};

class TreeExp;

class TreeNode{
public:
    enum{
        SEQ,LABEL,JUMP,CJUMP,MOVE,EXP
    } kind;
    //seq
    TreeNode* leftNode;
    TreeNode* rightNode;
    //label
    string label;
    //jump
    string destination;
    //cjump
    relOP op;
    TreeExp* leftExp;
    TreeExp* rightExp;
    string trueLabel;
    string falseLabel;
    //move
    TreeExp* moveFrom;
    TreeExp* moveTo;
    //exp
    TreeExp* exp;
    virtual string toString(){
    }
	virtual void pushto(queue<TreeNode*> *q){
	}
};

class SeqNode:public TreeNode{
public:
    SeqNode(TreeNode* left, TreeNode* right){
        this->kind = SEQ;
        this->leftNode = left;
        this->rightNode = right;
    }
    virtual string toString(){
    	return "seq";
    }
	virtual void pushto(queue<TreeNode*> *q){
        q->push(leftNode);
        q->push(rightNode);
	}
};

class LabelNode:public TreeNode{
public:
    LabelNode(string label){
        this->kind = LABEL;
        this->label = label;
    }
    virtual string toString(){
    	return label;
    }
};

class JumpNode:public TreeNode{
public:
    JumpNode(string destination){
        this->kind = JUMP;
        this->destination = destination;
    }
    virtual string toString(){
    	return "jump";
    }
};

class CjumpNode:public TreeNode{
public:
    CjumpNode(relOP op,TreeExp* leftExp,TreeExp* rightExp,string trueLabel,string falseLabel){
        this->kind = CJUMP;
        this->op = op;
        this->leftExp = leftExp;
        this->rightExp = rightExp;
        this->trueLabel = trueLabel;
        this->falseLabel = falseLabel;
    }
    virtual string toString(){
    	return "cjump";
    }
};

class MoveNode:public TreeNode{
public:
    MoveNode(TreeExp* moveFrom,TreeExp* moveTo){
        this->kind = MOVE;
        this->moveFrom = moveFrom;
        this->moveTo = moveTo;
    }
    virtual string toString(){
    	return "move";
    }
	virtual void pushto(queue<TreeNode*> *q){
        q->push((TreeNode*)moveFrom);
        q->push((TreeNode*)moveTo);
	}
};

class ExpNode:public TreeNode{
public:
    ExpNode(TreeExp* exp){
        this->kind = EXP;
        this->exp = exp;
    }
    virtual string toString(){
    	return "exp";
    }
	/*virtual void pushto(queue<TreeNode*> *q){
        q->push((TreeNode*)exp);
	}*/
};

class TreeExp: public TreeNode{
public:
    enum{
        SINOP,BINOP,MEM,ESEQ,NAME,CONST,CALL
    }kind;
    //sinop
    sinOP sinop;
    TreeExp* exp;
    //binop
    binOP binop;
    TreeExp* leftExp;
    TreeExp* rightExp;
    //mem
    TreeExp* mem;
    //eseq
    TreeNode* seq;
    TreeExp* res;
    //name
    string label;
    //const
    int constNum;
    //call
    string funcName;
    vector<TreeExp*>* expList;
};

class SinopExp:public TreeExp{
public:
    SinopExp(sinOP sinop, TreeExp* exp){
        this->kind = SINOP;
        this->sinop = sinop;
        this->exp = exp;
    }
    virtual string toString(){
        switch (sinop) {
        case UMINUS:
            return "uminus";
        case NOT:
            return "not";
        }
    }
	virtual void pushto(queue<TreeNode*> *q){
        q->push((TreeNode*)exp);
	}
};

class BinopExp:public TreeExp{
public:
    BinopExp(binOP binop, TreeExp* leftExp, TreeExp* rightExp){
        this->kind = BINOP;
        this->binop = binop;
        this->leftExp = leftExp;
        this->rightExp = rightExp;
    }
    virtual string toString(){
        switch (binop) {
        case ADD:
            return "add";
        case SUB:
            return "substraction";
        case MUL:
            return "multiply";
        case DIV:
            return "divide";
        case AND:
            return "and";
        case OR:
            return "or";
        }
    }
	virtual void pushto(queue<TreeNode*> *q){
        q->push((TreeNode*)leftExp);
        q->push((TreeNode*)rightExp);
	}
};

class MemExp:public TreeExp{
public:
    MemExp(TreeExp* mem){
        this->kind = MEM;
        this->mem = mem;
    }
    virtual string toString(){
    	return "mem";
    }
	virtual void pushto(queue<TreeNode*> *q){
        q->push((TreeNode*)mem);
	}
};

class EseqExp:public TreeExp{
public:
    EseqExp(TreeNode* seq, TreeExp* res){
        this->kind = ESEQ;
        this->seq = seq;
        this->res = res;
    }
    virtual string toString(){
    	return "eseq";
    }
};

class NameExp:public TreeExp{
public:
    NameExp(string label){
        this->kind = NAME;
        this->label = label;
    }
    virtual string toString(){
    	return label;
    }
};

class ConstExp:public TreeExp{
public:
    ConstExp(int constNum){
        this->kind = CONST;
        this->constNum = constNum;
    }
    virtual string toString(){
    	return to_string(constNum);
    }
};

class CallExp:public TreeExp{
public:
    CallExp(string funcName, vector<TreeExp*>* expList){
        this->kind = CALL;
        this->funcName = funcName;
	this->expList = new vector<TreeExp*>();
        this->expList->assign(expList->begin(), expList->end());
    }
    virtual string toString(){
    	return "call"+ funcName;
    }
};
