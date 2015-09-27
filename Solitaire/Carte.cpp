#include "Carte.h"

using namespace std;

Carte::Carte (Valeur p_valeur, Sorte p_sorte)
{
	this->m_valeur = p_valeur;
	this->m_sorte = p_sorte;
}

const bool Carte::estSuivante(const Carte & p_carte)
{
	return this->m_valeur + 1 == p_carte.m_valeur;
}

const bool Carte::estMemeCouleur(const Carte & p_carte)
{
	return this->m_sorte == p_carte.m_valeur;
}

ostream &operator<< (ostream &sortie, const Carte &p_carte)
{
	sortie << p_carte.m_valeur << "'" << p_carte.m_sorte;
	return sortie;
}

ostream &operator<< (ostream &sortie, const Sorte &p_sorte)
{
	switch (p_sorte)
	{
	case COEUR:
		sortie << "CO";
		break;
	case CARREAU:
		sortie << "CA";
		break;
	case PIQUE:
		sortie << "PI";
		break;
	case TREFLE:
		sortie << "TR";
		break;
	default:
		break;
	}
	return sortie;
}


ostream &operator<< (ostream &sortie, const Valeur &p_valeur)
{
	switch (p_valeur)
	{
	case AS:
		sortie << "As";
		break;
	case DEUX:
		sortie << "2";
		break;
	case TROIS:
		sortie << "3";
		break;
	case QUATRE:
		sortie << "4";
		break;
	case CINQ:
		sortie << "5";
		break;
	case SIX:
		sortie << "6";
		break;
	case SEPT:
		sortie << "7";
		break;
	case HUIT:
		sortie << "8";
		break;
	case NEUF:
		sortie << "9";
		break;
	case DIX:
		sortie << "10";
		break;
	case VALET:
		sortie << "V";
		break;
	case DAME:
		sortie << "D";
		break;
	case ROI:
		sortie << "R";
		break;
	default:
		break;
	}
	return sortie;
}