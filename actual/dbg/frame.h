#pragma once

class IFrame {
public:
	virtual int wordSize() const = 0;
};

class FrameStub : public IFrame
{
public:

	std::string& name;
	int nlocvar;
	int nargs;

	FrameStub(std::string _name, int _nargs, int _nlocvar): name(_name), nargs(_nlocvar), nlocvar(_nlocvar) {}

	int wordSize() const
	{
		return 2;
	}
};

class IFrameFactory
{
public:
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
