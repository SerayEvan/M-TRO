#ifndef ARGUMENT
#define ARGUMENT

#include <iostream>
#include <math.h>

using namespace std;

enum ArgumentType
{
	Tint,       // 1
	Tfloat,     // 0.0f
	Tdouble,    // 0.0d
	Tchar,      // 'c'
	Tstring,    // "string"
	TprogPoint, // @point
	TpilePoint, // $point
	Tmacro,     // #balise
	Tnone
};

struct Argument
{
	ArgumentType type;
	string text;
	union {
		long int intValue;
		float floatValue;
		double doubleValue;
		char charValue;
		uint32_t progPointValue;
		uint32_t pilePointValue;
	};
};

#endif