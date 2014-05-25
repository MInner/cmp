#pragma once

#include "asmfragment.h"
#include <map>
#include <algorithm>
#include <vector>

using std::list;
using std::map;
using std::set;


#define PRINTFGCON_debug(str) std::cout << str << std::endl;


std::set<const Temp::Temp*> TempListToSet (const Temp::TempList* start)
{
	std::set<const Temp::Temp*> ret;
	for (const Temp::TempList* tl = start; tl != 0; tl = tl->next)
	{
		ret.insert(tl->temp);
	}
	return ret;
}



namespace Assemble
{

class VarGraphNode
{
public:
	Temp::Temp* name;
	int color; // -1 - stackCandidate 0 - stack, 1..k - num of register
	VarGraphNode(Temp::Temp* _name): name(_name) { color = 0; }
};

class VarGraphEdge
{
public:
	const VarGraphNode* from;
	const VarGraphNode* to;
	VarGraphEdge(const VarGraphNode* _from, const VarGraphNode* _to): from(_from), to(_to) {}
};

class VarGraph
{
public:
	list<VarGraphNode*> allnodes;
	list<VarGraphEdge*> alledges;

	VarGraphNode* addNode(Temp::Temp* i)
	{
		auto newnode = new VarGraphNode(i);
		allnodes.push_front(newnode);
		return newnode;
	}

	void printGr() {
	    std::cout << "NODES" << std::endl;
	    for (auto node: allnodes) {
            PRINTFGCON_debug(" Node " + node->name->name);
        }
	    std::cout << "EDGEES" << std::endl;
        for (auto edge: alledges) {
            PRINTFGCON_debug(" Edge " + edge->from->name->name + " to " + edge->to->name->name);
        }
	}

	void removeNode(VarGraphNode* node)
	{
	    list<VarGraphEdge*> edgesToRemove;
	    for (auto edge: alledges) {
            if ((edge->from ==  node)||(edge->to == node)) {
                PRINTFGCON_debug(" Removing " + edge->from->name->name + " to " + edge->to->name->name);
                edgesToRemove.push_back(edge);
            }
        }
        for (auto edge: edgesToRemove) {
            alledges.remove(edge);
        }
		allnodes.remove(node);
	}

	int getColor(VarGraphNode* node, int k){
        std::vector<int> colors(k + 1, 1);
        for (auto edge: alledges) {
            for(int i = 1; i <= k; i++){
                if (colors[i])
                std::cout << 1;
                else
                std::cout << 0;
            }
            std::cout << std::endl;
            const VarGraphNode* neighbor;
            if (edge->from ==  node) {
                neighbor = edge->to;
            }
            else if(edge->to == node) {
                neighbor = edge->from;
            } else {
                continue;
            }
            colors[neighbor->color] = 0;
        }
        for(int i = 1; i <= k; i++){
            if (colors[i]) return i;
        }
        return 0;
	}

	VarGraphNode* addNode(VarGraphNode* node)
	{
		allnodes.push_front(node);
		return node;
	}

	VarGraphNode* getUnsociableNode(int k) {
	    for (auto node: allnodes) {
	        if (!isNNMoreThan(k, node)) {
	            return node;
	        }
	    }
	    return nullptr;
	}

	VarGraphNode* getSomeNode() {
	    if (!allnodes.empty())  {
            return allnodes.front();
	    } else {
	        return nullptr;
	    }
	}

	VarGraphEdge* addEdge(const VarGraphNode* from, const VarGraphNode* to)
	{
		PRINTFGCON_debug(" Connecting " + from->name->name + " to " + to->name->name);
		auto newedge = new VarGraphEdge(from, to);
		alledges.push_front(newedge);
		std::cout << " neighborsNumber " << neighborsNumber(from) <<  " isNNMoreThan " << isNNMoreThan(0, to) << std::endl;
		return newedge;
	}

	bool isNNMoreThan(int k, const VarGraphNode* node) {
	    return (neighborsNumber(node) > k );
	}

	int neighborsNumber(const VarGraphNode* node) {
	    int num = 0;
        for (auto edge: alledges) {
            if (edge->from ==  node) num++;
        }
        return num;
	}
	void draw(std::ofstream& out){
		
	}
};

class FlowGraphNode
{
public:
	Instruction* instruction;
	list<FlowGraphNode*> upper;
	std::set<Temp::Temp*> in;
	std::set<Temp::Temp*> out;
	FlowGraphNode(Instruction* i)
	{
		instruction = i;
	}
};

class FlowGraphEdge
{
public:
	const FlowGraphNode* from;
	const FlowGraphNode* to;
	FlowGraphEdge(const FlowGraphNode* _from, const FlowGraphNode* _to): from(_from), to(_to) {}
};

class FlowGraph
{
public:
	list<FlowGraphNode*> allnodes;
	list<FlowGraphEdge*> alledges;

	FlowGraphNode* addNode(Instruction* i)
	{
		auto newnode = new FlowGraphNode(i);
		allnodes.push_front(newnode);
		return newnode;
	}

	FlowGraphEdge* addEdge(const FlowGraphNode* from, const FlowGraphNode* to)
	{
		PRINTFGCON_debug(" Connecting " + from->instruction->asmcode + " to " + to->instruction->asmcode);
		auto newedge = new FlowGraphEdge(from, to);
		alledges.push_front(newedge);
		return newedge;
	}
	list<const FlowGraphNode*> getNodesFrom(FlowGraphNode* node)
	{
		list<const FlowGraphNode*> ret;
		for (FlowGraphEdge* edge : this->alledges)
		{
			if (edge->from == node)
			{
				ret.push_front(edge->to);
			}
		}
		return ret;
	}

	list<const FlowGraphNode*> getNodesTo(FlowGraphNode* node)
	{
		list<const FlowGraphNode*> ret;
		for (FlowGraphEdge* edge : this->alledges)
		{
			if (edge->to == node)
			{
				ret.push_front(edge->from);
			}
		}
		return ret;
	}
};

class FlowGraphBuilder
{
public:
	list<FlowGraph*> flowgraph_list;
	void build(AsmFragment* root_af) // list of asm_fragments
	{
		// два прохода:
		// 1. 	строим линейно,
		// 		если текущий = JMP, то не присоединяем к нему следущий
		//  	+ jumpDirection = {JMP/JE/JZ node -> char LabelName }
		//		+ labelLocation = {char LabelName -> LABEL* node }
		// 2. Итерируем по jumpDirection's,
		// ищем соответствующие labelLocation,
		// добавляем ребра [LABEL* node -> JMP/JE/JZ node]

		for (AsmFragment* af = root_af; af != 0; af = af->next)
		{
			FlowGraph* flowgraph = new FlowGraph();
			flowgraph_list.push_front(flowgraph);
			map<const FlowGraphNode*, std::string> jumpDirection;
			map<std::string, const FlowGraphNode*> labelLocation;

			bool previousIsJump = false;

			FlowGraphNode* previousNode = 0;

			for (auto il = af->firstInstructionList; il != 0 ; il = il->next)
			{
				// PRINTFGCON_debug( "Converting instruction " + il->instr->asmcode );
				// new node of graph
				FlowGraphNode* newNode = flowgraph->addNode(il->instr);

				// building linear connections
				if (!previousIsJump && previousNode)
				{
					flowgraph->addEdge(newNode, previousNode);
				}

				previousIsJump = false;
				if (auto j = dynamic_cast<JMP*>(il->instr))
				{
					// if it is jump we wont add next to it
					previousIsJump = j->type == "JMP";

					// if it is JE/JZ/JMP add jumpDirection to this node
					jumpDirection[newNode] = j->where;
				}

				// if that is ASM::LABEL add it's ptr to labelLocation
				if (auto lab = dynamic_cast<LABEL*>(il->instr))
				{
					labelLocation[lab->name] = newNode;
				}

				previousNode = newNode;

			}

			for (auto& kv : jumpDirection) {
				// kv = [jumpNode, labelName]
				// labelLocation[labelName] = labelNode
				flowgraph->addEdge(labelLocation.at(kv.second), kv.first);
			}

		}
	}

	void draw(std::ofstream& out)
	{

		out << "digraph top {" << std::endl;
		int subgraph_n = 0;
		int node_n = 0;
		std::map<const FlowGraphNode*, int> nodes_map;
		for (FlowGraph* fg : flowgraph_list)
		{
			out << "subgraph cluster" << subgraph_n++ << " {" << std::endl;
			for (FlowGraphNode* node : fg->allnodes)
			{
				nodes_map[node] = node_n;
				out << "n" << node_n << " [shape=\"box\",label=\"" << node->instruction->asmcode << "  ["<< node_n << "]\"];" << std::endl;
				node_n++;
			}
			for (FlowGraphEdge* edge : fg->alledges)
			{
				out << "n" << nodes_map[edge->to] << " -> n" <<  nodes_map[edge->from] << ';' << std::endl;
			}
			out << "}" << std::endl;
		}
		out << "}" << std::endl;

	}

	void process()
	{
		// for (FlowGraph* fg : flowgraph_list)
		// {
		// 	for (FlowGraphNode* node : fg->allnodes)
		// 	{
		// 		auto nodesToThis = fg->getNodesTo(node);
		// 		for (auto to_node : nodesToThis)
		// 		{
		// 			for (const Temp::Temp* i : to_node->in)
		// 			{
		// 				node->out.insert(i);
		// 			}
		// 		}
		// 	}
		// }

	}
};

}
