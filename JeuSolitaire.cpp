/*
* jeuSolitaire.cpp
*
*  Created on: 2015-09-27
*      Author: etudiant
*/

#include "Solitaire.h"
#include <iostream>
#include <sstream>

const std::string m_menu = "*******************************************\n      Menu\n*******************************************\n 1. Prochaine carte du talon.\n 2. Deplacer une carte du talon vers une colonne.\n 3. Deplacer une carte du talon vers une pile.\n 4. Deplacer une(des) carte(s) d'une colonne\n    vers une autre.\n 5. Deplacer une carte d'une colonne vers une pile.\n 6. Quitter.\n*******************************************\nVotre choix :\n";
Solitaire m_solitaire;

const void afficherMessageCoupNonValide()
{
	std::cout << "\n!!! COUP NON VALIDE !!!\n";
}


const bool afficherMessageSucces()
{
	std::cout << "\n\nVous avez gagné!\n\nChoisissez 'q' pour quitter ou entrer pour continuer : ";
	std::string valeurEntree;
	std::getline(std::cin, valeurEntree);
	if (valeurEntree.compare("q") || valeurEntree.compare("Q"))
	{
		return true;
	}
	return false;
}

/***
Cette fonction va tenter d'effectué une conversion d'un caractère et mettre le resultat dans la valeur en référence.
Les caractères q et Q sont acceptés et mettent -1 dans la valeurEntière.
Le caractère doit être entier et situé entre les deux paramètres "debutPortee" et "finPortee"

La fonction retourne true si le caractère entrée et valide, sinon false.

*/
const bool convertirStringEnIntAvecValidation(const std::string p_caractereEntree, int& p_valeurEntiereEntree, const int p_debutPortee , const int p_finPortee, const int p_maxNombreCaractere)
{

	p_valeurEntiereEntree = -1;
	if (p_caractereEntree.length() == 0 || p_caractereEntree.length() > p_maxNombreCaractere)
	{
		return false;
	}
	// Bon... mon == arrête de fonctionner pour les strings rendu ici dans le code... Je trouve un bypass... 
	// Preuve: http://i.imgur.com/WX3eGA3.png
	else if (p_caractereEntree.compare("q") == 0 || p_caractereEntree.compare("Q") == 0)
	{
		return true;
	}
	else
	{
		std::stringstream(p_caractereEntree) >> p_valeurEntiereEntree;
		if (p_debutPortee <= p_valeurEntiereEntree && p_valeurEntiereEntree <= p_finPortee )
		{
			return true;
		}
		else
		{
			return false;
		}
	}

}

const int afficherSousMenuAvecSelection(const std::string p_message, const int p_debutPorteeValeur, const int p_finPorteeValeur, int p_maxNombreCaractere)
{
	std::string valeurEntree;
	int valeurEntiereEntree;
	while (!convertirStringEnIntAvecValidation(valeurEntree,valeurEntiereEntree,p_debutPorteeValeur,p_finPorteeValeur,p_maxNombreCaractere))
	{
		valeurEntiereEntree = -1;
		std::cout << "\n" << p_message << " [" << p_debutPorteeValeur << ", " << p_finPorteeValeur << "] ou 'q' pour quitter : ";
		std::getline(std::cin, valeurEntree);
	}
	return valeurEntiereEntree;
}

const bool validerMouvementTalonVersColonne(const int p_colonne)
{
	PRECONDITION(p_colonne >=0);
	PRECONDITION(p_colonne <=6);
	if (!m_solitaire.estVideTalon())
	{
		const Carte& dessusTalon = m_solitaire.reqDessusTalon();
		if (!m_solitaire.estVideColonne(p_colonne))
		{
			const Carte& dessusColonne = m_solitaire.reqDessusColonne(p_colonne);
			if (!dessusTalon.estMemeCouleur(dessusColonne))
			{
				if (dessusColonne.estSuivante(dessusTalon))
				{
					return true;
				}
			}
		}
		else
		{
			if (dessusTalon.reqValeur() == ROI)
			{
				return true;
			}
		}
	}
	return false;
}

const bool validerMouvementTalonVersPile(const int p_pile)
{
	PRECONDITION(p_pile >=0);
	PRECONDITION(p_pile <=3);

	if (!m_solitaire.estVideTalon())
	{
		const Carte& dessusTalon = m_solitaire.reqDessusTalon();
		if (!m_solitaire.estVidePile(p_pile))
		{
			const Carte& dessusPile = m_solitaire.reqDessusPile(p_pile);
			if (dessusTalon.reqSorte() == dessusPile.reqSorte())
			{
				if (dessusTalon.estSuivante(dessusPile))
				{
					return true;
				}
			}
		}
		else
		{
			if (dessusTalon.reqValeur() == AS)
			{
				return true;
			}
		}
	}
	return false;
}

const bool validerMouvementColonneVersPile(const int p_colonneSource, const int p_pileDestination)
{
	PRECONDITION(p_colonneSource >=0);
	PRECONDITION(p_colonneSource <=6);

	PRECONDITION(p_pileDestination >=0);
	PRECONDITION(p_pileDestination <=3);

	if (!m_solitaire.estVideColonne(p_colonneSource))
	{
		const Carte& dessusColonne = m_solitaire.reqDessusColonne(p_colonneSource);
		if (!m_solitaire.estVidePile(p_pileDestination))
		{
			const Carte& dessusPile = m_solitaire.reqDessusPile(p_pileDestination);
			if (dessusColonne.reqSorte() == dessusPile.reqSorte())
			{
				if (dessusColonne.estSuivante(dessusPile))
				{
					return true;
				}
			}
		}
		else
		{
			if (dessusColonne.reqValeur() == AS)
			{
				return true;
			}
		}
	}
	return false;
}

const bool validerMouvementColonneVersColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nombreCarte)
{
	PRECONDITION(p_colonneSource >=0);
	PRECONDITION(p_colonneSource <=6);
	PRECONDITION(p_colonneDestination >=0);
	PRECONDITION(p_colonneDestination <=6);
	PRECONDITION(p_nombreCarte > 0);
	PRECONDITION(p_nombreCarte <=13);

	if (p_nombreCarte <= m_solitaire.reqNombreCartesVisibles(p_colonneSource))
	{
		if (!m_solitaire.estVideColonne(p_colonneSource))
		{
			const Carte& dessousColonneSource = m_solitaire.reqCartePositionColonne(p_colonneSource, p_nombreCarte);

			if (!m_solitaire.estVideColonne(p_colonneDestination))
			{
				const Carte& dessusColonneDestination = m_solitaire.reqDessusColonne(p_colonneDestination);
				if (!dessusColonneDestination.estMemeCouleur(dessousColonneSource))
				{
					if (dessusColonneDestination.estSuivante(dessousColonneSource))
					{
						return true;
					}
				}
			}
			else
			{
				if (dessousColonneSource.reqValeur() == ROI)
				{
					return true;
				}
			}
		}
	}
	return false;
}

const int menuSelectionnerColonneSource()
{
	return afficherSousMenuAvecSelection("Entrer le numero de la colonne d'origine", 0, 6, 1);
}

const int menuSelectionnerColonneDestination()
{
	return afficherSousMenuAvecSelection("Entrer le numero de la colonne destination", 0, 6, 1);
}

const int menuSelectionnerPileDestination()
{
	return afficherSousMenuAvecSelection("Entrer le numero de la pile destination", 0, 3, 1);
}

const int menuSelectionnerNombreCartes()
{
	return afficherSousMenuAvecSelection("Entrer le numero le nombre de carte a déplacer", 1, 13, 2);
}

const void menuDeplacerCarteTalonVersColonne()
{
	int colonneDestination = menuSelectionnerColonneDestination();
	if (colonneDestination != -1)
	{
		if (validerMouvementTalonVersColonne(colonneDestination))
		{
			m_solitaire.deplacerTalonAColonne(colonneDestination);
		}
		else
		{
			afficherMessageCoupNonValide();
		}
	}
}

const void menuDeplacerCarteTalonVersPile()
{
	int pileDestination = menuSelectionnerPileDestination();
	if (pileDestination != -1)
	{
		if (validerMouvementTalonVersPile(pileDestination))
		{
			m_solitaire.deplacerTalonAPile(pileDestination);
		}
		else
		{
			afficherMessageCoupNonValide();
		}
	}
}

const void menuDeplacerCarteColonneVersColonne()
{
	int colonneSource = menuSelectionnerColonneSource();
	if (colonneSource != -1)
	{
		int colonneDestination = menuSelectionnerColonneDestination();
		if (colonneDestination != -1)
		{
			int nombreCartes = menuSelectionnerNombreCartes();
			if (nombreCartes != -1)
			{
				if (validerMouvementColonneVersColonne(colonneSource, colonneDestination, nombreCartes))
				{
					m_solitaire.deplacerColonneAColonne(colonneSource, colonneDestination, nombreCartes);
				}
				else
				{
					afficherMessageCoupNonValide();
				}
			}
		}
	}
}

const void menuDeplacerCarteColonneVersPile()
{
	int colonneSource = menuSelectionnerColonneSource();
	if (colonneSource != -1)
	{
		int pileDestination = menuSelectionnerPileDestination();
		if (pileDestination != -1)
		{
			if (validerMouvementColonneVersPile(colonneSource, pileDestination))
			{
				m_solitaire.deplacerColonneAPile(colonneSource, pileDestination);
			}
			else
			{
				afficherMessageCoupNonValide();
			}
		}
	}
}


int main()
{
	m_solitaire = Solitaire();
	bool termine = false;
	while (!termine)
	{
		while (!m_solitaire.verifieGagne() && !termine)
		{
			std::cout << m_solitaire  <<"\n";
			std::cout << m_menu;
			std::string reponse;
			std::getline (std::cin, reponse);
			if (reponse == "1")
			{
				if (!m_solitaire.estVideTalon())
				{
					m_solitaire.avancerTalon();
				}
				else
				{
					afficherMessageCoupNonValide();
				}
			}
			else if (reponse == "2")
			{
				menuDeplacerCarteTalonVersColonne();
			}
			else if (reponse == "3")
			{
				menuDeplacerCarteTalonVersPile();
			}
			else if (reponse == "4")
			{
				menuDeplacerCarteColonneVersColonne();
			}
			else if (reponse == "5")
			{
				menuDeplacerCarteColonneVersPile();
			}
			else if (reponse == "6")
			{
				termine=true;
			}
			else
			{
				std::cout << "Choix invalide \n\n";
			}
		}
		if (!termine)
		{
			termine = afficherMessageSucces();
			if (!termine)
			{
				m_solitaire = Solitaire();
			}
		}
	}
}