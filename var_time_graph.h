#pragma once

#include "asmfragment.h"
#include "temp.h"

class CommandNode{
	Instruction asdCommand;
};

class VarTimeGraph{
	vector<CommandNode> nodes;
	vector<pair<CommandNode*, CommandNode*>> edges;

	vector<CommandNode*> getSucc(CommandNode* node){
		// find command nodes, which are successors of node
	}

	vector<CommandNode*> getPred(CommandNode* node){
		// find command nodes, which are predecessors of node
	}

	bool isAlive(Temp var, pair<CommandNode*, CommandNode*> edge){
		// determine if variable is alive in given edge
		// explanation is on page 7 of lecture 10
	}
};
