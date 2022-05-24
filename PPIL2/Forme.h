#pragma once

#include <iostream>
#include <string>
#include "ClientDessin.h"
#include <sstream>

using namespace std;

///
/// \class Forme
/// \brief Type : 1.Segment, 2.Cercle, 3.Polygone, 4.Compose
///			Couleur : 0.black, 1.blue, 2.red, 3.green, 4.yellow, 5.cyan
///

/**
 * Hiérarchie simplifiée de formes en 2D
 *
 * */
class Forme
{

public:
	//Constantes pour les couleurs
	static const int BLACK = 0;
	static const int BLUE = 1;
	static const int RED = 2;
	static const int GREEN = 3;
	static const int YELLOW = 4;
	static const int CYAN = 5;

	int _couleur;
	
	//Constructeur
	Forme(int couleur = 0) : _couleur(couleur) {}

	//Destructeur
	virtual ~Forme(){}

	//Getter
	int getCouleur()
	{
		return _couleur;
	}

	//Setter
	int setCouleur(int couleur)
	{
		_couleur = couleur;
	}

	//Fonctions dessin
	void dessiner() const;

	virtual  void dessiner1(ClientDessin& d, boolean compose) const = 0;

	//Fonction d'ajout dans les vectors
	virtual void ajouter(Vecteur2D vecteur) {};

	virtual void ajouter(Forme* forme) {};

	//Conversion en chaine de caractères
	virtual operator string () const = 0;

};

ostream& operator << (ostream& os, const Forme* forme);