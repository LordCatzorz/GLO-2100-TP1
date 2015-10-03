/*
 * Carte.h
 *
 *  Created on: 2015-09-24
 *      Author: etudiant
 */

#ifndef CARTE_H_
#define CARTE_H_

#include <ostream>

#include "Sorte.h"
#include "Valeur.h"
#include "ContratException.h"

class Carte
{
public:
	Carte (Valeur p_valeur, Sorte p_sorte);

	const bool estSuivante(const Carte& p_carte);

	const bool estMemeCouleur(const Carte& p_carte);

	friend std::ostream& operator<< (std::ostream& sortie, const Carte& p_carte);

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
