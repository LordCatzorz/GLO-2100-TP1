/*
* jeuSolitaire.cpp
*
*  Created on: 2015-09-27
*      Author: etudiant
*/



#include "JeuSolitaire.h"
#include <iostream>
#include <sstream>

const std::string JeuSolitaire::menu = "*******************************************\n      Menu\n*******************************************\n 1. Prochaine carte du talon.\n 2. Deplacer une carte du talon vers une colonne.\n 3. Deplacer une carte du talon vers une pile.\n 4. Deplacer une(des) carte(s) d'une colonne\n    vers une autre.\n 5. Deplacer une carte d'une colonne vers une pile.\n 6. Quitter.\n*******************************************\nVotre choix :\n";


JeuSolitaire::JeuSolitaire()
{
	solitaire = Solitaire();
}

void JeuSolitaire::jouer()
{
	bool termine = false;
	int i = 0;
	while (true)
	{
		std::cout << i << std::endl;
		std::cout << "Valeur :: " << menuSelectionnerColonneSource() << std::endl;
		i++;
	}

	/*while (!solitaire.verifieGagne() || termine)
	{
	std::cout << solitaire  <<"\n";
	std::cout << menu;
	std::string reponse;
	std::cin >> reponse;
	if (reponse == "1")
	{
	solitaire.avancerTalon();
	}
	else if (reponse == "2")
	{
	menuDeplacerCarteTalonVersColonne();
	}
	else if (reponse == "3")
	{
	menuDeplacerCarteTalonVersPile();
	}
	else if (reponse == "4")
	{
	menuDeplacerCarteColonneVersColonne();
	}
	else if (reponse == "5")
	{
	menuDeplacerCarteColonneVersPile();
	}
	else if (reponse == "6")
	{
	termine=true;
	}
	else
	{
	std::cout << "Choix invalide \n\n";
	}
	}*/
}

void JeuSolitaire::menuDeplacerCarteTalonVersColonne()
{
	int colonneDestination = menuSelectionnerColonneDestination();
}

void JeuSolitaire::menuDeplacerCarteTalonVersPile()
{
	int pileDestination =menuSelectionnerPileDestination();
}

void JeuSolitaire::menuDeplacerCarteColonneVersColonne()
{
	int colonneSource = menuSelectionnerColonneSource();
	int colonneDestination = menuSelectionnerColonneDestination();
	int nombreCartes = menuSelectionnerNombreCartes();
}

void JeuSolitaire::menuDeplacerCarteColonneVersPile()
{
	int colonneSource = menuSelectionnerColonneSource();
	int pileDestination = menuSelectionnerPileDestination();
}

int JeuSolitaire::menuSelectionnerColonneSource()
{
	std::string valeurEntree;
	int valeurEntiereEntree;
	while (valeurEntree.length() != 1 
		   || ( !(0 <= valeurEntiereEntree && valeurEntiereEntree <= 6) 
		   && valeurEntree != "q" && valeurEntree != "Q" ))
	{
		valeurEntiereEntree = -1;
		std::cout << "\nEntrer le numero de la colonne d'origine [0,6] ou 'q' pour quitter : ";
		std::getline(std::cin, valeurEntree);

	}
	return valeurEntiereEntree;
}

int JeuSolitaire::menuSelectionnerColonneDestination()
{
	std::cout << "menuSelectionnerColonneDestination n'est pas encore implémentée.";
	return -1;
}

int JeuSolitaire::menuSelectionnerPileDestination()
{
	std::cout << "menuSelectionnerPile n'est pas encore implémentée.";
	return -1;
}

int JeuSolitaire::menuSelectionnerNombreCartes()
{
	std::cout << "menuSelectionnerNombreCartes n'est pas encore implémentée.";
	return -1;
}

/***
Cette fonction va tenter d'effectué une conversion d'un caractère et mettre le resultat dans la valeur en référence.
Les caractères q et Q sont acceptés et mettent -1 dans la valeurEntière.
Le caractère doit être entier et situé entre les deux paramètres "debutPortee" et "finPortee"

La fonction retourne true si le caractère entrée et valide, sinon false.

*/
bool JeuSolitaire::convertirEntreeEnIntAvecValidation(std::string caractereEntree, int& valeurEntiereEntree, const int debutPortee , const int finPortee)
{
	if (caractereEntree.length() != 1)
	{
		return false;
	}
	else if (caractereEntree != "q" && caractereEntree != "Q" )
	{
		valeurEntiereEntree = -1;
		return true;
	}
	else
	{
		std::stringstream(caractereEntree) >> valeurEntiereEntree;
		if ( !(debutPortee <= valeurEntiereEntree && valeurEntiereEntree <= finPortee) )
		{
			return true;
		}
		else
		{
			valeurEntiereEntree = -1;
			return false;
		}
	}
	return false;
}