/*
 * Solitaire.h
 *
 *  Created on: 2015-09-24
 *      Author: Raphaël Sylvain (111 124 564)
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
	* @brief Cette méthode fait avancer le talon.
	*/
	void avancerTalon();

	/**
	* @brief Cette méthode déplace un nombre de carte d'une colonne vers une autre.
	* @param p_colonneSource Le numéro de la colonne sur laquelle prélever les Cartes.
	* @param p_colonneDestination Le numéro de la colonne sur laquelle poser les Cartes.
	* @brief p_nbCarte Le nombre de carte à déplacer.
	*/
	void deplacerColonneAColonne(const int p_colonneSource, const int p_colonneDestination, const int p_nbCartes);

	/**
	* @brief Cette méthode prend la carte sur le dessus du talon et la déplace sur une colonne.
	* @param p_colonneDestination Le numéro de la colonne sur laquelle déplacer la carte du talon.	*
	*/
	void deplacerTalonAColonne (const int p_colonneDestination);

	/**
	* @brief Cette méthode prend la carte sur le dessus du talon et la déplace sur une pile.
	* @param p_pileDestination Le numéro de la pile sur laquelle déplacer la carte du talon.	*
	*/
	void deplacerTalonAPile (const int p_pileDestination);

	/**
	* @brief Cette méthode déplace une carte d'une colonne vers une pile
	* @param p_colonneSource Le numéro de la colonne sur laquelle prélever les Cartes.
	* @param p_pileDestination Le numéro de la pile sur laquelle poser les Cartes.
	*/
	void deplacerColonneAPile (const int p_colonneSource, const int p_pileDestination);

	/**
	* @brief Cette méthode indique si la partie est terminée.
	* @return Vrai si toutes les Cartes sont placées sur les piles, sinon faux.
	*/
	bool verifieGagne() const;

	/**
	* @brief Cette méthode retourne sous le forme de string affichable la table de jeu.
	* @return L'état du jeu (Talon, Piles et Colonnes) sous la forme d'une string formattée.
	*/
	std::string reqEtatJeu () const;

	/**
	* @brief Surcharge de l'opérateur << qui fait l'affichage du Solitaire.
	* @param p_sortie Une référence vers l'objet ostream de l'opérateur <<
	* @param p_carte Une référence constante vers le Solitaire
	* @return L'état du jeu Solitaire
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const Solitaire& p_solitaire);
	
	/**
	* @brief Cette méthode retourne le talon.
	* @return Une référence constante vers le talon.
	*/
	const std::deque<Carte>& reqTalon() const;

	/**
	* @brief Cette méthode retourne une ColonneCartes selon un numéro en paramètre.
	* @param p_numeroColonne Le numéro de la ColonneCartes désirée
	* @return Une référence constante vers une ColonneCarte
	*/
	const ColonneCartes& reqColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette méthode retourne une pile selon un numéro en paramètre.
	* @param p_numeroPile Le numéro de la pile désirée
	* @return Une référence constante vers une pile
	*/
	const std::stack<Carte>& reqPile(const int p_numeroPile) const;

	/**
	* @brief Cette méthode indique si une ColonneCartes est vide selon un numéro en paramètre.
	* @param p_numeroColonne Le numéro de la ColonneCartes désirée
	* @return Vrai si la ColonneCartes est vide, sinon faux.
	*/
	const bool estVideColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette méthode indique si le talon est vide.
	* @return Vrai si le talon est vide, sinon faux.
	*/
	const bool estVideTalon() const;

	/**
	* @brief Cette méthode indique si une pile est vide selon un numéro en paramètre.
	* @param p_numeroPile Le numéro de la pile désirée
	* @return Vrai si la pile est vide, sinon faux.
	*/
	const bool estVidePile(const int p_numeroPile) const;

	/**
	* @brief Cette méthode fourni le nombre de carte visible sur une ColonneCartes selon un numéro en paramètre.
	* @param p_numeroPile Le numéro de la ColonneCartes désirée
	* @return Le nombre de cartes visibles de la ColonneCartes
	*/
	const int reqNombreCartesVisibles(const int p_numeroColonne) const;
	
	/**
	* @brief Cette méthode donne la Carte sur le dessus d'une pile selon un numéro en paramètre
	* @param p_numeroPile Le numéro de la pile désirée
	* @return Une référence constante vers la Carte sur le dessus de la pile.
	*/
	const Carte& reqDessusPile(const int p_numeroPile) const;

	/**
	* @brief Cette méthode donne la Carte sur le dessus du talon
	* @return Une référence constante vers la Carte sur le dessus du talon.
	*/
	const Carte& reqDessusTalon() const;

	/**
	* @brief Cette méthode donne la Carte sur le dessus d'une ColonneCartes selon un numéro en paramètre
	* @param p_numeroColonne Le numéro de la ColonneCartes désirée
	* @return Une référence constante vers la Carte sur le dessus de la ColonneCarte.
	*/
	const Carte& reqDessusColonne(const int p_numeroColonne) const;

	/**
	* @brief Cette méthode donne la Carte situé à une position en paramètre d'une ColonneCartes selon un numéro en paramètre
	* @param p_numeroColonne Le numéro de la pile désirée
	* @param p_positionCarte La position de la carte désirée dans la colonne carte. 1 étant le dessus.
	* @return Une référence constante vers la Carte à la position donnée de la ColonneCartes
	*/
	const Carte& reqCartePositionColonne(const int p_numeroColonne, const int p_positionCarte) const;

private:
	std::deque<Carte> m_talon;
	ColonneCartes m_colonnes[7];
	std::stack<Carte> m_piles[4];

	/**
	* @brief Cette fonction sert à initialiser le talon.
	*/
	void initialiserTalon();
	/**
	* @brief Cette fonction sert à initialiser les ColonneCartes.
	*/
	void initialiserColonnes();
};



#endif /* SOLITAIRE_H_ */
