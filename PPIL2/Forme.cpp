
#include <iostream>
#include "Erreur.h"
#include "Forme.h"


using namespace std;

void Forme::dessiner() const
{
	try
	{
		ClientDessin clientDessin("127.0.0.1", 8091);

		dessiner1(clientDessin, false);
	}
	catch (Erreur e)
	{
		cerr << "le dessinateur n'est pas disponible : " << e << endl;
	}
}



ostream& operator << (ostream& os, const Forme* forme)
{
	return os << (string)(*forme);
}