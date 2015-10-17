/*
 * Solitaire.h
 *
 *  Created on: 2015-09-24
 *      Author: Rapha�l Sylvain (111 124 564)
 */

#ifndef SOLITAIRE_H_
#define SOLITAIRE_H_

#include <queue>
#include <stack>
#include <algorithm>
#include <ctime>
#include <sstream>

#include "ColonneCartes.h"


class Solitaire
{
public:
	/**
	* @brief Constructeur de Solitaire
	*/
	Solitaire();

	/**
	* @brief Cette m�thode fait avancer le talon.
	*/
	void avancerTalon();

	/**
	* @brief Cette m�thode d�place un nombre de carte d'une colonne vers une autre.
	* @param p_colonneSource Le num�ro de la colonne sur laquelle pr�lever les Cartes.
	* @param p_colonneDestination Le num�ro de la colonne sur laquelle poser les Cartes.
	* @brief p_nbCarte Le nombre de carte � d�placer.
	*/
	void deplacerColonneAColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nbCartes);

	/**
	* @brief Cette m�thode prend la carte sur le dessus du talon et la d�place sur une colonne.
	* @param p_colonneDestination Le num�ro de la colonne sur laquelle d�placer la carte du talon.	*
	*/
	void deplacerTalonAColonne (const int p_colonneDestination);

	/**
	* @brief Cette m�thode prend la carte sur le dessus du talon et la d�place sur une pile.
	* @param p_pileDestination Le num�ro de la pile sur laquelle d�placer la carte du talon.	*
	*/
	void deplacerTalonAPile (const int p_pileDestination);

	/**
	* @brief Cette m�thode d�place une carte d'une colonne vers une pile
	* @param p_colonneSource Le num�ro de la colonne sur laquelle pr�lever les Cartes.
	* @param p_pileDestination Le num�ro de la pile sur laquelle poser les Cartes.
	*/
	void deplacerColonneAPile (const int p_colonneSource, const int p_pileDestination);

	/**
	* @brief Cette m�thode indique si la partie est termin�e.
	* @return Vrai si toutes les Cartes sont plac�es sur les piles, sinon faux.
	*/
	bool verifieGagne() const;

	/**
	* @brief Cette m�thode retourne sous le forme de string affichable la table de jeu.
	* @return L'�tat du jeu (Talon, Piles et Colonnes) sous la forme d'une string formatt�e.
	*/
	std::string reqEtatJeu () const;

	/**
	* @brief Surcharge de l'op�rateur << qui fait l'affichage du Solitaire.
	* @param p_sortie Une r�f�rence vers l'objet ostream de l'op�rateur <<
	* @param p_carte Une r�f�rence constante vers le Solitaire
	* @return L'�tat du jeu Solitaire
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const Solitaire& p_solitaire);
	
	/**
	* @brief Cette m�thode retourne le talon.
	* @return Une r�f�rence constante vers le talon.
	*/
	const std::deque<Carte>& reqTalon() const;

	/**
	* @brief Cette m�thode retourne une ColonneCartes selon un num�ro en param�tre.
	* @param p_numeroColonne Le num�ro de la ColonneCartes d�sir�e
	* @return Une r�f�rence constante vers une ColonneCarte
	*/
	const ColonneCartes& reqColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette m�thode retourne une pile selon un num�ro en param�tre.
	* @param p_numeroPile Le num�ro de la pile d�sir�e
	* @return Une r�f�rence constante vers une pile
	*/
	const std::stack<Carte>& reqPile(const int p_numeroPile) const;

	/**
	* @brief Cette m�thode indique si une ColonneCartes est vide selon un num�ro en param�tre.
	* @param p_numeroColonne Le num�ro de la ColonneCartes d�sir�e
	* @return Vrai si la ColonneCartes est vide, sinon faux.
	*/
	const bool estVideColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette m�thode indique si le talon est vide.
	* @return Vrai si le talon est vide, sinon faux.
	*/
	const bool estVideTalon() const;

	/**
	* @brief Cette m�thode indique si une pile est vide selon un num�ro en param�tre.
	* @param p_numeroPile Le num�ro de la pile d�sir�e
	* @return Vrai si la pile est vide, sinon faux.
	*/
	const bool estVidePile(const int p_numeroPile) const;

	/**
	* @brief Cette m�thode fourni le nombre de carte visible sur une ColonneCartes selon un num�ro en param�tre.
	* @param p_numeroPile Le num�ro de la ColonneCartes d�sir�e
	* @return Le nombre de cartes visibles de la ColonneCartes
	*/
	const int reqNombreCartesVisibles(const int p_numeroColonne) const;
	
	/**
	* @brief Cette m�thode donne la Carte sur le dessus d'une pile selon un num�ro en param�tre
	* @param p_numeroPile Le num�ro de la pile d�sir�e
	* @return Une r�f�rence constante vers la Carte sur le dessus de la pile.
	*/
	const Carte& reqDessusPile(const int p_numeroPile) const;

	/**
	* @brief Cette m�thode donne la Carte sur le dessus du talon
	* @return Une r�f�rence constante vers la Carte sur le dessus du talon.
	*/
	const Carte& reqDessusTalon() const;

	/**
	* @brief Cette m�thode donne la Carte sur le dessus d'une ColonneCartes selon un num�ro en param�tre
	* @param p_numeroColonne Le num�ro de la ColonneCartes d�sir�e
	* @return Une r�f�rence constante vers la Carte sur le dessus de la ColonneCarte.
	*/
	const Carte& reqDessusColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette m�thode donne la Carte situ� � une position en param�tre d'une ColonneCartes selon un num�ro en param�tre
	* @param p_numeroColonne Le num�ro de la pile d�sir�e
	* @param p_positionCarte La position de la carte d�sir�e dans la colonne carte. 1 �tant le dessus.
	* @return Une r�f�rence constante vers la Carte � la position donn�e de la ColonneCartes
	*/
	const Carte& reqCartePositionColonne(const int p_numeroColonne, const int p_positionCarte) const;

private:
	std::deque<Carte> m_talon;
	ColonneCartes m_colonnes[7];
	std::stack<Carte> m_piles[4];

	/**
	* @brief Cette fonction sert � initialiser le talon.
	*/
	void initialiserTalon();
	/**
	* @brief Cette fonction sert � initialiser les ColonneCartes.
	*/
	void initialiserColonnes();
};



#endif /* SOLITAIRE_H_ */
