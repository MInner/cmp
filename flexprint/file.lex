%option noyywrap
%option nounput

NUMBER [0-9]*
ID [a-zA-Z][a-zA-Z0-9]*

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

class 			{ return  yytokentype::CLASS }
extends 		{ return yytokentype::EXTENDS }
public 			{ return yytokentype::PUBLIC }
static 			{ return yytokentype::STATIC }
main 			{ return yytokentype::MAIN }
if 			    printf("IF{%d, %d} ", n_chars, n_lines); n_chars += 2;
while 			printf("WHILE{%d, %d} ", n_chars, n_lines); n_chars += 5;
true			printf("TRUE{%d, %d} ", n_chars, n_lines); n_chars += 4;
false			printf("FASLE{%d, %d} ", n_chars, n_lines); n_chars += 5;
new			    printf("NEW{%d, %d} ", n_chars, n_lines); n_chars += 3;
this			printf("THIS{%d, %d} ", n_chars, n_lines); n_chars += 4;

	/* func */
System.out.println	printf("SYSPrint{%d, %d} ", n_chars, n_lines); n_chars += 18;

	/* types */
int		printf("TYPE_INT{%d, %d} ", n_chars, n_lines); n_chars += 3;
bool		printf("TYPE_BOOL{%d, %d} ", n_chars, n_lines); n_chars += 4;
int\[\]		printf("TYPE_INTARR{%d, %d} ", n_chars, n_lines); n_chars += 5;

	/* entities */
{NUMBER} 		printf("DIGIT(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;
{ID} 		printf("ID(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;

	/* other symbols */
.		printf("%s ", yytext); n_chars += yyleng;

%%
