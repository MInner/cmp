#include <vector>
#include "symbol.h"
#include "interfaces.h"

class ClassTable {
	public:
		std::vector<ClassInfo*> classes;
		
		const ClassInfo* addClass(const Symbol* name, const Symbol* parentName);
		const ClassInfo* getClass(const Symbol* name);

};

class ClassInfo {
	public:
		const Symbol* name;
		const Symbol* parentName;
		std::vector<VarInfo*> fields;
		std::vector<MethodInfo*> methods;

		ClassInfo(const Symbol* name, const Symbol* parentName);
		const VarInfo* addField(const Symbol* name_, const IType* type_);
		const VarInfo* getField(const Symbol* name);
		const MethodInfo* addMethod(const Symbol* name,const IType* returnType);
		const MethodInfo* getMethod(const Symbol* name);
};

class MethodInfo {
	public:
		const Symbol* name;
		std::vector<VarInfo*> params;
		std::vector<VarInfo*> localVars;
		const IType* returnType;	

		MethodInfo(const Symbol* name_, const IType* returnType_):
			name(name_), returnType(returnType_){};
		const VarInfo* addParam(const Symbol* name);
		const VarInfo* getParam(const Symbol* name);
		const VarInfo* addLocalVar(const Symbol* name);
		const VarInfo* getLocalVar(const Symbol* name);
};


class VarInfo {
	public:
		const Symbol* name;
		const IType* type;		
		VarInfo(const Symbol* name_, const IType* type_):
			name(name_), type(type_){};
};
