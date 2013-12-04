#pragma once

#include "enums.h"
#include "fwdclasses.h"

class IVisitor
{
public:
	virtual int visit(const ArithmExp* n) = 0;
	virtual int visit(const LogicExp* n) = 0;
	virtual int visit(const IntVal* n) = 0;
	virtual int visit(const BoolVal* n) = 0;
	virtual int visit(const IdExp* n) = 0;
	virtual int visit(const NewExp* n) = 0;
	virtual int visit(const ThisExp* n) = 0;
	virtual int visit(const LenExp* n) = 0;
	virtual int visit(const CallMethodExp* n) = 0;
	virtual int visit(const NewIntArrExp* n) = 0;
	virtual int visit(const ArrValExp* n) = 0;
	virtual int visit(const BlockStm* n) = 0;
	virtual int visit(const AssignStm* n) = 0;
	virtual int visit(const PrintStmPrintStm* n) = 0;
	virtual int visit(const WhileStm* n) = 0;
	virtual int visit(const IfElseStm* n) = 0;
	virtual int visit(const AssignArrStm* n) = 0;
	virtual int visit(const ExpressionListImpl* n) = 0;
	virtual int visit(const StatementsImpl* n) = 0;
	virtual int visit(const AssignmentImpl* n) = 0;
	virtual int visit(const ArguementImpl* n) = 0;
	virtual int visit(const ArguementsImpl* n) = 0;
	virtual int visit(const InternalType* n) = 0;
	virtual int visit(const CustomType * n) = 0;
	virtual int visit(const VarDeclarationImpl* n) = 0;
	virtual int visit(const VarDeclarationsImpl* n) = 0;
	virtual int visit(const MethodDeclarationsImpl* n) = 0;
	virtual int visit(const MethodDeclarationImpl* n) = 0;
	virtual int visit(const ClassDeclarationsImpl* n) = 0;
	virtual int visit(const ClassDeclarationImpl* n) = 0;
	virtual int visit(const ProgramImpl* n) = 0;
	virtual int visit(const MainClassImpl* n) = 0;
};