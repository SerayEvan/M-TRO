#ifndef MACRO_INSTRUCTION
#define MACRO_INSTRUCTION

struct MacroInstructionData
{
	uint16_t id;
	string name;
	uint16_t sizeofInstruction;

	/*
	Exemple
	I32 : prend un int 32
	UI32 : prend un uint 32						
	CHR : prend un char							
	PI : prend une position dans la pile		index : @
	PR : prend une position dans le programe	index : #
	*/
	string inputSyntaxe;

};

void initMacroInstructionTable();

struct Section{
	uint32_t start;
	uint32_t end;// WARNING end est la possition de l'instruction suivent le :}
	uint32_t pileSize;
	//uint32_t pilePos;
	std::map<string, uint32_t> variable;
	Section* parent = nullptr;
};

typedef function<void(Ligne)->list<Ligne>> MacroInstructionFunc;

extern MacroInstructionData* macroInstructionTableData;
extern MacroInstructionFunc* macroInstructionTable;
extern uint16_t numberMacroInstruction;

#endif