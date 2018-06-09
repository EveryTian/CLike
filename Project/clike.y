%{
#include "ast.h"
#include <stdio.h>
#include <string>
%}

%token <string> INT_VALUE FLOAT_VALUE IDENT_VALUE
%token <token> LCB RCB LP RP LB RB SQ DQ
%token <token> ADD SUB MUL DIV ASSIGN EQ NE GT GE LT LE AND OR NOT
%token <token> IF ELSE DO WHILE FOR BREAK CONTINUE
%token <token> VOID INT FLOAT CHAR
%token <token> SEMI COMMA

%type 

%left SEMI
%left OR
%left AND
%right NOT
%left ADD SUB
%left MUL DIV
%right UMINUS
%left RP
%right LP

$start program

%union {
    int intNum;
    float floatNum;
    char c;
    std::string ident;
}

%%

program: global_statements {}
    ;

global_statements: global_statement {}
    | global_statement global_statements {}
    ;

global_statement: variable_declaration_statement {}
    | function_declaration_statement {}
    ;

variable_declaration_statement: variable_type variable_declaration_list SEMI {}
    ;

function_declaration_statement: variable_type function_identifier LP parameter_list RP block {}
    | variable_type LB RB function_identifier
    | VOID function_identifier LP parameter_list RP block {}
    ;

variable_type: INT {}
    | FLOAT {}
    | CHAR {}
    ;

variable_declaration_list: variable_declaration {}
    | variable_declaration variable_declaration_list {}
    ;

variable_declaration: variable

function_identifier


    

statement :
    LCB statements RCB {

    }
    |
    if_statement {

    }
    |
    while_statement {

    }
    |
    declare_statement {

    }
    |
    assign_statement {

    }
;

if_statement :
    IF LP expression RP statement {

    }
    |
    IF LP expression RP statement ELSE statement {

    }
    


%%