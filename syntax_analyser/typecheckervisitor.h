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
	InternalType internalType;
	Symbol* customType;

};

class TypeCheckerVisitor : public IVisitor
{
public:

	ClassTable* curclasstable;
	MethodInfo* curMethodInfo;

	InternalType* lastinternaltype;
	CustomType* lastcustomtype;


	bool isCurMethodStatic = false;
	Symbol* curClass;
	Symbol* curMethod;
	std::vector<VarInfo*> currentMethodParams; // есть сомнения

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
		type.internalType = type::INT;
		return 0;
	}
	int visit(const BoolVal* n)
	{
		type.isInternal = true;
		type.internalType = Type::BOOL;
		return 0;
	}
	int visit(const IdExp* n)
	{
		// check if var exists (in symbable)
		if ( (getClass(curClass))->getField(n->name))
		{
			// struct type = ((getClass(curClass))->getField(n->name))->type; // <- returns IType!!! TODO!!!
		} 
		else if ( ((getClass(curClass))->getMethod(curMethod))->getLocalVar(n->name) )
		{
			// struct type = (((getClass(curClass))->getMethod(curMethod))->getLocalVar(n->name))->type; // <- returns IType!!! TODO!!!
		}
		else
		{
			//error
		}
		
		return 0;
	}
	int visit(const NewExp* n)
	{
		if(getClass(n->name))
		{
			type.customType = (getClass(n->name))->name;
		}
		return 0;
	}
	int visit(const ThisExp* n)
	{
		if (isCurMethodStatic) 
		{
			//error!
		}
		type.CustomType = (getClass(curClass))->name;
		return 0;
	}
	int visit(const LenExp* n)
	{
		if(n->exp) 
		{	n->exp->Accept(this); 
			type.isInternal = true;
			type.internalType = Type::INT; // type = int
		}
		else 
		{
			//error?!
		}
		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		MemStruct localMem;
		if(n->exp) { n->exp->Accept(this); }
		// save type1
		if (type.isInternal == true) // check type.isinternal = false
		{
			//error
		}// так?
		
		// check m = type.getMethod(id) or parent.getMethod(id)
		if(n->list) { n->list->Accept(this); }
		// TODO: ADD FIELD currentfunctionparams // добавил, но нафига, если в методе уже хранятся параметры?!
		// if (m) : // что сделать-то?
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		if(n->exp) 
		{ 
			n->exp->Accept(this); 
			type.isInternal = true;
			type.internalType = Type::INT; //type = Type::INT_ARR
		}
		else
		{
			//error?!
		}
		return 0;
	}
	int visit(const ArrValExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		
		if (type.internalType != Type::INT) //check exp type is INT_ARR
		{
			//error
		}

		if(n->inExp) { n->inExp->Accept(this); }
		if (n->inExp->type != Type::INT) //check inExp type is int_type
		{
			//error
		}
		type.internalType = Type::INT; // type.it = type::int_type
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

		if(n->exp->type != Type::INT) // check exp type is INT_Type
		{
			//error
		}
		return 0;
	}
	int visit(const WhileStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->exp->type != Type::BOOL) // check exp type is type::bool_type
		{
			//error
		}
		if(n->stm) { n->stm->Accept(this); }
		return 0;
	}
	int visit(const IfElseStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(n->exp->type != Type::BOOL) // check exp type is type::bool_type
		{
			//error
		}
		if(n->stm) { n->stm->Accept(this); }
		if(n->elseStm) { n->elseStm->Accept(this); }
		return 0;
	}
	int visit(const AssignArrStm* n)
	{
		// check in SymbolTable existence of such array serge^ how?
		if(n->exp) { n->exp->Accept(this); }
		if(n->exp->type != Type::INT) // check exp type is INT_Type
		{
			//error
		}
		if(n->stm) { n->stm->Accept(this); } // !!! тут правило надо каскадно менять начиная с бизоновского файла, там id[exp] = exp;(а не stm как сейчас)
		if(n->exp->type != Type::INT) // check exp type is INT_Type
		{
			//error
		}
		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
		// это список аргументов для вызова метода
		// их нужно сравнить хутрым методом с семинара. // dont remember the method
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
		if (ID.type != exp.type) //dont understand, where is ID
		{
			//error
		}
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
		isCurMethodStatic = true;
		if(n->stm) { n->stm->Accept(this); }
		isCurMethodStatic = false;
		return 0;
	}
};