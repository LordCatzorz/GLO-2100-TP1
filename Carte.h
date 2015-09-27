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

class Carte
{
public:
	Sorte m_sorte;
	Valeur m_valeur;

	Carte (Valeur p_valeur, Sorte p_sorte);

	const bool estSuivante(const Carte& p_carte);

	const bool estMemeCouleur(const Carte& p_carte);

	friend std::ostream& operator<< (std::ostream& sortie, const Carte& p_carte);

	const bool estCouleurNoir(const Sorte p_sorte) const;

private:
	std::string reqSorteString() const;
	std::string reqValeurString() const;
};

#endif /* CARTE_H_ */
