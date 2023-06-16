#include <iostream>
#include <fstream>
#include <string>

#include "syntaxe.hpp"
#include "instruction.hpp"
#include "interpreter.hpp"
#include "emulator.hpp"

// gcc src/main.cpp src/syntaxe.cpp src/interpreter.cpp src/instruction.cpp src/split.cpp -o bin/remarq

using namespace std; 

int main()
{

   initInstructionTable();

   void* prog = makeProg("test/main.Cmetro");

   MaterialRestriction materialRestriction;

   runProg(prog,materialRestriction);

   return 0;
}