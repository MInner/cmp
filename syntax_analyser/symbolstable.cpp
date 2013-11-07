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

