%{
#include "ast.h"
#include <stdio.h>
#include <string>
%}

%token <string> INT_VALUE FLOAT_VALUE IDENT_VALUE
%token <token> LCB RCB LP RP LB RB SQ DQ
%token <token> ADD SUB MUL DIV ASSIGN EQ NE GT GE LT LE AND OR NOT
%token <token> IF ELSE DO WHILE FOR BREAK CONTINUE RETURN
%token <token> VOID INT FLOAT CHAR
%token <token> SEMI COMMA

%right '='
%left OR
%left AND
%left ADD SUB
%left MUL DIV
%right UPLUS UMINUS
%right NOT
%left RP RB LP LB
%nanossoc NOELSE
%nanossoc ELSE

$start program

%union {
    int intNum;
    float floatNum;
    char c;
    std::string ident;
}

%%

program: global_statement_list {}
    ;

global_statement_list: global_statement {}
    | global_statement global_statement_list {}
    ;

global_statement: variable_declaration_statement {}
    | function_declaration_statement {}
    ;

variable_declaration_statement: variable_type variable_declaration_list SEMI {}
    ;

function_declaration_statement: variable_type identifier LP parameter_list RP block {}
    // | variable_type LB RB identifier
    | VOID identifier LP parameter_list RP block {}
    ;

variable_type: INT {}
    | FLOAT {}
    | CHAR {}
    ;

variable_declaration_list: variable_declaration {}
    | variable_declaration COMMA variable_declaration_list {}
    ;

identifier: IDENT_VALUE {}
    ;

parameter_list: parameter {}
    | parameter COMMA parameter_list {}
    | VOID {}
    | {} // The same to VOID.
    ;

block: LCB RCB {}
    | LCB statement_list RCB {}
    | LCB variable_declaration_statement_list statement_list RCB {}
    ;

variable_declaration_statement_list: variable_declaration_statement {}
    | variable_declaration_statement variable_declaration_statement_list {}
    ;

statement_list: statement {}
    | statement statement_list {}
    ;

parameter: variable_type identifier {}
    ;


variable_declaration: variable ASSIGN expression {}
    | variable {}
    ;

variable: identifier {}
    | identifier LB INT_VALUE RB {}
    ;

statement: expression SEMI {}
    | block {}
    | RETURN expression SEMI {}
    | WHILE LP expression RP statement {}
    | FOR LP expression SEMI expression SEMI expression RP statement {}
    | IF LP expression RP statement %prec NOELSE {}
    | IF LP expression RP statement ELSE statement {}

expression: expression ASSIGN expression {}
    | expression AND expression {}
    | expression OR expression {}
    | expression GT expression {}
    | expression LT expression {}
    | expression GE expression {}
    | expression LE expression {}
    | expression EQ expression {}
    | expression NE expression {}
    | expression ADD expression {}
    | expression SUB expression {}
    | expression MUL expression {}
    | expression DIV expression {}
    | LP expression RP {}
    | SUB expression %prec UMINUS {}
    | ADD expression %prec UPLUS {}
    | NOT expression {}
    | identifier LP argument_list RP {}
    | identifier {}
    | number {}
    | expression LB expression LP {}

number: INT_VALUE {}
    | FLOAT_VALUE {}

argument_list: expression {}
    | expression COMMA argument_list {}
    | {}
    

%%