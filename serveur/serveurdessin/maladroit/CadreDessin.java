package serveurdessin.maladroit;

import java.awt.Frame;
import java.awt.Graphics;
import java.awt.Toolkit;
import java.awt.Dimension;

/**
 * destiné à recevoir des dessins réalisés en Active-Rendering
 * 
 * paint() est désactivée
 * 
 * pourrait être améliorée par l'utilisation d'un Canvas : Panel spécialisé pour le dessin
 * pourrait être améliorée par l'utilisation de coordonnées relatives plutôt que des coordonnées en pixels
 * */
public class CadreDessin extends Frame
{
public Graphics graphics;      // pour dessiner sur this

/**
 * @param titre : titre de la fenêtre
 * @param ox : abscisse souhaité pour le bord gauche de la fenêtre
 * @param oy : ordonnée souhaitée pour le bord supérieur de la fenêtre
 * @param largeur : largeur souhaitée pour la fenêtre
 * @param hauteur : hauteur souhaitée pour la fenêtre
 * 
 * l'unité pour ces 4 paramètres est le pixel 
 * 
 * */
public CadreDessin(String titre, int ox, int oy, int largeur, int hauteur) throws InterruptedException
{
super(titre);
// ------------------ paramétrage de la position et des dimensions de la fenêtre --------------------------

Toolkit tk = Toolkit.getDefaultToolkit();

int le, he; // largeur écran, hauteur écran

Dimension dim = tk.getScreenSize(); // dimensions de l'écran

le = (int) dim.getWidth();
he = (int) dim.getHeight();

int bordGauche, bordSupérieur, l, h ;

bordGauche = Math.max(0, ox);
bordSupérieur = Math.max(0, oy);
l = Math.min(largeur, le - bordGauche);
h = Math.min(hauteur, he - bordSupérieur);
this.setBounds(bordGauche, bordSupérieur, l, h);

//this.setBounds(ox, oy, largeur, hauteur);

this.setVisible(true);

//------------------------- initialisation de l'active rendering -----------------------

this.setIgnoreRepaint(true);

int nombreBuffers = 2;
this.createBufferStrategy(nombreBuffers);
Thread.sleep(50);   // il faut attendre un minimum de 50 ms pour que le buffer soit opérationnel
this.graphics = this.getBufferStrategy().getDrawGraphics();
}

}
