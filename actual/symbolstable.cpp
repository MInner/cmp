#include "symbolstable.h"
#include <vector>
#include "interfaces.h"
#include <string>
#include <iostream>
#include <algorithm>

ClassInfo* ClassTable::addClass(const Symbol* name, const Symbol* parentName){
	// std::cout << "New class: " << name << std::endl;
	for(unsigned int i = 0; i < classes.size(); i++){
		if(classes.at(i)->name == name){
			std::cout << "WARNING: class already exists" << std::endl; 
			return NULL;
		}
	}
	ClassInfo* a = new ClassInfo(name, parentName);
	classes.push_back(a);
	return a;
}

ClassInfo* ClassTable::getClass(const Symbol* name){
	for(unsigned int i = 0; i < classes.size(); i++){
		if(classes.at(i)->name == name){
			return classes.at(i);
		}
	}
	std::cout << "WARNING: there is no such class" << std::endl; 
	return NULL;
}

//--------------------------------------------------

VarInfo* ClassInfo::addField(const Symbol* fname, TypeData type){
	// std::cout << "New field: " << name << "::" << fname << std::endl;
	for(unsigned int i = 0; i < fields.size(); i++){
		if(fields.at(i)->name == fname){
			std::cout << "WARNING: field already exists" << std::endl; 
			return NULL;
		}
	}
	VarInfo* a = new VarInfo(name, type);
	fields.push_back(a);
	return a;
}

VarInfo* ClassInfo::getField(const Symbol* name){
	for(unsigned int i = 0; i < fields.size(); i++){
		if(fields.at(i)->name == name){
			return fields.at(i);
		}
	}
	// std::cout << "WARNING: there is no such field" << std::endl; 
	return NULL;
}

MethodInfo* ClassInfo::addMethod(const Symbol* mname,TypeData returnType){	
	// std::cout << "New method: " << name << "::" << mname << std::endl;
	for(unsigned int i = 0; i < methods.size(); i++){
		if(methods.at(i)->name == mname){
			std::cout << "WARNING: method already exists" << std::endl; 
			return NULL;
		}
	}
	MethodInfo* a = new MethodInfo(mname, returnType);
	methods.push_back(a);
	return a;
}

MethodInfo* ClassInfo::getMethod(const Symbol* name){
	for(unsigned int i = 0; i < methods.size(); i++){
		if(methods.at(i)->name == name){
			return methods.at(i);
		}
	}
	std::cout << "WARNING: there is no such method" << std::endl; 
	return NULL;
}

int ClassInfo::getSize()
{
	return fields.size(); // TODO!!!!: ADD hierarchy SUPPORT LIKE (paernt ? table->get(parnt)->getsize() : 0 )
}

int ClassInfo::getFiledShift(const Symbol* name)
{
	for (int i=0; i<fields.size(); i++)
	{
		if (fields[i]->name == name)
			return i;
	}
}

//------------------------------------------------


VarInfo* MethodInfo::addParam(const Symbol* pname, TypeData type){
	// std::cout << "New param: CLASS::" << name << " ( .. " << pname << " .. )" << std::endl;
	for(unsigned int i = 0; i < params.size(); i++){
		if(params.at(i)->name == pname){
			std::cout << "WARNING: param already exists" << std::endl; 
			return NULL;
		}
}
	VarInfo* a = new VarInfo(pname, type);
	params.push_back(a);
	return a;
}

VarInfo* MethodInfo::getParam(const Symbol* name){
	for(unsigned int i = 0; i < params.size(); i++){
		if(params.at(i)->name == name){
			return params.at(i);
		}
	}
	// std::cout << "WARNING: there is no such param" << std::endl; 
	return NULL;
}

VarInfo* MethodInfo::addLocalVar(const Symbol* vname, TypeData type){
	// std::cout << "New locvar: CLASS::" << name << " { def " << vname << " }" << std::endl;
	for(unsigned int i = 0; i < localVars.size(); i++){
		if(localVars.at(i)->name == vname){
			std::cout << "WARNING: localVar already exists" << std::endl; 
			return NULL;
		}
	}
	VarInfo* a = new VarInfo(vname, type);
	localVars.push_back(a);
	return a;
}

VarInfo* MethodInfo::getLocalVar(const Symbol* name){
	for(unsigned int i = 0; i < localVars.size(); i++){
		if(localVars.at(i)->name == name){
			return localVars.at(i);
		}
	}
	// std::cout << "WARNING: there is no such localVar" << std::endl; 
	return NULL;
}
