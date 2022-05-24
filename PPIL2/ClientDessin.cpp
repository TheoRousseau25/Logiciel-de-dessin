/*
 * ClientDessin.cpp
 *
 *  Created on: 26 ao�t 2014
 *      Author: Dominique
 */

#include <winsock2.h>
#include <string.h>
#include <string>
#include <sstream>
#include "Erreur.h"
#include "MaWinsock.h"
#include "ClientDessin.h"
#include "Ws2tcpip.h"
#include "Polygone.h"
#include "Compose.h"

using namespace std;

#pragma warning(disable:4996) 

/**
 * cr�e un client TCP/IP vers un serveur de dessin
 *
 * envoie 3 requ�tes possibles :
 *
 * ouvrir une fen�tre graphique
 * tracer un segment
 * tracer une ellipse pleine
 *
 * protocole : Chaque requ�te est cod�e sous forme d'une seule String se terminant par le caract�re fin de ligne.
 * Sur la ligne, 2 param�tres cons�cutifs sont s�par�s par ", ".
 *
 * */

ClientDessin::ClientDessin(const string& adresseServeurDessin, const int portServeurDessin)
{
    MaWinsock::getInstance();	// initialisation de la DLL : effectu�e une seule fois


	/**
 *
 * Etape 1: Creation du Socket
 *
 */

    int r;

    int familleAdresses = AF_INET;         // IPv4
    int typeSocket = SOCK_STREAM;           // mode connect� TCP
    int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers param�tres
                                            // pour les valeurs des param�tres : cf. fct socket dans la doc sur winsock

    sock = socket(familleAdresses, typeSocket, protocole);
	//Verification des valeurs envoy�es
    if (sock == INVALID_SOCKET)
    {
        ostringstream oss;
        oss << "la cr�ation du socket a �chou� : code d'erreur = " << WSAGetLastError() << endl;	// pour les valeurs renvoy�es par WSAGetLastError() : cf. doc r�f winsock
        throw Erreur(oss.str().c_str());
    }

    cout << "socket de dessin cr��" << endl;

	/**
 *	Etape 2:Creation du Representant serveur
 *
 */

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(adresseServeurDessin.c_str());   // inet_addr() convertit de l'ASCII en entier
    sockaddr.sin_port = htons((short)portServeurDessin);                 //htons() assure que le port est bien inscrit dans le format du r�seau (little-endian ou big-endian)

	 /**
  * Etape 3 : Creation de la connexion au serveur
  *
 */

    r = connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));     // renvoie une valeur non nulle en cas d'�chec.
                                                                    // Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()

    if (r == SOCKET_ERROR)
        throw Erreur("La connexion au serveur de dessin a �chou�");

    cout << "connexion au serveur de dessin r�ussie" << endl;
}
//Destructeur
ClientDessin::~ClientDessin() noexcept(false)
{
	// Coupure connexion et reception
    int r = shutdown(sock, SD_BOTH);							// on coupe la connexion pour l'envoi et la r�ception
                                                        // renvoie une valeur non nulle en cas d'�chec. Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()
	//Verification si la connexion est coupee
    if (r == SOCKET_ERROR)
        throw Erreur("la coupure de connexion a �chou�");

	//Fermeture Socket
    r = closesocket(sock);                          // renvoie une valeur non nulle en cas d'�chec. Le code d'erreur peut �tre obtenu par un appel � WSAGetLastError()
    if (r) throw Erreur("La fermeture du socket a �chou�");

    cout << "arr�t normal du client" << endl;
}

//Methode qui permet d'ouvrir une fenetre graphique
void ClientDessin::ouvreFenetreGraphique(const string& titre, const int bordGauche, const int bordHaut, const int largeur, const int hauteur)
{
    ostringstream oss;

    oss << titre << ", " << bordGauche << ", " << bordHaut << ", " << largeur << ", " << hauteur << "\r\n";

    string requete = oss.str();

    consRequeteEnvoi(oss.str());

}

//Methode qui permet d'envoyer une requete au server
void ClientDessin::consRequeteEnvoi(const string requete) {
    //Envoi de la requete
    int r = send(sock, requete.c_str(), (int)requete.length(), 0);

    //Verification de l'envoi de la requete
    if (r == SOCKET_ERROR)
        throw Erreur("Echec d'envoi de la requete a la fenetre graphique");
    cout << "requete envoye:" << requete << endl;
}

/**
    envoie sur une seule ligne les 5 param�tres au serveur.
 * Les 5 param�tres drawLine, ... , y2 sont au pr�alable encod�s en 1 seule String. Les param�tres sont s�par�s par ", "
 *  * */
void ClientDessin::traceSegment(const int x1, const int y1, const int x2, const int y2, const int couleur)
{
    ostringstream oss;

    oss << "segment," << couleur << ", " <<  x1 << ", " << y1 << ", " << x2 << ", " << y2 << "\r\n";

    string requete = oss.str();

    consRequeteEnvoi(oss.str());
}

/**
envoie sur une seule ligne les 5 param�tres au serveur.
* Les 5 param�tres fillOval, ... , hauteur sont au pr�alable encod�s en 1 seule String. Les param�tres sont s�par�s par ", "
*  * */
void ClientDessin::remplitEllipse(const int bordGauche, const int bordHaut, const int largeur, const int hauteur, const int couleur)
{
    ostringstream oss;

    oss << "cercle" << ", " << couleur << ", " << bordGauche << ", " << bordHaut << ", " << largeur << ", " << hauteur << "\r\n";

    consRequeteEnvoi(oss.str());
}

void ClientDessin::traceTriangle(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int couleur)
{
    ostringstream oss;

    oss << "triangle," << couleur << ", " <<  x1 << ", " << y1 << ", " << x2 << ", " << y2 << ", " << x3 << ", " << y3 << "\r\n";

    string requete = oss.str();

    consRequeteEnvoi(oss.str());
}

void ClientDessin::tracePolygone(const Polygone* polygone)
{
    ostringstream oss;

    oss << "polygone," << polygone->_vecteurs.size() << ", " << polygone->_couleur;

    for (size_t i = 0; i < polygone->_vecteurs.size(); i++) {
        oss << ", " << polygone->_vecteurs[i].x << ", " << polygone->_vecteurs[i].y;
    }

    oss << "\r\n";

    string requete = oss.str();

    consRequeteEnvoi(oss.str());
}

void ClientDessin::traceCompose(const Compose* compose)
{
    for (size_t i = 0; i < compose->_formes.size(); i++) {
        compose->_formes[i]->dessiner1(*this, true);
    }
}
