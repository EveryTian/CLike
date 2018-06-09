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
// class GlobalFunctionDeclarationStatement;
class FunctionDeclarationStatement;
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

// typedef std::vector<GlobalStatement *> GlobalStatementList;
// typedef std::vector<VariableDeclaration *> VariableDeclarationList;
typedef std::vector<Parameter *> ParameterList;
typedef std::vector<VariableDeclarationStatement *> VariableDeclarationStatementList;
typedef std::vector<Statement *> StatementList;
typedef std::vector<Argument *> ArgumentList;

class Node {
public:
};

class Program : public Node {
public:
	StatementList *globalStatementList;
};

class Statement : public Node {
public:
};

class Expression : public Node {
public:
};

// class GlobalStatement : Statement {
// public:
// };

class VariableType : public Node {
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

// class GlobalVariableDeclarationStatement : GlobalStatement {
// public:
// 	VariableType *variableType;
//     Variable *variable;
//     Expression *expression;
//     GlobalVariableDeclarationStatement(VariableType *varType, Variable *var, Expression *expr) {
//         variableType = varType;
//         variable = var;
//         expression = expr;
//     }
// };

class VariableDeclarationStatement : public Statement {
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

class Variable : public Expression {
public:
	Identifier *identifier;
	Expression *indexExpression;
    Variable(Identifier *ident, Expression *indexExpr) {
        identifier = ident;
        indexExpression = indexExpr;
    }
};

class Identifier : public Expression {
public:
	std::string *identifier;
    Identifier(std::string *ident) {
        identifier = ident;
    }
};

// class GlobalFunctionDeclarationStatement : GlobalStatement {
class FunctionDeclarationStatement : public Statement {
public:
	VariableType *variableType;
	Identifier *identifier;
	ParameterList *parameterList;
	Block *block;
    FunctionDeclarationStatement(VariableType *varType, Identifier *ident, ParameterList *paraList, Block *blk) {
        variableType = varType;
        identifier = ident;
        parameterList = paraList;
        block = blk;
    }
};

class Parameter : public Node {
public:
	VariableType *variableType;
	Identifier *identifier;
    Parameter(VariableType *varType, Identifier *ident) {
        variableType = varType;
        identifier = ident;
    }
};

class Block : public Statement {
public:
	VariableDeclarationStatementList *variableDeclarationstatementList;
	StatementList *statementList;
    Block(VariableDeclarationStatementList *vdsl, StatementList *sl) {
        variableDeclarationstatementList = vdsl;
        statementList = sl;
    }
};

class ExpressionStatement : public Statement {
public:
	Expression *expression;
    ExpressionStatement(Expression *e) {
        expression = e;
    }
};

class ReturnStatement : public Statement {
public:
	Expression *expression;
    ReturnStatement(Expression *e) {
        expression = e;
    }
};

class WhileStatement : public Statement {
public:
	Expression *expression;
	Statement *statement;
    WhileStatement(Expression *expr, Statement* stmt) {
        expression = expr;
        statement = stmt;
    }
};

class ForStatement : public Statement {
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

class IfStatement : public Statement {
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

class AssignExpression : public Expression {
public:
	Variable *variable;
	Expression *expression;
    AssignExpression(Variable *v, Expression *e) {
        variable = v;
        expression = e;
    }
};

class AndExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    AndExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class OrExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    OrExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class GtExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    GtExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class LtExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    LtExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class GeExpression : public Expression {
public:
	Expression * expression1;
	Expression *expression2;
    GeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class LeExpression : public Expression {
public:
	Expression * expression1;
	Expression *expression2;
    LeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class EqExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    EqExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class NeExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    NeExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class AddExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    AddExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class SubExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    SubExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class MulExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    MulExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class DivExpression : public Expression {
public:
	Expression *expression1;
	Expression *expression2;
    DivExpression(Expression *e1, Expression *e2) {
        expression1 = e1;
        expression2 = e2;
    }
};

class UnaryExpression : public Expression {
public:
	Expression * expression;
    UnaryExpression(Expression* e) {
        expression = e;
    }
};

class NotExpression : public Expression {
public:
	Expression * expression;
    NotExpression(Expression* e) {
        expression = e;
    }
};

class FunctionCallExpression : public Expression {
public:
	Identifier *identifier;
	ArgumentList *argumentList;
    FunctionCallExpression(Identifier *ident, ArgumentList *argList) {
        identifier = ident;
        argumentList = argList;
    }
};

class Argument : public Expression {
public:
	Expression *expression;
    Argument(Expression *expr) {
        expression = expr;
    }
};

class Value : public Expression {
public:
};

class IntValue : public Value {
public:
	int value;
	IntValue(int v) { value = v; }
};

class FloatValue : public Value {
public:
	float value;
	FloatValue(float v) { value = v; }
};

#endif
