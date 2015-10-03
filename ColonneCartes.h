/*
 * ColonneCartes.h
 *
 *  Created on: 2015-09-24
 *      Author: etudiant
 */

#ifndef COLONNECARTES_H_
#define COLONNECARTES_H_

#include <vector>

#include "Carte.h"

class ColonneCartes
{
public:

		ColonneCartes();

		void initColonneCartes (std::vector<Carte>& p_listeCartes);

		void ajoute (const Carte& p_carte);

		void deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes);

		void supprimeDerniereCarte ();

		int reqNbCartesVisibles () const;

		friend std::ostream& operator<< (std::ostream& sortie, const ColonneCartes& p_colonneCartes);
		const std::vector<Carte>& reqLesCartes() const;

		Carte& reqCarteDessus();
		Carte& reqCartePosition(const int p_position);

private:
		int m_nbCartesVisibles;
		std::vector<Carte> m_lesCartes;

		bool peutAjouterCarte(const Carte& p_carte) const;
		void changerNombreCarteVisible(const int p_differenceNbCarte);
};



#endif /* COLONNECARTES_H_ */
