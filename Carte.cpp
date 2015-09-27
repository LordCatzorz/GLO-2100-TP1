/*
 * Carte.cpp
 *
 *  Created on: 2015-09-24
 *      Author: etudiant
 */


#include "Carte.h"
#include <sstream>
 #include <cstdlib>
using namespace std;

Carte::Carte (Valeur p_valeur, Sorte p_sorte)
{
	this->m_valeur = p_valeur;
	this->m_sorte = p_sorte;
}

const bool Carte::estSuivante(const Carte& p_carte)
{
	return this->m_valeur == p_carte.m_valeur + 1;
}

const bool Carte::estMemeCouleur(const Carte& p_carte)
{
	return this->estCouleurNoir(this->m_sorte) == this->estCouleurNoir(p_carte.m_sorte);
}

ostream& operator<< (ostream& sortie, const Carte& p_carte)
{
	sortie << p_carte.reqValeurString() << "'" << p_carte.reqSorteString();
	return sortie;
}

std::string Carte::reqSorteString() const
{
	string sortie;

	switch (this->m_sorte)
	{
	case COEUR:
		sortie = "CO";
		break;
	case CARREAU:
		sortie = "CA";
		break;
	case PIQUE:
		sortie = "PI";
		break;
	case TREFLE:
		sortie = "TR";
		break;
	default:
		break;
	}
	return sortie;
}


std::string Carte::reqValeurString () const
{
	std::string sortie;
	switch (this->m_valeur)
	{
	case AS:
		sortie = "A";
		break;
	case DEUX:
		sortie = "2";
		break;
	case TROIS:
		sortie = "3";
		break;
	case QUATRE:
		sortie = "4";
		break;
	case CINQ:
		sortie = "5";
		break;
	case SIX:
		sortie = "6";
		break;
	case SEPT:
		sortie = "7";
		break;
	case HUIT:
		sortie = "8";
		break;
	case NEUF:
		sortie = "9";
		break;
	case DIX:
		sortie = "10";
		break;
	case VALET:
		sortie = "V";
		break;
	case DAME:
		sortie = "D";
		break;
	case ROI:
		sortie = "R";
		break;
	default:
		break;
	}
	return sortie;
}

const bool Carte::estCouleurNoir(const Sorte p_sorte) const
{
	bool carteEstNoire;
	switch (p_sorte)
	{
		case PIQUE:
		case TREFLE:
			carteEstNoire = true;
			break;
		default:
			carteEstNoire = false;
			break;
	};
	return carteEstNoire;
}


