#ifndef CARTE_H
#define CARTE_H

#include <ostream>
#include "Sorte.h"
#include "Valeur.h"


using namespace std;
class Carte
{
public:

	Sorte m_sorte;
	Valeur m_valeur;

	Carte (Valeur p_valeur, Sorte p_sorte);

	const bool estSuivante(const Carte & p_carte);

	const bool estMemeCouleur(const Carte & p_carte);

	friend ostream &operator<< (ostream &sortie, const Sorte &p_sorte);
	friend ostream &operator<< (ostream &sortie, const Valeur &p_valeur);
	friend ostream &operator<< (ostream &sortie, const Carte &p_carte);


};
#endif