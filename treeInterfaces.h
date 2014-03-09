#pragma once

#include "itreevisitor.h"

namespace IRTree{

class IExp
{
public:
	virtual ~IExp() {};
	virtual int Accept(ITreeVisitor* v) const = 0;
	virtual ExpList* kids() const = 0;
	virtual IExp* build(const ExpList* kids) const = 0;
};

class IStm
{
public:
	virtual ~IStm() {};
	virtual int Accept(ITreeVisitor* v) const = 0;
	virtual ExpList* kids() const = 0;
	virtual IStm* build(const ExpList* kids) const = 0;
};

}
