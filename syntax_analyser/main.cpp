#include <stdio.h>
#include <iostream>

#include "enums.h"
#include "bi.hpp"
#include "printvisitor.h"
#include "classes.h"
#include "symbol.h"

extern int yyparse();

void yyerror(const char* descr){
	printf("%s on line #%d\n", descr, yylloc.first_line);
}

const ProgramImpl* ProgramImpl::me = 0;

int main(void){

	// std::cout << Symbol::getSymbol("a") << std::endl << Symbol::getSymbol("b") << std::endl << Symbol::getSymbol("a") << std::endl;
	// const Symbol* d = Symbol::getSymbol("a");
	// std::cout << d << std::endl;

	yyparse();

	PrintVisitor* pv = new PrintVisitor();
	pv->padding = -1;

	ProgramImpl::me->Accept(pv);
	return 0;
}