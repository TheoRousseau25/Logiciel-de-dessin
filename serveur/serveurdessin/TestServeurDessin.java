package serveurdessin;
/**
 * Serveur dessinant des scènes 2D en Active-Rendering sur l'écran local. Les ordres de tracés sont donnés par les clients distants.
 * 
 *  Serveur multi-client
 * 
 * 
 * 
 * */

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

//import serveurdessin.maladroit.SessionDessin;
import serveurdessin.mieux.SessionDessin;

public class TestServeurDessin
{

public static void main(String[] args)
{
int portServeurDessin = 8091;   // arbitraire. N'importe quel port libre convient
try
    {
    ServerSocket serveurDessin = new ServerSocket(portServeurDessin);
    
    System.out.println("serveur de dessin prêt, \n détails : "+serveurDessin);
    
    int nombreClients;
    
    nombreClients = 0;
    
    while (true)
        {
        System.out.println("serveur de dessin en attente du prochain client");
        Socket socket = serveurDessin.accept();
        ++nombreClients;
        System.out.println("nouveau client connecté n° = " + nombreClients);
        SessionDessin sessionDessin = new SessionDessin(socket);                // interlocuteur prenant en charge la session de dessin du nouveau client,
        sessionDessin.start();                                                  // il travaille dans un thread séparé, en parallèle de l'activité de serveurDessin
        }
    }
catch (IOException e)
    {
    
    System.err.println("Le serveur n'a pu être connecté sur le port d'écoute ou la connexion sur ce port a été rompue. \n Détails : "+e);
    }
}
}
