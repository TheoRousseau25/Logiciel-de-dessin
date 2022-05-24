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
	SOCKET sock;  // informations concernant le socket à créer : famille d'adresses acceptées, mode connecté ou non, protocole 
	SOCKADDR_IN sockaddr; // informations concernant le serveur avec lequel on va communiquer

public:
	//Constructeur
	ClientDessin(const string& adresseServeurDessin, const int portServeurDessin);
	//Destructeur
	~ClientDessin() noexcept(false);  // noexcept(false) signifie que ce destructeur peut lancer une exception
									  // noexcept(false) en C++ a la même signification que throws en JAVA

	void ouvreFenetreGraphique(const string& titre, const int bordGauche, const int bordHaut, const int largeur, const int hauteur);

	/**
		envoie sur une seule ligne les 5 paramètres au serveur.
	 * Les 5 paramètres drawLine, ... , y2 sont au préalable encodés en 1 seule String. Les paramètres sont séparés par ", "
	 *  * */
	void traceSegment(const int x1, const int y1, const int x2, const int y2, const int couleur);

	/**
	envoie sur une seule ligne les coordonées au serveur.
	*  * */
	void remplitEllipse(const int bordGauche, const int bordHaut, const int largeur, const int hauteur, const int couleur);

	void traceTriangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int couleur);

	void tracePolygone(const Polygone* polygone);

	void traceCompose(const Compose* compose);

	void consRequeteEnvoi(const string requete);

};



