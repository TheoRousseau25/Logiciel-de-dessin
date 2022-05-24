package serveurdessin.mieux;

import serveurdessin.maladroit.CadreDessin;

public class ParseurFigureCORTriangle extends SolveurCOR {
	
	ParseurFigureCORTriangle(SolveurCOR suivant) {
		super(suivant);
	}


	@Override
	public boolean resoudre1(String s[], CadreDessin cadreDessin) {
		String opération;
	    
	    opération = s[0].trim();
	    
	    if (!opération.contains("triangle")  )
	    	return false;

        int x1, y1, x2, y2, x3, y3;
    
        x1 = Integer.parseInt(s[2].trim());
        y1 = Integer.parseInt(s[3].trim());
        x2 = Integer.parseInt(s[4].trim());
        y2 = Integer.parseInt(s[5].trim());
        x3 = Integer.parseInt(s[6].trim());
        y3 = Integer.parseInt(s[7].trim());
        
        cadreDessin.graphics.setColor(colors[Integer.parseInt(s[1].trim())]);
        cadreDessin.graphics.drawPolygon(new int[] {x1, x2, x3}, new int[] {y1, y2, y3}, 3);
        
        cadreDessin.getBufferStrategy().show();
	    
	    return true;
	    
	    
	}

}
