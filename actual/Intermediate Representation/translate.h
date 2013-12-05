namespace Translate{

class Exp 
{
public:
    const IRTree::Exp* ToExp() const = 0;
    const IRTree::Stm* ToStm() const = 0;
    const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const =0;     
}

class IExp : public Exp {
public:
    IExp(const Exp* e) {exp=e;}
    
    const IRTree.Exp* ToExp() {return exp;}
    const IRTree.Stm* ToStm() {return new IRTree.EXP(exp);}
    //const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) { ... ?... }
    
    const Exp* exp;
}
class IStm :public Exp {
public:
    IStm(const Stm* s) {stm=s;}
    
    //IRTree.Exp ToExp() { ... ?... }
    const Stm* ToStm() {return stm;}
    // IRTree.Stm ToConditional(Label t, Label f) { ... ?... }
    
    const Stm* stm;
}

class ICond :public Exp {
public:
    const IRTree.Exp* ToExp() {
    Temp::Temp r;
    Temp::Label t;
    Temp::Label f;
    
    return new IRTree.ESEQ(
        new IRTree.SEQ(new IRTree.MOVE(new IRTree.TEMP(r),
        new IRTree.CONST(1)),
        new IRTree.SEQ(ToConditional(t,f),
        new IRTree.SEQ(new IRTree.LABEL(f),
        new IRTree.SEQ(new IRTree.MOVE(new IRTree.TEMP(r),
        new IRTree.CONST(0)),
        new IRTree.LABEL(t))))),
        new IRTree.TEMP(r)
    );
    }
    const Stm* ToStm() { ... }
    abstract IRTree.Stm ToConditional(Label t, Label f);
}






class ISunIRTreeWrapper {
public:
	const IRTree::Exp* ToExp() const = 0; // как Expr
	const IRTree::Stm* ToStm() const = 0; // как Stm
	const IRTree::Stm* ToConditional(const Temp::Label* t, const Temp::Label* f) const = 0; // как if/jump
}

}
