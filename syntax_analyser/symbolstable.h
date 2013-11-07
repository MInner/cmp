#include <vector>
#include "symbol.h"
#include "interfaces.h"

class ClassTable {

		std::vector<ClassInfo> classes;

	public:	
		const ClassInfo& addClass(const Symbol&);
		const ClassInfo& getClass(const Symbol&);

};

class ClassInfo {

		Symbol* name;
		std::vector<VarInfo> fields;
		std::vector<MethodInfo> methods;

	public:
		const VarInfo& addField(const Symbol&);
		const VarInfo& getField(const Symbol&);
		const MethodInfo& addMethod(const Symbol&);
		const MethodInfo& getMethod(const Symbol&);
};

class MethodInfo {

		Symbol* name;
		std::vector<VarInfo> params;
		std::vector<VarInfo> localVars;
		IType* returnType;	

	public:
		const VarInfo& addParam(const Symbol&);
		const VarInfo& getParam(const Symbol&);
		const VarInfo& addLocalVar(const Symbol&);
		const VarInfo& getLocalVar(const Symbol&);
};


class VarInfo {

		Symbol* name;
		IType* type;	
	
};
