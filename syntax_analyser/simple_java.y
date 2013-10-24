%{	
// here we will include .h files from the first exercise
#include <stdio.h>
#include "interfaces.h"

int yylex(void);
void yyerror(const char *);
int yydebug = 1;

%}
/*Bison declarations*/

%union { 
const Program* program; 
const MainClass* mainClass; 
const ClassDeclarations* classDeclarations; 
const ClassDeclaration* classDeclaration; 
const Var_declarations* var_declarations; 
const Var_declaration* var_declaration; 
const Method_declarations* method_declarations; 
const Method_declaration* method_declaration; 
const Statements* statements; 
const Statement* statement; 
const Type* type; 
const Arguements* arguements; 
const Arguement* arguement; 
const Assignment* assignment; 
const Expression* expression; 
const Expression_list* expression_list; 
}

%token <intval> INTEGER
%token <boolval> BOOLEAN
%token <var_pointer> ID

%token CLASS EXTENDS PUBLIC STATIC MAIN IF WHILE TRUE FALSE NEW THIS VOID RETURN SYSPRINT LENGTH ELSE
%token INT_TYPE BOOLEAN_TYPE STRING_TYPE

%nonassoc ASSIGN '.' '[' ']'/* = */


%left AND  	/* && */
%left LT    /* < */
%left '!'
%left '+' '-'	/* + - */
%left '*' 	/* * / */

%start program

%error-verbose

%%

program: mainClass classDeclarations  /*ok*/ 	{ $$ = new ProgramImpl($1, $2);	}


mainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '('STRING_TYPE '['']' ID ')' '{' statement '}' '}' /*ok*/
	{ $$ = new MainClassImpl("_", "_", $1) 	}


classDeclarations: /*ok*/
											{ $$ = new ClassDeclarationsImpl()}
	| classDeclaration classDeclarations 	{ $$ = new ClassDeclarationsImpl($1, $2)}

classDeclaration: /*ok*/
	CLASS ID '{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl("_", $1)}
	| CLASS ID EXTENDS ID'{' varDeclarations methodDeclarations '}' { $$ = new ClassDeclarationImpl("_", "_", $1)}

varDeclarations: /*ok*/
	/*{$$ = NULL ;}*/					{ $$ = new varDeclarationsImpl()}
	| varDeclaration varDeclarations 	{ $$ = new varDeclarationsImpl($1, $2)}


varDeclaration: /*ok*/
	type ID ';' { $$ = new varDeclarationImpl($1, "_")}


methodDeclarations: /*ok*/
	/*{$$ = NULL ;}*/							{ $$ = new methodDeclarationsImpl()}
	| methodDeclaration methodDeclarations 		{ $$ = new methodDeclarationsImpl($1, $2)}

methodDeclaration: /*ok*/
	PUBLIC type ID '(' arguements ')' '{' varDeclarations statements RETURN expression ';' '}'
	{$$ = new methodDeclarationImpl($1, "_", $2, $3, $4, $5)}

statements: /*ok*/
	/*{$$ = NULL ;}*/ 		{$$ = new StatementsImpl()}
	| statement statements	{$$ = new StatementsImpl($1, $2)}

statement: /*ok*/
	'{' statements '}'   								{ $$ = new BlockStm($1)}
	| assignment ';'    			 					{ $$ = new AssignStm($1)}
	| IF '(' expression ')' statement ELSE statement	{ $$ = new IfElseStm($1, $2, $3)}
	| WHILE '(' expression ')' statement				{ $$ = new WhileStm($1, $2)}
	| SYSPRINT '(' expression ')' ';'					{ $$ = new PrintStmPrintStm($1)}
	| ID '['expression']' = statement ';'				{ $$ = new AssignArrStm("_", $1, $2)}

type: /*ok*/
	 INT_TYPE '['']'	{ $$ = new InternalType(Type.INT_ARR)}
	| BOOLEAN_TYPE		{ $$ = new InternalType(Type.BOOL)}
	| STRING_TYPE		{ $$ = new InternalType(Type.STRING)}	
	| INT_TYPE			{ $$ = new InternalType(Type.INT)}

arguements: /*ok*/
	/*{$$ = NULL ;}*/			{$$ = new ArguementsImpl()}
	| arguement ',' arguements	{$$ = new ArguementsImpl($1, $2)}
	| arguement					{$$ = new ArguementsImpl($1, new Arguments())}

arguement: /*ok*/
	type ID		{$$ = new ArguementImpl($1, "_")}

assignment:
	ID ASSIGN expression {$$ = new AssignmentImpl("_", $1)}

expression: /*ok*/
	expression '+' expression  	{ $$ = new ArithmExp(Arithm.PLUS, $1, $2)} 
	| expression '-' expression	{ $$ = new ArithmExp(Arithm.MINUS, $1, $2)}	
	| expression '*' expression	{ $$ = new ArithmExp(Arithm.MUL, $1, $2)}
	| expression '/' expression	{ $$ = new ArithmExp(Arithm.DIV, $1, $2)}
	| expression AND expression	{ $$ = new LogicExp(Logic.AND, $1, $2)}	
	| expression LT expression  { $$ = new LogicExp(Logic.LT, $1, $2)}
	| expression '[' expression ']'  	{ $$ = new ArrValExp($1, $2)}
	| expression '.' LENGTH  			{ $$ = new LenExp($1)}
	| expression '.' ID '('expressionList')'	{ $$ = new CallMethodExp($1, "_", $2)}
	| INTEGER 									{$$ = new IntVal($1)}
	/*| STRING*/
	| TRUE			{ $$ = new BoolVal(true)}
	| FALSE			{ $$ = new BoolVal(false))}
	| ID			{ $$ = new IdExp("_")}
	| THIS			{ $$ = new ThisExp("_")}
	| NEW INT_TYPE '[' expression ']' { $$ = new NewIntArrExp($1)}
	| NEW ID '(' ')'		{ $$ = new NewExp("_")}
	| '!' expression 		{ $$ = new LogicExp(Logic.NOT, $1)}
	| '(' expression ')' 	{ $$ = $1}

expressionList: /*ok*/
	/*{$$ = NULL ;}*/					{$$ = new expressionListImpl()}
	| expression ',' expressionList		{$$ = new expressionListImpl($1, $2)}
	| expression						{$$ = new expressionListImpl($1)}

%%
