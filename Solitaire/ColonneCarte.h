#ifndef COLONNE_CARTE_H
#define COLONNE_CARTE_H

#include "Carte.h"
#include <vector>

using namespace std;
class ColonneCartes
{
public:

	vector<Carte> m_lesCartes;
	int m_nbCartesVisibles;

	ColonneCartes();

	void initColonneCartes (vector<Carte>& p_listeCartes);

	void ajoute (const Carte & p_carte);

	void deplacePaquet (ColonneCartes & p_destination, int p_nombreCartes);

	void supprimeDerniereCarte ();

	int reqNbCartesVisibles () const;

	friend ostream& operator<< (ostream& os, const ColonneCartes & p_colonneCartes);

};

#endif