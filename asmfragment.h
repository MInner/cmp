#pragma once

#include "temp.h"
#include <boost/algorithm/string/replace.hpp>

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
		const IFrame* frame;
		std::list<std::string> code;
		int additionalStackSpace;
		InstructionList* currentInstructionList;
		InstructionList* firstInstructionList;
		AsmFragment* next;
		AsmFragment(AsmFragment* next = NULL): next(next), currentInstructionList(NULL), firstInstructionList(NULL), additionalStackSpace(0) {}
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

				#if PRINTPREASM
				std::cout << frame->getName()->name << ":" << std::endl;
				#endif
			}

			// log
			#if PRINTPREASM
			std::cout << "	";
			std::string line = i->asmcode;
			int j = 0;
			for (auto definedvar = i->definedVars; definedvar != 0; definedvar = definedvar->next, j++)
			{
				boost::replace_all(line, "d" + NumberToString(j), definedvar->temp->name);
			}
			j = 0;
			for (auto usedvar = i->usedVars; usedvar != 0; usedvar = usedvar->next, j++)
			{
				boost::replace_all(line, "u" + NumberToString(j), usedvar->temp->name);
			}

			std::cout << line << std::endl;

			#endif

		}

		void writeMappedTemps(std::map<const Temp::Temp*, std::string> regmapping)
		{
			for(auto instructionList = firstInstructionList; instructionList != 0; instructionList = instructionList->next )
			{
				auto instruction = instructionList->instr;
				int i = 0;
				std::string line = instruction->asmcode;
				for (auto uservar = instruction->usedVars; uservar != 0; uservar = uservar->next, i++)
				{
					if (regmapping[ uservar->temp ].substr(0, 1) == "<")
					{
						additionalStackSpace++;
						int shift = StringToInt(regmapping[ uservar->temp ].substr(1));
						std::string place = "[" + regmapping[ Temp::Temp::getTemp("##FP") ] + \
							" - " + NumberToString( frame->wordSize()*(shift + frame->localVarCount() + 1) ) + "]";
						boost::replace_all(line, "u" + NumberToString(i), place);
					} else {
						boost::replace_all(line, "u" + NumberToString(i), regmapping[ uservar->temp ]);
					}
				}
				i = 0;
				for (auto definedvar = instruction->definedVars; definedvar != 0; definedvar = definedvar->next, i++)
				{
					if (regmapping[ definedvar->temp ].substr(0, 1) == "<")
					{
						additionalStackSpace++;
						int shift = StringToInt(regmapping[ definedvar->temp ].substr(1));
						std::string place = "[" + regmapping[ Temp::Temp::getTemp("##FP") ] + \
							" - " + NumberToString( frame->wordSize()*(shift + frame->localVarCount() + 1) ) + "]";
						boost::replace_all(line, "d" + NumberToString(i), place);
					} else {
						boost::replace_all(line, "d" + NumberToString(i), regmapping[ definedvar->temp ]);
					}
				}

				if (line.substr(0, 3) == "MOV" && std::count(line.begin(), line.end(), '[') == 2 )
				{
					auto first_close = line.find("]");
					auto second_open = line.find('[', first_close );
					auto second_close = line.find(']', first_close );
					code.push_back( "PUSH DX" );
					code.push_back( "MOV DX, " + line.substr(second_open, second_close) );
					line.replace(second_open, second_close - second_open, "DX");
					code.push_back( line );
					code.push_back( "POP DX" );
				}
				else
				{
					code.push_back(line);
				}
			}
		}

		void writePrologueEpilogue(std::vector<std::string> regnames)
		{
			std::list<std::string> full;
			full.push_back("; prologue start");

			/* 
			<- BP
			param1
			param2
			param3
			retAddr
			*/

			full.push_back("PUSH EBP");
			full.push_back("MOV EBP, ESP");

			for (auto name : regnames)
			{
				full.push_back("PUSH " + name);
			}
			
			/* 
			param1
			param2
			param3
			retAddr
			oldEBP <- BP
			oldAX
			..
			oldDX
			*/

			auto total_shift = ( additionalStackSpace + frame->localVarCount() )*frame->wordSize();
			full.push_back("SUB ESP, " + NumberToString( total_shift ));
			/* 
			param1
			param2
			param3
			retAddr
			oldEBP <- BP
			oldAX
			..
			oldDX
			space
			...
			space <- SP
			*/
			full.push_back("; prologue end");

			// main code
			full.insert(full.end(), code.begin(), code.end());

			full.push_back("; epilogue start");
			full.push_back("ADD ESP, " + NumberToString( total_shift ));

			std::reverse(regnames.begin(),regnames.end());
			for (auto name : regnames)
			{
				full.push_back("POP " + name);
			}

			full.push_back("POP EBP");
			full.push_back("RET");


			full.push_back("; epilogue ends");

			code = full;

		}
	};

}
