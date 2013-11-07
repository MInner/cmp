#include "symbolstable.h"
#include <vector>
#include "interfaces.h"

const ClassInfo* ClassTable::addClass(const Symbol* name, const Symbol* parentName){
	for(int i = 0; i < classes.size(); i++){
		if(classes.at(i)->name == name){
			throw "class already exists";
		}
	}
	ClassInfo* a = new ClassInfo(name, parentName);
	classes.push_back(a);
}

const ClassInfo* ClassTable::getClass(const Symbol* name){
	for(int i = 0; i < classes.size(); i++){
		if(classes.at(i)->name == name){
			return classes.at(i);
		}
	}
	throw "there is no such class";
}

ClassInfo::ClassInfo(const Symbol* name_, const Symbol* parentName_):
	name(name_), parentName(parentName_){}

const VarInfo* ClassInfo::addField(const Symbol* name, const IType* type){
	for(int i = 0; i < fields.size(); i++){
		if(fields.at(i)->name == name){
			throw "field already exists";
		}
	}
	VarInfo* a = new VarInfo(name, type);
	fields.push_back(a);
}

const VarInfo* ClassInfo::getField(const Symbol* name){
	for(int i = 0; i < fields.size(); i++){
		if(fields.at(i)->name == name){
			return fields.at(i);
		}
	}
	throw "there is no such field";
}

const MethodInfo* ClassInfo::addMethod(const Symbol* name,const IType* returnType){
	for(int i = 0; i < methods.size(); i++){
		if(methods.at(i)->name == name){
			throw "method already exists";
		}
	}
	MethodInfo* a = new MethodInfo(name, returnType);
	methods.push_back(a);
}

const MethodInfo* ClassInfo::getMethod(const Symbol* name){
	for(int i = 0; i < methods.size(); i++){
		if(methods.at(i)->name == name){
			return methods.at(i);
		}
	}
	throw "there is no such method";
}