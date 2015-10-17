/*
* Carte.cpp
*
*  Created on: 2015-09-24
*      Author: Rapha�l Sylvain (111 124 564)
*/


#include "Carte.h"
#include <sstream>
#include <cstdlib>

/**
* @brief Le constructeur d'une Carte.
* @param p_valeur La valeur Valeur de la carte.
* @param p_sorte La valeur Sorte de la carte.
*/
Carte::Carte (Valeur p_valeur, Sorte p_sorte)
{
	this->m_valeur = p_valeur;
	this->m_sorte = p_sorte;
}

/**
* @brief Cette �thode v�rifie si la Carte actuelle a une valeur consid�r� comme la suivante de la Carte en param�tre.
* @param p_carte Une r�f�rence constante vers une carte.
* @return Vrai si la carte actuelle est la suivante, sinon faux.
* La carte est consid�r�e comme la suivante si elle est d'un unit� plus �lev�e que la carte en param�tre.
* @see Carte.reqValeur()
*/
const bool Carte::estSuivante(const Carte& p_carte) const
{
	return this->reqValeur() == p_carte.reqValeur() + 1;
}

/**
* @brief Cette m�thode v�rifie si la Carte actuelle a la m�me couleur [Rouge|Noire] que la Carte en param�tre.
* @param p_carte Une r�f�rence constante vers une carte.
* La comparaison s'effectue en regardant si les deux cartes ont la m�me valeur retourn�e par estCouleurNoir
* @see Carte.estCouleurNoir()
*/
const bool Carte::estMemeCouleur(const Carte& p_carte) const
{
	return this->estCouleurNoir() == p_carte.estCouleurNoir();
}

/**
* @brief Surcharge de l'op�rateur << qui fait l'affichage d'une carte.
* @param p_sortie Une r�f�rence vers l'objet ostream de l'op�rateur <<
* @param p_carte Une r�f�rence constante vers une carte
* @return Un ostream sous le format "VALEUR'SORTE"
*/
std::ostream& operator<< (std::ostream& p_sortie, const Carte& p_carte)
{
	p_sortie << p_carte.reqValeurString() << "'" << p_carte.reqSorteString();
	return p_sortie;
}

/**
* @brief Cette m�thode retourne la Valeur de la Carte.
* @return La Valeur de la Carte
*/
std::string Carte::reqSorteString() const
{
	std::string sortie;

	switch (this->reqSorte())
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

/**
* @brief Cette m�thode retourne la Sorte de la Carte.
* @return La Sorte de la Carte
*/
std::string Carte::reqValeurString () const
{
	std::string sortie;
	switch (this->reqValeur())
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

/**
* @brief Cette m�thode v�rifie si la couleur de la Carte est noire.
* @return Vrai si la couleur est noire, sinon faux.
* La couleur de la carte est consid�r�e comme noire si elle est de sorte Tr�fle ou Pique.
* @see Carte.reqSorte()
*/
const bool Carte::estCouleurNoir() const
{
	bool carteEstNoire;
	switch (this->reqSorte())
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

/**
* @brief Cette m�thode retourne la Valeur de la Carte.
* @return La Valeur de la Carte en constante
*/
const Valeur Carte::reqValeur() const
{
	return this->m_valeur;
}

/**
* @brief Cette m�thode retourne la Sorte de la Carte.
* @return La Sorte de la Carte en constante
*/
const Sorte Carte::reqSorte() const
{
	return this->m_sorte;
}

