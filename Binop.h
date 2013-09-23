


class Binop {
public:
    Binop( const char sign,const NumExp* left, const Statement* right ) :
	sign( sign ), leftExp( left ), rightExp( right )
	{
		assert( left != 0 );
		assert( right != 0 );
		assert( sign != 0);
	}

private:
	const Statement* const leftExp;
	const Statement* const rightExp;
	const char sign;
};
