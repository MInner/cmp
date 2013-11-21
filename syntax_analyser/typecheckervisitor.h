#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>
#include "symbolstable.h"
#include "enums.h"

void err()
{
	std::cout << "Noname Error ;(" << std::endl;
}

inline bool operator==(const TypeData& l, const TypeData& r)
{
	if (l.isInternal != r.isInternal)
		return false;

	if (l.isInternal)
		return l.internalType == r.internalType;
	else
		return l.customType == r.customType;

	return false;

}

class TypeCheckerVisitor : public IVisitor
{
public:

	TypeData type;
	static const TypeData NULLTYPE;

	ClassTable* ct;
	ClassInfo* curclass;
	MethodInfo* curmethod;

	bool isCurMethodStatic;

//	std::vector<VarInfo*> currentMethodParams;

	TypeCheckerVisitor(ClassTable* ct_)
	{
		ct = ct_;
	}

	int visit(const ArithmExp* n)
	{
		if(n->left) 
		{
			n->left->Accept(this); 

			if (!type.isInternal || type.internalType != Type::INT )
				std::cout << "ArExp: not ints" << std::endl; 

			type = NULLTYPE;
		}
		if(n->right) 
		{
			n->right->Accept(this);

			if (!type.isInternal || type.internalType != Type::INT )
				std::cout << "ArExp: not ints" << std::endl; 

			type = NULLTYPE;
		}

		type.isInternal = true;
		type.internalType = Type::INT;
		
		return 0;
	}

	int visit(const LogicExp* n)
	{
		TypeData localMemRight;
		TypeData localMemLeft;
		
		if(n->left) { 
			n->left->Accept(this); 

			if (!type.isInternal || type.internalType != Type::BOOL )
				std::cout << "WARNING: Logic Operation not bools" << std::endl; 

			type = NULLTYPE;
		}
		if(n->right) 
		{ 
			n->right->Accept(this); 

			if (!type.isInternal || type.internalType != Type::BOOL )
				std::cout << "WARNING: Logic Operation not bools"  << std::endl; 

			type = NULLTYPE;
		}

		type.isInternal = true;
		type.internalType = Type::BOOL;

		return 0;
	}
	int visit(const IntVal* n)
	{
		type.isInternal = true;
		type.internalType = Type::INT;
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
		VarInfo* var;

		if ( var = curmethod->getLocalVar(n->id) )
			type = var->type;
		else if ( var = curmethod->getParam(n->id) )
			type = var->type;
		else if ( var = curclass->getField(n->id))
			type = var->type;
		else
			err();
		
		return 0;
	}

	int visit(const NewExp* n)
	{
		type.isInternal = false;
		type.customType = n->id;
		return 0;
	}

	int visit(const ThisExp* n)
	{
		if (isCurMethodStatic) 
		{
			std::cout << "WARNING!!: THIS in static method" << std::endl;
		}
		type.customType = curclass->name;
		return 0;
	}

	int visit(const LenExp* n)
	{
		if(n->exp) 
		{	n->exp->Accept(this); 
			type.isInternal = true;
			type.internalType = Type::INT;
		}

		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if (type.isInternal == true) 
		{
			std::cout << "WARNING: Trying to call method of internal method" << std::endl;
		}

		ClassInfo* ci = ct->getClass(type.customType);
		
		MethodInfo* mi = ci->getMethod(n->id);

		if (!mi)
			std::cout << "WARNING: No such method at class" << std::endl;

		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		if(n->exp) 
		{ 
			n->exp->Accept(this); 
			type.isInternal = true;
			type.internalType = Type::INT_ARR; //type = Type::INT_ARR
		}
		return 0;
	}
	int visit(const ArrValExp* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		
		if (type.internalType != Type::INT_ARR) //check exp type is INT_ARR
			std::cout << "WARNING: Trying [] of not ARRAY type" << std::endl;

		if(n->idExp) { n->idExp->Accept(this); }

		if (type.internalType != Type::INT)
			std::cout << "WARNING: Inside [] must be INT" << std::endl;
		
		type.isInternal = true;
		type.internalType = Type::INT;
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

		if(type.internalType != Type::INT) // check exp type is INT_Type
			std::cout << "Can print only INTs" << std::endl;
		return 0;
	}

	int visit(const WhileStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::BOOL)
			std::cout << "Not Bool in WHILE" << std::endl;

		if(n->stm) { n->stm->Accept(this); }
		return 0;
	}
	int visit(const IfElseStm* n)
	{
		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::BOOL) // check exp type is type::bool_type
		{
			std::cout << "Not Bool in IF" << std::endl;
		}
		if(n->stm) { n->stm->Accept(this); }
		if(n->elseStm) { n->elseStm->Accept(this); }
		return 0;
	}
	int visit(const AssignArrStm* n)
	{
		// check in SymbolTable existence of such array serge^ how?
		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::INT) // check exp type is INT_Type
		{
			err();
		}
		if(n->newexp) { n->newexp->Accept(this); }
		if(type.internalType != Type::INT) 
			err();

		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
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
		
		VarInfo* var;
		TypeData lefttype;

		if ( var = curmethod->getLocalVar(n->id) )
			lefttype = var->type;
		else if ( var = curmethod->getParam(n->id) )
			lefttype = var->type;
		else if ( var = curclass->getField(n->id))
			lefttype = var->type;
		else
			err();

		
		if(n->exp) { n->exp->Accept(this); }

		if ( !( lefttype == type ) )
			err();

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
	
	int visit(const CustomType* n)
	{
		type.isInternal = false;
		type.customType = n->type;
		
		return 0;
	}

	int visit(const InternalType* n)
	{
		type.isInternal = true;
		type.internalType = n->type;

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
		curmethod = curclass->getMethod(n->id);

		// TODO returnvalcheck !
		if(n->type) { n->type->Accept(this); }
		// here we Call InternalType or CustomType depending on VirtualFunctionTable, so we can look into type
		if(n->args) { n->args->Accept(this); }
		if(n->vars) { n->vars->Accept(this); }
		if(n->statements) { n->statements->Accept(this); }
		if(n->exp) { n->exp->Accept(this); }

		curmethod = NULL;

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
		curclass = ct->getClass(n->id);

		if(n->vars) { n->vars->Accept(this); }
		if(n->methods) { n->methods->Accept(this); }

		curclass = NULL;
		
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
		isCurMethodStatic = true;
		if(n->stm) { n->stm->Accept(this); }
		isCurMethodStatic = false;
		return 0;
	}
};