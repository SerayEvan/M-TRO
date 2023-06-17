#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

#include "binaryser/binaryser.hpp"
#include "instruction/instruction.hpp"
#include "interpreter/interpreter.hpp"
#include "reader/reader.hpp"

// gcc src/main.cpp src/syntaxe.cpp src/interpreter.cpp src/instruction.cpp src/split.cpp -o bin/remarq

using namespace std; 

int main()
{
   initInstructionTable();

   list<string> contentFile = openFile("test/main.Cmetro");

   void* prog = makeProg(contentFile);

   MaterialRestriction materialRestriction;

   runProg(prog,materialRestriction);

   return 0;
}