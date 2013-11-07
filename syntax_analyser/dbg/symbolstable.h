#pragma once

#include <vector>
#include "symbol.h"
#include "interfaces.h"

class ClassInfo;
class MethodInfo;
class VarInfo;

class ClassTable {
	public:
		std::vector<ClassInfo*> classes;

		ClassInfo* addClass(const Symbol* name, const Symbol* parentName);
		ClassInfo* getClass(const Symbol* name);

};

class ClassInfo {
	public:
		const Symbol* name;
		const Symbol* parentName;
		std::vector<VarInfo*> fields;
		std::vector<MethodInfo*> methods;

		ClassInfo(const Symbol* name_, const Symbol* parentName_):
			name(name_), parentName(parentName_){};
		VarInfo* addField(const Symbol* name_, const IType* type_);
		VarInfo* getField(const Symbol* name);
		MethodInfo* addMethod(const Symbol* name, const IType* returnType);
		MethodInfo* getMethod(const Symbol* name);
};

class MethodInfo {
	public:
		const Symbol* name;
		const IType* returnType;
		std::vector<VarInfo*> params;
		std::vector<VarInfo*> localVars;

		MethodInfo(const Symbol* name_, const IType* returnType_):
			name(name_), returnType(returnType_){   }
		VarInfo* addParam(const Symbol* name, const IType* type);
		VarInfo* getParam(const Symbol* name, const IType* type);
		VarInfo* addLocalVar(const Symbol* name, const IType* type);
		VarInfo* getLocalVar(const Symbol* name, const IType* type);
};


class VarInfo {
	public:
		const Symbol* name;
		const IType* type;
		VarInfo(const Symbol* name_, const IType* type_):
			name(name_), type(type_){};
};
