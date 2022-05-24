#pragma once
#include "Forme.h"
///
/// Classe Segment
///
/**
cf. classe JAVA de même nom

*/
class Segment : public Forme
{
	//Attributs
	Vecteur2D X, Y;

public:
	//Constructeurs
	Segment(double x1, double y1, double x2, double y2, int couleur = 0);
	Segment(Vecteur2D x, Vecteur2D y, int couleur = 0);

	//Destructeur
	virtual ~Segment(){}

	//Getters
	Vecteur2D getDebut()const { return X; }
	Vecteur2D getFin()const { return Y; }

	//Vecteur2D Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const;

	//Setters
	void setDebut(Vecteur2D debut) { X = debut; }
	void setFin(Vecteur2D fin) { Y = fin; }

	//Fonction dessiner
	void dessiner1(ClientDessin& clientDessin, boolean compose) const;

	/*//méthode translation
	void translation(Segment *seg,Vecteur2D vecteur)const
	{
		seg->setDebut(seg->getDebut() + vecteur);
		seg->setFin(seg->getFin() + vecteur);
	}
	//rotation 

	void rotation(Segment *seg, const double angle)const
	{
		seg->setDebut(Rotation_Vecteur(angle, seg->getDebut()));
		seg->setFin(Rotation_Vecteur(angle, seg->getFin()));
	}
	//homothetie
	void homotethie(Segment *seg,double rapport)const {
		seg->setDebut(seg->getDebut() * rapport);
		seg->setFin(seg->getFin() * rapport);
	}*/

	double Aire()const
	{
		return 0.0; 
	}

	//Conversion en chaine de caractères
	operator string() const;
};
/*inline Vecteur2D Segment::Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const {
	if (vecteur.getX() == vecteur.getY() == 0)
		return vecteur;
	double x = vecteur.getX() * cos(angle) - vecteur.getY() * sin(angle);
	double y = vecteur.getX() * sin(angle) + vecteur.getY() * cos(angle);
	vecteur = Vecteur2D(x, y);
	return vecteur;
}*/

