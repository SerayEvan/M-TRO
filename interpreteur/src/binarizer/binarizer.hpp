#ifndef SYNTAXE
#define SYNTAXE

#include <vector>
#include <list>
#include <limits>
#include <math.h>
#include <string>
#include <iostream>
#include <fstream>

#include "instruction/instruction.hpp"

using namespace std;

struct InstructToken{
	InstructionData instrcution;
	vector<string> param;
};

void* makeProg(list<string> fileName);

#endif