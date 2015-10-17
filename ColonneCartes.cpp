/*
* ColonneCartes.cpp
*
*  Created on: 2015-09-24
*      Author: Rapha�l Sylvain (111 124 564)
*/

#include "ColonneCartes.h"

/**
* @brief Constructeur d'une colonne de carte.
* Cette m�thode cr�e une coquille pour une ColonneCarte.
* Elle initialise son vecteur de carte comme un vecteur vide.
*/
ColonneCartes::ColonneCartes()
{
	this->m_lesCartes = std::vector<Carte>();
}

/**
* @brief Initialise ColonneCarte avec les Cartes contenus dans le vecteur en param�tre.
* @param p_listeCarte Les Cartes avec lesquels initialiser la ColonneCarte
* Cette m�thode vide le vecteur actuel de carte de la colonne carte pour
* le remplacer par le vecteur en param�tre. 
* Il va aussi remettre le nombre de carte visible � 1.
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
* @brief Cette m�thode ajoute une Carte � la fin de colonne carte.
* @param p_carte La Carte � ajouter � la fin de la colonne.
* Cette m�thode s'attend � ajouter une carte qui lui est possible d'ajouter selon les r�gles du Klondike.
* Si la carte � ajouter n'est pas valide, une erreur de pr�condition est lanc�e.
* Cette m�thode ajoute � la carte � la suite du vecteur et incr�mente le nombre de carte visible.
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
* @brief Cette m�thode prend des cartes de la colonne et les d�places � la suite d'une autre colonne.
* @param p_destination La ColonneCarte sur laquelle ajouter les cartes d�plac�s.
* @param p_nombreCartes La quantit� de carte � d�placer.
* Cette m�thode s'attend � avoir comme instruction d'effectuer un coup valide selon les r�gles du Klondike.
* Si ce n'est pas le cas, une erreur de pr�condition est lanc�e.
* Cette m�thode boucle au travers de l'ensemble des cartes � d�placer et les ajoutes 1 � 1 sur la ColonneCarte destinations.
* Elle va par la suite supprimer 1 � 1 ses cartes qui sont maintenant d�plac�e.
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
* @brief Cette m�thode supprime la derni�re Carte qui est sur le dessus de la ColonneCarte
* Cette m�thode s'attend � �tre appel�e lorsqu'il y a encore au moins un carte.
* Si la colonne est vide, une erreur de pr�condition est lanc�e.
* Elle supprime la derni�re carte, puis d�cr�mente le nombre de carte visible.
*/
void ColonneCartes::supprimeDerniereCarte ()
{
	PRECONDITION(!this->estVide());
	this->m_lesCartes.pop_back();
	this->changerNombreCarteVisible(-1);
}

/**
* @brief Cette m�thode retourne le nombre de carte qui sont visible sur la colonne.
* @return Le nombre de carte visible en constante.
*/
const int ColonneCartes::reqNbCartesVisibles () const
{
	return this->m_nbCartesVisibles;
}

/**
* @brief Surcharge de l'op�rateur << qui fait l'affichage d'une ColonneCarte
* @param p_sortie Une r�f�rence vers l'objet ostream de l'op�rateur <<
* @param p_carte Une r�f�rence constante vers une ColonneCarte
* @return Un ostream repr�sentant la ColonneCarte
* Cette m�thode affiche une colonne selon ces r�gles:
*	1. Si la pile est vide, affich� une X.
*	2. Pour chaque carte cach�e, afficher un ?.
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
* @brief Cette m�thode change le nombre de carte selon un terme donn� en param�tre.
* @param p_diffenrenceNbCarte La diff�rence de carte � effectuer
* Apr�s avoir ajuster le nombre de carte visible selon la quantit� donn�e en param�tre,
* la m�thode v�rifie si le nombre de carte est inf�rieure � 1. Si c'est le cas, elle le remet � 1.
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
* @return Une r�f�rence constante d'un vecteur contant les Cartes de la ColonneCarte.
*/
const std::vector<Carte>& ColonneCartes::reqLesCartes() const
{
	return this->m_lesCartes;
}

/**
* @brief Cette m�thode retourne la carte qui est sur le dessus de la ColonneCarte
* @return Une r�f�rence constante vers la Carte qui est sur le dessus de la ColonneCarte.
* Cette m�thode s'attend � �tre appel� seulement si la colone n'est pas vide.
* Si elle est vide, une erreur de pr�condition est lanc�e.
* Elle retourne la derni�re carte du vecteur.
*/
Carte& ColonneCartes::reqCarteDessus()
{
	PRECONDITION(!this->estVide());
	return this->m_lesCartes.back();
}

/**
* @brief Cette m�thode retourne la carte situ� � une position donn�e du d�but du paquet.
* @param p_position La position � partir du d�but de la Carte d�sir�e. Le dessus = 1.
* @return Une r�f�rence constante vers la Carte situ� � une position donn�e de la ColonneCarte
* Cette m�thode s'attend � �tre appel� seulement si la colone n'est pas vide.
* Elle s'attend aussi � ce que la position demand�e soit une carte visible.
* Si ce n'est pas le cas, une erreur de pr�condition est lanc�e.
*/
Carte& ColonneCartes::reqCartePosition(const int p_position)
{
	PRECONDITION(!this->estVide());
	PRECONDITION(p_position <= this->reqNbCartesVisibles());
	return *(this->m_lesCartes.end() - p_position);
}

/**
* @brief Cette m�thode retourne la carte qui est sur le dessus de la ColonneCarte
* @return Une r�f�rence vers la Carte qui est sur le dessus de la ColonneCarte.
* Cette m�thode s'attend � �tre appel� seulement si la colone n'est pas vide.
* Si elle est vide, une erreur de pr�condition est lanc�e.
* Elle retourne la derni�re carte du vecteur.
*/
const Carte& ColonneCartes::reqCarteDessus() const
{
	PRECONDITION(!this->estVide());
	return this->m_lesCartes.back();
}

/**
* @brief Cette m�thode retourne la carte situ� � une position donn�e du d�but du paquet.
* @param p_position La position � partir du d�but de la Carte d�sir�e. Le dessus = 1.
* @return Une r�f�rence vers la Carte situ� � une position donn�e de la ColonneCarte
* Cette m�thode s'attend � �tre appel� seulement si la colone n'est pas vide.
* Elle s'attend aussi � ce que la position demand�e soit une carte visible.
* Si ce n'est pas le cas, une erreur de pr�condition est lanc�e.
*/
const Carte& ColonneCartes::reqCartePosition(const int p_position) const
{
	PRECONDITION(!this->estVide());
	PRECONDITION(p_position <= this->reqNbCartesVisibles());
	return *(this->m_lesCartes.end() - p_position);
}

/**
* @brief Cette m�thode indique si la ColonneCarte n'a aucune Carte.
* @return Vrai si aucune Carte n'est pr�sent dans la ColonneCarte, sinon faux.
*/
const bool ColonneCartes::estVide() const
{
	return this->m_lesCartes.empty();
}