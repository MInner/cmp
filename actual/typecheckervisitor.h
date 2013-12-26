#pragma once

#include "visitor.h"
#include "fwdclasses.h"
#include <iostream>
#include <string>
#include "symbolstable.h"
#include "enums.h"

void err(int a)
{
	std::cout << "Noname Error code " << a << std::endl;
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

	static int line;
//	std::vector<VarInfo*> currentMethodParams;

	TypeCheckerVisitor(ClassTable* ct_)
	{
		ct = ct_;
	}

	static const Symbol* getExpressionType(
		ClassTable* classTable,
		ClassInfo* currentClass,
		MethodInfo* currentMethod,
		const IExpression* expression )
	{
		TypeCheckerVisitor tempVisitor( classTable );
		tempVisitor.curclass = currentClass;
		tempVisitor.curmethod = currentMethod;
		tempVisitor.isCurMethodStatic = (currentMethod->name->getStr() == "main");
		expression->Accept( &tempVisitor );
		return tempVisitor.type.customType;
	}

	int visit(const ArithmExp* n)
	{
		TypeCheckerVisitor::line = n->line;
		if(n->left)
		{
			n->left->Accept(this);

			if (!type.isInternal || type.internalType != Type::INT )
				std::cout << "WARNING: line " << n->line <<" ArythmeticExp: LEFT is not of type INT " << std::endl;

			type = NULLTYPE;
		}
		if(n->right)
		{
			n->right->Accept(this);

			if (!type.isInternal || type.internalType != Type::INT )
				std::cout << "WARNING: line " << n->line <<" ArythmeticExp: RIGHT is not of type INT" << std::endl;

			type = NULLTYPE;
		}

		type.isInternal = true;
		type.internalType = Type::INT;

		return 0;
	}

	int visit(const LogicExp* n)
	{
		TypeCheckerVisitor::line = n->line;

		if (n->op == Logic::L_LT)
		{
			if(n->left) {
				n->left->Accept(this);

				if (!type.isInternal || type.internalType != Type::INT )
					std::cout << "WARNING: line " << n->line <<" Logic Operation < : LEFT is not INT" << std::endl;

				type = NULLTYPE;
			}
			if(n->right)
			{
				n->right->Accept(this);

				if (!type.isInternal || type.internalType != Type::INT )
					std::cout << "WARNING: line " << n->line <<" Logic Operation <: RIGHT is not INT"  << std::endl;

				type = NULLTYPE;
			}
		}
		else
		{
			if(n->left) {
				n->left->Accept(this);

				if (!type.isInternal || type.internalType != Type::BOOL )
					std::cout << "WARNING: line " << n->line <<" Logic Operation: LEFT is not bools" << std::endl;

				type = NULLTYPE;
			}
			if(n->right)
			{
				n->right->Accept(this);

				if (!type.isInternal || type.internalType != Type::BOOL )
					std::cout << "WARNING: line " << n->line <<" Logic Operation: RIGHT is not bools"  << std::endl;

				type = NULLTYPE;
			}
		}


		type.isInternal = true;
		type.internalType = Type::BOOL;

		return 0;
	}
	int visit(const IntVal* n)
	{
		TypeCheckerVisitor::line = n->line;

		type.isInternal = true;
		type.internalType = Type::INT;
		return 0;
	}

	int visit(const BoolVal* n)
	{
		TypeCheckerVisitor::line = n->line;

		type.isInternal = true;
		type.internalType = Type::BOOL;
		return 0;
	}

	int visit(const IdExp* n)
	{
		TypeCheckerVisitor::line = n->line;

		VarInfo* var;

		if ( var = curmethod->getLocalVar(n->id) )
			type = var->type;
		else if ( var = curmethod->getParam(n->id) )
			type = var->type;
		else if ( var = curclass->getField(n->id))
			type = var->type;
		else
		{
			const Symbol* s = n->id;
			std::cout << "WARNING: line " << n->line <<" variable " << s << " not found in this scope :(" << std::endl;
		}
		return 0;
	}

	int visit(const NewExp* n)
	{
		TypeCheckerVisitor::line = n->line;

		type.isInternal = false;
		type.customType = n->id;
		return 0;
	}

	int visit(const ThisExp* n)
	{
		TypeCheckerVisitor::line = n->line;

		if (isCurMethodStatic)
		{
			std::cout << "WARNING: line " << n->line <<" THIS in static method" << std::endl;
		}

		type.isInternal = false;
		type.customType = curclass->name;
		return 0;
	}

	int visit(const LenExp* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->exp)
		{	n->exp->Accept(this);
			type.isInternal = true;
			type.internalType = Type::INT;
		}

		return 0;
	}
	int visit(const CallMethodExp* n)
	{
		type = NULLTYPE;
		if (n->exp) { n->exp->Accept(this); }

		if (type.isInternal == true)
		{
			std::cout << "WARNING: line " << n->line <<" Trying to call method of _internal_ (int / bool) type var" << std::endl;
		}

		ClassInfo* ci = ct->getClass(type.customType);

		MethodInfo* mi = ci->getMethod(n->id);

		if (!mi)
			std::cout << "WARNING: line " << n->line <<" No such method at class" << std::endl;

		if(n->list) { n->list->Accept(this); }

		type = mi->returnType;
		return 0;
	}
	int visit(const NewIntArrExp* n)
	{
		TypeCheckerVisitor::line = n->line;

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
		TypeCheckerVisitor::line = n->line;
		
		if(n->exp) { n->exp->Accept(this); }

		if (type.internalType != Type::INT_ARR) //check exp type is INT_ARR
			std::cout << "WARNING: line " << n->line <<" Trying [] of not ARRAY type" << std::endl;

		if(n->idExp) { n->idExp->Accept(this); }

		if (type.internalType != Type::INT)
			std::cout << "WARNING: line " << n->line <<" index of ARR[..] must be INT" << std::endl;

		type.isInternal = true;
		type.internalType = Type::INT;
		return 0;
	}
	int visit(const BlockStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->stms) { n->stms->Accept(this); }
		return 0;
	}
	int visit(const AssignStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->assign) { n->assign->Accept(this); }
		return 0;
	}
	int visit(const PrintStmPrintStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->exp) { n->exp->Accept(this); }

		if(type.internalType != Type::INT) // check exp type is INT_Type
			std::cout << "Line " << n->line <<"Can print only INTs" << std::endl;
		return 0;
	}

	int visit(const WhileStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::BOOL)
			std::cout << "Line " << n->line << "Not Bool in WHILE" << std::endl;

		if(n->stm) { n->stm->Accept(this); }
		return 0;
	}
	int visit(const IfElseStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::BOOL) // check exp type is type::bool_type
		{
			std::cout << "WARNING: line " << n->line <<" Not bool val in IF" << std::endl;
		}
		if(n->stm) { n->stm->Accept(this); }
		if(n->elseStm) { n->elseStm->Accept(this); }
		return 0;
	}
	int visit(const AssignArrStm* n)
	{
		TypeCheckerVisitor::line = n->line;

		// check in SymbolTable existence of such array serge^ how?
		if(n->exp) { n->exp->Accept(this); }
		if(type.internalType != Type::INT) // check exp type is INT_Type
		{
			std::cout << "WARNING: line " << n->line <<" array id is not of type INT" << std::endl;
		}
		if(n->newexp) { n->newexp->Accept(this); }
		if(type.internalType != Type::INT)
			std::cout << "WARNING: line " << n->line <<" new value of an array element is not of type INT" << std::endl;

		return 0;
	}
	int visit(const ExpressionListImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->exp) { n->exp->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const StatementsImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->stm) { n->stm->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}
	int visit(const AssignmentImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		VarInfo* var;
		TypeData lefttype;

		if ( var = curmethod->getLocalVar(n->id) )
			lefttype = var->type;
		else if ( var = curmethod->getParam(n->id) )
			lefttype = var->type;
		else if ( var = curclass->getField(n->id))
			lefttype = var->type;
		else
		{
			const Symbol* s = n->id;
			std::cout << "WARNING: line " << n->line <<" assigment to the variable '" << s << "' before declaration" << std::endl;
		}

		if(n->exp) { n->exp->Accept(this); }

		if ( !( lefttype == type ) )
		{
			const Symbol* s = n->id;
			std::cout << "WARNING: line " << n->line <<" type mismatch when assigning to '" << s << "'" << std::endl;
		}
		return 0;
	}

	int visit(const ArguementImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->type) { n->type->Accept(this); }
		return 0;
	}

	int visit(const ArguementsImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->arg) { n->arg->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}

	int visit(const CustomType* n)
	{
		TypeCheckerVisitor::line = n->line;

		type.isInternal = false;
		type.customType = n->type;

		return 0;
	}

	int visit(const InternalType* n)
	{
		TypeCheckerVisitor::line = n->line;

		type.isInternal = true;
		type.internalType = n->type;

		return 0;
	}

	int visit(const VarDeclarationImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->type) { n->type->Accept(this); }
		return 0;
	}

	int visit(const VarDeclarationsImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}

	int visit(const MethodDeclarationsImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}

	int visit(const MethodDeclarationImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		curmethod = curclass->getMethod(n->id);

		// TODO returnvalcheck !
		if(n->type) { n->type->Accept(this); }
		// here we Call InternalType or CustomType depending on VirtualFunctionTable, so we can look into type
		if(n->args) { n->args->Accept(this); }
		if(n->vars) { n->vars->Accept(this); }
		if(n->statements) { n->statements->Accept(this); }
		if(n->exp) { n->exp->Accept(this); }

		if ( !(type == curmethod->returnType) )
		{
			std::cout << "WARNING: line " << n->line <<" Return type of method " << curmethod->name << " is wrong" << std::endl;
		}
		curmethod = NULL;

		return 0;
	}

	int visit(const ClassDeclarationsImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->dec) { n->dec->Accept(this); }
		if(n->list) { n->list->Accept(this); }
		return 0;
	}

	int visit(const ClassDeclarationImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		curclass = ct->getClass(n->id);

		if(n->vars) { n->vars->Accept(this); }
		if(n->methods) { n->methods->Accept(this); }

		curclass = NULL;

		return 0;
	}

	int visit(const ProgramImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		if(n->cl) { n->cl->Accept(this); }
		if(n->decs) { n->decs->Accept(this); }
		return 0;
	}
	int visit(const MainClassImpl* n)
	{
		TypeCheckerVisitor::line = n->line;

		curclass = ct->getClass(n->id);
		curmethod = curclass->getMethod(Symbol::getSymbol("main"));

		isCurMethodStatic = true;
		if(n->stm) { n->stm->Accept(this); }
		isCurMethodStatic = false;

		curmethod = NULL;
		curclass = NULL;

		return 0;
	}
};
