#include "symbolstable.h"
#include <vector>
#include "interfaces.h"

const ClassInfo& ClassTable::addClass(const Symbol*& name){
	for(int i = 0; i < classes.size(); i++){
		if(classes.at(i).name == name){
			throw "class already exists";
		}
	}
	ClassInfo a(name);
	classes.push_back(a);
}
