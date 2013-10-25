#pragma once 

#include "visitor.h" 

class IProgram 
{
public: 
	virtual ~IProgram() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IMainClass 
{
public: 
	virtual ~IMainClass() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IClassDeclarations 
{
public: 
	virtual ~IClassDeclarations() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IClassDeclaration 
{
public: 
	virtual ~IClassDeclaration() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IVarDeclarations 
{
public: 
	virtual ~IVarDeclarations() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IVarDeclaration 
{
public: 
	virtual ~IVarDeclaration() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IMethodDeclarations 
{
public: 
	virtual ~IMethodDeclarations() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IMethodDeclaration 
{
public: 
	virtual ~IMethodDeclaration() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IStatements 
{
public: 
	virtual ~IStatements() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IStatement 
{
public: 
	virtual ~IStatement() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IType 
{
public: 
	virtual ~IType() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IArguements 
{
public: 
	virtual ~IArguements() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IArguement 
{
public: 
	virtual ~IArguement() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IAssignment 
{
public: 
	virtual ~IAssignment() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IExpression 
{
public: 
	virtual ~IExpression() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
class IExpressionList 
{
public: 
	virtual ~IExpressionList() {};
	virtual int Accept(IVisitor* v) const = 0;
}; 
