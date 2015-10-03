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
	Solitaire solitaire;
	static const std::string menu;

	void menuDeplacerCarteTalonVersColonne();
	void menuDeplacerCarteTalonVersPile();
	void menuDeplacerCarteColonneVersColonne();
	void menuDeplacerCarteColonneVersPile();

	int menuSelectionnerColonneSource();
	int menuSelectionnerColonneDestination();
	int menuSelectionnerPileDestination();
	int menuSelectionnerNombreCartes();

	bool convertirStringEnIntAvecValidation(std::string stringEntree, int& valeurEntiereEntree, const int debutPortee , const int finPortee, const int maxNombreCaractere);
};


#endif /* JEUSOLITAIRE_H_ */
