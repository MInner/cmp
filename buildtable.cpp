#include <iostream>
#include <string>

#include "buildtable.h"

BuildTableVisitor::BuildTableVisitor()
{
	curclasstable = new ClassTable();
}

int BuildTableVisitor::visit(const ArithmExp* n)
{
	if(n->left) { n->left->Accept(this); }
	if(n->right) { n->right->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const LogicExp* n)
{
	if(n->left) { n->left->Accept(this); }
	if(n->right) { n->right->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const IntVal* n)
{

	return 0;
}
int BuildTableVisitor::visit(const BoolVal* n)
{

	return 0;
}
int BuildTableVisitor::visit(const IdExp* n)
{

	return 0;
}
int BuildTableVisitor::visit(const NewExp* n)
{

	return 0;
}
int BuildTableVisitor::visit(const ThisExp* n)
{

	return 0;
}
int BuildTableVisitor::visit(const LenExp* n)
{
	if(n->exp) { n->exp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const CallMethodExp* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const NewIntArrExp* n)
{
	if(n->exp) { n->exp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const ArrValExp* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->idExp) { n->idExp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const BlockStm* n)
{
	if(n->stms) { n->stms->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const AssignStm* n)
{
	if(n->assign) { n->assign->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const PrintStmPrintStm* n)
{
	if(n->exp) { n->exp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const WhileStm* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->stm) { n->stm->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const IfElseStm* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->stm) { n->stm->Accept(this); }
	if(n->elseStm) { n->elseStm->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const AssignArrStm* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->newexp) { n->newexp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const ExpressionListImpl* n)
{
	if(n->exp) { n->exp->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const StatementsImpl* n)
{
	if(n->stm) { n->stm->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const AssignmentImpl* n)
{
	if(n->exp) { n->exp->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const ArguementImpl* n)
{
	t = NULLTYPE;

	if(n->type) { n->type->Accept(this); }

	curmethod->addParam(n->id, t);

	return 0;
}
int BuildTableVisitor::visit(const ArguementsImpl* n)
{
	if(n->arg) { n->arg->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}

int BuildTableVisitor::visit(const InternalType* n)
{
	t.isInternal = true;
	t.internalType = n->type; // is of enum Type::Type
	return 0;
}
int BuildTableVisitor::visit(const CustomType* n)
{
	t.isInternal = false;
	t.customType = n->type; // is of Symbol*
	return 0;
}
int BuildTableVisitor::visit(const VarDeclarationImpl* n)
{
	t = NULLTYPE;

	if(n->type) { n->type->Accept(this); }

	if (curmethod)
		curmethod->addLocalVar(n->id, t);
	else
		curclass->addField(n->id, t);

	return 0;
}
int BuildTableVisitor::visit(const VarDeclarationsImpl* n)
{
	if(n->dec) { n->dec->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const MethodDeclarationsImpl* n)
{
	if(n->dec) { n->dec->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const MethodDeclarationImpl* n)
{
	t = NULLTYPE;

	if(n->type) { n->type->Accept(this); }

	curmethod = curclass->addMethod(n->id, t);

	if(n->args) { n->args->Accept(this); }
	if(n->vars) { n->vars->Accept(this); }
	if(n->statements) { n->statements->Accept(this); }
	if(n->exp) { n->exp->Accept(this); }

	curmethod = NULL;
	return 0;
}
int BuildTableVisitor::visit(const ClassDeclarationsImpl* n)
{
	if(n->dec) { n->dec->Accept(this); }
	if(n->list) { n->list->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const ClassDeclarationImpl* n)
{
	curclass = curclasstable->addClass(n->id, n->extId);

	if(n->vars) { n->vars->Accept(this); }
	if(n->methods) { n->methods->Accept(this); }

	curclass = NULL;
	return 0;
}
int BuildTableVisitor::visit(const ProgramImpl* n)
{
	if(n->cl) { n->cl->Accept(this); }
	if(n->decs) { n->decs->Accept(this); }
	return 0;
}
int BuildTableVisitor::visit(const MainClassImpl* n)
{
    curclass = curclasstable->addClass(n->id, NULL);

    t = NULLTYPE;
    curmethod = curclass->addMethod(Symbol::getSymbol("main"), t);

	if(n->stm) { n->stm->Accept(this); }

	curmethod = NULL;
	curclass = NULL;
	return 0;
}

