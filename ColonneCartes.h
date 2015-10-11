/*
* ColonneCartes.h
*
*  Created on: 2015-09-24
*      Author: Rapha�l Sylvain (111 124 564)
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
	* @brief Initialise ColonneCarte avec les Cartes contenus dans le vecteur en param�tre.
	* @param p_listeCarte Les Cartes avec lesquels initialiser la ColonneCarte
	*/
	void initColonneCartes (std::vector<Carte>& p_listeCartes);

	/**
	* @brief Cette m�thode ajoute une Carte � la fin de colonne carte.
	* @param p_carte La Carte � ajouter � la fin de la colonne.
	*/
	void ajoute (const Carte& p_carte);

	/**
	* @brief Cette m�thode prend des cartes de la colonne et les d�places � la suite d'une autre colonne.
	* @param p_destination La ColonneCarte sur laquelle ajouter les cartes d�plac�s.
	* @param p_nombreCartes La quantit� de carte � d�placer.
	*/
	void deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes);

	/**
	* @brief Cette m�thode supprime la derni�re Carte qui est sur le dessus de la ColonneCarte
	*/
	void supprimeDerniereCarte ();

	/**
	* @brief Cette m�thode retourne le nombre de carte qui sont visible sur la colonne.
	* @return Le nombre de carte visible en constante.
	*/
	const int reqNbCartesVisibles () const;

	/**
	* @brief Surcharge de l'op�rateur << qui fait l'affichage d'une ColonneCarte
	* @param p_sortie Une r�f�rence vers l'objet ostream de l'op�rateur <<
	* @param p_carte Une r�f�rence constante vers une ColonneCarte
	* @return Un ostream repr�sentant la ColonneCarte
	*/
	friend std::ostream& operator<< (std::ostream& p_sortie, const ColonneCartes& p_colonneCartes);

	/**
	* @brief Cette fonction retourne les Cartes composant la ColonneCarte
	* @return Une r�f�rence constante d'un vecteur contant les Cartes de la ColonneCarte.
	*/
	const std::vector<Carte>& reqLesCartes() const;

	/**
	* @brief Cette m�thode retourne la carte qui est sur le dessus de la ColonneCarte
	* @return Une r�f�rence constante vers la Carte qui est sur le dessus de la ColonneCarte.
	*/
	const Carte& reqCarteDessus() const;

	/**
	* @brief Cette m�thode retourne la carte situ� � une position donn�e du d�but du paquet.
	* @param p_position La position � partir du d�but de la Carte d�sir�e. Le dessus = 1.
	* @return Une r�f�rence constante vers la Carte situ� � une position donn�e de la ColonneCarte
	*/
	const Carte& reqCartePosition(const int p_position) const;

	/**
	* @brief Cette m�thode indique si la ColonneCarte n'a aucune Carte.
	* @return Vrai si aucune Carte n'est pr�sent dans la ColonneCarte, sinon faux.
	*/
	const bool estVide() const;
private:
	int m_nbCartesVisibles;
	std::vector<Carte> m_lesCartes;
	
	/**
	* @brief Cette m�thode retourne la carte qui est sur le dessus de la ColonneCarte
	* @return Une r�f�rence vers la Carte qui est sur le dessus de la ColonneCarte.
	*/
	Carte& reqCarteDessus();

	/**
	* @brief Cette m�thode retourne la carte situ� � une position donn�e du d�but du paquet.
	* @param p_position La position � partir du d�but de la Carte d�sir�e. Le dessus = 1.
	* @return Une r�f�rence vers la Carte situ� � une position donn�e de la ColonneCarte
	*/
	Carte& reqCartePosition(const int p_position);

	/**
	* @brief Cette m�thode change le nombre de carte selon un terme donn� en param�tre.
	* @param p_diffenrenceNbCarte La diff�rence de carte � effectuer
	*/
	void changerNombreCarteVisible(const int p_differenceNbCarte);
};



#endif /* COLONNECARTES_H_ */
