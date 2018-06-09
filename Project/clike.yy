%{

#include "ast.hpp"
#include <string>
#include <cstdlib>

Program *program;
int yylex(void);
void yyerror(const char *);

%}

%token <value> INT_VALUE FLOAT_VALUE IDENT_VALUE
%token <token> LCB RCB LP RP LB RB SQ DQ
%token <token> ADD SUB MUL DIV ASSIGN EQ NE GT GE LT LE AND OR NOT
%token <token> IF ELSE DO WHILE FOR BREAK CONTINUE RETURN
%token <token> VOID INT FLOAT CHAR
%token <token> SEMI COMMA

%union {
    Node *node;
    Program *prog;
    Statement *stmt;
    Expression *expr;

    GlobalStatement *glbstmt;
    GlobalVariableDeclarationStatement *glbvardecstmt;
    GlobalFunctionDeclarationStatement *glbfundecstmt;

    VariableDeclarationStatement *vardecstmt;
    VariableType *vartype;
    VariableDeclaration *vardec;
    Variable *var;
    Identifier *idt;
    Parameter *para;
    Block *block;
    ExpressionStatement *exprstmt;
    Argument *arg;

    GlobalStatementList *glbstmtls;
    
    // VariableDeclarationList *vardecls;
    ParameterList *parals;
    VariableDeclarationStatementList *vardecstmtls;
    StatementList *stmtls;
    ArgumentList *argls;
    Value *value;
}

%type <node> program
%type <glbstmtls> global_statement_list
%type <glbstmt> global_statement
%type <stmt> statement variable_declaration_statement function_declaration_statement block
%type <vartype> variable_type
// %type <vardecls> variable_declaration_list
%type <idt> identifier
%type <parals> parameter_list
%type <vardecstmtls> variable_declaration_statement_list
%type <stmtls> statement_list
%type <para> parameter
// %type <vardec> variable_declaration
%type <var> variable
%type <expr> expression
%type <value> number
%type <argls> argument_list

%right '='
%left OR
%left AND
%left ADD SUB
%left MUL DIV
%right UPLUS UMINUS
%right NOT
%left RP RB LP LB
%nonassoc NOELSE
%nonassoc ELSE

%start program

%%

program: global_statement_list {
        program = new Program();
        program->globalStatementList = $1;
    }
    ;

global_statement_list: global_statement {
        $$ = new GlobalStatementList();
        $$->push_back($1);
    }
    | global_statement_list global_statement {
        $1->push_back($2);
    }
    ;

global_statement:
    variable_declaration_statement {
        $$ = $1; 
    }
    | function_declaration_statement {
        $$ = $1;
    }
    ;

variable_declaration_statement:
    variable_type variable ASSIGN expression SEMI {
        $$ = new VariableDeclarationStatement($1, $2, $3);
    }
    ;

function_declaration_statement:
    variable_type identifier LP parameter_list RP block {
        $$ = new GlobalFunctionDeclarationStatement($1, $2, $4, $6);
    }
    // | variable_type LB RB identifier
    | VOID identifier LP parameter_list RP block {
        $$ = new GlobalFunctionDeclarationStatement(NULL, $2, $4, $6);
    }
    ;

variable_type:
    INT {
        $$ = new VariableType(1);
    }
    | FLOAT {
        $$ = new VariableType(2);
    }
    | CHAR {
        $$ = new VariableType(3);
    }
    ;

// variable_declaration_list: variable_declaration {}
//     | variable_declaration COMMA variable_declaration_list {}
//     ;

identifier:
    IDENT_VALUE {
        $$ = Identifier($1);
    }
    ;

parameter_list:
    parameter {
        $$ = new ParameterList();
        $$->push_back($1);
    }
    | parameter_list COMMA parameter {
        $1->push_back($3);
    }
    | VOID {
        $$ = NULL;
    }
    | {
        $$ = NULL;
    } // The same to VOID.
    ;

block:
    LCB RCB {
        $$ = NULL;
    }
    | LCB statement_list RCB {
        $$ = new Block(NULL, $2);
    }
    | LCB variable_declaration_statement_list statement_list RCB {
        $$ = new Block($1, $2);
    }
    ;

variable_declaration_statement_list:
    variable_declaration_statement {
        $$ = new VariableDeclarationStatementList();
        $$->push_back($1);
    }
    | variable_declaration_statement_list variable_declaration_statement {
        $1->push_back($2);
    }
    ;

statement_list:
    statement {
        $$ = new StatementList();
        $$->push_back($1);
    }
    | statement_list statement {
        $1->push_back($2);
    }
    ;

parameter:
    variable_type identifier {
        $$ = new Parameter($1, $2);
    }
    ;

// variable_declaration: variable ASSIGN expression {}
//     | variable {}
//     ;

variable:
    identifier {
        $$ = new Variable($1, NULL);
    }
    | identifier LB expression RB {
        $$ = new Variable($1, $3);
    }
    ;

statement:
    expression SEMI {
        $$ = new ExpressionStatement($1);
    }
    | block {
        $$ = $1;
    }
    | RETURN expression SEMI {
        $$ = new ReturnStatement($2);
    }
    | WHILE LP expression RP statement {
        $$ = new WhileStatement($3, $5);
    }
    | FOR LP expression SEMI expression SEMI expression RP statement {
        $$ = new ForStatement($3, $5, $7, $9);
    }
    | IF LP expression RP statement %prec NOELSE {
        $$ = new IfStatement($3, $5, NULL);
    }
    | IF LP expression RP statement ELSE statement {
        $$ = new IfStatement($3, $5, $7);
    }
    ;

expression:
    variable ASSIGN expression {
        $$ = new AssignExpression($1, $3);
    }
    | expression AND expression {
        $$ = new AndExpression($1, $3);
    }
    | expression OR expression {
        $$ = new OrExpression($1, $3);
    }
    | expression GT expression {
        $$ = new GtExpression($1, $3);
    }
    | expression LT expression {
        $$ = new LtExpression($1, $3);
    }
    | expression GE expression {
        $$ = new GeExpression($1, $3);
    }
    | expression LE expression {
        $$ = new LeExpression($1, $3);
    }
    | expression EQ expression {
        $$ = new EqExpression($1, $3);
    }
    | expression NE expression {
        $$ = new NeExpression($1, $3);
    }
    | expression ADD expression {
        $$ = new AddExpression($1, $3);
    }
    | expression SUB expression {
        $$ = new SubExpression($1, $3);
    }
    | expression MUL expression {
        $$ = new MulExpression($1, $3);
    }
    | expression DIV expression {
        $$ = new DivExpression($1, $3);
    }
    | LP expression RP {
        $$ = $2;
    }
    | SUB expression %prec UMINUS {
        $$ = new UnaryExpression($2);
    }
    | ADD expression %prec UPLUS {
        $$ = $2;
    }
    | NOT expression {
        $$ = new NotExpression($2);
    }
    | variable LP argument_list RP {
        $$ = new FunctionCallExpression()
    }
    | number {
        $$ = $1;
    }
    | variable {
        $$ = $1;
    }
    ;

number: 
    INT_VALUE { 
        $$ = new IntValue(atoi($1->c_str()));
        delete $1;
    }
    | FLOAT_VALUE {
        $$ = new FloatValue(atof($1->c_str()));
        delete $1;
    }
    ;

argument_list: 
    expression {
        $$ = new ArgumentList();
        $$->push_back($1);
    }
    | argument_list COMMA expression {
        $1->push_back($2);
    }
    | {
        $$ = NULL;
    }
    ;
    
%%

int main(void) {
    return yyparse();
}
