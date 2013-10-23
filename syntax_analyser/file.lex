

%{
#include <math.h>
#include "simple_java.tab.h"
#include <stdio.h>
int n_lines = 1, n_chars = 1; 

void update_loc();
%}

%option noyywrap
%option nounput


NUMBER [0-9]*
ID [a-zA-Z_][a-zA-Z0-9_-]*
/*STRING ""*/


%%

	/* keywords */

"class" 			{update_loc(); n_chars += 5; return CLASS; }
"extends" 		{update_loc(); n_chars += 7; return EXTENDS;} 
"public" 			{update_loc(); n_chars += 6; return PUBLIC; }
"static" 			{update_loc(); n_chars += 6; return STATIC; }
"main" 			{update_loc(); n_chars += 4; return MAIN; }
"if" 			    {update_loc(); n_chars += 2; return IF; }
"while" 			{update_loc(); n_chars += 5; return WHILE;} 
"new"			    {update_loc(); n_chars += 3; return NEW; }
"this"			{update_loc(); n_chars += 4; return THIS; }
"void" 			{update_loc(); n_chars += 4; return VOID; }
"return" 			{update_loc(); n_chars += 6; return RETURN;} 
"length" 			{update_loc(); n_chars += 6; return LENGTH; }
"else" 			{update_loc(); n_chars += 4; return ELSE; }


"&&" 			{update_loc(); n_chars += 2; return AND; }
"<" 			{update_loc(); n_chars += 1; return LT; }
"=" 			{update_loc(); n_chars += 1; return ASSIGN; }

"true"			{update_loc(); n_chars += 4; yylval.intval = 1; return BOOLEAN; }
"false"			{update_loc(); n_chars += 5; yylval.intval = 0; return BOOLEAN; }

	/* func */
"System.out.println"	{update_loc(); n_chars += 18; return SYSPRINT;}

	/* types */
"int"			{update_loc(); n_chars += 3; return INT_TYPE;}
"bool"		{update_loc(); n_chars += 4; return BOOLEAN_TYPE;}
	/*int\[\]		printf("INTARR_TYPE{%d, %d} ", n_chars, n_lines); n_chars += 5;*/
"String" 			{update_loc(); n_chars += 6; return STRING_TYPE;}

	/* entities */
{NUMBER} 	{update_loc(); n_chars += yyleng; return INTEGER;} /*yylval.intval = atoi(yytext);*/ 
{ID} 		{update_loc(); n_chars += yyleng; return ID;}
	/*{STRING} 		printf("STRING(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;*/

	/* other symbols */
[\r\n]			{update_loc(); n_lines++; n_chars = 1;}
[[:space:]]			{update_loc(); n_chars++;}
[+-/*()_;,\[\]\.{}] 	{update_loc(); n_chars++; return *yytext;}
.		{update_loc(); n_chars += yyleng; yyerror("Unknown symbol\n"); printf("Symbol:%c", *yytext);}

%%
void update_loc(){
	printf("%s\n", yytext);
	yylloc.first_line=n_lines;
	yylloc.last_line=n_lines;
	yylloc.first_column=n_chars;
	yylloc.last_column=n_chars+yyleng;
}

