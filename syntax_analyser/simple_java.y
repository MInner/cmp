%{	
// here we will include .h files from the first exercise
#include <stdio.h>

int yylex(void);
void yyerror(char *);
int yydebug = 1;

%}
/*Bison declarations*/

%union { /*union для возможности сделать больше типов*/
  int intval;	/*для возврата целого числа*/
  int boolvar; /*для возврата булевой переменной*/
  int /*VarTableRecord* */ 	var_pointer; 
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
/*Grammars*/
program: mainClass classDeclarations  /*ok*/
	{
		/*TODO some execute*/
	}


mainClass: CLASS ID '{' PUBLIC STATIC VOID MAIN '('STRING_TYPE '[]' ID ')' '{' statement '}' '}' /*ok*/
	{
		/*TODO after semantic analysis*/
	}
	


classDeclarations: /*ok*/
	{ @$;}
	| classDeclaration classDeclarations {/*TODO after semantic analysis*/}

classDeclaration: /*ok*/
	CLASS ID '{' var_declarations method_declarations '}' 
	| CLASS ID EXTENDS ID'{' var_declarations method_declarations '}' 

var_declarations: /*ok*/
	/*{$$ = NULL ;}*/
	| var_declaration var_declarations {/*TODO after SA*/}

var_declaration: /*ok*/
	type ID 

method_declarations: /*ok*/
	/*{$$ = NULL ;}*/
	| method_declaration method_declarations {/*TODO after SA*/}

method_declaration: /*ok*/
	PUBLIC type ID '(' arguements ')' '{' var_declarations statements RETURN expression ';' '}'

statements: /*ok*/
	/*{$$ = NULL ;}*/
	| statement statements

statement: /*ok*/
	'{' statements '}'
	| IF '(' expression ')' statement ELSE statement
	| WHILE '(' expression ')' statement
	| SYSPRINT '(' expression ')' ';'
	| ID ASSIGN expression ';'
	| ID '['expression']' statement ';'

type: /*ok*/
	 INT_TYPE '['']'
	| BOOLEAN_TYPE
	| STRING_TYPE
	| INT_TYPE

arguements: /*ok*/
	/*{$$ = NULL ;}*/
	| arguement ',' arguements 
	| arguement

arguement: /*ok*/
	type ID

expression: /*ok*/ 
	expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression AND expression
	| expression LT expression
	| expression '[' expression ']'
	| expression '.' LENGTH
	| expression '.' ID '('expression_list')'
	| INTEGER
	/*| STRING*/
	| TRUE
	| FALSE
	| ID
	| THIS
	| NEW INT_TYPE '[' expression ']'
	| NEW ID '(' ')'
	| '!' expression
	| '(' expression ')'
	
expression_list: /*ok*/ 
	/*{$$ = NULL ;}*/
	| expression ',' expression_list
	| expression

%%
/*Epologue*/
void yyerror(char* descr){
	printf("%s on line #%d", descr, yylloc.first_line);
}

int main(void){
	yyparse();
	return 0;
}