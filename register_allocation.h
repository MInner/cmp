#pragma once

#include "flowgraph.h"

#include <stack>

namespace RegisterAllocation
{
	class RegAllocator
	{
	public:
        Assemble::VarGraph* colorGraph(Assemble::VarGraph* graph, int registerCount)
        {
            Assemble::VarGraph* constGr = new Assemble::VarGraph();
            constGr->alledges = graph->alledges;
            constGr->allnodes = graph->allnodes;
            graph->printGr();
            std::cout << "Colorization" << std::endl;
            std::stack<Assemble::VarGraphNode*> stack;
            std::cout <<  " stack size " << stack.size() << std::endl;
            while(!graph->allnodes.empty()){
                while (simplify(graph, stack, registerCount));
                spill(graph, stack);
            }
            std::cout <<  " stack size " << stack.size() << std::endl;
            while (!stack.empty()) {
                constGr->printGr();
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
                graph->printGr();
                stack.push(node);
                graph->removeNode(node);
                graph->printGr();
                return TRUE;
            } else {
                return false;
            }
        }

        void spill(Assemble::VarGraph* graph, std::stack<Assemble::VarGraphNode*>& stack) {
            graph->printGr();
            auto node = graph->getSomeNode();
            if (node) {
                node->color = -1; // candidate
                stack.push(node);
                graph->removeNode(node);
                graph->printGr();
            }
        }
	};
}
