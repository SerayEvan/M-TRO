#ifndef INTERPRETER
#define INTERPRETER

#include "instruction.hpp"
#include "emulator.hpp"

void runProg(void* prog, MaterialRestriction material);

#endif