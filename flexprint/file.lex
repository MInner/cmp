/* int TId = 1, TNum = 2, TBinop = 3, TComment = 4, KWClass = 5; */

DIGIT [0-9]
ID [a-z][a-z0-9]*

%{
#include <math.h>
/* #include "lex.h" */
#include <stdio.h>
%}

%%
	/* entities */
DIGIT* 		printf("DIGIT(%s)", yytext);
ID 		printf("ID(%s)", yytext);

	/* keywords */
class 			printf("CLASS");
extern 			printf("EXTERN");
public 			printf("PUBLIC");
static 			printf("STATIC");
main 			printf("MAIN");
if 			printf("IF");
while 			printf("WHILE");
true			printf("TRUE");
false			printf("FASLE");
new			printf("NEW");
this			printf("THIS");

	/* func */
System.out.println	printf("SYSPrint");

	/* types */
int		printf("TYPE_INT");
bool		printf("TYPE_BOOL");
int\[\]		printf("TYPE_INTARR");

	/* other symbols */
.		printf("%s", yytext);
