%{
// here we will include .h files from the first exercise

int yylex(void);
void yyerror(const char *);
int yydebug = 1;

%}
/*Bison declarations*/

%union { /*union для возможности сделать больше типов*/
  int intval;	/*для возврата целого числа*/
  bool boolvar; /*для возврата булевой переменной*/
}

%token <intval> INTEGER
%token <boolval> BOOLEAN
%token <var_pointer> ID

%token INT PLUS MINUS MULTIPLY UMINUS DIV
%token CLASS EXTERN PUBLIC STATIC MAIN IF WHILE TRUE FALSE NEW THIS

%nonassoc ASSIGN /* = */
%left AND  	/* && */
%left LT    /* < */
%left PLUS MINUS	/* + - */
%left MULTIPLY DIV	/* * / */

%start program

%error-verbose

%%
/*Grammars*/
program: mainClass classDeclarations
	{
		/*TODO some execute*/
	}


mainClass: CLASS 


classDeclarations: 
	{$$ = NULL ;}
	| classDeclaration classDeclarations {/*TODO*/}


%%
/*Epologue*/
