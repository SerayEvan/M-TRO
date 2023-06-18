#include "reader.hpp"

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