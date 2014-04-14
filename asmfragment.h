#pragma once

#include "temp.h"

namespace Assemble {

	class Instruction {
	public:
		const char* asmcode;
		const Temp::TempList* usedVars;
		const Temp::TempList* definedVars;
		// const Temp::TempList* usedVars() const = 0;
		// const Temp::TempList* definedVars() const = 0;
		// const Temp::LabelList* jumpTargets() const = 0;
		// std::string format()
	};

	class ASM : public Instruction {
	public:
		ASM(const char* _asmcode, const Temp::TempList* _usedVars = NULL, const Temp::TempList* _definedVars = NULL)
		{
			asmcode = _asmcode;
			usedVars = _usedVars;
			definedVars = _definedVars;
		}
	};

	class LABEL : public Instruction {
	public:
		LABEL(const Temp::Label* l) 
		{
			asmcode = (l->name + ":").c_str();
			usedVars = NULL;
			definedVars = NULL;
		}
	};

	class MOVE : public Instruction {
	public:
		MOVE(const char* asmcode, const Temp::TempList* _usedVars = NULL, const Temp::TempList* _definedVars = NULL)
		{
			this->asmcode = asmcode;
			usedVars = _usedVars;
			definedVars = _definedVars;
		}
	};

	class InstructionList {
	public:
		Instruction* instr;
		InstructionList* next;
		InstructionList(Instruction* ins)
		{
			instr = ins;
		}
	};

	class AsmFragment {
	public:
		InstructionList* instructionList;
		InstructionList* firstLinstruction;
		AsmFragment* next;
		AsmFragment(AsmFragment* next = NULL): next(next), instructionList(NULL) {}
		void addInstruction(Instruction* i)
		{
			if(instructionList)
			{
				InstructionList* newil = new InstructionList(i);
				instructionList->next = newil;
				instructionList = newil;
			}
			else
			{
				instructionList = new InstructionList(i);
				firstLinstruction = instructionList;
			}

			// log
			#if PRINTPREASM
			std::cout << "ASM: ";
			std::cout << i->asmcode << " ( ";
			if (i->usedVars)
			{
				for(auto curUsedVar = i->usedVars;
			        curUsedVar != nullptr; curUsedVar = curUsedVar->next ) 
				{
					std::cout << curUsedVar->temp->name << ", ";
				}
			}

			if (i->definedVars)
			{
				std::cout << " ; ";
				for(auto curUsedVar = i->definedVars; 
			        curUsedVar != nullptr; curUsedVar = curUsedVar->next ) 
				{
					std::cout << curUsedVar->temp->name;
				}
			}

			std::cout << " )" << std::endl;
			#endif

		}
	};

}
