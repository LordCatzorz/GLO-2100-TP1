/*
 * jeuSolitaire.h
 *
 *  Created on: 2015-09-27
 *      Author: etudiant
 */

#ifndef JEUSOLITAIRE_H_
#define JEUSOLITAIRE_H_

#include "Solitaire.h"

class JeuSolitaire {
public:
	JeuSolitaire();
	void jouer();
private:
	Solitaire m_solitaire;
	static const std::string m_menu;

	void menuDeplacerCarteTalonVersColonne();
	void menuDeplacerCarteTalonVersPile();
	void menuDeplacerCarteColonneVersColonne();
	void menuDeplacerCarteColonneVersPile();

	int menuSelectionnerColonneSource();
	int menuSelectionnerColonneDestination();
	int menuSelectionnerPileDestination();
	int menuSelectionnerNombreCartes();

	int afficherSousMenuAvecSelection(const std::string p_message, const int p_debutPorteeValeur, const int p_finPorteeValeur, int p_maxNombreCaractere);

	bool convertirStringEnIntAvecValidation(std::string p_stringEntree, int& p_valeurEntiereEntree, const int p_debutPortee , const int p_finPortee, const int p_maxNombreCaractere);
	
	const bool validerMouvementTalonVersColonne(const int p_colonne) const;
	const bool validerMouvementTalonVersPile(const int p_pile) const;
	const bool validerMouvementColonneVersPile(const int p_colonneSource, const int p_pileDestination) const;
	const bool validerMouvementColonneVersColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nombreCarte) const;

};


#endif /* JEUSOLITAIRE_H_ */
