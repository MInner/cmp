%option noyywrap
%option nounput

NUMBER [0-9]*
ID [a-zA-Z][a-zA-Z0-9]*
/*STRING ""*/

%{
#include <math.h>
/* #include "lex.h" */
#include <stdio.h>
#include <bi.hpp>
int n_lines = 0, n_chars = 0;
%}



%%

	/* keywords */

" "|\t          n_chars++;

\n              n_lines++; n_chars = 0;


class 			printf("CLASS{%d, %d} ", n_chars, n_lines); n_chars += 5;
extends 		printf("EXTENDS{%d, %d} ", n_chars, n_lines); n_chars += 7;
public 			printf("PUBLIC{%d, %d} ", n_chars, n_lines); n_chars += 6;
static 			printf("STATIC{%d, %d} ", n_chars, n_lines); n_chars += 6;
main 			printf("MAIN{%d, %d} ", n_chars, n_lines); n_chars += 4;
if 			    printf("IF{%d, %d} ", n_chars, n_lines); n_chars += 2;
while 			printf("WHILE{%d, %d} ", n_chars, n_lines); n_chars += 5;
new			    printf("NEW{%d, %d} ", n_chars, n_lines); n_chars += 3;
this			printf("THIS{%d, %d} ", n_chars, n_lines); n_chars += 4;
void 			printf("VOID{%d, %d} ", n_chars, n_lines); n_chars += 4;
return 			printf("RETURN{%d, %d} ", n_chars, n_lines); n_chars += 6;
length 			printf("LENGTH{%d, %d} ", n_chars, n_lines); n_chars += 6;


"&&" 			printf("AND{%d, %d} ", n_chars, n_lines); n_chars += 2;
"<" 			printf("LT{%d, %d} ", n_chars, n_lines); n_chars += 1;

true			printf("TRUE{%d, %d} ", n_chars, n_lines); n_chars += 4;
false			printf("FALSE{%d, %d} ", n_chars, n_lines); n_chars += 5;

	/* func */
System.out.println	printf("SYSPRINT{%d, %d} ", n_chars, n_lines); n_chars += 18;

	/* types */
int			printf("INT_TYPE{%d, %d} ", n_chars, n_lines); n_chars += 3;
bool		printf("BOOL_TYPE{%d, %d} ", n_chars, n_lines); n_chars += 4;
/*int\[\]		printf("INTARR_TYPE{%d, %d} ", n_chars, n_lines); n_chars += 5;*/
string 			printf("STRING_TYPE{%d, %d} ", n_chars, n_lines); n_chars += 6;

	/* entities */
{NUMBER} 	printf("INTEGER(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;
{ID} 		printf("VARIABLE(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;
/*{STRING} 		printf("STRING(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;*/

	/* other symbols */
.		printf("%s ", yytext); n_chars += yyleng;

%%
