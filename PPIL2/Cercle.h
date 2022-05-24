#pragma once
#include "Forme.h"
using namespace std;

///
/// Class Cercle
///
class Cercle : public Forme
{
private:
	//Attributs
	Vecteur2D X, Y;
public:

	//Constructeurs
	Cercle(double x1, double y1, double rayon, int couleur = 0) : Forme(couleur)
	{

		X.x = x1;
		X.y = y1;
		Y.x = rayon;
		Y.y = rayon;
	}

	Cercle(Vecteur2D centre, double rayon, int couleur = 0) : Forme(couleur)
	{
		X = centre;
		Y.x = rayon;
		Y.y = rayon;
	}

	//Destructeur
	virtual ~Cercle(){}

	

	//Getters
	Vecteur2D getCentre() const {
		return X;
	}
	double getRayon() const {
		return Y.x;
	}

	//Setters
	void setCentre(Vecteur2D v) {
		X = v;
	}
	void setRayon(double r) {
		Y.x = r;
		Y.y = r;
	}

	//Vecteur2D Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const;

	//Fonction dessiner
	void dessiner1(ClientDessin & d, boolean compose) const {

		int marge = 100;
		int largeur, hauteur;
		largeur = hauteur = (int)(2 * X.x);
		int bordGauche, bordHaut;

		bordGauche = (int)(X.x - Y.x);
		bordHaut = (int)(X.y - Y.x);

		if (!compose)
		    d.ouvreFenetreGraphique("cercle client C++", bordGauche - marge, bordHaut - marge, largeur + 2 * marge, hauteur + 2 * marge);
		d.remplitEllipse(X.x, X.y, Y.x, Y.y, _couleur);
	}

	/*//translation
	void translation(Cercle *cercle, Vecteur2D vecteur)const
	{
		cercle->setCentre(cercle->getCentre() + vecteur);
	}

	//rotation
	void rotation(Cercle *cercle, const double angle)const
	{
		cercle->setCentre(Rotation_Vecteur(angle, cercle->getCentre()));

	}

	//homotethie
	void homotethie(Cercle *cercle, double rapport)const
	{
		cercle->setCentre(cercle->getCentre() * rapport);
		cercle->setRayon(cercle->getRayon() * rapport);
	}*/
	//Conversion en string
	operator string() const
	{
		ostringstream oss;

		oss << "Cercle : " << "xCentre = " << X.x << ", yCentre = " << X.y << ", rayon = " << Y.x;

		return oss.str();
	}
};

/*inline Vecteur2D Cercle::Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const {
	if (vecteur.getX() == vecteur.getY() == 0)
		return vecteur;
	double x = vecteur.getX() * cos(angle) - vecteur.getY() * sin(angle);
	double y = vecteur.getX() * sin(angle) + vecteur.getY() * cos(angle);
	vecteur = Vecteur2D(x, y);
	return vecteur;
}*/

