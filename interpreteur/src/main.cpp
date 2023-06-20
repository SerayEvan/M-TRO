#include <iostream>
#include <ostream>
#include <fstream>
#include <string>

#include "binaryser/binaryser.hpp"
#include "instruction/instruction.hpp"
#include "interpreter/interpreter.hpp"
#include "macro/macro.hpp"
#include "tokenizer/tokenizer.hpp"
#include "reader/reader.hpp"

// gcc src/main.cpp src/syntaxe.cpp src/interpreter.cpp src/instruction.cpp src/split.cpp -o bin/remarq

using namespace std; 

int main()
{
   initInstructionTable();
   initMacroInstructionTable();

   list<string> contentFile = openFile("test/main.Cmetro");

   list<ligne> contentFile = tokeniz(string);

   decode_macro(contentFile);
   aplyMacro(contentFile);

   void* prog = compile(contentFile);

   MaterialRestriction materialRestriction;

   runProg(prog,materialRestriction);

   return 0;
}