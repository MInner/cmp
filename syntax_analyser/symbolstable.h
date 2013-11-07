#include <vector>
#include "symbol.h"
#include "interfaces.h"

class ClassTable {
	public:
		std::vector<ClassInfo> classes;

		
		const ClassInfo& addClass(const Symbol*& name);
		const ClassInfo& getClass(const Symbol*& name);

};

class ClassInfo {

	public:
		Symbol* name;
		std::vector<VarInfo> fields;
		std::vector<MethodInfo> methods;

		ClassInfo(const Symbol* name);
		const VarInfo& addField(const Symbol*& name);
		const VarInfo& getField(const Symbol*& name);
		const MethodInfo& addMethod(const Symbol*& name);
		const MethodInfo& getMethod(const Symbol*& name);
};

class MethodInfo {
	public:
		Symbol* name;
		std::vector<VarInfo> params;
		std::vector<VarInfo> localVars;
		IType* returnType;	

	
		const VarInfo& addParam(const Symbol*& name);
		const VarInfo& getParam(const Symbol*& name);
		const VarInfo& addLocalVar(const Symbol*& name);
		const VarInfo& getLocalVar(const Symbol*& name);
};


class VarInfo {
	public:
		Symbol* name;
		IType* type;	
	
};
