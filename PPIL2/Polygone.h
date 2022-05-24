#pragma once
#include "Forme.h"

///
/// Classe Polygone
///
class Polygone : public Forme
{
public:
	//Attributs
	vector<Vecteur2D> _vecteurs;

	//Constructeur
	Polygone(int couleur = 0):Forme(couleur) {}

	//Destructeur
	virtual ~Polygone(){}

	//Fonction pour ajouter un vecteur au vector
	void ajouter(Vecteur2D vecteur) {
	     _vecteurs.push_back(vecteur);
	}

	//Vecteur2D Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const;

	//Fonction de dessin
	void dessiner1(ClientDessin& d, boolean compose) const {

		int marge, largeur, hauteur;
		largeur = _vecteurs[0].x + 50;
		hauteur = _vecteurs[1].x + 50;

		int gauche = _vecteurs[0].x + 50;
		int haut = _vecteurs[1].x + 50;

		marge = 50;

		if(!compose)
		    d.ouvreFenetreGraphique("polygone client C++", gauche - marge, haut - marge, largeur + 2 * marge, hauteur + 2 * marge);
		d.tracePolygone(this);
	}

	/*//translation
	void translation(Polygone *pol,Vecteur2D vecteur)const
	{
		for (int i = 0; i < (int)pol->_vecteurs.size(); i++) {
			*(pol->_vecteurs[i]) += vecteur;
		}
	}

	//rotation
	void rotation(Polygone *pol,const double angle)
	{
		for (int i = 0; i < (int)pol->_vecteurs.size(); i++) {
			pol->_vecteurs[i] = &Rotation_Vecteur(angle, *(pol->_vecteurs[i]));
		}
	}

	//homotethie
	void homotethie(Polygone *pol,double rapport)const
	{
		for (int i = 0; i < (int)pol->_vecteurs.size(); i++) {
			*(pol->_vecteurs[i]) = *(pol->_vecteurs[i]) * rapport;
		}
	}*/

	//Conversion en chaine de caractères
	operator string() const
	{
		ostringstream oss;

		oss << "Polygone : " << "gauche = " << _vecteurs[0].x + 50 << ", haut = " << _vecteurs[1].x + 50 << ", droit = " << _vecteurs[0].x << ", bas = " << _vecteurs[0].x;

		return oss.str();
	}

};

/*inline Vecteur2D Polygone::Rotation_Vecteur(const double angle, Vecteur2D  vecteur)const {
	if (vecteur.getX() == vecteur.getY() == 0)
		return vecteur;
	double x = vecteur.getX() * cos(angle) - vecteur.getY() * sin(angle);
	double y = vecteur.getX() * sin(angle) + vecteur.getY() * cos(angle);
	vecteur = Vecteur2D(x, y);
	return vecteur;
}*/