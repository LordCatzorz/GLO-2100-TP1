/*
 * Carte.h
 *
 *  Created on: 2015-09-24
 *      Author: etudiant
 */

#ifndef CARTE_H_
#define CARTE_H_

#include <ostream>

#include "ContratException.h"


enum Sorte
{
	COEUR=1,
	CARREAU=2,
	PIQUE=3,
	TREFLE=4
};

enum Valeur
{
	AS=1,
	DEUX=2,
	TROIS=3,
	QUATRE=4,
	CINQ=5,
	SIX=6,
	SEPT=7,
	HUIT=8,
	NEUF=9,
	DIX=10,
	VALET=11,
	DAME=12,
	ROI=13,
};

class Carte
{
public:

	/**
	* @brief Le constructeur d'une Carte.
	* @param p_valeur La valeur Valeur de la carte.
	* @param p_sorte La valeur Sorte de la carte.
	*/
	Carte (Valeur p_valeur, Sorte p_sorte);

	/**
	* @brief Cette éthode vérifie si la Carte actuelle a une valeur considéré comme la suivante de la Carte en paramètre.
	* @param p_carte Une référence constante vers une carte.
	* @return Vrai si la carte actuelle est la suivainte, sinon faux.
	*/
	const bool estSuivante(const Carte& p_carte) const;

	/**
	* @brief Cette méthode vérifie si la Carte actuelle a la même couleur [Rouge|Noire] que la Carte en paramètre.
	* @param p_carte Une référence constante vers une carte.
	*/
	const bool estMemeCouleur(const Carte& p_carte) const;

	/**
	* @brief Surcharge de l'opérateur << qui fait l'affichage d'une carte.
	* @param p_sortie Une référence vers l'objet ostream de l'opérateur <<
	* @param p_carte Une référence constante vers une carte
	* @return Un ostream sous le format "VALEUR'SORTE"
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const Carte& p_carte);

	/**
	*
	*/
	const bool estCouleurNoir() const;

	const Valeur reqValeur() const;
	const Sorte reqSorte() const;

private:
	Sorte m_sorte;
	Valeur m_valeur;

	std::string reqSorteString() const;
	std::string reqValeurString() const;
};



#endif /* CARTE_H_ */
