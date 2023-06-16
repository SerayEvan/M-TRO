#include <iostream>
#include <fstream>
#include <string>

#include "syntaxe.hpp"
#include "interpreter.hpp"
#include "split.hpp"

// gcc src/main.cpp src/syntaxe.cpp src/interpreter.cpp src/instruction.cpp src/split.cpp -o bin/remarq

using namespace std; 

int main()
{
   void* prog = makeProg("test/main.remc");

   return 0;
}