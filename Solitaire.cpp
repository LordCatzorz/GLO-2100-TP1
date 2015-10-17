/*
* Solitaire.cpp
*
*  Created on: 2015-09-24
*      Author: Rapha�l Sylvain (111 124 564)
*/

#include "Solitaire.h"
/**
* Il y a premi�rement l'initialisation du talon qui est fait, suivi de celle des colonnes.
*/
Solitaire::Solitaire()
{
	this->initialiserTalon();
	this->initialiserColonnes();
}
/**
* Pour pouvoir appeler cette m�thode, il faut qu'il y ait au moins une carte dans le talon.
* Si ce n'est pas le cas, une erreur de pr�condition est lanc�e.
* Cette m�thode va prendre la carte � la premi�re position et va la mettre � la fin, faisant avancer le reste du talon.
*/
void Solitaire::avancerTalon()
{
	PRECONDITION(this->m_talon.size() > 0);
	std::rotate(this->m_talon.begin(), this->m_talon.end() - 1, this->m_talon.end());
}

/**
* Plusieurs conditions sont a respecter pour faire fonctionner cette m�thode.
* Il faut que le nombre en param�tre pour le num�ro de colonne soit entre 0 et 6.
* Il faut aussi qu'il y ait au moins le nombre de carte visible sur le paquet source que le nombre de carte � d�placer.
* Le coup d�sir� doit aussi �tre valide selon les r�gles du Klondike.
* Si l'une de ces conditions n'est pas respect�e, une erreur de pr�condition est lanc�e.
* @see ColonneCartes.deplacePaquet()
*/
void Solitaire::deplacerColonneAColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nbCartes)
{
	PRECONDITION(p_colonneSource >= 0);
	PRECONDITION(p_colonneDestination >= 0);
	PRECONDITION(p_nbCartes > 0);
	PRECONDITION(p_colonneSource <= 6);
	PRECONDITION(p_colonneDestination <= 6);
	PRECONDITION(this->m_colonnes[p_colonneSource].reqNbCartesVisibles() >= p_nbCartes);
	PRECONDITION(this->reqColonne(p_colonneDestination).estVide() || !this->reqDessusColonne(p_colonneDestination).estMemeCouleur(this->reqCartePositionColonne(p_colonneSource, p_nbCartes)));
	PRECONDITION(this->reqColonne(p_colonneDestination).estVide() || this->reqDessusColonne(p_colonneDestination).estSuivante(this->reqCartePositionColonne(p_colonneSource, p_nbCartes)));
	PRECONDITION(!this->reqColonne(p_colonneDestination).estVide() || this->reqCartePositionColonne(p_colonneSource, p_nbCartes).reqValeur() == ROI);

	this->m_colonnes[p_colonneSource].deplacePaquet(this->m_colonnes[p_colonneDestination], p_nbCartes);
}

/**
* Plusieurs conditions sont a respecter pour faire fonctionner cette m�thode.
* Il faut que le nombre en param�tre pour le num�ro de colonne soit entre 0 et 6.
* Il faut qu'il y ait au moins une carte dans le talon.
* Le coup d�sir� doit aussi �tre valide selon les r�gles du Klondike.
* Si l'une de ces conditions n'est pas respect�e, une erreur de pr�condition est lanc�e.
* La carte du talon est ajout�e sur la colonne avant d'�tre retir�e du talon.
* @see ColonneCartes.ajoute()
*/
void Solitaire::deplacerTalonAColonne (const int p_colonneDestination)
{
	PRECONDITION(p_colonneDestination >= 0);
	PRECONDITION(p_colonneDestination <= 6);
	PRECONDITION(!this->estVideTalon());
	PRECONDITION(this->reqColonne(p_colonneDestination).estVide() || !this->reqDessusTalon().estMemeCouleur(this->reqDessusColonne(p_colonneDestination)));
	PRECONDITION(this->reqColonne(p_colonneDestination).estVide() || this->reqDessusColonne(p_colonneDestination).estSuivante(this->reqDessusTalon()));
	PRECONDITION(!this->reqColonne(p_colonneDestination).estVide() || this->reqDessusTalon().reqValeur() == ROI);

	this->m_colonnes[p_colonneDestination].ajoute(this->m_talon.front());
	this->m_talon.pop_front();
}

/**
* Plusieurs conditions sont a respecter pour faire fonctionner cette m�thode.
* Il faut que le nombre en param�tre pour le num�ro de pile soit entre 0 et 3u.
* Il faut qu'il y ait au moins une carte dans le talon.
* Le coup d�sir� doit aussi �tre valide selon les r�gles du Klondike.
* Si l'une de ces conditions n'est pas respect�e, une erreur de pr�condition est lanc�e.
* La carte du talon est ajout�e sur la colonne avant d'�tre retir�e du talon.
* @see ColonneCartes.ajoute()
*/
void Solitaire::deplacerTalonAPile (const int p_pileDestination)
{
	PRECONDITION(p_pileDestination >= 0);
	PRECONDITION(p_pileDestination <= 3);
	PRECONDITION(!this->estVideTalon());
	PRECONDITION(this->estVidePile(p_pileDestination) || this->reqDessusTalon().estMemeCouleur(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(this->estVidePile(p_pileDestination) || this->reqDessusTalon().estSuivante(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(!this->estVidePile(p_pileDestination) || this->reqDessusTalon().reqValeur() == AS);

	this->m_piles[p_pileDestination].push(this->reqDessusTalon());
	this->m_talon.pop_front();
}


/**
* Plusieurs conditions sont a respecter pour faire fonctionner cette m�thode.
* Il faut que le nombre en param�tre pour le num�ro de colonne soit entre 0 et 6.
* Il faut que le nombre en param�tre pour le num�ro de la pile soit entre 0 et 3.
* Le coup d�sir� doit aussi �tre valide selon les r�gles du Klondike.
* Si l'une de ces conditions n'est pas respect�e, une erreur de pr�condition est lanc�e.
* La carte de la colonne est ajout�e sur la pile avant d'�tre retir�e de la colonne.
* @see ColonneCartes.supprimeDerniereCarte();
*/
void Solitaire::deplacerColonneAPile (const int p_colonneSource, const int p_pileDestination)
{
	PRECONDITION(p_pileDestination >= 0);
	PRECONDITION(p_pileDestination <= 3);
	PRECONDITION(p_colonneSource >= 0);
	PRECONDITION(p_colonneSource <= 6);
	PRECONDITION(!this->estVideColonne(p_colonneSource));
	PRECONDITION(this->estVidePile(p_pileDestination) || this->reqDessusColonne(p_colonneSource).estMemeCouleur(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(this->estVidePile(p_pileDestination) || this->reqDessusColonne(p_colonneSource).estSuivante(this->reqDessusPile(p_pileDestination)));
	PRECONDITION(!this->estVidePile(p_pileDestination) ||	this->reqDessusColonne(p_colonneSource).reqValeur() == AS);

	this->m_piles[p_pileDestination].push(this->reqDessusColonne(p_colonneSource));
	this->m_colonnes[p_colonneSource].supprimeDerniereCarte();
}

/**
* Cette m�thode regarde si chacune des 4 piles ont 13 cartes.
* Si l'application a respect�e les r�gles du Klondike, si 13 cartes sont sur chaque pile, la partie est gagn�e.
*/
bool Solitaire::verifieGagne() const
{
	return (this->m_piles[0].size() == 13) &&
		(this->m_piles[1].size() == 13) &&
		(this->m_piles[2].size() == 13) &&
		(this->m_piles[3].size() == 13);
}


/**
* Le format de la string retourn�e est :
*   TALON				PILE1	PILE2	PILE3	PILE4
*	
*	COLONNE1
*	COLONNE2
*	COLONNE3
*	COLONNE4
*	COLONNE5
*	COLONNE6
*	COLONNE7
*
*/
std::string Solitaire::reqEtatJeu () const
{
	std::ostringstream etatJeu;
	//Talon
	etatJeu << "Talon: ";
	if (this->estVideTalon())
	{
		etatJeu << "X";
	}
	else
	{ 
		etatJeu << this->m_talon.front();
	}

	//Pile
	etatJeu << "             Piles ";
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (this->m_piles[i].size() == 0)
		{
			etatJeu << "   X  ";
		}
		else
		{
			etatJeu <<" " << this->m_piles[i].top()<< " ";
		}
	}
	etatJeu << std::endl << std::endl;

	//Colonnes
	for (unsigned int i = 0 ; i < 7; ++i)
	{
		etatJeu << "Col." << i << ": " << this->m_colonnes[i] << std::endl;
	}

	return etatJeu.str();
}

/**
* @see Solitaire.reqEtatJeu()
*/
std::ostream& operator<< (std::ostream& p_sortie, const Solitaire& p_solitaire)
{
	p_sortie << p_solitaire.reqEtatJeu();
	return p_sortie;
}

/**
* Cette m�thode cr�e un paquet de carte complet (13 cartes pour chaque 4 sortes), puis le m�lange.
*/
void Solitaire::initialiserTalon()
{

	for (unsigned int i = 1; i < 5; i++) // Sortes
	{
		for (unsigned int j = 1; j < 14; j++) // Valeurs
		{
			Carte carte((Valeur) j, (Sorte) i);
			this->m_talon.push_back(carte);
		}
	}
	srand((unsigned int)time(0));

	std::random_shuffle(this->m_talon.begin(), this->m_talon.end());
}

/**
* Pour initialiser chacune des colonnes, cette m�thode va piger les cartes dans le talon,
* puis va mettre ces cartes au-dessus d'une colonne.
* @see ColonneCartes.initColonneCartes
*/
void Solitaire::initialiserColonnes()
{
	for (unsigned int i = 0; i < 7; ++i)
	{
		this->m_colonnes[i] = ColonneCartes();

		const std::deque<Carte>::iterator finSousDeque = this->m_talon.begin() + i + 1;
		std::vector<Carte> carteDeColonne = std::vector<Carte>(this->m_talon.begin(), finSousDeque);
		this->m_colonnes[i].initColonneCartes(carteDeColonne);
		for (unsigned int j = 0; j < i+1; j++)
		{
			this->m_talon.pop_front();
		}
	}
}


const std::deque<Carte>& Solitaire::reqTalon() const
{
	return this->m_talon;
}

/**
* Cette m�thode s'attend que le num�ro de colonne en param�tre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
*/
const ColonneCartes& Solitaire::reqColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);

	return this->m_colonnes[p_numeroColonne];
}
/**
* Cette m�thode s'attend que le num�ro de la pile en param�tre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
*/
const std::stack<Carte>& Solitaire::reqPile(const int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile];
}

/**
* Cette m�thode s'attend que le num�ro de la pile en param�tre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
*/
const Carte& Solitaire::reqDessusPile(int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile].top();
}

const Carte& Solitaire::reqDessusTalon() const
{
	return this->m_talon.front();
}

/**
* Cette m�thode s'attend que le num�ro de la colonne en param�tre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
* @see ColonnesCartes.reqCarteDessus()
*/
const Carte& Solitaire::reqDessusColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	return this->m_colonnes[p_numeroColonne].reqCarteDessus();
}

/**
* Cette m�thode s'attend que le num�ro de la colonne en param�tre soit entre 0 et 6.
* Elle s'attend aussi que la position demand�e soit inf�rieure ou �gale au nombre de carte visible.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
* @see ColonneCartes.reqCartePosition()
*/
const Carte& Solitaire::reqCartePositionColonne(const int p_numeroColonne, const int p_position) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	PRECONDITION(p_position <= this->m_colonnes[p_numeroColonne].reqNbCartesVisibles());
	return this->m_colonnes[p_numeroColonne].reqCartePosition(p_position);
}

/**
* Cette m�thode s'attend que le num�ro de la colonne en param�tre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
* @see ColonneCartes.estVide()
*/
const bool Solitaire::estVideColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	return this->reqColonne(p_numeroColonne).estVide();
}

const bool Solitaire::estVideTalon() const
{
	return this->reqTalon().size() == 0;
}

/**
* Cette m�thode s'attend que le num�ro de la pile en param�tre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
*/
const bool Solitaire::estVidePile(const int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);
	return this->reqPile(p_numeroPile).size() == 0;
}

/**
* Cette m�thode s'attend que le num�ro de la colonne en param�tre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de pr�condition est lanc�e.
* @see ColonneCartes.reqNbCartesVisibles()
*/
const int Solitaire::reqNombreCartesVisibles(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);

	return this->reqColonne(p_numeroColonne).reqNbCartesVisibles();
}
