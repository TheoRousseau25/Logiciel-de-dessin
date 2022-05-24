#include "Forme.h"

///
/// class Compose
///

class Compose : public Forme {
public:
	//Attributs
	vector<Forme*> _formes;

	//Constructeur
	Compose(int couleur = 0) : Forme(couleur) {}

	//Destructeur
	virtual ~Compose() {
		vector<Forme*>::iterator it;
		for (it = _formes.begin(); it != _formes.end(); ++it) {
			delete(*it);
		}
		_formes.clear();
	}

	//Ajouter une figure au groupe
	void ajouter(Forme* f) {
		_formes.push_back(f);
	}

	//Fonction de dessin
	void dessiner1(ClientDessin& d, boolean compose) const {

		int marge, largeur, hauteur;
		largeur = 500;
		hauteur = 500;

		int gauche = 500;
		int haut = 500;

		marge = 500;
		d.ouvreFenetreGraphique("compose client C++", gauche - marge, haut - marge, largeur + 2 * marge, hauteur + 2 * marge);
		d.traceCompose(this);
	}

	//Conversion en chaine de caractères
	operator string() const
	{
		ostringstream  os;
		os << string("[Compose=");
		for (int i = 0; i < _formes.size(); i++)
			os << _formes[i];
		os <<  "]";
		return os.str();
	}
};