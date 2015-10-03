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
		std::vector<Carte> m_lesCartes;

		ColonneCartes();

		void initColonneCartes (std::vector<Carte>& p_listeCartes);

		void ajoute (const Carte& p_carte);

		void deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes);

		void supprimeDerniereCarte ();

		int reqNbCartesVisibles () const;

		friend std::ostream& operator<< (std::ostream& sortie, const ColonneCartes& p_colonneCartes);

private:
		int m_nbCartesVisibles;

		Carte& obtenirCarteDessus () const;
		bool peutAjouterCarte(const Carte& p_carte) const;
		void changerNombreCarteVisible(const int p_differenceNbCarte);
};



#endif /* COLONNECARTES_H_ */
