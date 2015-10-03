/*
 * Solitaire.h
 *
 *  Created on: 2015-09-24
 *      Author: etudiant
 */

#ifndef SOLITAIRE_H_
#define SOLITAIRE_H_

#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include <sstream>

#include "ColonneCartes.h"


class Solitaire
{
public:
	Solitaire();

	void avancerTalon();

	void deplacerColonneAColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nbCartes);

	void deplacerTalonAColonne (const int p_colonneDestination);

	void deplacerTalonAPile (const int p_pileDestination);

	void deplacerColonneAPile (const int p_colonneSource, const int p_pileDestination);

	bool verifieGagne() const;

	std::string reqEtatJeu () const;

	friend std::ostream& operator<< (std::ostream& sortie, const Solitaire& p_solitaire);
	
	const std::deque<Carte>& reqTalon() const;
	const ColonneCartes& reqColonne(const int p_numeroColonne) const;
	const std::stack<Carte>& reqPile(const int p_numeroPile) const;
private:
	std::deque<Carte> m_talon;
	ColonneCartes m_colonnes[7];
	std::stack<Carte> m_piles[4];

	void initialiserTalon();
	void initialiserColonnes();
	Carte& reqDessusPile(const int p_numeroPile);
	Carte& reqDessusTalon();
	Carte& reqDessusColonne(const int p_numeroColonne);
	Carte& reqCartePositionColonne(const int p_numeroColonne, const int p_positionCarte);
};



#endif /* SOLITAIRE_H_ */
