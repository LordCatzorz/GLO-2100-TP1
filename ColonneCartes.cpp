/*
* ColonneCartes.cpp
*
*  Created on: 2015-09-24
*      Author: etudiant
*/

#include "ColonneCartes.h"

ColonneCartes::ColonneCartes()
{
	this->m_lesCartes = std::vector<Carte>();
	this->m_nbCartesVisibles = 1;
}

void ColonneCartes::initColonneCartes (std::vector<Carte>& p_listeCartes)
{
	this->m_lesCartes.clear();
	this->m_lesCartes = p_listeCartes;
	POSTCONDITION(this->m_lesCartes.size() == p_listeCartes.size());
}

void ColonneCartes::ajoute (const Carte&  p_carte)
{
	PRECONDITION(this->peutAjouterCarte(p_carte));
	this->m_lesCartes.push_back (p_carte);
	this->changerNombreCarteVisible(1);
}

void ColonneCartes::deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes)
{
	PRECONDITION(p_nombreCartes > 0);
	PRECONDITION(p_nombreCartes <= this->reqNbCartesVisibles());
	std::vector<Carte>::iterator derniereCarteADeplacer = this->m_lesCartes.end() - p_nombreCartes;
	PRECONDITION(p_destination.peutAjouterCarte(*derniereCarteADeplacer));
	for (std::vector<Carte>::iterator iter = derniereCarteADeplacer; iter != this->m_lesCartes.end();)
	{
		p_destination.ajoute(*iter);
		this->supprimeDerniereCarte();
	}
}

void ColonneCartes::supprimeDerniereCarte ()
{
	PRECONDITION(!this->m_lesCartes.empty());
	this->m_lesCartes.pop_back();
	this->changerNombreCarteVisible(-1);
}

int ColonneCartes::reqNbCartesVisibles () const
{
	return this->m_nbCartesVisibles;
}

std::ostream& operator<< (std::ostream& sortie, const ColonneCartes& p_colonneCartes)
{
	if (p_colonneCartes.m_lesCartes.size() == 0)
	{
		sortie << "X ";
	}
	else
	{
		int nbCarteCache =  p_colonneCartes.m_lesCartes.size() - p_colonneCartes.reqNbCartesVisibles();
		if (nbCarteCache < 0)
		{
			nbCarteCache =0;
		}
		for (int i = 0; i < nbCarteCache; ++i)
		{
			sortie << "? ";
		}
		for (std::vector<Carte>::const_iterator iter =  p_colonneCartes.m_lesCartes.begin() + nbCarteCache; iter != p_colonneCartes.m_lesCartes.end(); ++iter)
		{
			sortie << *iter << " ";
		}
	}
	return sortie;
}


bool ColonneCartes::peutAjouterCarte(const Carte& p_carte) const
{

	if (this->m_lesCartes.empty())
	{
		if(p_carte.m_valeur == ROI)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		Carte derniereCarte = this->m_lesCartes.back();
		if (!derniereCarte.estMemeCouleur(p_carte))
		{
			if (derniereCarte.estSuivante(p_carte))
			{
				return true;
			}
		}
	}
	return false;
}

void ColonneCartes::changerNombreCarteVisible(const int p_differenceNbCarte)
{
	this->m_nbCartesVisibles += p_differenceNbCarte;
	if (this->m_nbCartesVisibles < 1)
	{
		this->m_nbCartesVisibles = 1;
	}
}

