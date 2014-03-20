#pragma once

#include "temp.h"

namespace Assemble {

	class Instruction {
	public:
		const char* asmcode;
		// const Temp::TempList* usedVars() const = 0;
		// const Temp::TempList* definedVars() const = 0;
		// const Temp::LabelList* jumpTargets() const = 0;
		// std::string format()
	};

	class ASM : Instruction {
	public:
		const Temp::TempList* usedVars;
		const Temp::TempList* definedVars;
		ASM(const char* asmcode, const Temp::TempList* usedVars, const Temp::TempList* definedVars): 
			usedVars(usedVars), definedVars(definedVars) {this->asmcode = asmcode;}
	};

	class LABEL : Instruction {
	public:
		LABEL(const char* asmcode) {this->asmcode = asmcode;}
	};

	class MOVE : Instruction {
	public:
		const Temp::TempList* usedVars;
		const Temp::TempList* definedVars;
		MOVE(const char* asmcode, const Temp::TempList* usedVars, const Temp::TempList* definedVars): 
			usedVars(usedVars), definedVars(definedVars){this->asmcode = asmcode;}
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
		AsmFragment(AsmFragment* next = NULL):next(next), instructionList(NULL) {}
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
		}
	};

}
