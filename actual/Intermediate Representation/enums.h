//other constants:
/*
BINOP.PLUS, BINOP.MINUS, BINOP.MUL, BINOP.DIV, BINOP.AND,
BINOP.OR, BINOP.LSHIFT, BINOP.RSHIFT, BINOP.ARSHIFT, BINOP.XOR;
CJUMP.EQ, CJUMP.NE, CJUMP.LT, CJUMP.GT, CJUMP.LE,
CJUMP.GE, CJUMP.ULT, CJUMP.ULE, CJUMP.UGT, CJUMP.UGE;
*/
enum BINOP { // Бэн это же инты получаются?? но их можно на равенство проверять, по крайней мере в кллассах я так считаю))
	PLUS,
	MINUS, 
	MUL,
	DIV,
	AND,
	OR, 
	LSHIFT,
	RSHIFT,
	ARSHIFT,
	XOR
};

enum CJUMP { // и это тоже
    EQ,
    NE, 
    LT, 
    GT, 
    LE,
    GE, 
    ULT, 
    ULE, 
    UGT, 
    UGE
};
