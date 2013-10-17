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


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     CLASS = 258,
     EXTENDS = 259,
     NEW = 260,
     THIS = 261,
     PUBLIC = 262,
     STATIC = 263,
     IF = 264,
     WHILE = 265,
     TRUE = 266,
     FLASE = 267,
     ELSE = 268,
     PRINT = 269,
     MAIN = 270,
     RETURN = 271,
     LENGTH = 272,
     VOID = 273,
     INT = 274,
     BOOL = 275,
     INTARR = 276,
     STRING = 277,
     STRINGARR = 278,
     DIGIT = 279,
     ID = 280,
     BINOP = 281
   };
#endif
/* Tokens.  */
#define CLASS 258
#define EXTENDS 259
#define NEW 260
#define THIS 261
#define PUBLIC 262
#define STATIC 263
#define IF 264
#define WHILE 265
#define TRUE 266
#define FLASE 267
#define ELSE 268
#define PRINT 269
#define MAIN 270
#define RETURN 271
#define LENGTH 272
#define VOID 273
#define INT 274
#define BOOL 275
#define INTARR 276
#define STRING 277
#define STRINGARR 278
#define DIGIT 279
#define ID 280
#define BINOP 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;

