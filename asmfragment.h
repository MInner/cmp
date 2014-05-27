#pragma once

#include "temp.h"

namespace Assemble {

	class Instruction {
	public:
        int depth;
		std::string asmcode;
		const Temp::TempList* usedVars;
		const Temp::TempList* definedVars;
		// const Temp::TempList* usedVars() const = 0;
		// const Temp::TempList* definedVars() const = 0;
		// const Temp::LabelList* jumpTargets() const = 0;
		// std::string format()
		virtual ~Instruction() {}
	};

	class ASM : public Instruction {
	public:
		ASM(std::string _asmcode, const Temp::TempList* _usedVars = NULL, const Temp::TempList* _definedVars = NULL)
		{
			asmcode = _asmcode;
			usedVars = _usedVars;
			definedVars = _definedVars;
		}
	};

	class LABEL : public Instruction {
	public:
		std::string name;
		LABEL(const Temp::Label* l)
		{
			asmcode = l->name + ":";
			name = l->name;
			usedVars = NULL;
			definedVars = NULL;
		}
	};

	class JMP : public Instruction {
	public:
		std::string type;
		std::string where;
		JMP(const std::string _type, const Temp::Label* _where)
		{
			asmcode = _type + " " + _where->name;
			type = _type;
			where = _where->name.c_str();
			usedVars = NULL;
			definedVars = NULL;
		}
	};

	class MOVE : public Instruction {
	public:
		bool betweenTemp;
		bool reverse;
		MOVE(std::string asmcode, const Temp::TempList* _usedVars = NULL,
			const Temp::TempList* _definedVars = NULL, bool _betweenTemp = false, bool _reverse = false)
		{
			this->asmcode = asmcode;
			usedVars = _usedVars;
			definedVars = _definedVars;
			betweenTemp = _betweenTemp;
			reverse = _reverse;
		}
	};

	class InstructionList {
	public:
		Instruction* instr;
		InstructionList* next;
		InstructionList(Instruction* ins)
		{
			instr = ins;
			next = NULL;
		}
	};

	class AsmFragment {
	public:
		InstructionList* currentInstructionList;
		InstructionList* firstInstructionList;
		AsmFragment* next;
		AsmFragment(AsmFragment* next = NULL): next(next), currentInstructionList(NULL), firstInstructionList(NULL) {}
		void addInstruction(Instruction* i)
		{
			if(firstInstructionList) // if list already exists
			{
				InstructionList* newil = new InstructionList(i);
				currentInstructionList->next = newil;
				currentInstructionList = newil;
			}
			else
			{
				currentInstructionList = new InstructionList(i);
				firstInstructionList = currentInstructionList;
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
