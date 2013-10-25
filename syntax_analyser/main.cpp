#include <stdio.h>
#include "bi.hpp"
#include "printvisitor.h"
#include "classes.h"

extern int yyparse();

void yyerror(const char* descr){
	printf("%s on line #%d\n", descr, yylloc.first_line);
}

int main(void){
	PrintVisitor pv();

	yyparse();
	return 0;
}