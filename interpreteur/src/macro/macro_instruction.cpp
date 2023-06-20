#include "macro_instruction.hpp"

void AddInstruction( string name, string inputSyntaxe, uint32_t sizeInstruct, const InstructionFunc func )
{
	instructionTableData[numberInstruction].id = numberInstruction;
	instructionTableData[numberInstruction].name = name;
	instructionTableData[numberInstruction].inputSyntaxe = inputSyntaxe;
	instructionTableData[numberInstruction].sizeofInstruction = sizeInstruct;

	instructionTable[numberInstruction] = func;

	numberInstruction++;
}

list<Section> sections;
Section actualSection;
int deepTree = 0;

void initMacroInstructionTable()
{
	AddInstruction(":{","",0, [](Ligne self) -> list<Ligne> {

		Section section;

		section.start = self.memoryPos;
		*section.parent = actualSection;

		actualSection = section;

		deepTree += 1;

		list<ligne> content;

		return content;

	});
	
	AddInstruction(":}","",0, [](Ligne self) -> list<ligne> {

		actualSection.end = self.memoryPos;

		actualSection = *actualSection.parent;

		deepTree -= 1;

		list<ligne> content;

		return content;
	});

	AddInstruction(":define","T M",0,[](Ligne self) -> list<ligne> {

		actualSection.variable.insert({self.argue[1].text,actualSection.pileSize});
		actualSection.pileSize += self.argue[0].sizeTypeValue;

		return nullptr;
	});
}