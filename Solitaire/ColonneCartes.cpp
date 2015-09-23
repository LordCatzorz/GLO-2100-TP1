#include "ColonneCarte.h"

ColonneCartes::ColonneCartes()
{
}

void ColonneCartes::initColonneCartes (vector<Carte>& p_listeCartes)
{
	this->m_lesCartes.clear();
	this->m_lesCartes = p_listeCartes;
}

void ColonneCartes::ajoute (const Carte & p_carte)
{
	this->m_lesCartes.push_back (p_carte);
}

void ColonneCartes::deplacePaquet (ColonneCartes & p_destination, int p_nombreCartes)
{
	throw "deplacePaquet n'est pas encore impl�ment�e";
}

void ColonneCartes::supprimeDerniereCarte ()
{
	throw "supprimeDerniereCarte n'est pas encore impl�ment�e";
}

int ColonneCartes::reqNbCartesVisibles () const
{
	throw "reqNbCartesVisibles n'est pas encore impl�ment�e";
}

ostream& operator<< (ostream& os, const ColonneCartes & p_colonneCartes)
{
	throw "operator<< n'est pas encore impl�ment�e";
}