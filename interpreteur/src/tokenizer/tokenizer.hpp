#ifndef TOKENIZER
#define TOKENIZER

#include <string>

using namespace std;

#include "instruction/instruction.hpp"
#include "argument.hpp"

enum TypeLigne
{
	instruction,
	balise,
	comment,
	none
};

struct Ligne
{
	TypeLigne type;
	union {
		InstructionData instruction;
		BaliseData balise;
	}
	list<Argument> argue;
	uint32_t memorySize;
	uint32_t memoryPos;
};

list<Ligne> tokeniz(list<string> contentFile);

#endif