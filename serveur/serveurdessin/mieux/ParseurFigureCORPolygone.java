package serveurdessin.mieux;

import java.awt.Color;

import serveurdessin.maladroit.CadreDessin;

public class ParseurFigureCORPolygone extends SolveurCOR {	
	
	ParseurFigureCORPolygone(SolveurCOR suivant) {
		super(suivant);
	}


	@Override
	public boolean resoudre1(String s[], CadreDessin cadreDessin) {
		String opération;
		int nbVecteurs;
	    
	    opération = s[0].trim();
	    
	    if (!opération.contains("polygone") )
	    	return false;
	    
	    nbVecteurs =  Integer.parseInt(s[1].trim());

	    int x[] = new int[nbVecteurs], y[] =new int[nbVecteurs];
	    
	    for(int i = 3, j = 0; j < nbVecteurs; i += 2, j += 1) {
			x[j] = Integer.parseInt(s[i].trim());
			y[j] = Integer.parseInt(s[i+1].trim());
		}
	    cadreDessin.graphics.setColor(colors[Integer.parseInt(s[2].trim())]);
	    
        cadreDessin.graphics.drawPolygon(x, y, nbVecteurs);
        
        cadreDessin.getBufferStrategy().show();

	    return true;
	}

}
