#pragma once

#include "flowgraph.h"

#include <stack>

namespace RegisterAllocation
{
	class RegAllocator
	{
	public:
        Assemble::VarGraph* colorGraph(Assemble::VarGraph* graph, Assemble::FlowGraph* flowgraph, int registerCount)
        {
            Assemble::VarGraph* constGr = new Assemble::VarGraph();
            constGr->alledges = graph->alledges;
            constGr->allnodes = graph->allnodes;
            // graph->printGr();
            std::cout << "Colorization" << std::endl;
            std::stack<Assemble::VarGraphNode*> stack;
            std::cout <<  " stack size " << stack.size() << std::endl;
            while(!graph->allnodes.empty()){
                while (simplify(graph, stack, registerCount));
                //calculateSpillPriorities(graph, flowgraph);
                auto spNode = getNodeForSpill(graph, flowgraph);
                spill(graph, stack, spNode);
            }
            std::cout <<  " stack size " << stack.size() << std::endl;
            while (!stack.empty()) {
                //constGr->printGr();
                auto node = stack.top();
                stack.pop();
                node->color = constGr->getColor(node, registerCount);
                std::cout << " Node " << node->name->name << " color " << node->color << std::endl;
            }

            return constGr;
        }

        bool simplify(Assemble::VarGraph* graph, std::stack<Assemble::VarGraphNode*>& stack, int k) {
            auto node = graph->getUnsociableNode(k);
            if (node) {
                // graph->printGr();
                stack.push(node);
                graph->removeNode(node);
                //graph->printGr();
                return TRUE;
            } else {
                return false;
            }
        }

        void spill(Assemble::VarGraph* graph, std::stack<Assemble::VarGraphNode*>& stack, Assemble::VarGraphNode* node) {
            //graph->printGr();
           // auto node = graph->getSomeNode();
            if (node) {
                node->color = -1; // candidate
                stack.push(node);
                std::cout << " Removing " << node->name << std::endl;
                graph->removeNode(node);
                //graph->printGr();
            }
        }

        Assemble::VarGraphNode* getNodeForSpill(Assemble::VarGraph* graph, Assemble::FlowGraph* flowgraph) {
            Assemble::VarGraphNode* ret;
            double min_priority;
            if (!graph->allnodes.empty())  {
                ret = graph->allnodes.front();
                min_priority = (double)flowgraph->countUsesDefs(ret->name) / graph->neighborsNumber(ret);
                ret->spillPriority = min_priority;
            } else {
                return nullptr;
            }

            double curr_priority;
            for(auto node: graph->allnodes) {
                curr_priority = (double)flowgraph->countUsesDefs(node->name) / graph->neighborsNumber(node);
                node->spillPriority = curr_priority;
                if (curr_priority < min_priority){
                    min_priority = curr_priority;
                    ret = node;
                }
                cout << " NODE " << node->name->name << " spillPriority: " << node->spillPriority << std::endl;
            }
            return ret;
        }
	};
}
