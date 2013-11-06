#include <vector>
#include "symbol.h"
#include "interfaces.h"

class ClassTable {

		std::vector<ClassInfo> classes;

	public:	
		static const ClassInfo& addClass(const Symbol&);
		static const ClassInfo& getClass(const Symbol&);

};

class ClassInfo {

		Symbol* name;
		std::vector<VarInfo> fields;
		std::vector<MethodInfo> methods;

	public:
		static const VarInfo& addField(const Symbol&);
		static const VarInfo& getField(const Symbol&);
		static const MethodInfo& addMethod(const Symbol&);
		static const MethodInfo& getMethod(const Symbol&);
};

class MethodInfo {

		Symbol* name;
		std::vector<VarInfo> params;
		std::vector<VarInfo> localVars;

	public:
		static const VarInfo& addParam(const Symbol&);
		static const VarInfo& getParam(const Symbol&);
		static const VarInfo& addLocalVar(const Symbol&);
		static const VarInfo& getLocalVar(const Symbol&);
};


class VarInfo {

		Symbol* name;
		IType* type;	
	
};
