
#include <sstream>
#include "Segment.h"

Segment::Segment(double x1, double y1, double x2, double y2, int couleur) : Forme(couleur)
{
	X.x = x1;
	X.y = y1;
	Y.x = x2;
	Y.y = y2;
}

Segment::Segment(Vecteur2D x, Vecteur2D y, int couleur) : X(x), Y(y), Forme(couleur){}

void Segment::dessiner1(ClientDessin& clientDessin, boolean compose) const
{
	int marge, largeur, hauteur;
	largeur = X.x - Y.x;
	hauteur = X.y - Y.y;
	double gauche = min(X.x, Y.x);
	double haut = max(X.y, Y.y);
	marge = 500;
	if (!compose)
	    clientDessin.ouvreFenetreGraphique("segment client C++", (int)gauche - marge, (int)haut - marge, largeur + 2 * marge, hauteur + 2 * marge);

	clientDessin.traceSegment(marge, marge, marge + largeur, marge + hauteur, _couleur);

}

Segment::operator string() const
{
	ostringstream oss;

	oss << "Segment : " << "gauche = " << min(X.x, Y.x) << ", haut = " << max(X.y, Y.y) << ", droit = " << max(X.x, Y.x) << ", bas = " << min(X.y, Y.y);

	return oss.str();
}
