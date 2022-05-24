#pragma once

#include <WinSock2.h>
#include <string>
#include "Vecteur2D.h"
#include <Vector>
class Polygone;
class Compose;

using namespace std;
//
//Cette classe permet de creer un client TCP/IP vers un serveur JAVA
//

class ClientDessin
{
	SOCKET sock;  // informations concernant le socket � cr�er : famille d'adresses accept�es, mode connect� ou non, protocole 
	SOCKADDR_IN sockaddr; // informations concernant le serveur avec lequel on va communiquer

public:
	//Constructeur
	ClientDessin(const string& adresseServeurDessin, const int portServeurDessin);
	//Destructeur
	~ClientDessin() noexcept(false);  // noexcept(false) signifie que ce destructeur peut lancer une exception
									  // noexcept(false) en C++ a la m�me signification que throws en JAVA

	void ouvreFenetreGraphique(const string& titre, const int bordGauche, const int bordHaut, const int largeur, const int hauteur);

	/**
		envoie sur une seule ligne les 5 param�tres au serveur.
	 * Les 5 param�tres drawLine, ... , y2 sont au pr�alable encod�s en 1 seule String. Les param�tres sont s�par�s par ", "
	 *  * */
	void traceSegment(const int x1, const int y1, const int x2, const int y2, const int couleur);

	/**
	envoie sur une seule ligne les coordon�es au serveur.
	*  * */
	void remplitEllipse(const int bordGauche, const int bordHaut, const int largeur, const int hauteur, const int couleur);

	void traceTriangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int couleur);

	void tracePolygone(const Polygone* polygone);

	void traceCompose(const Compose* compose);

	void consRequeteEnvoi(const string requete);

};



