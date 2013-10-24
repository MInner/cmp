#include <stdio.h>
#include "bi.hpp"

extern int yyparse();

void yyerror(const char* descr){
	// printf("%s on line #%d\n", descr, yylloc.first_line);
}

int main(void){
	yyparse();
	return 0;
}