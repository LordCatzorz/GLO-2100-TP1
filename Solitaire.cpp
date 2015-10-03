/*
* Solitaire.cpp
*
*  Created on: 2015-09-24
*      Author: etudiant
*/

#include "Solitaire.h"

Solitaire::Solitaire()
{
	this->initialiserTalon();
	this->initialiserColonnes();
}

void Solitaire::avancerTalon()
{
	PRECONDITION(this->m_talon.size() > 0);
	std::rotate(this->m_talon.begin(), this->m_talon.end() - 1, this->m_talon.end());
}

void Solitaire::deplacerColonneAColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nbCartes)
{
	PRECONDITION(p_colonneSource >= 0);
	PRECONDITION(p_colonneDestination >= 0);
	PRECONDITION(p_nbCartes > 0);
	PRECONDITION(p_colonneSource <= 6);
	PRECONDITION(p_colonneSource <= 6);
	PRECONDITION(this->m_colonnes[p_colonneSource].reqNbCartesVisibles() >= p_nbCartes);
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() == 0 || !this->reqDessusColonne(p_colonneDestination).estMemeCouleur(this->reqCartePositionColonne(p_colonneSource, p_nbCartes)));
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() == 0 || this->reqDessusColonne(p_colonneDestination).estSuivante(this->reqCartePositionColonne(p_colonneSource, p_nbCartes)));
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() > 0 || this->reqCartePositionColonne(p_colonneSource, p_nbCartes).reqValeur() == ROI);

	this->m_colonnes[p_colonneSource].deplacePaquet(this->m_colonnes[p_colonneDestination], p_nbCartes);
}

void Solitaire::deplacerTalonAColonne (const int p_colonneDestination)
{
	PRECONDITION(p_colonneDestination >= 0);
	PRECONDITION(p_colonneDestination <= 6);
	PRECONDITION(this->m_talon.size() > 0);
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() == 0 || !this->reqDessusTalon().estMemeCouleur(this->reqDessusColonne(p_colonneDestination)));
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() == 0 || this->reqDessusColonne(p_colonneDestination).estSuivante(this->reqDessusTalon()));
	PRECONDITION(this->reqColonne(p_colonneDestination).reqLesCartes().size() > 0 || this->reqDessusTalon().reqValeur() == ROI);

	this->m_colonnes[p_colonneDestination].ajoute(this->m_talon.front());
	this->m_talon.pop_front();
}

void Solitaire::deplacerTalonAPile (const int p_pileDestination)
{
	PRECONDITION(p_pileDestination >= 0);
	PRECONDITION(p_pileDestination <= 3);
	PRECONDITION(this->m_talon.size() > 0);
	PRECONDITION(this->m_piles[p_pileDestination].size() == 0 || !this->reqDessusTalon().estMemeCouleur(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(this->m_piles[p_pileDestination].size() == 0 || this->reqDessusPile(p_pileDestination).estSuivante(this->reqDessusTalon()));
	PRECONDITION(this->m_piles[p_pileDestination].size() > 0 || this->reqDessusTalon().reqValeur() == AS);

	this->m_piles[p_pileDestination].push(this->reqDessusTalon());
	this->m_talon.pop_front();
}

void Solitaire::deplacerColonneAPile (const int p_colonneSource, const int p_pileDestination)
{
	PRECONDITION(p_pileDestination >= 0);
	PRECONDITION(p_pileDestination <= 3);
	PRECONDITION(p_colonneSource >= 0);
	PRECONDITION(p_colonneSource <= 6);

	PRECONDITION(this->m_colonnes[p_colonneSource].reqLesCartes().size() > 0);
	PRECONDITION(this->m_piles[p_pileDestination].size() == 0 || !this->reqDessusColonne(p_colonneSource).estMemeCouleur(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(this->m_piles[p_pileDestination].size() == 0 || this->reqDessusPile(p_pileDestination).estSuivante(this->reqDessusColonne(p_colonneSource)));
	PRECONDITION(this->m_piles[p_pileDestination].size() > 0 ||	this->reqDessusColonne(p_colonneSource).reqValeur() == AS);

	this->m_piles[p_pileDestination].push(this->reqDessusColonne(p_colonneSource));
	this->m_colonnes[p_colonneSource].supprimeDerniereCarte();
}

bool Solitaire::verifieGagne() const
{
	return (this->m_piles[0].size() == 13) &&
		(this->m_piles[1].size() == 13) &&
		(this->m_piles[2].size() == 13) &&
		(this->m_piles[3].size() == 13);
}

std::string Solitaire::reqEtatJeu () const
{
	std::ostringstream etatJeu;
	//Talon
	etatJeu << "Talon: " << this->m_talon.front();

	//Pile
	etatJeu << "             Piles ";
	for (int i = 0; i < 4; ++i)
	{
		if (this->m_piles[i].size() == 0)
		{
			etatJeu << "   X  ";
		}
		else
		{
			etatJeu <<" " << this->m_piles[i].top()<< " ";
		}
	}
	etatJeu << std::endl << std::endl;

	//Colonnes
	for (int i = 0 ; i < 7; ++i)
	{
		etatJeu << "Col." << i << ": " << this->m_colonnes[i] << std::endl;
	}

	return etatJeu.str();
}

std::ostream& operator<< (std::ostream& sortie, const Solitaire& p_solitaire)
{
	sortie << p_solitaire.reqEtatJeu();
	return sortie;
}

void Solitaire::initialiserTalon()
{

	for (int i = 1; i <= 4; i++) // Sortes
	{
		for (int j = 1; j <= 13; j++) // Valeurs
		{
			Carte carte((Valeur) j, (Sorte) i);
			this->m_talon.push_back(carte);
		}
	}

	srand((unsigned int)time(0));

	std::random_shuffle(this->m_talon.begin(), this->m_talon.end());
}

void Solitaire::initialiserColonnes()
{
	for (int i = 0; i < 7; ++i)
	{
		this->m_colonnes[i] = ColonneCartes();

		const std::deque<Carte>::iterator finSousDeque = this->m_talon.begin() + i + 1;
		std::vector<Carte> carteDeColonne = std::vector<Carte>(this->m_talon.begin(), finSousDeque);
		this->m_colonnes[i].initColonneCartes(carteDeColonne);
		for (int j = 0; j < i+1; j++)
		{
			this->m_talon.pop_front();
		}
	}
}


const std::deque<Carte>& Solitaire::reqTalon() const
{
	return this->m_talon;
}
const ColonneCartes& Solitaire::reqColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);

	return this->m_colonnes[p_numeroColonne];
}
const std::stack<Carte>& Solitaire::reqPile(const int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile];
}

Carte& Solitaire::reqDessusPile(int p_numeroPile)
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile].top();
}

Carte& Solitaire::reqDessusTalon()
{
	return this->m_talon.front();
}


Carte& Solitaire::reqDessusColonne(const int p_numeroColonne)
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	return this->m_colonnes[p_numeroColonne].reqCarteDessus();
}

Carte& Solitaire::reqCartePositionColonne(const int p_numeroColonne, const int p_position)
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	PRECONDITION(p_position <= this->m_colonnes[p_numeroColonne].reqNbCartesVisibles());
	return this->m_colonnes[p_numeroColonne].reqCartePosition(p_position);
}
