#pragma once

#include <vector>
#include "symbol.h"
#include "interfaces.h"
#include "enums.h"

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
		VarInfo* addField(const Symbol* name_, TypeData type_);
		VarInfo* getField(const Symbol* name);
		MethodInfo* addMethod(const Symbol* name, TypeData returnType);
		MethodInfo* getMethod(const Symbol* name);
};

class MethodInfo {
	public:
		const Symbol* name;
		TypeData returnType;	
		std::vector<VarInfo*> params;
		std::vector<VarInfo*> localVars;

		MethodInfo(const Symbol* name_, TypeData returnType_):
			name(name_), returnType(returnType_){};
		VarInfo* addParam(const Symbol* name, TypeData type);
		VarInfo* getParam(const Symbol* name);
		VarInfo* addLocalVar(const Symbol* name, TypeData type);
		VarInfo* getLocalVar(const Symbol* name);
};


class VarInfo {
	public:
		const Symbol* name;
		TypeData type;
		VarInfo(const Symbol* name_, TypeData type_):
			name(name_), type(type_){};
};
