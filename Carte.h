/*
 * Carte.h
 *
 *  Created on: 2015-09-24
 *      Author: Rapha�l Sylvain (111 124 564)
 */

#ifndef CARTE_H_
#define CARTE_H_

#include <ostream>

#include "ContratException.h"

/**
* �numeration qui correspond aux quatre sorte de carte
*/
enum Sorte
{
	COEUR=1,
	CARREAU=2,
	PIQUE=3,
	TREFLE=4
};


/**
* �numeration qui correspond au 13 valeurs de carte.
*/
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
	* @brief Cette �thode v�rifie si la Carte actuelle a une valeur consid�r� comme la suivante de la Carte en param�tre.
	* @param p_carte Une r�f�rence constante vers une carte.
	* @return Vrai si la carte actuelle est la suivante, sinon faux.
	*/
	const bool estSuivante(const Carte& p_carte) const;

	/**
	* @brief Cette m�thode v�rifie si la Carte actuelle a la m�me couleur [Rouge|Noire] que la Carte en param�tre.
	* @param p_carte Une r�f�rence constante vers une carte.
	*/
	const bool estMemeCouleur(const Carte& p_carte) const;

	/**
	* @brief Surcharge de l'op�rateur << qui fait l'affichage d'une carte.
	* @param p_sortie Une r�f�rence vers l'objet ostream de l'op�rateur <<
	* @param p_carte Une r�f�rence constante vers une carte
	* @return Un ostream sous le format "VALEUR'SORTE"
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const Carte& p_carte);

	/**
	* @brief Cette m�thode v�rifie si la couleur de la Carte est noire.
	* @return Vrai si la couleur est noire, sinon faux.
	*/
	const bool estCouleurNoir() const;

	/**
	* @brief Cette m�thode retourne la Valeur de la Carte.
	* @return La Valeur de la Carte en constante
	*/
	const Valeur reqValeur() const;

	/**
	* @brief Cette m�thode retourne la Sorte de la Carte.
	* @return La Sorte de la Carte en constante
	*/
	const Sorte reqSorte() const;

private:
	Sorte m_sorte;
	Valeur m_valeur;

	/**
	* @brief Cette m�thode retourne la Valeur de la Carte.
	* @return La Valeur de la Carte
	*/
	std::string reqSorteString() const;

	/**
	* @brief Cette m�thode retourne la Sorte de la Carte.
	* @return La Sorte de la Carte
	*/
	std::string reqValeurString() const;
};



#endif /* CARTE_H_ */
