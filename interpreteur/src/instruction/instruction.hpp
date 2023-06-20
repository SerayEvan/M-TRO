#ifndef INSTRUCT
#define INSTRUCT

#include <functional>
#include <iostream>

#include "reader/split.hpp"
#include "interpreter/emulator.hpp"

using namespace std;

#define SIZE_INSTRUCTION_TABLE 65536

typedef function<void()> InstructionFunc;

#define SIZEOF_I8 1
#define SIZEOF_I16 2
#define SIZEOF_I32 4
#define SIZEOF_I64 8
#define SIZEOF_U8 1
#define SIZEOF_U16 2
#define SIZEOF_U32 4
#define SIZEOF_U64 8
#define SIZEOF_F 4
#define SIZEOF_D 8
#define SIZEOF_C 1
#define SIZEOF_P 8// TODO taille pointeur
#define SIZEOF_PI 2
#define SIZEOF_PR 4

#define SIZEOF_INTERFUNC 6 // pile translation + instruct pos => 2+4

struct InstructionData
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

void initInstructionTable();

extern InstructionData* instructionTableData;
extern InstructionFunc* instructionTable;
extern uint16_t numberInstruction;

#endif