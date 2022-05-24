#pragma once

/**
singleton contenant l'initialisation de la librairie winsock2.

Assure que la DLL de la winsock est initialisée une unique fois

*/

#include <WinSock2.h>

class MaWinsock
{
	WSADATA wsaData;	//  structure contenant les données de la librairie winsock à initialiser. représente la DLL.
	MaWinsock(void);

	static MaWinsock* instanceUnique;
public:
	static MaWinsock* getInstance();
	~MaWinsock(void);
};

