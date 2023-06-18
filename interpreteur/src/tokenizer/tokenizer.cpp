
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

	return instructionTableData[0];// None instruction
}

Ligne tokenizLine(string ligne)
{
	Ligne ligneData;

	list<string> conent = split(ligne);

	if (conent.size())
	{
		ligneData.type = TypeLigne.none;
		ligneData.memorySize = 0;
		return ligneData;
	}

	else if (conent[0][0] == '/')
	{
		ligneData.type = TypeLigne.comment;
		ligneData.memorySize = 0;

		Argue content;
		content.type = ArgueType.string;

		ligneData.argue.push_back(content)

		return ligneData;
	}

	else if (conent[0][0] == ':')
	{
		// Todo décoder un token
	}

	else
	{
		ligneData.type = TypeLigne.instruction;
		ligneData.instruction = findInstruction( conent[0] );
	}

	for (int i = 1; i < ligneData.size(); ++i)
	{
		ligneData.argue.push_back( DecodeArgue( ligneData[i] ) );
	}
}