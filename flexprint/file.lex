%option noyywrap
%option nounput

NUMBER [0-9]*
ID [a-zA-Z][a-zA-Z0-9]*

%{
#include <math.h>
/* #include "lex.h" */
#include <stdio.h>
int n_lines = 0, n_chars = 0;
%}



%%

	/* keywords */

" "|\t          n_chars++;

\n              n_lines++; n_chars = 0;

class 			printf("CLASS{%d, %d} ", n_chars, n_lines); n_chars += 5;
extern 			printf("EXTERN{%d, %d} ", n_chars, n_lines); n_chars += 6;
public 			printf("PUBLIC{%d, %d} ", n_chars, n_lines); n_chars += 6;
static 			printf("STATIC{%d, %d} ", n_chars, n_lines); n_chars += 6;
main 			printf("MAIN{%d, %d} ", n_chars, n_lines); n_chars += 4;
if 			    printf("IF{%d, %d} ", n_chars, n_lines); n_chars += 2;
while 			printf("WHILE{%d, %d} ", n_chars, n_lines); n_chars += 5;
new			    printf("NEW{%d, %d} ", n_chars, n_lines); n_chars += 3;
this			printf("THIS{%d, %d} ", n_chars, n_lines); n_chars += 4;

true			printf("TRUE{%d, %d} ", n_chars, n_lines); n_chars += 4;
false			printf("FALSE{%d, %d} ", n_chars, n_lines); n_chars += 5;

	/* func */
System.out.println	printf("SYSPrint{%d, %d} ", n_chars, n_lines); n_chars += 18;

	/* types */
int			printf("TYPE_INT{%d, %d} ", n_chars, n_lines); n_chars += 3;
bool		printf("TYPE_BOOL{%d, %d} ", n_chars, n_lines); n_chars += 4;
int\[\]		printf("TYPE_INTARR{%d, %d} ", n_chars, n_lines); n_chars += 5;

	/* entities */
{NUMBER} 	printf("INTEGER(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;
{ID} 		printf("VARIABLE(%s){%d, %d} ", yytext, n_chars, n_lines); n_chars += yyleng;

	/* other symbols */
.		printf("%s ", yytext); n_chars += yyleng;

%%

int main()
{
  printf("Give me your input:\n");
  yylex();
}
