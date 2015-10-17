/*
* ColonneCartes.cpp
*
*  Created on: 2015-09-24
*      Author: Raphaël Sylvain (111 124 564)
*/

#include "ColonneCartes.h"

/**
* @brief Constructeur d'une colonne de carte.
* Cette méthode crée une coquille pour une ColonneCarte.
* Elle initialise son vecteur de carte comme un vecteur vide.
*/
ColonneCartes::ColonneCartes()
{
	this->m_lesCartes = std::vector<Carte>();
}

/**
* @brief Initialise ColonneCarte avec les Cartes contenus dans le vecteur en paramètre.
* @param p_listeCarte Les Cartes avec lesquels initialiser la ColonneCarte
* Cette méthode vide le vecteur actuel de carte de la colonne carte pour
* le remplacer par le vecteur en paramètre. 
* Il va aussi remettre le nombre de carte visible à 1.
*/
void ColonneCartes::initColonneCartes (std::vector<Carte>& p_listeCartes)
{
	this->m_lesCartes.clear();
	this->m_lesCartes = p_listeCartes;
	this->m_nbCartesVisibles = 1;

	POSTCONDITION(this->m_lesCartes.size() == p_listeCartes.size());
	POSTCONDITION(this->m_lesCartes.size() >= this->m_nbCartesVisibles);
}

/**
* @brief Cette méthode ajoute une Carte à la fin de colonne carte.
* @param p_carte La Carte à ajouter à la fin de la colonne.
* Cette méthode s'attend à ajouter une carte qui lui est possible d'ajouter selon les règles du Klondike.
* Si la carte à ajouter n'est pas valide, une erreur de précondition est lancée.
* Cette méthode ajoute à la carte à la suite du vecteur et incrémente le nombre de carte visible.
*/
void ColonneCartes::ajoute (const Carte&  p_carte)
{
	PRECONDITION(this->estVide() || !this->reqCarteDessus().estMemeCouleur(p_carte));
	PRECONDITION(this->estVide() || this->reqCarteDessus().estSuivante(p_carte));
	PRECONDITION(!this->estVide() || p_carte.reqValeur() == ROI);

	this->m_lesCartes.push_back (p_carte);
	this->changerNombreCarteVisible(1);
}

/**
* @brief Cette méthode prend des cartes de la colonne et les déplaces à la suite d'une autre colonne.
* @param p_destination La ColonneCarte sur laquelle ajouter les cartes déplacés.
* @param p_nombreCartes La quantité de carte à déplacer.
* Cette méthode s'attend à avoir comme instruction d'effectuer un coup valide selon les règles du Klondike.
* Si ce n'est pas le cas, une erreur de précondition est lancée.
* Cette méthode boucle au travers de l'ensemble des cartes à déplacer et les ajoutes 1 à 1 sur la ColonneCarte destinations.
* Elle va par la suite supprimer 1 à 1 ses cartes qui sont maintenant déplacée.
* @see ColonneCartes.ajoute()
* @see ColonneCartes.supprimerDerniereCarte
*/
void ColonneCartes::deplacePaquet (ColonneCartes& p_destination, int p_nombreCartes)
{
	PRECONDITION(p_nombreCartes > 0);
	PRECONDITION(p_nombreCartes <= this->reqNbCartesVisibles());
	PRECONDITION(this->estVide() || !p_destination.reqCarteDessus().estMemeCouleur(this->reqCartePosition(p_nombreCartes)));
	PRECONDITION(this->estVide() || p_destination.reqCarteDessus().estSuivante(this->reqCartePosition(p_nombreCartes)));
	PRECONDITION(!this->estVide() || this->reqCartePosition(p_nombreCartes).reqValeur() == ROI);
	for (std::vector<Carte>::iterator iter = this->m_lesCartes.end() - p_nombreCartes; iter != this->m_lesCartes.end();iter++)
	{
		p_destination.ajoute(*iter);
	}
	for (unsigned int i = 0; i < p_nombreCartes; i++)
	{
		this->supprimeDerniereCarte();
	}
}

/**
* @brief Cette méthode supprime la dernière Carte qui est sur le dessus de la ColonneCarte
* Cette méthode s'attend à être appelée lorsqu'il y a encore au moins un carte.
* Si la colonne est vide, une erreur de précondition est lancée.
* Elle supprime la dernière carte, puis décrémente le nombre de carte visible.
*/
void ColonneCartes::supprimeDerniereCarte ()
{
	PRECONDITION(!this->estVide());
	this->m_lesCartes.pop_back();
	this->changerNombreCarteVisible(-1);
}

/**
* @brief Cette méthode retourne le nombre de carte qui sont visible sur la colonne.
* @return Le nombre de carte visible en constante.
*/
const int ColonneCartes::reqNbCartesVisibles () const
{
	return this->m_nbCartesVisibles;
}

/**
* @brief Surcharge de l'opérateur << qui fait l'affichage d'une ColonneCarte
* @param p_sortie Une référence vers l'objet ostream de l'opérateur <<
* @param p_carte Une référence constante vers une ColonneCarte
* @return Un ostream représentant la ColonneCarte
* Cette méthode affiche une colonne selon ces règles:
*	1. Si la pile est vide, affiché une X.
*	2. Pour chaque carte cachée, afficher un ?.
*	3. Afficher les cartes visibles.
*/
std::ostream& operator<< (std::ostream& p_sortie, const ColonneCartes& p_colonneCartes)
{
	if (p_colonneCartes.estVide())
	{
		p_sortie << "X ";
	}
	else
	{
		int nbCarteCache =  p_colonneCartes.m_lesCartes.size() - p_colonneCartes.reqNbCartesVisibles();
		if (nbCarteCache < 0)
		{
			nbCarteCache = 0;
		}

		for (unsigned int i = 0; i < nbCarteCache; ++i)
		{
			p_sortie << "? ";
		}
		for (std::vector<Carte>::const_iterator iter =  p_colonneCartes.m_lesCartes.begin() + nbCarteCache; iter != p_colonneCartes.m_lesCartes.end(); ++iter)
		{
			p_sortie << *iter << " ";
		}
	}
	return p_sortie;
}

/**
* @brief Cette méthode change le nombre de carte selon un terme donné en paramètre.
* @param p_diffenrenceNbCarte La différence de carte à effectuer
* Après avoir ajuster le nombre de carte visible selon la quantité donnée en paramètre,
* la méthode vérifie si le nombre de carte est inférieure à 1. Si c'est le cas, elle le remet à 1.
*/
void ColonneCartes::changerNombreCarteVisible(const int p_differenceNbCarte)
{
	this->m_nbCartesVisibles += p_differenceNbCarte;
	if (this->m_nbCartesVisibles < 1)
	{
		this->m_nbCartesVisibles = 1;
	}
}

/**
* @brief Cette fonction retourne les Cartes composant la ColonneCarte
* @return Une référence constante d'un vecteur contant les Cartes de la ColonneCarte.
*/
const std::vector<Carte>& ColonneCartes::reqLesCartes() const
{
	return this->m_lesCartes;
}

/**
* @brief Cette méthode retourne la carte qui est sur le dessus de la ColonneCarte
* @return Une référence constante vers la Carte qui est sur le dessus de la ColonneCarte.
* Cette méthode s'attend à être appelé seulement si la colone n'est pas vide.
* Si elle est vide, une erreur de précondition est lancée.
* Elle retourne la dernière carte du vecteur.
*/
Carte& ColonneCartes::reqCarteDessus()
{
	PRECONDITION(!this->estVide());
	return this->m_lesCartes.back();
}

/**
* @brief Cette méthode retourne la carte situé à une position donnée du début du paquet.
* @param p_position La position à partir du début de la Carte désirée. Le dessus = 1.
* @return Une référence constante vers la Carte situé à une position donnée de la ColonneCarte
* Cette méthode s'attend à être appelé seulement si la colone n'est pas vide.
* Elle s'attend aussi à ce que la position demandée soit une carte visible.
* Si ce n'est pas le cas, une erreur de précondition est lancée.
*/
Carte& ColonneCartes::reqCartePosition(const int p_position)
{
	PRECONDITION(!this->estVide());
	PRECONDITION(p_position <= this->reqNbCartesVisibles());
	return *(this->m_lesCartes.end() - p_position);
}

/**
* @brief Cette méthode retourne la carte qui est sur le dessus de la ColonneCarte
* @return Une référence vers la Carte qui est sur le dessus de la ColonneCarte.
* Cette méthode s'attend à être appelé seulement si la colone n'est pas vide.
* Si elle est vide, une erreur de précondition est lancée.
* Elle retourne la dernière carte du vecteur.
*/
const Carte& ColonneCartes::reqCarteDessus() const
{
	PRECONDITION(!this->estVide());
	return this->m_lesCartes.back();
}

/**
* @brief Cette méthode retourne la carte situé à une position donnée du début du paquet.
* @param p_position La position à partir du début de la Carte désirée. Le dessus = 1.
* @return Une référence vers la Carte situé à une position donnée de la ColonneCarte
* Cette méthode s'attend à être appelé seulement si la colone n'est pas vide.
* Elle s'attend aussi à ce que la position demandée soit une carte visible.
* Si ce n'est pas le cas, une erreur de précondition est lancée.
*/
const Carte& ColonneCartes::reqCartePosition(const int p_position) const
{
	PRECONDITION(!this->estVide());
	PRECONDITION(p_position <= this->reqNbCartesVisibles());
	return *(this->m_lesCartes.end() - p_position);
}

/**
* @brief Cette méthode indique si la ColonneCarte n'a aucune Carte.
* @return Vrai si aucune Carte n'est présent dans la ColonneCarte, sinon faux.
*/
const bool ColonneCartes::estVide() const
{
	return this->m_lesCartes.empty();
}