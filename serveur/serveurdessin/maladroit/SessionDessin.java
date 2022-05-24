package serveurdessin.maladroit;

/**
 * représente la session de dessin entreprise par un client distant.
 * 
 * Effectue principalement les opérations suivantes :
 * 
 * ouvre une fenêtre awt (Frame) pour dessiner dessus (les coordonnées de la fenêtre sont indiquées par le client).
 * puis exécute sur la fenêtre ouverte tous les ordres de tracé du client distant.
 * 
 * doit être améliorée : doit fonctionner dans un thread séparé du thread principal. cf. classe Thread et/ou interface Runnable
 * 
 * pourrait être améliorée en gérant les WindowEvent pour garantir la restauration du dessin (comme ce que fait repaint()) :
 * La classe pourrait donc être améliorée en héritant de WindowAdapter ou de WindowListener
 * 
 * */
import java.net.Socket;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.SocketException;

public class SessionDessin 
{
BufferedReader fluxEntrant;     // flux entrant pour recevoir les requêtes du client


/**
 * crée la session de dessin avec le client distant connecté sur socket
 * @throws IOException 
 * 
 * */
public SessionDessin(Socket socket) throws IOException
{
this.fluxEntrant = new BufferedReader(new InputStreamReader(socket.getInputStream()));
}

public void start()
{
String requête;

try
    {
    requête = this.fluxEntrant.readLine();  // lit le titre et les 4 coordonnées Ox, Oy, largeur et hauteur de la fenêtre, les arguments sont séparés par des ","
    System.out.println("requête reçue : " + requête);
    String arguments[] = requête.split(",");        // redondance de code à éliminer. Il faut écrire la méthode décoder() réciproque de la méthode encoder() de ClientDessin
    
    String titre;
    int Ox, Oy, largeur, hauteur;
    
    titre = arguments[0].trim();
    Ox = Integer.parseInt(arguments[1].trim());         // redondance de code à éliminer pour 8 lignes !!!! cf. lignes suivantes
    Oy = Integer.parseInt(arguments[2].trim());
    largeur = Integer.parseInt(arguments[3].trim());
    hauteur = Integer.parseInt(arguments[4].trim());
    
    CadreDessin cadreDessin = new CadreDessin(titre,Ox,Oy,largeur,hauteur);
   
    while (true)
        {
        requête = this.fluxEntrant.readLine();  // lit l'instruction de tracé et les 4 paramètres entiers du tracé, les arguments sont séparés par des ","
        
        System.out.println("requête reçue : " + requête);
        arguments = requête.split(",");                     // redondance de code à éliminer
    
        String opération;
        int x1, y1, x2, y2;
    
        opération = arguments[0].trim();
        x1 = Integer.parseInt(arguments[1].trim());
        y1 = Integer.parseInt(arguments[2].trim());
        x2 = Integer.parseInt(arguments[3].trim());
        y2 = Integer.parseInt(arguments[4].trim());
    
        if (opération.equalsIgnoreCase("drawLine"))             // if-else à éliminer par l'utilisation du Design Pattern "Chain Of Responsibility" 
           cadreDessin.graphics.drawLine(x1,y1,x2,y2);
           
        else
            if (opération.equalsIgnoreCase("fillOval"))
               cadreDessin.graphics.fillOval(x1,y1,x2,y2);
               
            else
                {
                /* Opération non reconnue, on ne fait rien */
                }
        cadreDessin.getBufferStrategy().show();
        } // while
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
