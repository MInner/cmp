namespace Translate
{
	class Expression{
	public: 
		const Tree::Expression* ToExpression() const = 0;
		const Tree::Expression* ToStatement() const = 0;
		const Tree::Expression* ToConditional() const = 0;

		
	};
	class Statement{
	public:
		Move()
	};
}


namespace Tree
{
	class Expression
	{
	public:
		Expression();
		~Expression() = 0 ;
	
		class CONST{
		public:
			CONST(int value);
		};
		class NAME{
			public:
				NAME(Label*);
		};
		class TEMP{
			public:
				TEMP(Temp::Temp* temp);
		};
		class BINOP{
			public:
				BINOP(int binop, Expression* left, Expression* right);
		};
		class MEM{
			public:
				MEM(Expression* exp);
		};
		class CALL{
			public:
				CALL(Expression* func, ExpressionList* expList);
		};
		class ESEQ{
			public:
				ESEQ(Statement* stm, Expression* exp);
		};
	};

	class Statement
	{
	public:
		Statement(arguments);
		~Statement();
	
		class MOVE
		{
		public:
			MOVE(Expression* dst, Expression* src);
			~MOVE();
		
			/* data */
		};
		class EXP
		{
		public:
			EXP(Expression* exp);
			~EXP();
		
			/* data */
		};
		class JUMP
		{
		public:
			JUMP(Expression* exp, Temp::LabelList targets);
			~JUMP();
		
			/* data */
		};
		class CJUMP
		{
		public:
			CJUMP(int relop, Expression* left, Expression* right, Label* iftrue, Label* iffalse);
			~CJUMP();
		
			/* data */
		};
		class SEQ
		{
		public:
			SEQ(Statement* left, Statement* right);
			~SEQ();
		
			/* data */
		};
		class LABEL
		{
		public:
			LABEL(Label* label);
			~LABEL();
		
			/* data */
		};
	};

	class ExpressionList
	{
	public:
		ExpressionList(arguments);
		~ExpressionList();
	
		/* data */
	};

	class StatementList
	{
	public:
		StatementList(arguments);
		~StatementList();
	
		/* data */
	};
}