#pragma once

#include <assert.h>


namespace Translate{

class IRTreeNodeConverter 
{
public://vitrual and destructor
    virtual ~IRTreeNodeConverter() {};
    
    virtual const IRTree::Exp* ToExp() const = 0;
    virtual const IRTree::Stm* ToStm() const = 0;
    virtual const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const =0;     
};

class ExpWrapper : public IRTreeNodeConverter {
public:
    ExpWrapper(const IRTree::Exp* exp_) :
        exp(exp_) {}
    
    const IRTree::Exp* ToExp() {return exp;}
    const IRTree.Stm* ToStm() {return new IRTree::EXP(exp);}
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) {
        return new IRTree::CJUMP(IRTree::EQ, exp, IRTree::CONST(0), f, t);
    }
    
    const IRTree::Exp* exp;
};

class StmWrapper : public IRTreeNodeConverter {
public:
    StmWrapper(const IRTree::Stm* stm_) :
        stm(stm_) {}    
    
    const IRTree.Exp* ToExp() { assert(false); } // no sense but in c++ / a = (b = 3) - stm(exp)
    const Stm* ToStm() {return stm;}
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) {assert(false)} // no sense
    
    const IRTree::Stm* stm;
};

class ConditionalWrapper : public IRTreeNodeConverter {
public:
    ConditionalWrapper(const Temp::Label* t, const Temp::Label* f) {}
    
    const IRTree.Exp* ToExp() {
    Temp::Temp r;
    Temp::Label t;
    Temp::Label f;
    
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
	
    const Stm* ToStm() { ToConditional(t,f); }
	
    virtual const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const =0; 
    
    const Stm* stm;
};

class AndConditionWrapper : public ConditionalWrapper {
public:
    AndConditionWrapper(const IRTree::Exp* left_, const IRTree::Exp* right_):
		left(left_), right(right_) {}
    
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f){ 
		Temp::Label* z = new Temp::Label();
		return new IRTree::SEQ(new IRTree::CJUMP(IRTree::EQ, left, IRTree::CONST(0), f, z),
							   new IRTree::SEQ(new IRTree::LABEL(z),
											   new IRTree::CJUMP(IRTree::EQ, right, IRTree::CONST(0), f, t)
											   )
							   )
	}
    
    const IRTree::Exp* left;
	const IRTree::Exp* right;
};

class OrConditionWrapper : public ConditionalWrapper {
public:
    OrConditionWrapper(const IRTree::Exp* left_, const IRTree::Exp* right_):
		left(left_), right(right_) {}
    
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f){ 
		Temp::Label* z = new Temp::Label();
		return new IRTree::SEQ(new IRTree::CJUMP(IRTree::EQ, left, IRTree::CONST(0), z, t),
							   new IRTree::SEQ(new IRTree::LABEL(z),
											   new IRTree::CJUMP(IRTree::EQ, right, IRTree::CONST(0), f, t)
											   )
							   )
							
	}
    
    const IRTree::Exp* left;
	const IRTree::Exp* right;
};

class RelativeConditionWrapper : public ConditionalWrapper {
public:
    RelativeConditionWrapper(int op_, const IRTree::Exp* left_, const IRTree::Exp* right_):
		op(op_), left(left_), right(right_) {}
    
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f){ 
		Temp::Label* z = new Temp::Label();
		return new CJUMP(op, left, right, t, f);							
	}
    
    const IRTree::Exp* left;
	const IRTree::Exp* right;
};

class Translator{

    void Visit(const AssingStm* assign)
    {
        // доп записи на доске
        // move - leftVal
        //     |- rightVal
        // id=exp; -> IAccess / exp

        assign->Accept(this);
        const IRTree::IExp* rightValue = lastReturnValue->ToExp();
        const IRTree::IExp* rightValue = 0;
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
};


}
