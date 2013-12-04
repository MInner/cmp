%code requires { 
#include "interfaces.h" 
#include "enums.h"
#include "classes.h"
#include "symbol.h"
}
%locations

%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *);
int yydebug = 1;

%}
/*Bison declarations*/

%union { 
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
} 


%token <intval> INTEGER
%token <boolval> BOOLEAN
%token <strval> ID

%type <program> program
%type <mainClass> mainClass
%type <classDeclarations> classDeclarations
%type <classDeclaration> classDeclaration
%type <varDeclarations> varDeclarations
%type <varDeclaration> varDeclaration
%type <methodDeclarations> methodDeclarations
%type <methodDeclaration> methodDeclaration
%type <statements> statements
%type <statement> statement
%type <type> type
%type <arguements> arguements
%type <arguement> arguement
%type <assignment> assignment
%type <expression> expression
%type <expressionList> expressionList


%token CLASS EXTENDS PUBLIC STATIC MAIN IF WHILE TRUE FALSE NEW THIS VOID RETURN SYSPRINT LENGTH ELSE
%token INT_TYPE BOOLEAN_TYPE STRING_TYPE

%nonassoc ASSIGN '.' '[' ']'/* = */


%left AND  	/* && */
%left LT    /* < */
%left '!'
%left '+' '-'	/* + - */
%left '*' 	/* * / */
%left '/'

%start program

%error-verbose

%%

program: mainClass classDeclarations  /*ok*/ 	{ $$ = new ProgramImpl($1, $2);}


mainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '('STRING_TYPE '['']' ID ')' '{' statement '}' '}' /*ok*/
	{ $$ = new MainClassImpl(Symbol::getSymbol($2), Symbol::getSymbol($12), $15); 	}


classDeclarations: /*ok*/
											{ $$ = NULL;}
	| classDeclaration classDeclarations 	{ $$ = new ClassDeclarationsImpl($1, $2);}

classDeclaration: /*ok*/
	CLASS ID '{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl(Symbol::getSymbol($2), $4, $5);}
	| CLASS ID EXTENDS ID'{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl(Symbol::getSymbol($2), Symbol::getSymbol($4), $6, $7);}

varDeclarations: /*ok*/
	/*{$$ = NULL ;}*/					{ $$ = NULL;}
	| varDeclarations varDeclaration 	{ $$ = new VarDeclarationsImpl($2, $1);}


varDeclaration: /*ok*/
	type ID ';' { $$ = new VarDeclarationImpl($1, Symbol::getSymbol($2));}

methodDeclarations: /*ok*/
	/*{$$ = NULL ;}*/							{ $$ = NULL;}
	| methodDeclaration methodDeclarations 		{ $$ = new MethodDeclarationsImpl($1, $2);}

methodDeclaration: /*ok*/
	PUBLIC type ID '(' arguements ')' '{' varDeclarations statements RETURN expression ';' '}'
	{$$ = new MethodDeclarationImpl($2, Symbol::getSymbol($3), $5, $8, $9, $11);}

statements: /*ok*/
	/*{$$ = NULL ;}*/ 		{$$ = NULL;}
	| statement statements	{$$ = new StatementsImpl($1, $2);}

statement: /*ok*/
	'{' statements '}'   								{ $$ = new BlockStm($2);}
	| assignment ';'    			 					{ $$ = new AssignStm($1);}
	| IF '(' expression ')' statement ELSE statement	{ $$ = new IfElseStm($3, $5, $7);}
	| WHILE '(' expression ')' statement				{ $$ = new WhileStm($3, $5);}
	| SYSPRINT '(' expression ')' ';'					{ $$ = new PrintStmPrintStm($3);}
	| ID '['expression']' ASSIGN expression ';'			{ $$ = new AssignArrStm(Symbol::getSymbol($1), $3, $6);}  // TODO третий аргумент должен быть экспрешеном

type: /*ok*/
	 INT_TYPE '['']'	{ $$ = new InternalType(Type::INT_ARR);}
	| BOOLEAN_TYPE		{ $$ = new InternalType(Type::BOOL);}
	| STRING_TYPE		{ $$ = new InternalType(Type::STRING);}	
	| INT_TYPE			{ $$ = new InternalType(Type::INT);}
	| ID 				{ $$ = new CustomType(Symbol::getSymbol($1));}

arguements: /*ok*/
	/*{$$ = NULL ;}*/			{$$ = NULL;}
	| arguement ',' arguements	{$$ = new ArguementsImpl($1, $3);}
	| arguement					{ArguementsImpl* a = NULL; $$ = new ArguementsImpl($1, a);}

arguement: /*ok*/
	type ID		{$$ = new ArguementImpl($1, Symbol::getSymbol($2));}

assignment:
	ID ASSIGN expression {$$ = new AssignmentImpl( Symbol::getSymbol($1), $3);}

expression: /*ok*/
	expression '+' expression  	{ $$ = new ArithmExp(Arithm::PLUS, $1, $3);} 
	| expression '-' expression	{ $$ = new ArithmExp(Arithm::MINUS, $1, $3);}	
	| expression '*' expression	{ $$ = new ArithmExp(Arithm::MUL, $1, $3);}
	| expression '/' expression	{ $$ = new ArithmExp(Arithm::DIV, $1, $3);}
	| expression AND expression	{ $$ = new LogicExp(Logic::L_AND, $1, $3);}	
	| expression LT expression  { $$ = new LogicExp(Logic::L_LT, $1, $3);}
	| expression '[' expression ']'  	{ $$ = new ArrValExp($1, $3);}
	| expression '.' LENGTH  			{ $$ = new LenExp($1);}
	| expression '.' ID '('expressionList')'	{ $$ = new CallMethodExp($1, Symbol::getSymbol($3), $5);}
	| INTEGER 									{$$ = new IntVal($1);}
	| TRUE			{ $$ = new BoolVal(true);}
	| FALSE			{ $$ = new BoolVal(false);}
	| ID			{ $$ = new IdExp(Symbol::getSymbol($1));}
	| THIS			{ $$ = new ThisExp(); } 
	| NEW INT_TYPE '[' expression ']' { $$ = new NewIntArrExp($4);}
	| NEW ID '(' ')'		{ $$ = new NewExp(Symbol::getSymbol($2));}
	| '!' expression 		{ $$ = new LogicExp(Logic::L_NOT, $2);}
	| '(' expression ')' 	{ $$ = $2;}

expressionList: /*ok*/
	/*{$$ = NULL ;}*/					{$$ = NULL;}
	| expression ',' expressionList		{$$ = new ExpressionListImpl($1, $3);}
	| expression						{$$ = new ExpressionListImpl($1);}

%%
