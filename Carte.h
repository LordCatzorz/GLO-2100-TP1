/*
* Carte.h
*
*  Created on: 2015-09-24
*      Author: Raphaël Sylvain (111 124 564)
*/

#ifndef CARTE_H_
#define CARTE_H_

#include <ostream>

#include "ContratException.h"

/**
* @enum Sorte
* @brief Énumeration qui correspond aux quatre sorte de carte
*/
enum Sorte
{
	COEUR=1,
	CARREAU=2,
	PIQUE=3,
	TREFLE=4
};

/**
* @enum Valeur
* @brief Énumeration qui correspond au 13 valeurs de carte.
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
	Carte (Valeur p_valeur, Sorte p_sorte);

	const bool estSuivante(const Carte& p_carte) const;
	const bool estMemeCouleur(const Carte& p_carte) const;

	friend std::ostream& operator<< (std::ostream& p_sortie, const Carte& p_carte);

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
