#include "argument.hpp"

Argue DecodeArgue(string content)
{
	Argue argue;

	if ( isInt(content) ) {
		return argue;
	} else {
	}

	return argue;
}

bool isInt(content, Argue* argue)
{
	long int val = 0;

	for(int i = 0; i < ligne.length(); ++i)
	{
		val *= 10;

		if ( c == '0') {
			val += 0;
		} else if ( c == '1' ) {
			val += 1;
		} else if ( c == '2' ) {
			val += 2;
		} else if ( c == '3' ) {
			val += 3;
		} else if ( c == '4' ) {
			val += 4;
		} else if ( c == '5' ) {
			val += 5;
		} else if ( c == '6' ) {
			val += 6;
		} else if ( c == '7' ) {
			val += 7;
		} else if ( c == '8' ) {
			val += 8;
		} else if ( c == '9' ) {
			val += 9;
		} else {
			return false
		}
	}

	argue->type = ArgumentType.int;
	argue->intValue = val;

	return true;
}