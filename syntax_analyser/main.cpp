#include <stdio.h>
#include <iostream>
#include "bi.hpp"
#include "printvisitor.h"
#include "classes.h"

extern int yyparse();

void yyerror(const char* descr){
	printf("%s on line #%d\n", descr, yylloc.first_line);
}

const ProgramImpl* ProgramImpl::me = 0;

int main(void){

	yyparse();

	PrintVisitor* pv = new PrintVisitor();

	ProgramImpl::me->Accept(pv);
	return 0;
}