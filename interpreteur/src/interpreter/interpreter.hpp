#ifndef INTERPRETER
#define INTERPRETER

#include "instruction/instruction.hpp"
#include "emulator.hpp"

void runProg(void* prog, MaterialRestriction material);

#endif