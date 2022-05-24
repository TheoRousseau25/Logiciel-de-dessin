/*
 * ClientDessin.cpp
 *
 *  Created on: 26 août 2014
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
 * crée un client TCP/IP vers un serveur de dessin
 *
 * envoie 3 requêtes possibles :
 *
 * ouvrir une fenêtre graphique
 * tracer un segment
 * tracer une ellipse pleine
 *
 * protocole : Chaque requête est codée sous forme d'une seule String se terminant par le caractère fin de ligne.
 * Sur la ligne, 2 paramètres consécutifs sont séparés par ", ".
 *
 * */

ClientDessin::ClientDessin(const string& adresseServeurDessin, const int portServeurDessin)
{
    MaWinsock::getInstance();	// initialisation de la DLL : effectuée une seule fois


	/**
 *
 * Etape 1: Creation du Socket
 *
 */

    int r;

    int familleAdresses = AF_INET;         // IPv4
    int typeSocket = SOCK_STREAM;           // mode connecté TCP
    int protocole = IPPROTO_TCP;            // protocole. On peut aussi mettre 0 et la fct choisit le protocole en fct des 2 1ers paramètres
                                            // pour les valeurs des paramètres : cf. fct socket dans la doc sur winsock

    sock = socket(familleAdresses, typeSocket, protocole);
	//Verification des valeurs envoyées
    if (sock == INVALID_SOCKET)
    {
        ostringstream oss;
        oss << "la création du socket a échoué : code d'erreur = " << WSAGetLastError() << endl;	// pour les valeurs renvoyées par WSAGetLastError() : cf. doc réf winsock
        throw Erreur(oss.str().c_str());
    }

    cout << "socket de dessin créé" << endl;

	/**
 *	Etape 2:Creation du Representant serveur
 *
 */

    sockaddr.sin_family = AF_INET;
    sockaddr.sin_addr.s_addr = inet_addr(adresseServeurDessin.c_str());   // inet_addr() convertit de l'ASCII en entier
    sockaddr.sin_port = htons((short)portServeurDessin);                 //htons() assure que le port est bien inscrit dans le format du réseau (little-endian ou big-endian)

	 /**
  * Etape 3 : Creation de la connexion au serveur
  *
 */

    r = connect(sock, (SOCKADDR*)&sockaddr, sizeof(sockaddr));     // renvoie une valeur non nulle en cas d'échec.
                                                                    // Le code d'erreur peut être obtenu par un appel à WSAGetLastError()

    if (r == SOCKET_ERROR)
        throw Erreur("La connexion au serveur de dessin a échoué");

    cout << "connexion au serveur de dessin réussie" << endl;
}
//Destructeur
ClientDessin::~ClientDessin() noexcept(false)
{
	// Coupure connexion et reception
    int r = shutdown(sock, SD_BOTH);							// on coupe la connexion pour l'envoi et la réception
                                                        // renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()
	//Verification si la connexion est coupee
    if (r == SOCKET_ERROR)
        throw Erreur("la coupure de connexion a échoué");

	//Fermeture Socket
    r = closesocket(sock);                          // renvoie une valeur non nulle en cas d'échec. Le code d'erreur peut être obtenu par un appel à WSAGetLastError()
    if (r) throw Erreur("La fermeture du socket a échoué");

    cout << "arrêt normal du client" << endl;
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
    envoie sur une seule ligne les 5 paramètres au serveur.
 * Les 5 paramètres drawLine, ... , y2 sont au préalable encodés en 1 seule String. Les paramètres sont séparés par ", "
 *  * */
void ClientDessin::traceSegment(const int x1, const int y1, const int x2, const int y2, const int couleur)
{
    ostringstream oss;

    oss << "segment," << couleur << ", " <<  x1 << ", " << y1 << ", " << x2 << ", " << y2 << "\r\n";

    string requete = oss.str();

    consRequeteEnvoi(oss.str());
}

/**
envoie sur une seule ligne les 5 paramètres au serveur.
* Les 5 paramètres fillOval, ... , hauteur sont au préalable encodés en 1 seule String. Les paramètres sont séparés par ", "
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
