/*
* ColonneCartes.h
*
*  Created on: 2015-09-24
*      Author: Raphaël Sylvain (111 124 564)
*/

#ifndef COLONNECARTES_H_
#define COLONNECARTES_H_

#include <vector>

#include "Carte.h"

class ColonneCartes
{
public:
	/**
	* @brief Constructeur d'une colonne de carte.
	*/
	ColonneCartes();

	/**
	* @brief Initialise ColonneCarte avec les Cartes contenus dans le vecteur en paramètre.
	* @param p_listeCarte Les Cartes avec lesquels initialiser la ColonneCarte
	*/
	void initColonneCartes (std::vector<Carte>& p_listeCartes);

	/**
	* @brief Cette méthode ajoute une Carte à la fin de colonne carte.
	* @param p_carte La Carte à ajouter à la fin de la colonne.
	*/
	void ajoute (const Carte& p_carte);

	/**
	* @brief Cette méthode prend des cartes de la colonne et les déplaces à la suite d'une autre colonne.
	* @param p_destination La ColonneCarte sur laquelle ajouter les cartes déplacés.
	* @param p_nombreCartes La quantité de carte à déplacer.
	*/
	void deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes);

	/**
	* @brief Cette méthode supprime la dernière Carte qui est sur le dessus de la ColonneCarte
	*/
	void supprimeDerniereCarte ();

	/**
	* @brief Cette méthode retourne le nombre de carte qui sont visible sur la colonne.
	* @return Le nombre de carte visible en constante.
	*/
	const int reqNbCartesVisibles () const;

	/**
	* @brief Surcharge de l'opérateur << qui fait l'affichage d'une ColonneCarte
	* @param p_sortie Une référence vers l'objet ostream de l'opérateur <<
	* @param p_carte Une référence constante vers une ColonneCarte
	* @return Un ostream représentant la ColonneCarte
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const ColonneCartes& p_colonneCartes);

	/**
	* @brief Cette fonction retourne les Cartes composant la ColonneCarte
	* @return Une référence constante d'un vecteur contant les Cartes de la ColonneCarte.
	*/
	const std::vector<Carte>& reqLesCartes() const;

	/**
	* @brief Cette méthode retourne la carte qui est sur le dessus de la ColonneCarte
	* @return Une référence constante vers la Carte qui est sur le dessus de la ColonneCarte.
	*/
	const Carte& reqCarteDessus() const;

	/**
	* @brief Cette méthode retourne la carte situé à une position donnée du début du paquet.
	* @param p_position La position à partir du début de la Carte désirée. Le dessus = 1.
	* @return Une référence constante vers la Carte situé à une position donnée de la ColonneCarte
	*/
	const Carte& reqCartePosition(const int p_position) const;

	/**
	* @brief Cette méthode indique si la ColonneCarte n'a aucune Carte.
	* @return Vrai si aucune Carte n'est présent dans la ColonneCarte, sinon faux.
	*/
	const bool estVide() const;
private:
	int m_nbCartesVisibles;
	std::vector<Carte> m_lesCartes;
	
	/**
	* @brief Cette méthode retourne la carte qui est sur le dessus de la ColonneCarte
	* @return Une référence vers la Carte qui est sur le dessus de la ColonneCarte.
	*/
	Carte& reqCarteDessus();

	/**
	* @brief Cette méthode retourne la carte situé à une position donnée du début du paquet.
	* @param p_position La position à partir du début de la Carte désirée. Le dessus = 1.
	* @return Une référence vers la Carte situé à une position donnée de la ColonneCarte
	*/
	Carte& reqCartePosition(const int p_position);

	/**
	* @brief Cette méthode change le nombre de carte selon un terme donné en paramètre.
	* @param p_diffenrenceNbCarte La différence de carte à effectuer
	*/
	void changerNombreCarteVisible(const int p_differenceNbCarte);
};



#endif /* COLONNECARTES_H_ */
