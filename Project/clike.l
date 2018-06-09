%{

#include <string>

#include "ast.hpp"
#include "clike.tab.hh"

#define YYSTYPE union {std::string *string}
// #include "syntactic.hpp"

#define HANDLE_TOKEN(tokenName) return tokenName
#define HANDLE_TOKEN_WITH_VALUE(tokenName) yylval.string = new std::string(yytext, yyleng); return tokenName

%}

%option noyywrap

whitespace          [ \t\n\r]
integer             [0-9]+
float               [0-9]+\.[0-9]+
identifier          [a-zA-Z_][a-zA-Z_0-9]*

lineComment         "//"[^\n]*
blockCommentOp      "/*"
blockCommentEd      "*/"

leftBrace           "{"
rightBrace          "}"
leftParenthesis     "("
rightParenthesis    ")"
leftBracket         "["
rightBracket        "]"
singleQuote         "'"
doubleQuote         "\""

addOp               "+"
subOp               "-"
mulOp               "*"
divOp               "/"
assignOp            "="
eqOp                "=="
neOp                "!="
gtOp                ">"
geOp                ">="
ltOp                "<"
leOp                "<="
andOp               "&&"
orOp                "||"
notOp               "!"
bitAndOp            "&"
bitOrOp             "|"
bitNotOp            "~"

semicolon           ";"
comma               ","

ifKey               "if"
elseKey             "else"
doKey               "do"
whileKey            "while"
forKey              "for"
breakKey            "break"
continueKey         "continue"
returnKey           "return"

voidKey             "void"
intKey              "int"
floatKey            "float"
charKey             "char"

%%

{whitespace}        {}
{lineComment}       {}

{leftBrace}         { HANDLE_TOKEN(LCB); }
{rightBrace}        { HANDLE_TOKEN(RCB); }
{leftParenthesis}   { HANDLE_TOKEN(LP); }
{rightParenthesis}  { HANDLE_TOKEN(RP); }
{leftBracket}       { HANDLE_TOKEN(LB); }
{rightBracket}      { HANDLE_TOKEN(RB); }
{singleQuote}       { HANDLE_TOKEN(SQ); }
{doubleQuote}       { HANDLE_TOKEN(DQ); }

{addOp}             { HANDLE_TOKEN(ADD); }
{subOp}             { HANDLE_TOKEN(SUB); }
{mulOp}             { HANDLE_TOKEN(MUL); }
{divOp}             { HANDLE_TOKEN(DIV); }
{assignOp}          { HANDLE_TOKEN(ASSIGN); }
{eqOp}              { HANDLE_TOKEN(EQ); }
{neOp}              { HANDLE_TOKEN(NE); }
{gtOp}              { HANDLE_TOKEN(GT); }
{geOp}              { HANDLE_TOKEN(GE); }
{ltOp}              { HANDLE_TOKEN(LT); }
{leOp}              { HANDLE_TOKEN(LE); }
{andOp}             { HANDLE_TOKEN(AND); }
{orOp}              { HANDLE_TOKEN(OR); }
{notOp}             { HANDLE_TOKEN(NOT); }

{semicolon}         { HANDLE_TOKEN(SEMI); }
{comma}             { HANDLE_TOKEN(COMMA); }

{ifKey}             { HANDLE_TOKEN(IF); }
{elseKey}           { HANDLE_TOKEN(ELSE); }
{doKey}             { HANDLE_TOKEN(DO); }
{whileKey}          { HANDLE_TOKEN(WHILE); }
{forKey}            { HANDLE_TOKEN(FOR); }
{breakKey}          { HANDLE_TOKEN(BREAK); }
{continueKey}       { HANDLE_TOKEN(CONTINUE); }
{returnKey}         { HANDLE_TOKEN(RETURN); }

{voidKey}           { HANDLE_TOKEN(VOID); }
{intKey}            { HANDLE_TOKEN(INT); }
{floatKey}          { HANDLE_TOKEN(FLOAT); }
{charKey}           { HANDLE_TOKEN(CHAR); }

{integer}           { HANDLE_TOKEN_WITH_VALUE(INT_VALUE); }
{float}             { HANDLE_TOKEN_WITH_VALUE(FLOAT_VALUE); }
{identifier}        { HANDLE_TOKEN_WITH_VALUE(IDENT_VALUE); }

.                   { fprintf(stderr, "Unknown Token at Line %d.\n", yylineno); yyterminate(); }

%%

/*
{bitAndOp}          { HANDLE_TOKEN(BAND); }
{bitOrOp}           { HANDLE_TOKEN(BOR); }
{bitNotOp}          { HANDLE_TOKEN(BNOT); }
*/
