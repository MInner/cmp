#pragma once

#include <assert.h>
#include "temp.h"
#include "treeClasses.h"

namespace Wrapper {

class IRTreeWrapper 
{
public://vitrual and destructor
    virtual ~IRTreeWrapper() {};
    
    virtual const IRTree::IExp* ToExp() const = 0;
    virtual const IRTree::IStm* ToStm() const = 0;
    virtual const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const =0;     
};

class ExpWrapper : public IRTreeWrapper {
public:
    ExpWrapper(const IRTree::IExp* exp_) :
        exp(exp_) {}
    
    const IRTree::IExp* ToExp() const {return exp;}
    const IRTree::IStm* ToStm() const {return new IRTree::EXP(exp); }
    const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const {
        return new IRTree::CJUMP(IRTree::OPERATOR::EQ, exp, new IRTree::CONST(0), f, t);
    }
    
    const IRTree::IExp* exp;
};

class StmWrapper : public IRTreeWrapper {
public:
    StmWrapper(const IRTree::IStm* stm_) :
        stm(stm_) {}    
    
    const IRTree::IExp* ToExp() const { assert(false); } // no sense but in c++ / a = (b = 3) - stm(exp)
    const IRTree::IStm* ToStm() const {return stm;}
    const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const
        {assert(false);} // no sense
    
    const IRTree::IStm* stm;
};

class ConditionalWrapper : public IRTreeWrapper {
public:
    ConditionalWrapper() {}
    
    const IRTree::IExp* ToExp() const
    {
        const Temp::Temp* r = new Temp::Temp();
        const Temp::Label* t = new Temp::Label();
        const Temp::Label* f = new Temp::Label();

        return new IRTree::ESEQ(
                new IRTree::SEQ(new IRTree::MOVE(new IRTree::TEMP(r), new IRTree::CONST(1)),
                                new IRTree::SEQ(ToConditional(t,f), 
                                                new IRTree::SEQ(new IRTree::LABEL(f), 
    															new IRTree::SEQ(new IRTree::MOVE(new IRTree::TEMP(r), new IRTree::CONST(0)), 
    																			new IRTree::LABEL(t)
    																			)
    															)
    											)
    							),
    			new IRTree::TEMP(r)
    			);
    }
	
    const IRTree::IStm* ToStm() const { 
        //ToConditional(t,f); 
    }
	
    virtual const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const = 0; 
    
    const IRTree::IStm* stm;
};

class AndConditionWrapper : public ConditionalWrapper {
public:
    AndConditionWrapper(const IRTree::IExp* left_, const IRTree::IExp* right_):
		left(left_), right(right_) {}
    
    const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const { 
		Temp::Label* z = new Temp::Label();
		return new IRTree::SEQ(new IRTree::CJUMP(IRTree::OPERATOR::EQ, left, new IRTree::CONST(0), f, z),
							   new IRTree::SEQ(new IRTree::LABEL(z),
											   new IRTree::CJUMP(IRTree::OPERATOR::EQ, right, new IRTree::CONST(0), f, t)
											   )
							   );
	}
    
    const IRTree::IExp* left;
	const IRTree::IExp* right;
};

class OrConditionWrapper : public ConditionalWrapper {
public:
    OrConditionWrapper(const IRTree::IExp* left_, const IRTree::IExp* right_):
		left(left_), right(right_) {}
    
    const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const { 
		Temp::Label* z = new Temp::Label();
		return new IRTree::SEQ(new IRTree::CJUMP(IRTree::OPERATOR::EQ, left, new IRTree::CONST(0), z, t),
							   new IRTree::SEQ(new IRTree::LABEL(z),
											   new IRTree::CJUMP(IRTree::OPERATOR::EQ, right, new IRTree::CONST(0), f, t)
											   )
							   );
							
	}
    
    const IRTree::IExp* left;
	const IRTree::IExp* right;
};

class RelativeConditionWrapper : public ConditionalWrapper {
public:
    RelativeConditionWrapper(int op_, const IRTree::IExp* left_, const IRTree::IExp* right_):
		op(op_), left(left_), right(right_) {}
    
    const IRTree::IStm* ToConditional(const Temp::Label* t, const Temp::Label* f) const
    { 
		Temp::Label* z = new Temp::Label();
		return new IRTree::CJUMP(op, left, right, t, f);							
	}
    
    int op;
    const IRTree::IExp* left;
	const IRTree::IExp* right;
};

/*class Translator{

    void Visit(const AssingStm* assign)
    {
        // доп записи на доске
        // move - leftVal
        //     |- rightVal
        // id=exp; -> IAccess / exp

        assign->Accept(this);
        const IRTree::IIExp* rightValue = lastReturnValue->ToExp();
        const IRTree::IIExp* rightValue = 0;
        if (locals.Has(Id))
        { //локальная переменная
            leftValue = locals[id]->ToExp();
        }
        else
        { //переменная класса
            //currentClass.Lookup(id, ...)
            // ...
        }
    }
};*/


}
