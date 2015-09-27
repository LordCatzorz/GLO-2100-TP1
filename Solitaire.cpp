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
		std::rotate(this->m_talon.begin(), this->m_talon.end() - 1, this->m_talon.end());
	}

	void Solitaire::deplacerColonneAColonne(int p_colonneSource, int p_colonneDestination, int p_nbCartes)
	{
		this->m_colonnes[p_colonneSource].deplacePaquet(this->m_colonnes[p_colonneDestination], p_nbCartes);
	}

	void Solitaire::deplacerTalonAColonne (int p_colonneDestination)
	{
		this->m_colonnes[p_colonneDestination].ajoute(this->m_talon.front());
		this->m_talon.pop_front();
	}

	void Solitaire::deplacerTalonAPile (int p_pileDestination)
	{
		this->m_piles[p_pileDestination].push(this->m_talon.front());
		this->m_talon.pop_front();
	}

	void Solitaire::deplacerColonneAPile (int p_colonneSource, int p_pileDestination)
	{
		this->m_piles[p_pileDestination].push(this->m_colonnes[p_colonneSource].m_lesCartes.front());
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

