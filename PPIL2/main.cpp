#include <iostream>
#include <string>
#include "Erreur.h"
#include "Segment.h"
#include "Triangle.h"
#include "Cercle.h"
#include "ClientDessin.h"
#include "Polygone.h"
#include "Compose.h"

#pragma comment(lib, "ws2_32.lib")


int main()
{
    try
    {
        //Création des formes
        Forme* f1; 
        Forme* f2;
        Forme* f3;
        Forme* f4;
        Forme* f5;
        
        //Création des vecteurs à ajouter au polygone
        Vecteur2D v1(10, 100);
        Vecteur2D v2(20, 20);
        Vecteur2D v3(30, 100);
        Vecteur2D v4(40, 100);
        
        //Création des figures simples
        f1 = new Polygone(Forme::CYAN);
        f1->ajouter(v1);
        f1->ajouter(v2);
        f1->ajouter(v3);
        f1->ajouter(v4);
        f2 = new Triangle(10, 100, 20, 20, 30, 100, Forme::BLUE );
        f3 = new Cercle(300, 300, 30, Forme::RED);
        f4 = new Segment(30, 30, 90, 90, Forme::GREEN);
        //Création d'une forme composée
        f5 =  new Compose(Forme::BLACK);
        f5->ajouter(f1);
        f5->ajouter(f2);
        f5->ajouter(f3);
        f5->ajouter(f4);

        //Affichage des requêtes en string
        cout << "f1 = " << f1 << endl;
        cout << "f2 = " << f2 << endl;
        cout << "f3 = " << f3 << endl;
        cout << "f4 = " << f4 << endl;
        cout << "f5 = " << f5 << endl;

        //Dessin des figures
        f1->dessiner();     
        f2->dessiner();
        f3->dessiner();
        f4->dessiner();
        f5->dessiner();
    }
    catch (Erreur e)
    {
        cerr << e << endl;
    }
    char ch;
    cin >> ch;

    return 0;
}


