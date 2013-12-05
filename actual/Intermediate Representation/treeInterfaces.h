namespace IRTree{

class Exp 
{
public: 
	virtual ~Exp() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 

class Stm 
{
public: 
	virtual ~Stm() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 

}
