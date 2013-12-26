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

program: mainClass classDeclarations  /*ok*/ 	{ $$ = new ProgramImpl($1, $2, @$.first_line, @$.first_column);}


mainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '('STRING_TYPE '['']' ID ')' '{' statement '}' '}' /*ok*/
	{ $$ = new MainClassImpl(Symbol::getSymbol($2), Symbol::getSymbol($12), $15, @$.first_line, @$.first_column); 	}


classDeclarations: /*ok*/
											{ $$ = NULL;}
	| classDeclaration classDeclarations 	{ $$ = new ClassDeclarationsImpl($1, $2, @$.first_line, @$.first_column);}

classDeclaration: /*ok*/
	CLASS ID '{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl(Symbol::getSymbol($2), $4, $5, @$.first_line, @$.first_column);}
	| CLASS ID EXTENDS ID'{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl(Symbol::getSymbol($2), Symbol::getSymbol($4), $6, $7, @$.first_line, @$.first_column);}

varDeclarations: /*ok*/
	/*{$$ = NULL ;}*/					{ $$ = NULL;}
	| varDeclarations varDeclaration 	{ $$ = new VarDeclarationsImpl($2, $1, @$.first_line, @$.first_column);}


varDeclaration: /*ok*/
	type ID ';' { $$ = new VarDeclarationImpl($1, Symbol::getSymbol($2), @$.first_line, @$.first_column);}

methodDeclarations: /*ok*/
	/*{$$ = NULL ;}*/							{ $$ = NULL;}
	| methodDeclaration methodDeclarations 		{ $$ = new MethodDeclarationsImpl($1, $2, @$.first_line, @$.first_column);}

methodDeclaration: /*ok*/
	PUBLIC type ID '(' arguements ')' '{' varDeclarations statements RETURN expression ';' '}'
	{$$ = new MethodDeclarationImpl($2, Symbol::getSymbol($3), $5, $8, $9, $11, @$.first_line, @$.first_column);}

statements: /*ok*/
	/*{$$ = NULL ;}*/ 		{$$ = NULL;}
	| statement statements	{$$ = new StatementsImpl($1, $2, @$.first_line, @$.first_column);}

statement: /*ok*/
	'{' statements '}'   								{ $$ = new BlockStm($2, @$.first_line, @$.first_column);}
	| assignment ';'    			 					{ $$ = new AssignStm($1, @$.first_line, @$.first_column);}
	| IF '(' expression ')' statement ELSE statement	{ $$ = new IfElseStm($3, $5, $7, @$.first_line, @$.first_column);}
	| WHILE '(' expression ')' statement				{ $$ = new WhileStm($3, $5, @$.first_line, @$.first_column);}
	| SYSPRINT '(' expression ')' ';'					{ $$ = new PrintStmPrintStm($3, @$.first_line, @$.first_column);}
	| ID '['expression']' ASSIGN expression ';'			{ $$ = new AssignArrStm(Symbol::getSymbol($1), $3, $6, @$.first_line, @$.first_column);}  // TODO третий аргумент должен быть экспрешеном

type: /*ok*/
	 INT_TYPE '['']'	{ $$ = new InternalType(Type::INT_ARR, @$.first_line, @$.first_column);}
	| BOOLEAN_TYPE		{ $$ = new InternalType(Type::BOOL, @$.first_line, @$.first_column);}
	| STRING_TYPE		{ $$ = new InternalType(Type::STRING, @$.first_line, @$.first_column);}	
	| INT_TYPE			{ $$ = new InternalType(Type::INT, @$.first_line, @$.first_column);}
	| ID 				{ $$ = new CustomType(Symbol::getSymbol($1), @$.first_line, @$.first_column);}

arguements: /*ok*/
	/*{$$ = NULL ;}*/			{$$ = NULL;}
	| arguement ',' arguements	{$$ = new ArguementsImpl($1, $3, @$.first_line, @$.first_column);}
	| arguement					{ArguementsImpl* a = NULL; $$ = new ArguementsImpl($1, a, @$.first_line, @$.first_column);}

arguement: /*ok*/
	type ID		{$$ = new ArguementImpl($1, Symbol::getSymbol($2), @$.first_line, @$.first_column);}

assignment:
	ID ASSIGN expression {$$ = new AssignmentImpl( Symbol::getSymbol($1), $3, @$.first_line, @$.first_column);}

expression: /*ok*/
	expression '+' expression  	{ $$ = new ArithmExp(Arithm::PLUS, $1, $3, @$.first_line, @$.first_column);} 
	| expression '-' expression	{ $$ = new ArithmExp(Arithm::MINUS, $1, $3, @$.first_line, @$.first_column);}	
	| expression '*' expression	{ $$ = new ArithmExp(Arithm::MUL, $1, $3, @$.first_line, @$.first_column);}
	| expression '/' expression	{ $$ = new ArithmExp(Arithm::DIV, $1, $3, @$.first_line, @$.first_column);}
	| expression AND expression	{ $$ = new LogicExp(Logic::L_AND, $1, $3, @$.first_line, @$.first_column);}	
	| expression LT expression  { $$ = new LogicExp(Logic::L_LT, $1, $3, @$.first_line, @$.first_column);}
	| expression '[' expression ']'  	{ $$ = new ArrValExp($1, $3, @$.first_line, @$.first_column);}
	| expression '.' LENGTH  			{ $$ = new LenExp($1, @$.first_line, @$.first_column);}
	| expression '.' ID '('expressionList')'	{ $$ = new CallMethodExp($1, Symbol::getSymbol($3), $5, @$.first_line, @$.first_column);}
	| INTEGER 									{$$ = new IntVal($1, @$.first_line, @$.first_column);}
	| TRUE			{ $$ = new BoolVal(true, @$.first_line, @$.first_column);}
	| FALSE			{ $$ = new BoolVal(false, @$.first_line, @$.first_column);}
	| ID			{ $$ = new IdExp(Symbol::getSymbol($1), @$.first_line, @$.first_column);}
	| THIS			{ $$ = new ThisExp(@$.first_line, @$.first_column); } 
	| NEW INT_TYPE '[' expression ']' { $$ = new NewIntArrExp($4, @$.first_line, @$.first_column);}
	| NEW ID '(' ')'		{ $$ = new NewExp(Symbol::getSymbol($2), @$.first_line, @$.first_column);}
	| '!' expression 		{ $$ = new LogicExp(Logic::L_NOT, $2, @$.first_line, @$.first_column);}
	| '(' expression ')' 	{ $$ = $2;}

expressionList: /*ok*/
	/*{$$ = NULL ;}*/					{$$ = NULL;}
	| expression ',' expressionList		{$$ = new ExpressionListImpl($1, $3, @$.first_line, @$.first_column);}
	| expression						{$$ = new ExpressionListImpl($1, @$.first_line, @$.first_column);}

%%
