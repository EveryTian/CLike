/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_CLIKE_TAB_HH_INCLUDED
# define YY_YY_CLIKE_TAB_HH_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_VALUE = 258,
    FLOAT_VALUE = 259,
    IDENT_VALUE = 260,
    LCB = 261,
    RCB = 262,
    LP = 263,
    RP = 264,
    LB = 265,
    RB = 266,
    SQ = 267,
    DQ = 268,
    ADD = 269,
    SUB = 270,
    MUL = 271,
    DIV = 272,
    ASSIGN = 273,
    EQ = 274,
    NE = 275,
    GT = 276,
    GE = 277,
    LT = 278,
    LE = 279,
    AND = 280,
    OR = 281,
    NOT = 282,
    IF = 283,
    ELSE = 284,
    DO = 285,
    WHILE = 286,
    FOR = 287,
    BREAK = 288,
    CONTINUE = 289,
    RETURN = 290,
    VOID = 291,
    INT = 292,
    FLOAT = 293,
    CHAR = 294,
    SEMI = 295,
    COMMA = 296,
    UPLUS = 297,
    UMINUS = 298,
    NOELSE = 299
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 24 "clike.yy" /* yacc.c:1909  */

    Node                            *node;
    Program                         *prog;
    Statement                       *stmt;
    Expression                      *expr;

    // GlobalStatement *glbstmt;
    // GlobalVariableDeclarationStatement *glbvardecstmt;
    // GlobalFunctionDeclarationStatement *glbfundecstmt;
    FunctionDeclarationStatement    *glbfundecstmt;

    VariableDeclarationStatement    *vardecstmt;
    VariableType                    *vartype;
    VariableDeclaration             *vardec;
    Variable                        *var;
    Identifier                      *idt;
    Parameter                       *para;
    Block                           *block;
    ExpressionStatement             *exprstmt;
    Argument                        *arg;

    // GlobalStatementList *glbstmtls;
    
    // VariableDeclarationList *vardecls;
    ParameterList *parals;
    VariableDeclarationStatementList *vardecstmtls;
    StatementList *stmtls;
    ArgumentList *argls;
    Value *value;
    std::string *string;

#line 131 "clike.tab.hh" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_CLIKE_TAB_HH_INCLUDED  */
