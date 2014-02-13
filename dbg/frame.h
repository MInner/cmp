#pragma once

#include "temp.h"
#include "treeInterfaces.h"
#include "treeClasses.h"

class IAccess;

class IFrame {

	int nlocvar;
	int nargs;
	Temp::Label* name;
	
public:
	IFrame(std::string _name, int _nargs, int _nlocvar)
			: nargs(_nlocvar), nlocvar(_nlocvar) { name = new Temp::Label(_name); }

	virtual const Temp::Label* getName() const { return name; }
	virtual int argsCount() const { return nargs; }
	virtual int localVarCount() const { return nlocvar; }

	virtual int wordSize() const = 0;
	virtual const IAccess* argByShift( int shift ) const = 0;
	virtual const IAccess* localVarByShift( int shift ) const = 0;
	virtual const Temp::Temp* framePointer() const = 0;
	virtual const IRTree::IExp* externalCall( const std::string& name, const IRTree::ExpList* args ) const = 0;
};

class IAccess {
	public:
		virtual ~IAccess() {}
		virtual const IRTree::IExp* Exp( const Temp::Temp* framePtr ) const = 0;
};

class AccessX86 : public IAccess {
	public:
		AccessX86 ( const IFrame* frame, int offset ) : frame( frame ), offset( offset ) {}

		virtual const IRTree::IExp* Exp( const Temp::Temp* framePtr ) const 
		{
			return new IRTree::MEM( new IRTree::BINOP( 
				IRTree::OPERATOR::PLUS, 
				new IRTree::TEMP( framePtr ), 
				new IRTree::CONST( offset * frame->wordSize() ) 
				) 
			); 
		}

	private:
		const IFrame* frame;
		int offset;
};

class FrameX86 : public IFrame
{
public:

	FrameX86(std::string _name, int _nargs, int _nlocvar)
			: IFrame(_name, _nargs, _nlocvar) {}

	virtual int wordSize() const { return 4; }	
	virtual const IAccess* argByShift( int shift ) const { return new AccessX86( this, shift ); }
	virtual const IAccess* localVarByShift( int shift ) const { return new AccessX86( this, -1 - shift ); }
	virtual const Temp::Temp* framePointer() const { return new Temp::Temp( "##FP" ); }
	virtual const IRTree::IExp* externalCall( const std::string& name, const IRTree::ExpList* args ) const { return new IRTree::CALL( new Temp::Label( name ), args ); }

};

class IFrameFactory
{
public:
	virtual ~IFrameFactory() {}
	virtual IFrame* create(std::string name, int nargs, int nlocvar) const = 0;
};

class FrameFactory_x86 : public IFrameFactory
{
public:
	IFrame* create(std::string name, int nargs, int nlocvar) const
	{
		return new FrameX86(name, nargs, nlocvar);
	}

};