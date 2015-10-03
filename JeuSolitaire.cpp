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

	while (!solitaire.verifieGagne() || termine)
	{
		std::cout << solitaire  <<"\n";
		std::cout << menu;
		std::string reponse;
		std::getline (std::cin, reponse);
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
	}
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
	if (colonneSource != -1)
	{
		int colonneDestination = menuSelectionnerColonneDestination();
		if (colonneDestination != -1)
		{
			int nombreCartes = menuSelectionnerNombreCartes();
			if (nombreCartes != -1)
			{
				throw "On s'est rendu au bout, mais on a pas fini!";
			}
		}
	}
}

void JeuSolitaire::menuDeplacerCarteColonneVersPile()
{
	int colonneSource = menuSelectionnerColonneSource();
	int pileDestination = menuSelectionnerPileDestination();
}

int JeuSolitaire::menuSelectionnerColonneSource()
{
	return this->afficherSousMenuAvecSelection("Entrer le numero de la colonne d'origine", 0, 6, 1);
}

int JeuSolitaire::menuSelectionnerColonneDestination()
{
	return this->afficherSousMenuAvecSelection("Entrer le numero de la colonne destination", 0, 6, 1);
}

int JeuSolitaire::menuSelectionnerPileDestination()
{
	return this->afficherSousMenuAvecSelection("Entrer le numero de la pile destination", 0, 3, 1);
}

int JeuSolitaire::menuSelectionnerNombreCartes()
{
	return this->afficherSousMenuAvecSelection("Entrer le numero le nombre de carte a déplacer", 1, 13, 2);
}

/***
Cette fonction va tenter d'effectué une conversion d'un caractère et mettre le resultat dans la valeur en référence.
Les caractères q et Q sont acceptés et mettent -1 dans la valeurEntière.
Le caractère doit être entier et situé entre les deux paramètres "debutPortee" et "finPortee"

La fonction retourne true si le caractère entrée et valide, sinon false.

*/
bool JeuSolitaire::convertirStringEnIntAvecValidation(const std::string caractereEntree, int& valeurEntiereEntree, const int debutPortee , const int finPortee, const int maxNombreCaractere)
{

	valeurEntiereEntree = -1;
	if (caractereEntree.length() == 0 || caractereEntree.length() > maxNombreCaractere)
	{
		return false;
	}
	// Bon... mon == a arrêté de fonctionner pour les strings... Je trouve un bypass... 
	// Preuve: http://i.imgur.com/WX3eGA3.png
	else if (caractereEntree.compare("q") == 0 || caractereEntree.compare("Q") == 0)
	{
		return true;
	}
	else
	{
		std::stringstream(caractereEntree) >> valeurEntiereEntree;
		if (debutPortee <= valeurEntiereEntree && valeurEntiereEntree <= finPortee )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

int JeuSolitaire::afficherSousMenuAvecSelection(const std::string message, const int debutPorteeValeur, const int finPorteeValeur, int maxNombreCaractere)
{
	std::string valeurEntree;
	int valeurEntiereEntree;
	while (!this->convertirStringEnIntAvecValidation(valeurEntree,valeurEntiereEntree,debutPorteeValeur,finPorteeValeur,maxNombreCaractere))
	{
		valeurEntiereEntree = -1;
		std::cout << "\n" << message << " [" << debutPorteeValeur << ", " << finPorteeValeur << "] ou 'q' pour quitter : ";
		std::getline(std::cin, valeurEntree);
	}
	return valeurEntiereEntree;
}
