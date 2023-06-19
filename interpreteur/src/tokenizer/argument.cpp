#include "argument.hpp"

int decode0to9(char c)
{
	if ( c == '0') {
		return 0;
	} else if ( c == '1' ) {
		return 1;
	} else if ( c == '2' ) {
		return 2;
	} else if ( c == '3' ) {
		return 3;
	} else if ( c == '4' ) {
		return 4;
	} else if ( c == '5' ) {
		return 5;
	} else if ( c == '6' ) {
		return 6;
	} else if ( c == '7' ) {
		return 7;
	} else if ( c == '8' ) {
		return 8;
	} else if ( c == '9' ) {
		return 9;
	} else {
		return -1;
	}
}

bool stringToInt( string content, Argument* argue)
{
	long int val = 0;
	long int signe = 1;

	for(int i = 0; i < ligne.length(); ++i)
	{
		val *= 10;

		int num = decode0to9(content[i]);
		if ( num != -1) {
			val += num;
		} else {
			return false;
		}
	}

	argue->type = ArgumentType::Tint;
	argue->intValue = val*signe;

	return true;
}

bool stringToFloatOrDouble( string content, Argument* argue )
{
	long int signe = 1;
	long int signeExposant = 1;

	int sectionWriting = 0;// 0 no section / 1 int section / 2 centil section / 3 sign exposant / 4 exposant section

	long double expo = 1;
	long double value = 0;
	int exposantValue = 0;

	for(int i = 0; i < content.length(); ++i)
	{
		
		char c = content[i];

		int num = decode0to9(content[i]);
		if ( num != -1 && sectionWriting <= 1 ) {
		    value *= 10;
			value += num;
			if (sectionWriting == 0) { sectionWriting = 1; }

		} else if ( num != -1 && sectionWriting == 2 ) {
		    expo *= 0.1d;
			value += num*expo;

		} else if ( num != -1 && sectionWriting >= 3 ) {
		    exposantValue *= 10;
			exposantValue += num;
			if (sectionWriting == 3) { sectionWriting = 4; }

		} else if ( c == '-' && sectionWriting == 0 ) {
			signe = -1;
			sectionWriting == 1;

		} else if ( c == '-' && sectionWriting == 3 ) {
			signeExposant = -1;
			sectionWriting = 4;

		} else if ( c == 'e' && sectionWriting < 3 ) {
			sectionWriting = 3;

		} else if ( c == 'f' && i == content.length()-1 && sectionWriting < 3 ) {
			argue->type = ArgumentType::Tfloat;
			argue->floatValue = signe*(float)(value);
			return true;

		} else if ( c == 'd' && i == content.length()-1 && sectionWriting < 3 ) {
			argue->type = ArgumentType::Tdouble;
			argue->doubleValue = signe*(value);
			return true;

		} else if ( c == '.' && sectionWriting <= 1 ) {
			sectionWriting = 2;

		} else { return false; }
	}

	if (sectionWriting >= 3)
	{
	    argue->type = ArgumentType::Tfloat;
		argue->floatValue = signe*(float)(value)*pow( 10, signeExposant*exposantValue );
		return true;
	} 

	argue->type = ArgumentType::Tdouble;
	argue->doubleValue = signe*(value);

	return true;
}

bool stringToChar( string content, Argument* argue )
{
	if (*content.begin() == '\'' && *(content.end()-1) == '\'')
	{
	    if (content[1] == '\\')
	    {
			uint32_t vch = 0;
			
			if (content[2] == 'x') { // forma : \x01
			    
				for (int i = 3; i < content.size()-1; ++i)
				{
					vch *= 16;
					if (content[i] == '0') {vch += 0;}
					else if (content[i] == '1') {vch += 1;}
					else if (content[i] == '2') {vch += 2;}
					else if (content[i] == '3') {vch += 3;}
					else if (content[i] == '4') {vch += 4;}
					else if (content[i] == '5') {vch += 5;}
					else if (content[i] == '6') {vch += 6;}
					else if (content[i] == '7') {vch += 7;}
					else if (content[i] == '8') {vch += 8;}
					else if (content[i] == '9') {vch += 9;}
					else if (content[i] == 'a' or content[i] == 'A') {vch += 10;}
					else if (content[i] == 'b' or content[i] == 'B') {vch += 11;}
					else if (content[i] == 'c' or content[i] == 'C') {vch += 12;}
					else if (content[i] == 'd' or content[i] == 'D') {vch += 13;}
					else if (content[i] == 'e' or content[i] == 'E') {vch += 14;}
					else if (content[i] == 'f' or content[i] == 'F') {vch += 15;}
					else {return false;}
					
					if (vch > 255) {return false;}
				}
			}
			else { // forma : \01 (hexa)
			    
				for (int i = 2; i < content.size()-1; ++i)
				{
					vch *= 8;
					if (content[i] == '0') {vch += 0;}
					else if (content[i] == '1') {vch += 1;}
					else if (content[i] == '2') {vch += 2;}
					else if (content[i] == '3') {vch += 3;}
					else if (content[i] == '4') {vch += 4;}
					else if (content[i] == '5') {vch += 5;}
					else if (content[i] == '6') {vch += 6;}
					else if (content[i] == '7') {vch += 7;}
					else if (content[i] == '8') {vch += 8;}
					else {return false;}
					
					if (vch > 255) {return false;}
				}
			}

			argue->type = ArgumentType::Tchar;
			argue->charValue = (char)vch;
			
			return true;
	    }
		if (content[1] == '\\' && content.size() == 4) {

			char ch = '\0';

			if (content[2] == '\'') { ch = '\''; }
			else if (content[2] == '\"') { ch = '\"'; }
			else if (content[2] == '\\') { ch = '\\'; }
			else if (content[2] == 'a') { ch = '\a'; }
			else if (content[2] == 'b') { ch = '\b'; }
			else if (content[2] == 'e') { ch = '\e'; }
			else if (content[2] == 'f') { ch = '\f'; }
			else if (content[2] == 'n') { ch = '\n'; }
			else if (content[2] == 'r') { ch = '\r'; }
			else if (content[2] == 't') { ch = '\t'; }
			else if (content[2] == 'v') { ch = '\v'; }
			else if (content[2] == '7') { ch = '\7'; }
			else if (content[2] == '?') { ch = '\?'; }

			argue->type = ArgumentType::Tchar;
			argue->charValue = ch;
			
			return true;

		} else if ( content.size() == 3 ) {

			argue->type = ArgumentType::Tchar;
			argue->charValue = content[1];
			return true;
		}
	}
	return false;
}

bool stringToString( string content, Argument* argue )
{
	if (*content.begin() == '"' && *(content.end()-1) == '"')
	{
		string text;

	    for (int i = 1; i < content.size()-1; ++i)
	    {
	    	if (content[i] != '\\') { text += content[i]; }
	    	else if (i!=content.size()-1)
	    	{
	    		i += 1;
				if      (content[i] == '\'') { text += '\''; }
				else if (content[i] == '\"') { text += '\"'; }
				else if (content[i] == '\\') { text += '\\'; }
				else if (content[i] == 'a')  { text += '\a'; }
				else if (content[i] == 'b')  { text += '\b'; }
				else if (content[i] == 'e')  { text += '\e'; }
				else if (content[i] == 'f')  { text += '\f'; }
				else if (content[i] == 'n')  { text += '\n'; }
				else if (content[i] == 'r')  { text += '\r'; }
				else if (content[i] == 't')  { text += '\t'; }
				else if (content[i] == 'v')  { text += '\v'; }
				else if (content[i] == '7')  { text += '\7'; }
				else if (content[i] == '?')  { text += '\?'; }
				else if (content[i] == 'x') {

					uint32_t vch;
					int i_;
					for ( i_ = i+1; i_ < content.size()-2; ++i_)
					{
						vch *= 16;

						if      (content[i_] == '0') {vch += 0;}
						else if (content[i_] == '1') {vch += 1;}
						else if (content[i_] == '2') {vch += 2;}
						else if (content[i_] == '3') {vch += 3;}
						else if (content[i_] == '4') {vch += 4;}
						else if (content[i_] == '5') {vch += 5;}
						else if (content[i_] == '6') {vch += 6;}
						else if (content[i_] == '7') {vch += 7;}
						else if (content[i_] == '8') {vch += 8;}
						else if (content[i_] == '9') {vch += 9;}
						else if (content[i_] == 'a' or content[i_] == 'A') {vch += 10;}
						else if (content[i_] == 'b' or content[i_] == 'B') {vch += 11;}
						else if (content[i_] == 'c' or content[i_] == 'C') {vch += 12;}
						else if (content[i_] == 'd' or content[i_] == 'D') {vch += 13;}
						else if (content[i_] == 'e' or content[i_] == 'E') {vch += 14;}
						else if (content[i_] == 'f' or content[i_] == 'F') {vch += 15;}

						else {
							vch = vch/16;
							break;
						}
						
						if (vch > 255) {
							vch = vch/16;
							break;
						}
					}

					i = i_-1;

					text += (char)vch;

				} else {

					uint32_t vch;
					int i_;
					for ( i_ = i+1; i_ < content.size()-2; ++i_)
					{
						vch *= 8;

						if      (content[i_] == '0') {vch += 0;}
						else if (content[i_] == '1') {vch += 1;}
						else if (content[i_] == '2') {vch += 2;}
						else if (content[i_] == '3') {vch += 3;}
						else if (content[i_] == '4') {vch += 4;}
						else if (content[i_] == '5') {vch += 5;}
						else if (content[i_] == '6') {vch += 6;}
						else if (content[i_] == '7') {vch += 7;}
						else if (content[i_] == '8') {vch += 8;}

						else {
							vch = vch/8;
							break;
						}
						
						if (vch > 255) {
							vch = vch/8;
							break;
						}
					}

					i = i_-1;

					text += (char)vch;
				}
	    	}
	    	else {return false;}
	    }
	    
	    argue->type = ArgumentType::Tstring;
		argue->text = text;
	    
	    return true;
	}
	return false;
}

Argue DecodeArgue(string content)
{
	Argue argue;

	argue.text = content;

	if ( stringToInt(content) ) {
		return argue;
	} else if ( stringToFloatOrInt(content) ) {
		return argue;
	} else if ( stringToChar(content) ) {
		return argue;
	} else if ( stringToString(content) ) {
		return argue;
	} else {
	}

	argue.type = ArgumentType::Tnone;

	return argue;
}