package serveurdessin.mieux;

import java.awt.Color;
import java.lang.reflect.Field;

import serveurdessin.maladroit.CadreDessin;

public class ParseurFigureCORCercle extends SolveurCOR {
	
	ParseurFigureCORCercle(SolveurCOR suivant) {
		super(suivant);
	}


	@Override
	public boolean resoudre1(String s[], CadreDessin cadreDessin) {
	
	String op�ration;
    
    op�ration = s[0].trim();
    
    if ((!op�ration.contains("cercle") ))
    	return false;

    int x1, y1, x2, y2;

    x1 = Integer.parseInt(s[2].trim());
    y1 = Integer.parseInt(s[3].trim());
    x2 = Integer.parseInt(s[4].trim());
    y2 = Integer.parseInt(s[5].trim());
    
    cadreDessin.graphics.setColor(colors[Integer.parseInt(s[1].trim())]);
    
    cadreDessin.graphics.fillOval(x1,y1,x2,y2);
    
    cadreDessin.getBufferStrategy().show();
    
    return true;
    
	}

}
