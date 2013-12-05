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
}

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
}

class StmWrapper : public IRTreeNodeConverter {
public:
    StmWrapper(const IRTree::Stm* stm_) :
        stm(stm_) {}    
    
    const IRTree.Exp* ToExp() { assert(false); } // no sense
    const Stm* ToStm() {return stm;}
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) {assert(false)} // no sense
    
    const IRTree::Stm* stm;
}

class ConditionalWrapper : public IRTreeNodeConverter {
public:
    ConditionalWrapper(const Temp::Label* t, const Temp::Label* f) {
        //stm = CJUMP(,,,t,f);
    }
    
    const IRTree.Exp* ToExp() {
    Temp::Temp r;
    Temp::Label t;
    Temp::Label f;
    
    return new IRTree::ESEQ(
            new IRTree::SEQ(new IRTree::MOVE(new IRTree::TEMP(r), new IRTree::CONST(1)),
                            new IRTree::SEQ(ToConditional(t,f), 
                                            new IRTree::SEQ(new IRTree::LABEL(f), 
                                                        new IRTree::SEQ(new IRTree::MOVE(new IRTree::TEMP(r), new IRTree::CONST(0)), 
                                                                    new IRTree::LABEL(t))))),
        new IRTree::TEMP(r)
    );
    }
    const Stm* ToStm() { ... }
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f){ return stm;}
    
    const Stm* stm;
}






class ISunIRTreeWrapper {
public:
	const IRTree::Exp* ToExp() const = 0; // как Expr
	const IRTree::Stm* ToStm() const = 0; // как Stm
	const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const = 0; // как if/jump
}

}
