package serveurdessin.mieux;

import java.awt.Color;

import serveurdessin.maladroit.CadreDessin;

public class ParseurFigureCORSegment extends SolveurCOR {
	
	ParseurFigureCORSegment(SolveurCOR suivant) {
		super(suivant);
	}


	@Override
	public boolean resoudre1(String s[], CadreDessin cadreDessin) {
		String opération;
	    
	    opération = s[0];
	    
	    if (!opération.contains("segment") )
	    	return false;
	    
        int x1, y1, x2, y2;
    
        x1 = Integer.parseInt(s[2].trim());
        y1 = Integer.parseInt(s[3].trim());
        x2 = Integer.parseInt(s[4].trim());
        y2 = Integer.parseInt(s[5].trim());
        
        cadreDessin.graphics.setColor(colors[Integer.parseInt(s[1].trim())]);
        cadreDessin.graphics.drawLine(x1,y1,x2,y2);
        
        cadreDessin.getBufferStrategy().show();
	    
	    return true;
	       
	    
	}
	
}
