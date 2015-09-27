#include "Carte.h"
#include <iostream>
#include <vld.h>
#include <vector>

void main()
{
	vector<Carte> v;
	for (int sorte = 1; sorte < 5; sorte++)
	{
		for (int valeur = 1; valeur < 14; valeur++)
		{
			Carte c1 = Carte(Valeur(valeur), Sorte(sorte));
			v.push_back(c1);
		}
	}
	Carte c = Carte(AS, PIQUE);

	cout << c;

	
	for (vector<Carte>::const_iterator iterator = v.begin(); iterator != v.end(); iterator++)
	{
		cout << *iterator << "\n";
	}
	cout << system("Pause");

	v.clear();
}