namespace Translate
{
	class Expression{
	public: 
		const Tree::Expression* toExpression() const = 0;
		const Tree::Statement* toStatement() const = 0;
		const Tree::Statement* toConditional() const = 0;
		
		
	};
	class Statement{
	public:
		Move()
	};

	class Ex: Expression
	{
	public:
		Tree::Expression* expression;
		Ex(Tree::Expression* exp){}
		~Ex();
		Tree::Expression toExpression()
		{
			return expression;
		}
		Tree::Statement toStatement()
		{
			//TODO
		}
		Tree::Statement toConditional(Label* trueLabel, Label* falseLabel)
		{
			//TODO
		}
		
	};

	class Nx: Expression
	{
	public:
		Tree::Statement* statement;
		Nx(Tree::Statement* statement){}
		~Nx();
		Tree::Expression toExpression()
		{
			//TODO
		}
		Tree::Statement toStatement()
		{
			return statement
		}
		Tree::Statement toConditional(Label* trueLabel, Label* falseLabel)
		{
			//TODO
		}
	};

	class Cx: Expression
	{
	public:
		Cx(arguments){}
		~Cx();

		Tree::Expression toExpression()
		{
			//TODO
		}
		Tree::Statement toStatement()
		{
			//TODO
		}
		Tree::Statement toConditional(Label* trueLabel, Label* falseLabel)
		{
			//TODO
		}
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