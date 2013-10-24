%{
#define YYSTYPE double
#include <math.h>
#include <stdio.h>

int yylex();

void yyerror (char const *s)
{
    fprintf(stdout, "%s\n", s);
}

%}


%token CLASS EXTENDS NEW THIS
%token PUBLIC STATIC
%token IF WHILE TRUE FLASE ELSE
%token PRINT MAIN RETURN LENGTH
%token VOID INT BOOL INTARR STRING STRINGARR
%token DIGIT
%token ID
%token BINOP

%left '.'
%left '['
%left '('
%left '!'
%left '+' '-'
%left '*'

%%
Program:          MainClass ClassDecls
;

MainClass:        CLASS ID '{' PUBLIC STATIC VOID MAIN '(' STRINGARR ID ')' '{' Statement '}' '}'
;

ClassDecls:       ClassDecl ClassDecls
                |
;

ClassDecl:        CLASS ID '{' VarDecls MethodDecls '}'
                | CLASS ID EXTENDS ID '{' VarDecls MethodDecls '}'
;

VarDecls:        VarDecls VarDecl
                |
;

VarDecl:          Type ID ';'
;

MethodDecls:     MethodDecl MethodDecls
                |
;

MethodDecl:       PUBLIC Type ID '(' FormatList ')' '{' VarDecls Statements RETURN Exp ';' '}'
;

FormatList:       Type ID FormatListRest
                |
;
FormatListRest:   ',' Type ID FormatListRest
                |
;

Type:             INTARR
                | STRINGARR
                | INT
                | STRING
                | BOOL
                | ID
;

Statement:        '{' Statements '}'
                | IF '(' Exp ')' Statement ELSE Statement
                | WHILE '(' Exp ')' Statement
                | PRINT '(' Exp ')' ';'
                | ID '=' Exp ';'
                | ID '[' Exp ']' '=' Exp ';'
;

Statements:       Statement Statements
                |

Exp:              Exp '+' Exp ';'
                | Exp '-' Exp ';'
                | Exp '*' Exp ';'
                | Exp '[' Exp ']'
                | Exp '.' LENGTH
                | Exp '.' ID '(' ExpList ')'
                | DIGIT
                | TRUE
                | FLASE
                | ID
                | THIS
                | NEW INT '[' Exp ']'
                | NEW  ID '(' ')'
                | '!' Exp
                | '(' Exp ')'
;

ExpList:          Exp ExpListRest
                |
;

ExpListRest:      ',' Exp ExpListRest
                |
;
%%
