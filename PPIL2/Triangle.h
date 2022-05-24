#pragma once
#include "Forme.h"

class Triangle : public Forme
{
	Vecteur2D X, Y, Z;
public:

	//Constructeurs
	Triangle(double x1, double y1, double x2, double y2, double x3, double y3, int couleur) : Forme(couleur)
	{
		X.x = x1;
		X.y = y1;
		Y.x = x2;
		Y.y = y2;
		Z.x = x3;
		Z.y = y3;
	}

	Triangle(Vecteur2D x, Vecteur2D y, Vecteur2D z, int couleur = 0) :X(x), Y(y), Z(z), Forme(couleur) {}

	//Destructeur
	~Triangle(){}

	Vecteur2D getX()const { return X; }
	Vecteur2D getY()const { return Y; }
	Vecteur2D getZ()const { return Z; }

	void setX(Vecteur2D x) { X = x; }
	void setY(Vecteur2D y) { Y = y; }
	void setZ(Vecteur2D z) { Z = z; }

	//Vecteur2D Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const;

	//Fonction dessiner 
	void dessiner1(ClientDessin& d, boolean compose) const {

		int marge, largeur, hauteur;
		largeur = Y.x + 50;
		hauteur = Z.x + 50;

		int gauche = X.x + 50;
		int haut = Z.x + 50;

		marge = 50;
		if (!compose)
		    d.ouvreFenetreGraphique("triangle client C++", gauche - marge, haut - marge, largeur + 2 * marge, hauteur + 2 * marge);
		d.traceTriangle(X.x, X.y, Y.x, Y.y,Z.x, Z.y, _couleur);
	}

	/*//translation
	void translation(Triangle *T,Vecteur2D vecteur)const
	{
		T->setX(T->getX() + vecteur);
		T->setY(T->getY() + vecteur);
		T->setZ(T->getZ() + vecteur);
	}

	//rotation
	void rotation(Triangle *T, const double angle)const
	{
		T->setX(Rotation_Vecteur(angle, T->getX()));
		T->setY(Rotation_Vecteur(angle, T->getY()));
		T->setZ(Rotation_Vecteur(angle, T->getZ()));
	}

	//homothetie
	void homotethie(Triangle *T, double rapport)const {
		T->setX(T->getX() * rapport);
		T->setY(T->getY() * rapport);
		T->setZ(T->getZ() * rapport);
	}*/



	//Conversion en chaine de caractères
	operator string() const
	{
		ostringstream oss;

		oss << "Triangle : " << "gauche = " << min(X.x, Y.x) << ", haut = " << max(X.y, Y.y) << ", droit = " << max(X.x, Y.x) << ", bas = " << min(X.y, Y.y);

		return oss.str();
	}
};

/*inline Vecteur2D Triangle::Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const {
	if (vecteur.getX() == vecteur.getY() == 0)
		return vecteur;
	double x = vecteur.getX() * cos(angle) - vecteur.getY() * sin(angle);
	double y = vecteur.getX() * sin(angle) + vecteur.getY() * cos(angle);
	vecteur = Vecteur2D(x, y);
	return vecteur;
}*/

