#include "syntaxe.hpp"

InstructionData findInstruction(string name)
{
	for (int i = 0; i < numberInstruction; ++i)
	{
		if (instructionTableData[i].name == name)
		{
			return instructionTableData[i];
		}
	}

	cout << "Not existe instruction : " << name << "\n";

	return instructionTableData[0];// None instruction
}

list<InstructToken> tokenize(list<string> content)
{
	list<InstructToken> tokens;

	for (auto ligne = content.begin(); ligne != content.end(); ligne++)
	{
		vector<string> argue = split(*ligne);

		InstructToken instructToken;

		instructToken.instrcution = findInstruction(argue[0]);

		argue.erase(argue.begin());

		instructToken.param = argue;

		tokens.push_back(instructToken);
	}

	return tokens;
}

list<string> openFile(const string fileName)
{
	list<string> l = {};

	ifstream fichier;
	fichier.open(fileName.c_str());

	if(fichier)
	{
		//L'ouverture s'est bien passée, on peut donc lire

		string ligne; //Une variable pour stocker les lignes lues

		while(getline(fichier, ligne)) //Tant qu'on n'est pas à la fin, on lit
		{
			l.push_back(ligne);
		}
	}
	else
	{
	  cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
	}

	return l;
}

uint32_t sizeofPrograme(list<InstructToken> tokens)
{
	uint32_t sizeProg = 0;

	for (auto token = tokens.begin(); token != tokens.end(); token++)
	{
		sizeProg += (*token).instrcution.sizeofInstruction;
	}

	return sizeProg;
}

long int stringToInt(string val)
{
	long int value = 0;

	for (int i = 0; i < val.length(); ++i)
	{
		value *= 10;
		switch (val[i])
		{
		case '0' : value += 0; break;
		case '1' : value += 1; break;
		case '2' : value += 2; break;
		case '3' : value += 3; break;
		case '4' : value += 4; break;
		case '5' : value += 5; break;
		case '6' : value += 6; break;
		case '7' : value += 7; break;
		case '8' : value += 8; break;
		case '9' : value += 9; break;
		}
	}

	return value;
}

float stringToFloat(string val)
{
	// TODO : effectuer la lecture d'un float

	return 0.0f;
}

double stringToDouble(string val)
{
	// TODO : effectuer la lecture d'un double

	return 0.0d;
}

char stringToChar(string val)
{
	// 'a' -> a

	// TODO : faire des protection

	return val[1];
}

template <typename T>
void binInt( void* prog, string name )
{
	long int val = stringToInt(name);

	if ( val < numeric_limits<T>::min())
		return;

	if ( val > numeric_limits<T>::max())
		return;

	*( (T*)prog ) = (T)val;
}

void binFloat( void* prog, string name )
{
	*( (float*)prog ) = stringToFloat(name);
}

void binDouble( void* prog, string name )
{
	*( (double*)prog ) = stringToDouble(name);
}

void binChar( void* prog, string name )
{
	*( (char*)prog ) = stringToChar(name);
}

void binPrograme( list<InstructToken> tokens, void* prog )
{
	for (auto token = tokens.begin(); token != tokens.end(); token++)
	{
		*( (uint16_t*)prog ) = token->instrcution.id;
		prog += 2;

		if (token->instrcution.inputSyntaxe != "N")
		{

			auto input = split(token->instrcution.inputSyntaxe);

			if (input.size() != token->param.size())
			{
				cout << "Nombre d'argument en désacord avec ceux requis\n";
				return;
			}

			for (int i = 0; i <= input.size(); i+=1)
			{
				if ( input[i] == "I8") {
					binInt<int8_t>( prog, token->param[i] );
					prog += SIZEOF_I8;
				} else if ( input[i] == "I16") {
					binInt<int16_t>( prog, token->param[i] );
					prog += SIZEOF_I16;
				} else if ( input[i] == "I32") {
					binInt<int32_t>( prog, token->param[i] );
					prog += SIZEOF_I32;
				} else if ( input[i] == "I64") {
					binInt<int64_t>( prog, token->param[i] );
					prog += SIZEOF_I64;

				} else if ( input[i] == "UI8") {
					binInt<uint8_t>( prog, token->param[i] );
					prog += SIZEOF_UI8;
				} else if ( input[i] == "UI16") {
					binInt<uint16_t>( prog, token->param[i] );
					prog += SIZEOF_UI16;
				} else if ( input[i] == "UI32") {
					binInt<uint32_t>( prog, token->param[i] );
					prog += SIZEOF_UI32;
				} else if ( input[i] == "UI64") {
					binInt<uint64_t>( prog, token->param[i] );
					prog += SIZEOF_UI64;

				} else if ( input[i] == "F") {
					binFloat( prog, token->param[i] );
					prog += SIZEOF_F;

				} else if ( input[i] == "D") {
					binDouble( prog, token->param[i] );
					prog += SIZEOF_D;

				} else if ( input[i] == "C") {
					binChar( prog, token->param[i] );
					prog += SIZEOF_C;

				} else if ( input[i] == "PI") {
					binInt<uint32_t>( prog, token->param[i] );
					prog += SIZEOF_PI;

				} else if ( input[i] == "PR") {
					binInt<uint32_t>( prog, token->param[i] );
					prog += SIZEOF_PR;
				}
			}
		}
	}
}

void* makeProg(string fileName)
{
	list<InstructToken> tokens = tokenize(openFile(fileName));

	uint32_t sizeProg = sizeofPrograme(tokens);

	void* prog = malloc(sizeProg);

	binPrograme(tokens,prog);

	return prog;
}