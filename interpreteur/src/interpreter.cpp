#include "interpreter.hpp"

void run( void* prog, MaterialRestriction material )
{
	void* instrcution = prog;

	emulator.material = material;

	emulator.run = true;
	emulator.pile = malloc(material.sizeOfPile);
	emulator.prog = prog;

	emulator.rPile = emulator.pile;
	emulator.rProg = emulator.prog;

	emulator.meroryAloc = 0;

	InitInstructionTable();

	while ( emulator.run )
	{
		uint16_t instructId = *(uint16_t*)emulator.rProg;
		emulator.rProg += 2;

		instructionTable[ instructId ]();
	}
}