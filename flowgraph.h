#pragma once

#include "asmfragment.h"
#include <map>
#include <algorithm>
#include <vector>
#include <string>

using std::list;
using std::map;
using std::set;
using std::string;

// #define PRINTFGCON_debug(str) std::cout << str << std::endl;
#define PRINTFGCON_debug(str) ;
// #define PRINTVG_debug(str) std::cout << str << std::endl;
#define PRINTVG_debug(str) ;
#define PRINTINOUT 0

string colors[] = {	"#10b5ad", "#cfff4a", "#4bcfff", "#fe4973", "#47fe79", "#ff0000",
					"#ceff00", "#2500ff", "#00fff4", "#2500ff", "#7e4141", "#00ff8d",
					"#00864a", "#00ff8d", "#dbc6cb", "#fa9e5f"};

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
	const Temp::Temp* name;
	int color; // -1 - stackCandidate 0 - stack, 1..k - num of register
	double spillPriority;
	static VarGraphNode* getVarGraphNode(const Temp::Temp* t)
    {
    	if (m.count(t))
    	{
    		return m[t];
    	}
    	else
    	{
    		auto n = new VarGraphNode(t);
    		m[t] = n;
    		return n;
    	}
    }
private:
    static std::map<const Temp::Temp*, VarGraphNode*> m;
	VarGraphNode(const Temp::Temp* _name): name(_name) { color = 0; }
};

class VarGraphEdge
{
public:
	const VarGraphNode* from;
	const VarGraphNode* to;
	bool simple;
	VarGraphEdge(const VarGraphNode* _from, const VarGraphNode* _to): from(_from), to(_to), simple(1) {}
};

class VarGraph
{
public:
	list<VarGraphNode*> allnodes;
	list<VarGraphEdge*> alledges;
	VarGraphNode* getNode(const Temp::Temp* i)
	{
		auto newnode = VarGraphNode::getVarGraphNode(i);
		if (std::find(allnodes.begin(), allnodes.end(), newnode) == allnodes.end())
		{
			allnodes.push_front(newnode);
		}
		return newnode;
	}

	void printGr() {
	    /*std::cout << "NODES" << std::endl;
	    for (auto node: allnodes) {
            std::cout <<" Node " << node->name->name << "(" << node << " | " << node->name << ")" << std::endl ;
        }
	    std::cout << "EDGEES" << std::endl;
        for (auto edge: alledges) {
            std::cout << " Edge " << edge->from->name->name << "(" << edge->from << ") to " << edge->to->name->name << "(" << edge->to << ")" << std::endl;
        } */
	}

	void removeNode(VarGraphNode* node)
	{
	    list<VarGraphEdge*> edgesToRemove;
	    for (auto edge: alledges) {
            if ((edge->from ==  node)||(edge->to == node)) {
                PRINTVG_debug(" Removing " + edge->from->name->name + " to " + edge->to->name->name);
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
		// kostil
		if (from == to)
		{
			return NULL;
		}

		for(auto e : alledges)
		{
			if (e->from == from && e->to == to)
			{
				return e;
			}
		}
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
		out << "graph VarGraph {" << std::endl;
		int node_count = 0;
		std::map<const VarGraphNode*, int> node_count_map;
		//int colorNum = getColorNum();
		for (VarGraphNode* node: this->allnodes){
			node_count_map[node] = node_count;
			string color;
			if (node->color > 0){
				color = colors[node->color - 1];
			}
			else if(node->color == 0){ // stack
				color = "#888888";
			}
			else if(node->color == 0){ // stack candidate
				color = "#cccccc";
			}

			out << "n" << node_count << " [shape=\"box\",style=\"filled\",fillcolor=\"" << color << "\", label=\"" << node->name->name << "  ["<< node_count << "]\"];" << std::endl;
			node_count++;
		}
		for (auto edge : this->alledges)
		{
			if (edge->to < edge->from)
			{
				out << "n" << node_count_map[edge->to] << " -- n" <<  node_count_map[edge->from] << ';' << std::endl;
			}
		}
		out << "}" << std::endl;
	}
};

class FlowGraphNode
{
public:
	Instruction* instruction;
	list<FlowGraphNode*> upper;
	std::set<const Temp::Temp*> in;
	std::set<const Temp::Temp*> out;
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

	int countUsesDefs(const Temp::Temp* var) {
	    int count = 0;
        for (FlowGraphNode* node : allnodes) {
            for(const Temp::Temp* use : TempListToSet(node->instruction->usedVars))
            {
                //std::cout << use->name << std::endl;
                if (use == var) {
                    count++;
                }
            }
            for(const Temp::Temp* def : TempListToSet(node->instruction->definedVars))
            {
                //std::cout << def->name << std::endl;
                if (def == var) {
                    count++;
                }
            }
        }
        std::cout << " count " << var->name <<  ": " << count << std::endl;
        return count;
	}
};

class FlowGraphBuilder
{
public:
	list<FlowGraph*> flowgraph_list;
	list<VarGraph*> vargraph_list;
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
				out << "n" << node_n << " [shape=\"box\",label=\"" << node->instruction->asmcode << " | "<< node_n << "\"];" << std::endl;
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

	list<VarGraph*> buildVarGraph()
	{
		for (FlowGraph* fg : flowgraph_list)
		{
			VarGraph* vg = new VarGraph();
			vargraph_list.push_front(vg);

			for (FlowGraphNode* node : fg->allnodes)
			{
				// out_i <- succ: in_k
				for (const FlowGraphNode* node_to : fg->getNodesTo(node)) // succ
				{
					for (const Temp::Temp* in_k : node_to->in)
					{
						node->out.insert(in_k);
					}
				}

				// in_i <- use_i

				for (const Temp::Temp* use_n : TempListToSet(node->instruction->usedVars))
				{
					node->in.insert(use_n);
				}

				// in <- out / def

				for (const Temp::Temp* out_n: node->out)
				{
					bool isNotInDef = true;
					for (const Temp::Temp* def_n : TempListToSet(node->instruction->definedVars))
					{
						if (out_n == def_n)
						{
							isNotInDef = false;
							break;
						}
					}
					if (isNotInDef)
					{
						node->in.insert(out_n);
					}
				}
			}

			#if PRINTINOUT

			for (FlowGraphNode* node : fg->allnodes)
			{
				std::cout << node->instruction->asmcode << std::endl;
				std::cout << "IN:" << std::endl;
				for(const Temp::Temp* in : node->in)
				{
					std::cout << in->name << std::endl;
				}
				std::cout << "OUT:" << std::endl;
				for(const Temp::Temp* out : node->out)
				{
					std::cout << out->name << std::endl;
				}
				std::cout << "USE:" << std::endl;
				for(const Temp::Temp* use : TempListToSet(node->instruction->usedVars))
				{
					std::cout << use->name << std::endl;
				}
				std::cout << "DEF:" << std::endl;
				for(const Temp::Temp* def : TempListToSet(node->instruction->definedVars))
				{
					std::cout << def->name << std::endl;
				}


				std::cout << "---" << std::endl;
			}

			#endif

			// add all nodes:
			for (FlowGraphNode* node : fg->allnodes)
			{
				for(const Temp::Temp* in : node->in)
				{
					vg->getNode( in );
				}
				for(const Temp::Temp* out : node->out)
				{
					vg->getNode( out );
				}
				for(const Temp::Temp* use : TempListToSet(node->instruction->usedVars))
				{
					vg->getNode( use );
				}
				for(const Temp::Temp* def : TempListToSet(node->instruction->definedVars))
				{
					vg->getNode( def );
				}
			}

			for (FlowGraphNode* node : fg->allnodes)
			{
				std::cout << "Node: " << node->instruction->asmcode << std::endl;
				if (const MOVE* move = dynamic_cast<const MOVE*>(node->instruction))
				{
					if (move->betweenTemp)
					{
						const Temp::Temp* a = move->usedVars->temp;
						const Temp::Temp* c;
						if (move->usedVars->next)
						{
							c = move->usedVars->next->temp;
						}
						else
						{
							c = move->definedVars->temp;
						}
						if (move->reverse)
						{
							const Temp::Temp* t;
							t = c;
							c = a;
							a = t;
						}
						VarGraphNode* a_node = vg->getNode(a);
						VarGraphNode* c_node = vg->getNode(c);

						for(const Temp::Temp* b : node->out)
						{
							if (b != c)
							{
								std::cout << "MOVE between staff" << std::endl;
								VarGraphNode* b_node = vg->getNode(b);
								vg->addEdge(a_node, b_node);
								vg->addEdge(b_node, a_node);
							}
						}
					}
				}
				else // not MOVE
				{
					for(const Temp::Temp* a : TempListToSet(node->instruction->definedVars))
					{
						std::cout << "Adding nodes" << std::endl;
						for(const Temp::Temp* b : node->out)
						{
							auto a_node = vg->getNode(a);
							auto b_node = vg->getNode(b);

							vg->addEdge(a_node, b_node);
							vg->addEdge(b_node, a_node);

							std::cout << "Add edge " << a->name << " to " << b->name << std::endl;
						}
					}
				}
			}
		}

		return vargraph_list;

	}

	// VarGraph* getVarGraph()
	// {
	// 	return
	// }
};

}
