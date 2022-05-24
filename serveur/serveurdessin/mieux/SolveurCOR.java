package serveurdessin.mieux;

import java.awt.Color;

import serveurdessin.maladroit.CadreDessin;

public abstract class SolveurCOR extends Solveur {
	
	SolveurCOR  _suivant;
	Color[] colors = {Color.black,Color.blue,Color.red,Color.green,Color.yellow,Color.cyan};
	
	SolveurCOR(SolveurCOR suivant) {
	
		_suivant = suivant;
	}

	@Override
	public boolean resoudre(String s[], CadreDessin cadreDessin ) {
		
		boolean resultat;
		
		resultat = resoudre1(s, cadreDessin );		// ce maillon tente de r�soudre le pb

		if (resultat) {
			return resultat;
		}
		else
			if (_suivant != null)		// ce maillon n'est pas le dernier de la cha�ne
				return _suivant.resoudre(s, cadreDessin);			// on confie le probl�me au maillon suivant
			else											// ce maillon est le dernier donc �chc de la cha�ne
				return false;
	}
	
	public abstract boolean resoudre1(String s[], CadreDessin cadreDessin );
	
	

}
