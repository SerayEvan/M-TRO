#ifndef ARGUMENT
#define ARGUMENT

enum ArgumentType
{
	int,       // 1
	float,     // 0.0f
	double,    // 0.0d
	char,      // 'c'
	string,    // "string"
	progPoint, // @point
	pilePoint, // $point
	macro,     // #balise
	none
};

struct Argument
{
	ArgueType type;
	union {
		long int intValue;
		float floatValue;
		double doubleValue;
		char charValue;
		string stringValue;
		uint32_t progPointValue;
		uint32_t pilePointValue;
		string macro;
	}
};

#endif