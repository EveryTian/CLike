#ifndef AST_H
#define AST_H

#include <vector>
#include <string>

class Node;
class Program;
class Statement;
class Expression;
class GlobalStatement;
class VariableType;
class GlobalVariableDeclarationStatement;
class VariableDeclarationStatement;
class VariableDeclaration;
class Variable;
class Identifier;
class GlobalFunctionDeclarationStatement;
class Parameter;
class Block;
class ExpressionStatement;
class ReturnStatement;
class WhileStatement;
class ForStatement;
class IfStatement;
class AssignExpression;
class AndExpression;
class OrExpression;
class GtExpression;
class LtExpression;
class GeExpression;
class LeExpression;
class EqExpression;
class NeExpression;
class AddExpression;
class SubExpression;
class MulExpression;
class DivExpression;
class UnaryExpression;
class NotExpression;
class FunctionCallExpression;
class Argument;
class Value;
class IntValue;
class FloatValue;

typedef std::vector<GlobalStatement *> GlobalStatementList;
// typedef std::vector<VariableDeclaration *> VariableDeclarationList;
typedef std::vector<Parameter *> ParameterList;
typedef std::vector<VariableDeclarationStatement *> VariableDeclarationStatementList;
typedef std::vector<Statement *> StatementList;
typedef std::vector<Argument *> ArgumentList;

class Node {

};

class Program : Node {
public:
	GlobalStatementList *globalStatementList;
};

class Statement : Node {

};

class Expression : Node {

};

class GlobalStatement : Statement {

};

class VariableType : Node {
public:
	enum VariableTypeEnum {
		INT = 1, FLOAT = 2, CHAR = 3
	};
	VariableTypeEnum variableType;
	VariableType(int type) {
        switch (type) {
        case 1:
            variableType = INT;
        case 2:
            variableType = FLOAT;
        case 3:
            variableType = CHAR;
        }
	}
};

class GlobalVariableDeclarationStatement : GlobalStatement {
public:
	VariableType *variableType;
    Variable *variable;
    Expression *expression;
    GlobalVariableDeclarationStatement(VariableType *varType, Variable *var, Expression *expr) {
        variableType = varType;
        variable = var;
        expression = expr;
    }
};

class VariableDeclarationStatement : Statement {
public:
	VariableType *variableType;
    Variable *variable;
    Expression *expression;
    VariableDeclarationStatement(VariableType *varType, Variable *var, Expression *expr) {
        variableType = varType;
        variable = var;
        expression = expr;
    }
};

// class VariableDeclaration : Node {
// public:
// 	Variable * variable;
// 	Expression *expression;
// };

class Variable : Expression {
public:
	Identifier *identifier;
	Expression *indexExpression;
    Variable(Identifier *ident, Expression *indexExpr) {
        identifier = ident;
        indexExpression = indexExpr;
    }
};

class Identifier : Expression {
public:
	std::string *identifier;
    Identifier(std::string *ident) {
        identifier = ident;
    }
};

class GlobalFunctionDeclarationStatement : GlobalStatement {
public:
	VariableType *variableType;
	Identifier *identifier;
	ParameterList *parameterList;
	Block *block;
    GlobalFunctionDeclarationStatement(VariableType *varType, Identifier *ident, ParameterList *paraList, Block *blk) {
        variableType = varType;
        identifier = ident;
        parameterList = paraList;
        block = blk;
    }
};

class Parameter : Node {
public:
	VariableType *variableType;
	Identifier *identifier;
    Parameter(VariableType *varType, Identifier *ident) {
        variableType = varType;
        identifier = ident;
    }
};

class Block : Statement {
public:
	VariableDeclarationStatementList *variableDeclarationstatementList;
	StatementList *statementList;
    Block(VariableDeclarationStatementList *vdsl, StatementList *sl) {
        variableDeclarationstatementList = vdsl;
        statementList = sl;
    }
};

class ExpressionStatement : Statement {
public:
	Expression *expression;
    ExpressionStatement(Expression *e) {
        expression = e;
    }
};

class ReturnStatement : Statement {
public:
	Expression *expression;
    ReturnStatement(Expression *e) {
        expression = e;
    }
};

class WhileStatement : Statement {
public:
	Expression *expression;
	Statement *statement;
    WhileStatement(Expression *expr, Statement* stmt) {
        expression = expr;
        statement = stmt;
    }
};

class ForStatement : Statement {
public:
	Expression *expression1;
	Expression *expression2;
	Expression *expression3;
	Statement *statement;
    ForStatement(Expression *expr1, Expression *expr2, Expression *expr3, Statement *stmt) {
        expression1 = expr1;
        expression2 = expr2;
        expression3 = expr3;
        statement = stmt;
    }
};

class IfStatement : Statement {
public:
	Expression *expression;
	Statement *ifStatement;
	Statement *elseStatement;
    IfStatement(Expression *e, Statement *ts, Statement *es) {
        expression = e;
        ifStatement = ts;
        elseStatement = es;
    }
};

class AssignExpression : Expression {
public:
	Variable *variable;
	Expression *expression;
    AssignExpression(Variable *v, Expression *e) {
        variable = v;
        expression = e;
    }
};

class AndExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    AndExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class OrExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    OrExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class GtExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    GtExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class LtExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    LtExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class GeExpression : Expression {
public:
	Expression * expression1;
	Expression *expression2;
    GeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class LeExpression : Expression {
public:
	Expression * expression1;
	Expression *expression2;
    LeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class EqExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    EqExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class NeExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    NeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class AddExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    AddExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class SubExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    SubExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class MulExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    MulExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class DivExpression : Expression {
public:
	Expression *expression1;
	Expression *expression2;
    DivExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class UnaryExpression : Expression {
public:
	Expression * expression;
    UnaryExpression(Expression* e) {
        expression = e;
    }
};

class NotExpression : Expression {
public:
	Expression * expression;
    NotExpression(Expression* e) {
        expression = e;
    }
};

class FunctionCallExpression : Expression {
public:
	Identifier * identifier;
	ArgumentList *argumentList;
};

class Argument : Expression {
public:
	Expression * expression;
};

class Value : Expression {
};

class IntValue : Value {
public:
	int value;
	IntValue(int v) { value = v; }
};

class FloatValue : Value {
public:
	float value;
	FloatValue(float v) { value = v; }
};

#endif
