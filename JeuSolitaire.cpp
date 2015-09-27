/*
 * jeuSolitaire.cpp
 *
 *  Created on: 2015-09-27
 *      Author: etudiant
 */



#include "JeuSolitaire.h"
#include <iostream>
#include <sstream>

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
			//Déplacer carte talon vers colonne
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
