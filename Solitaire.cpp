/*
* Solitaire.cpp
*
*  Created on: 2015-09-24
*      Author: Raphaël Sylvain (111 124 564)
*/

#include "Solitaire.h"
/**
* @brief Constructeur de Solitaire
* Il y a premièrement l'initialisation du talon qui est fait, suivi de celle des colonnes.
*/
Solitaire::Solitaire()
{
	this->initialiserTalon();
	this->initialiserColonnes();
}
/**
* @brief Cette méthode fait avancer le talon.
* Pour pouvoir appeler cette méthode, il faut qu'il y ait au moins une carte dans le talon.
* Si ce n'est pas le cas, une erreur de précondition est lancée.
* Cette méthode va prendre la carte à la première position et va la mettre à la fin, faisant avancer le reste du talon.
*/
void Solitaire::avancerTalon()
{
	PRECONDITION(this->m_talon.size() > 0);
	std::rotate(this->m_talon.begin(), this->m_talon.end() - 1, this->m_talon.end());
}

/**
* @brief Cette méthode déplace un nombre de carte d'une colonne vers une autre.
* @param p_colonneSource Le numéro de la colonne sur laquelle prélever les Cartes.
* @param p_colonneDestination Le numéro de la colonne sur laquelle poser les Cartes.
* @brief p_nbCarte Le nombre de carte à déplacer.
* Plusieurs conditions sont a respecter pour faire fonctionner cette méthode.
* Il faut que le nombre en paramètre pour le numéro de colonne soit entre 0 et 6.
* Il faut aussi qu'il y ait au moins le nombre de carte visible sur le paquet source que le nombre de carte à déplacer.
* Le coup désiré doit aussi être valide selon les règles du Klondike.
* Si l'une de ces conditions n'est pas respectée, une erreur de précondition est lancée.
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
* @brief Cette méthode prend la carte sur le dessus du talon et la déplace sur une colonne.
* @param p_colonneDestination Le numéro de la colonne sur laquelle déplacer la carte du talon.
* Plusieurs conditions sont a respecter pour faire fonctionner cette méthode.
* Il faut que le nombre en paramètre pour le numéro de colonne soit entre 0 et 6.
* Il faut qu'il y ait au moins une carte dans le talon.
* Le coup désiré doit aussi être valide selon les règles du Klondike.
* Si l'une de ces conditions n'est pas respectée, une erreur de précondition est lancée.
* La carte du talon est ajoutée sur la colonne avant d'être retirée du talon.
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
* @brief Cette méthode prend la carte sur le dessus du talon et la déplace sur une pile.
* @param p_pileDestination Le numéro de la pile sur laquelle déplacer la carte du talon.
* Plusieurs conditions sont a respecter pour faire fonctionner cette méthode.
* Il faut que le nombre en paramètre pour le numéro de pile soit entre 0 et 3u.
* Il faut qu'il y ait au moins une carte dans le talon.
* Le coup désiré doit aussi être valide selon les règles du Klondike.
* Si l'une de ces conditions n'est pas respectée, une erreur de précondition est lancée.
* La carte du talon est ajoutée sur la colonne avant d'être retirée du talon.
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
* @brief Cette méthode déplace une carte d'une colonne vers une pile
* @param p_colonneSource Le numéro de la colonne sur laquelle prélever les Cartes.
* @param p_pileDestination Le numéro de la pile sur laquelle poser les Cartes.
* Plusieurs conditions sont a respecter pour faire fonctionner cette méthode.
* Il faut que le nombre en paramètre pour le numéro de colonne soit entre 0 et 6.
* Il faut que le nombre en paramètre pour le numéro de la pile soit entre 0 et 3.
* Le coup désiré doit aussi être valide selon les règles du Klondike.
* Si l'une de ces conditions n'est pas respectée, une erreur de précondition est lancée.
* La carte de la colonne est ajoutée sur la pile avant d'être retirée de la colonne.
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
* @brief Cette méthode indique si la partie est terminée.
* @return Vrai si toutes les Cartes sont placées sur les piles, sinon faux.
* Cette méthode regarde si chacune des 4 piles ont 13 cartes.
* Si l'application a respectée les règles du Klondike, si 13 cartes sont sur chaque pile, la partie est gagnée.
*/
bool Solitaire::verifieGagne() const
{
	return (this->m_piles[0].size() == 13) &&
		(this->m_piles[1].size() == 13) &&
		(this->m_piles[2].size() == 13) &&
		(this->m_piles[3].size() == 13);
}


/**
* @brief Cette méthode retourne sous le forme de string affichable la table de jeu.
* @return L'état du jeu (Talon, Piles et Colonnes) sous la forme d'une string formattée.
* Le format de la string retournée est :
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
* @brief Surcharge de l'opérateur << qui fait l'affichage du Solitaire.
* @param p_sortie Une référence vers l'objet ostream de l'opérateur <<
* @param p_carte Une référence constante vers le Solitaire
* @return L'état du jeu Solitaire
* @see Solitaire.reqEtatJeu()
*/
std::ostream& operator<< (std::ostream& p_sortie, const Solitaire& p_solitaire)
{
	p_sortie << p_solitaire.reqEtatJeu();
	return p_sortie;
}

/**
* @brief Cette fonction sert à initialiser le talon.
* Cette méthode crée un paquet de carte complet (13 cartes pour chaque 4 sortes), puis le mélange.
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
* @brief Cette fonction sert à initialiser les ColonneCartes.
* Pour initialiser chacune des colonnes, cette méthode va piger les cartes dans le talon,
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

/**
* @brief Cette méthode retourne le talon.
* @return Une référence constante vers le talon.
*/
const std::deque<Carte>& Solitaire::reqTalon() const
{
	return this->m_talon;
}

/**
* @brief Cette méthode retourne une ColonneCartes selon un numéro en paramètre.
* @param p_numeroColonne Le numéro de la ColonneCartes désirée
* @return Une référence constante vers une ColonneCarte
* Cette méthode s'attend que le numéro de colonne en paramètre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de précondition est lancée.
*/
const ColonneCartes& Solitaire::reqColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);

	return this->m_colonnes[p_numeroColonne];
}
/**
* @brief Cette méthode retourne une pile selon un numéro en paramètre.
* @param p_numeroPile Le numéro de la pile désirée
* @return Une référence constante vers une pile
* Cette méthode s'attend que le numéro de la pile en paramètre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de précondition est lancée.
*/
const std::stack<Carte>& Solitaire::reqPile(const int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile];
}

/**
* @brief Cette méthode donne la Carte sur le dessus d'une pile selon un numéro en paramètre
* @param p_numeroPile Le numéro de la pile désirée
* @return Une référence constante vers la Carte sur le dessus de la pile.
* Cette méthode s'attend que le numéro de la pile en paramètre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de précondition est lancée.
*/
const Carte& Solitaire::reqDessusPile(int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);

	return this->m_piles[p_numeroPile].top();
}

/**
* @brief Cette méthode donne la Carte sur le dessus du talon
* @return Une référence constante vers la Carte sur le dessus du talon.
*/
const Carte& Solitaire::reqDessusTalon() const
{
	return this->m_talon.front();
}

/**
* @brief Cette méthode donne la Carte sur le dessus d'une ColonneCartes selon un numéro en paramètre
* @param p_numeroColonne Le numéro de la ColonneCartes désirée
* @return Une référence constante vers la Carte sur le dessus de la ColonneCarte.
* Cette méthode s'attend que le numéro de la colonne en paramètre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de précondition est lancée.
* @see ColonnesCartes.reqCarteDessus()
*/
const Carte& Solitaire::reqDessusColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	return this->m_colonnes[p_numeroColonne].reqCarteDessus();
}

/**
* @brief Cette méthode donne la Carte situé à une position en paramètre d'une ColonneCartes selon un numéro en paramètre
* @param p_numeroColonne Le numéro de la pile désirée
* @param p_positionCarte La position de la carte désirée dans la colonne carte. 1 étant le dessus.
* @return Une référence constante vers la Carte à la position donnée de la ColonneCartes
* Cette méthode s'attend que le numéro de la colonne en paramètre soit entre 0 et 6.
* Elle s'attend aussi que la position demandée soit inférieure ou égale au nombre de carte visible.
* Si ce n'est pas le cas une erreur de précondition est lancée.
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
* @brief Cette méthode indique si une ColonneCartes est vide selon un numéro en paramètre.
* @param p_numeroColonne Le numéro de la ColonneCartes désirée
* @return Vrai si la ColonneCartes est vide, sinon faux.k
* Cette méthode s'attend que le numéro de la colonne en paramètre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de précondition est lancée.
* @see ColonneCartes.estVide()
*/
const bool Solitaire::estVideColonne(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);
	return this->reqColonne(p_numeroColonne).estVide();
}

/**
* @brief Cette méthode indique si le talon est vide.
* @return Vrai si le talon est vide, sinon faux.
*/
const bool Solitaire::estVideTalon() const
{
	return this->reqTalon().size() == 0;
}

/**
* @brief Cette méthode indique si une pile est vide selon un numéro en paramètre.
* @param p_numeroPile Le numéro de la pile désirée
* @return Vrai si la pile est vide, sinon faux.
* Cette méthode s'attend que le numéro de la pile en paramètre soit entre 0 et 3.
* Si ce n'est pas le cas une erreur de précondition est lancée.
*/
const bool Solitaire::estVidePile(const int p_numeroPile) const
{
	PRECONDITION(p_numeroPile >= 0);
	PRECONDITION(p_numeroPile <= 3);
	return this->reqPile(p_numeroPile).size() == 0;
}

/**
* @brief Cette méthode fourni le nombre de carte visible sur une ColonneCartes selon un numéro en paramètre.
* @param p_numeroPile Le numéro de la ColonneCartes désirée
* @return Le nombre de cartes visibles de la ColonneCartes
* Cette méthode s'attend que le numéro de la colonne en paramètre soit entre 0 et 6.
* Si ce n'est pas le cas une erreur de précondition est lancée.
* @see ColonneCartes.reqNbCartesVisibles()
*/
const int Solitaire::reqNombreCartesVisibles(const int p_numeroColonne) const
{
	PRECONDITION(p_numeroColonne >= 0);
	PRECONDITION(p_numeroColonne <= 6);

	return this->reqColonne(p_numeroColonne).reqNbCartesVisibles();
}
