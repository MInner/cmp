#pragma once

#include "temp.h"

class IFrame {
public:
	virtual int wordSize() const = 0;
};

class FrameStub : public IFrame
{
public:
	int nlocvar;
	int nargs;
	Temp::Label* name;
	
	FrameStub(std::string _name, int _nargs, int _nlocvar)
			: nargs(_nlocvar), nlocvar(_nlocvar) { name = new Temp::Label(_name); }

	int wordSize() const
	{
		return 2;
	}
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
		return new FrameStub(name, nargs, nlocvar);
	}

};