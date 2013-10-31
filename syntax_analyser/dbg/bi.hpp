/* A Bison parser, made by GNU Bison 2.5.  */

/* Bison interface for Yacc-like parsers in C
   
      Copyright (C) 1984, 1989-1990, 2000-2011 Free Software Foundation, Inc.
   
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

/* "%code requires" blocks.  */

/* Line 2068 of yacc.c  */
#line 1 "simple_java.y"
 
#include "interfaces.h" 
#include "enums.h"
#include "classes.h"



/* Line 2068 of yacc.c  */
#line 46 "bi.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     INTEGER = 258,
     BOOLEAN = 259,
     ID = 260,
     CLASS = 261,
     EXTENDS = 262,
     PUBLIC = 263,
     STATIC = 264,
     MAIN = 265,
     IF = 266,
     WHILE = 267,
     TRUE = 268,
     FALSE = 269,
     NEW = 270,
     THIS = 271,
     VOID = 272,
     RETURN = 273,
     SYSPRINT = 274,
     LENGTH = 275,
     ELSE = 276,
     INT_TYPE = 277,
     BOOLEAN_TYPE = 278,
     STRING_TYPE = 279,
     ASSIGN = 280,
     AND = 281,
     LT = 282
   };
#endif
/* Tokens.  */
#define INTEGER 258
#define BOOLEAN 259
#define ID 260
#define CLASS 261
#define EXTENDS 262
#define PUBLIC 263
#define STATIC 264
#define MAIN 265
#define IF 266
#define WHILE 267
#define TRUE 268
#define FALSE 269
#define NEW 270
#define THIS 271
#define VOID 272
#define RETURN 273
#define SYSPRINT 274
#define LENGTH 275
#define ELSE 276
#define INT_TYPE 277
#define BOOLEAN_TYPE 278
#define STRING_TYPE 279
#define ASSIGN 280
#define AND 281
#define LT 282




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 2068 of yacc.c  */
#line 18 "simple_java.y"
 
const IProgram* program; 
const IMainClass* mainClass; 
const IClassDeclarations* classDeclarations; 
const IClassDeclaration* classDeclaration; 
const IVarDeclarations* varDeclarations; 
const IVarDeclaration* varDeclaration; 
const IMethodDeclarations* methodDeclarations; 
const IMethodDeclaration* methodDeclaration; 
const IStatements* statements; 
const IStatement* statement; 
const IType* type; 
const IArguements* arguements; 
const IArguement* arguement; 
const IAssignment* assignment; 
const IExpression* expression; 
const IExpressionList* expressionList;
const char* strval;
int intval;
bool boolval;



/* Line 2068 of yacc.c  */
#line 141 "bi.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
} YYLTYPE;
# define yyltype YYLTYPE /* obsolescent; will be withdrawn */
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif

extern YYLTYPE yylloc;

