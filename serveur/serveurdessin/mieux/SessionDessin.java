package serveurdessin.mieux;

/**
 * représente la session de dessin entreprise par un client distant.
 * 
 * Effectue principalement les opérations suivantes :
 * 
 * ouvre une fenêtre awt (Frame) pour dessiner dessus (les coordonnées de la fenêtre sont indiquées par le client).
 * puis exécute sur la fenêtre ouverte tous les ordres de tracé du client distant.
 * 
 * fonctionne dans un thread séparé du thread principal.
 * 
 * */
import java.net.Socket;
import java.awt.Color;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.SocketException;

import serveurdessin.maladroit.CadreDessin;


public class SessionDessin extends Thread
{
Socket socket;                  // pour dialoguer avec le client distant. Peut-on se passer de cet attribut ?
BufferedReader fluxEntrant;     // flux entrant pour recevoir les requêtes du client

/**
 * crée la session de dessin avec le client distant connecté sur socket
 * @throws IOException 
 * 
 * */
public SessionDessin(Socket socket) throws IOException
{
this.socket = socket;
this.fluxEntrant = new BufferedReader(new InputStreamReader(this.socket.getInputStream()));
}

@Override
public void run()
{
String requête;

try
    {
	Color[] colors = {Color.black,Color.blue,Color.red,Color.green,Color.yellow,Color.cyan};
    requête = this.fluxEntrant.readLine();  // lit le titre et les 4 coordonnées Ox, Oy, largeur et hauteur de la fenêtre, les arguments sont séparés par des ","
    System.out.println("requête reçue : " + requête);
    String arguments[] = requête.split(",");            // redondance de code à éliminer
    
    String titre;
    int Ox, Oy, largeur, hauteur;
    
    titre = arguments[0].trim();
    Ox = Integer.parseInt(arguments[1].trim());         // redondance de code à éliminer pour 8 lignes !!!! cf. lignes suivantes
    Oy = Integer.parseInt(arguments[2].trim());
    largeur = Integer.parseInt(arguments[3].trim());
    hauteur = Integer.parseInt(arguments[4].trim());
    
    
    CadreDessin cadreDessin = new CadreDessin(titre,Ox,Oy,largeur,hauteur);
    
    SolveurCOR pS, pT, pC, pP;
    
    pS = new ParseurFigureCORSegment(null);
    pC = new ParseurFigureCORCercle(pS);
    pT = new ParseurFigureCORTriangle(pC);
    pP = new ParseurFigureCORPolygone(pT);
    
    Solveur parseur = pP;
    
    while (true)
        {
        requête = this.fluxEntrant.readLine();
        
        System.out.println("requête reçue : " + requête);
        arguments = requête.split(",");    
        
        parseur.resoudre(arguments, cadreDessin);
        
        } 
    }

catch (SocketException e)
    {
    System.out.println("session de dessin terminée par le client");
    }
catch (NumberFormatException e)
    {
    e.printStackTrace();
    }
catch (IOException e)
    {
    e.printStackTrace();
    }
catch (InterruptedException e)
    {
    e.printStackTrace();
    }
}


}

