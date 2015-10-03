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
	while (!solitaire.verifieGagne() || termine)
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
	}
}

void JeuSolitaire::menuDeplacerCarteTalonVersColonne()
{
	std::cout << "menuDeplacerCarteTalonVersColonne n'est pas encore implémentée";
}

void JeuSolitaire::menuDeplacerCarteTalonVersPile()
{
	std::cout << "menuDeplacerCarteTalonVersPile n'est pas encore implémentée";
}

void JeuSolitaire::menuDeplacerCarteColonneVersColonne()
{
	std::cout << "menuDeplacerCarteColonneVersColonne n'est pas encore implémentée";
}

void JeuSolitaire::menuDeplacerCarteColonneVersPile()
{
	std::cout << "menuDeplacerCarteColonneVersPile n'est pas encore implémentée";
}
