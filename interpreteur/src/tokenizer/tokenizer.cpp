
list<string> split(string content)
{
	list<string> listArgue;
	string temp;

	for(int i = 0; i < ligne.length(); ++i)
	{
		char c = ligne[i];

		if (c != " ")
			temp += c;

		else if (temp != "")
		{
			listArgue.push_back(temp);
			temp = "";
		}
	}
}

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

	return nullptr;// None instruction
}

MacroInstructionData findMacroInstruction(string name)
{
	for (int i = 0; i < numberMacroInstruction; ++i)
	{
		if (macroInstructionTableData[i].name == name)
		{
			return macroInstructionTableData[i];
		}
	}

	cout << "Not existe instruction : " << name << "\n";

	return nullptr;// None instruction
}

bool tokenizLine(string ligne, Ligne* ligneData)
{
	list<string> conent = split(ligne);

	if (conent.size())
	{
		ligneData->type = TypeLigne.none;
		ligneData->memorySize = 0;
		return ligneData;
	}

	else if (conent[0][0] == '/')
	{
		ligneData->type = TypeLigne.comment;
		ligneData->memorySize = 0;

		Argue content;
		content.type = ArgueType.string;

		ligneData->argue.push_back(content)

		return ligneData;
	}

	else if (conent[0][0] == ':')
	{
		ligneData->type = TypeLigne::macro;
		ligneData->instruction = findMacroInstruction( conent[0] );
		if (ligneData->instruction == nullptr ) { return false; }
	}

	else
	{
		ligneData->type = TypeLigne::instruction;
		ligneData->instruction = findInstruction( conent[0] );
		if (ligneData->instruction == nullptr ) { return false; }
	}

	for (int i = 1; i < ligneData->size(); ++i)
	{
		Argument argue;
		if (!DecodeArgue( ligneData[i], &argue )){ return false; }
		ligneData->argue.push_back( argue );
	}

	return true;
}