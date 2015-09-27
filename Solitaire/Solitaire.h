#ifndef SOLITAIRE_H
#define SOLITAIRE_H

#include "ColonneCarte.h"
#include <queue>
#include <stack>

using namespace std;
class Solitaire
{
public:
	queue<Carte> m_talon;
	ColonneCartes m_colonnes[7];
	stack<Carte> m_piles[4];

	Solitaire();

	void avancerTalon();

	void deplacerColonneAColonne(int p_colonneSource, int p_colonneDestination, int p_nbCartes);

	void deplacerTalonAColonne (int p_colonneDestination);

	void deplacerTalonAPile (int p_pileDestination);

	void deplacerColonneAPile (int p_colonneSource, int p_pileDestination);

	bool verifieGagne() const;

	string reqEtatJeu () const;

};

#endif