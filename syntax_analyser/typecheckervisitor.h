#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>
#include "symbolstable.h"
#include "enums.h"


struct MemStruct
{
	bool isInternal; // is internal type
	InternalType* internalType;
	CustomType* customType;

};

class TypeCheckerVisitor : public IVisitor
{
public:

	ClassTable* curclasstable;
	MethodInfo* curMethodInfo;

	InternalType* lastinternaltype;
	CustomType* lastcustomtype;


	bool staticmethod;
	MemStruct type;

	int visit(const ArithmExp* n)
	{
		MemStruct localMemRight;
		MemStruct localMemLeft;
		// left, right types are int
		if(n->left) 
		{
			n->left->Accept(this); 
			localMemLeft = type;
			type = NULL;
		}
		if(n->right) 
		{
			n->right->Accept(this); 
			localMemRight = type;
			type = NULL;
		}
		
		//if (localMemRight != localMemLeft)
		//{
			//stop!
		//}
		return 0;
	}
	int visit(const LogicExp* n)
	{
		MemStruct localMemRight;
		MemStruct localMemLeft;
		
		if(n->left) { 
			n->left->Accept(this); 
			localMemLeft = type;
			type = NULL;
		}
		if(n->right) 
		{ 
			n->right->Accept(this); 
			localMemRight = type;
			type = NULL;
		}
		return 0;
	}
	int visit(const IntVal* n)
	{
		type.isInternal = true;
		type->internalType = type::int_type;
		return 0;
	}
	int visit(const BoolVal* n)
	{
		type.isInternal = true;
		type->internalType = Type::bool_type
		return 0;
	}
	int visit(const IdExp* n)
	{
		// check if var exists (in symbable)
		// struct type = ... ???
		return 0;
	}
	int visit(const NewExp* n)
	{
		// class (id) exists
		if(getClass(n->name))
		{
			type->CustomType = getClass(n->name)
		}
		return 0;
	}
	int visit(const ThisExp* n)
	{
		// if (staticmethod ) {error}
		// type = get(curclass)
		return 0;
	}
	int visit(const LenExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		// type = int
		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		// save type1
		// check type.isinternal = false
		// check m = type.getMethod(id) or parent.getMethod(id)
		if(n->list) { n->list->Accept(this); }
		// TODO: ADD FIELD currentfunctionparams
		// if (m) : 
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		//type = Type::INT_ARR
		return 0;
	}
	int visit(const ArrValExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		//check exp type is INT_ARR
		if(n->inExp) { n->inExp->Accept(this); }
		//check inExp type is int_type
		// type.it = type::int_type
		return 0;
	}
	int visit(const BlockStm* n)
	{
		if(n->stms) { n->stms->Accept(this); }
		return 0;
	}
	int visit(const AssignStm* n)
	{
		if(n->assign) { n->assign->Accept(this); }
		return 0;
	}
	int visit(const PrintStmPrintStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		// check exp type is INT_Type
		return 0;
	}
	int visit(const WhileStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		// check exp type is type::bool_type
		if(n->stm) { n->stm->Accept(this); }
		return 0;
	}
	int visit(const IfElseStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		// check exp type is type::bool_type
		if(n->stm) { n->stm->Accept(this); }
		if(n->elseStm) { n->elseStm->Accept(this); }
		return 0;
	}
	int visit(const AssignArrStm* n)
	{
		// check in SymbolTable existence of such array
		if(n->exp) { n->exp->Accept(this); }
		// check exp type is INT_Type
		if(n->stm) { n->stm->Accept(this); } // тут правило надо каскадно менять начиная с бизоновского файла, там id[exp] = exp;(а не stm как сейчас)
		// check exp2 type is INT_Type 
		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
		// это список аргументов для вызова метода
		// их нужно сравнить хутрым методом с семинара
		if(n->exp) { n->exp->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const StatementsImpl* n)
	{
		if(n->stm) { n->stm->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const AssignmentImpl* n)
	{
		// check in SymbolTable existence of such ID 
		if(n->exp) { n->exp->Accept(this); }
		// check ID.type == exp.type
		return 0;
	}
	int visit(const ArguementImpl* n)
	{
		if(n->type) { n->type->Accept(this); }
		return 0;
	}
	int visit(const ArguementsImpl* n)
	{
		if(n->arg) { n->arg->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const InternalType* n)
	{

		return 0;
	}
	int visit(const VarDeclarationImpl* n)
	{
		if(n->type) { n->type->Accept(this); }
		return 0;
	}
	int visit(const VarDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const MethodDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const MethodDeclarationImpl* n)
	{
		if(n->type) { n->type->Accept(this); }
		if(n->args) { n->args->Accept(this); }
		if(n->vars) { n->vars->Accept(this); }
		if(n->statements) { n->statements->Accept(this); }
		if(n->exp) { n->exp->Accept(this); }
		return 0;
	}
	int visit(const ClassDeclarationsImpl* n)
	{
		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const ClassDeclarationImpl* n)
	{
		if(n->vars) { n->vars->Accept(this); }
		if(n->methods) { n->methods->Accept(this); }
		
		return 0;
	}
	int visit(const ProgramImpl* n)
	{
		if(n->cl) { n->cl->Accept(this); }
		if(n->decs) { n->decs->Accept(this); }
		return 0;
	}
	int visit(const MainClassImpl* n)
	{
		// todo write that it is static method
		// staticMethod = true;
		if(n->stm) { n->stm->Accept(this); }
		// staticmethod = flase;
		return 0;
	}
};