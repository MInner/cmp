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
            
            std::stack<Assemble::VarGraphNode*> stack;
            #if PRINTREGALLOC
            std::cout << "Colorization" << std::endl;
            std::cout <<  " stack size " << stack.size() << std::endl;
            #endif
            
            while(!graph->allnodes.empty()){
                while (simplify(graph, stack, registerCount));
                calculateSpillPriorities(graph, flowgraph);
                spill(graph, stack);
            }
            
            #if PRINTREGALLOC
            std::cout <<  " stack size " << stack.size() << std::endl;
            #endif
            
            while (!stack.empty()) {
                //constGr->printGr();
                auto node = stack.top();
                stack.pop();
                node->color = constGr->getColor(node, registerCount);
                #if PRINTREGALLOC
                std::cout << " Node " << node->name->name << " color " << node->color << std::endl;
                #endif
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
        void spill(Assemble::VarGraph* graph, std::stack<Assemble::VarGraphNode*>& stack) {
            //graph->printGr();
            auto node = graph->getSomeNode();
            if (node) {
                node->color = -1; // candidate
                stack.push(node);
                graph->removeNode(node);
                //graph->printGr();
            }
        }

        void calculateSpillPriorities(Assemble::VarGraph* graph, Assemble::FlowGraph* flowgraph) {
            for(auto node: graph->allnodes) {
                node->spillPriority = (double)flowgraph->countUsesDefs(node->name) / graph->neighborsNumber(node);
                //cout << " NODE " << node->name->name << " spillPriority: " << node->spillPriority << std::endl;
            }
        }
	};
}
