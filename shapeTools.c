#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"
#include "TTVpoint.h"

/* macro donnant l'indice d'un pixel de coordonnées (_x,_y) de l'image _I */
#define INDICE_PIXEL(_I,_x,_y) ((_x)-1)+(_I).L*((_y)-1)

Point trouverPremierPixelNoir(Image imagePBM, int x, int y){
	int i = INDICE_PIXEL(imagePBM, x, y);
	while (i < imagePBM.H*imagePBM.L){
		if (imagePBM.tab[i] == NOIR){
			// Il n'y a pas besoin de faire -1 sur les coordonnees car l'indice i commence a 0
			// Il faut aussi faire +1 pour la meme raison
			Point pxNoir = {(i%imagePBM.L)+1 ,(i/imagePBM.L)+1};
			return pxNoir;
		}
		i ++;
	}
	// Si on sort du while c'est qu'il n'y a pas de pixel noir
	printf("Recherche de debut de contour : il n'y a pas de pixel noir.");
	return Point noPoint={-1, -1};
}

Orientation nouvelleOrientation(Image image, Point bordPixelNoir, Orientation orientation){
	Pixel pG, pD;
	// On donne la couleur des pixels gauche et droite par rapport au point donne, en fonction de l'orientation
	if (orientation == Nord){
		pG = get_pixel_image(image, bordPixelNoir.x, bordPixelNoir.y);
		pD = get_pixel_image(image, bordPixelNoir.x+1, bordPixelNoir.y);
	} else if (orientation == Sud){
		pG = get_pixel_image(image, bordPixelNoir.x+1, bordPixelNoir.y+1);
		pD = get_pixel_image(image, bordPixelNoir.x, bordPixelNoir.y+1);
	} else if (orientation == Est){
		pG = get_pixel_image(image, bordPixelNoir.x+1, bordPixelNoir.y);
		pD = get_pixel_image(image, bordPixelNoir.x+1, bordPixelNoir.y+1);
	} else {
		pG = get_pixel_image(image, bordPixelNoir.x, bordPixelNoir.y+1);
		pD = get_pixel_image(image, bordPixelNoir.x, bordPixelNoir.y);
	}

	// Si le pixel devant a gauche est noir, on sait tout de suite qu'on tourne a gauche
	if (pG == NOIR){
		return (orientation+3)%4;
	} else {
		// On tourne a droite uniquement si le pixel devant a droite est blanc, sinon on ne fait rien
		if (pD == BLANC) {
			return (orientation+1)%4;
		}
	}

	// Si aucun changement n'a ete fait on retourne simplement l'orientation de depart
	return orientation;

}

// Avancer n'a pas besoin de l'image, elle renvoie simplement les coordonnees du prochain point du contour
Point avancer(Orientation orientation, Point anciennesCoordonnees){
	Point nouveauPoint;

	switch (orientation){
		case Nord :
			nouveauPoint.x = anciennesCoordonnees.x;
			nouveauPoint.y = anciennesCoordonnees.y-1;
			break;
		case Est :
			nouveauPoint.x = anciennesCoordonnees.x+1;
			nouveauPoint.y = anciennesCoordonnees.y;
			break;
		case Sud :
			nouveauPoint.x = anciennesCoordonnees.x;
			nouveauPoint.y = anciennesCoordonnees.y+1;
			break;
		case Ouest :
			nouveauPoint.x = anciennesCoordonnees.x-1;
			nouveauPoint.y = anciennesCoordonnees.y;
			break;
	}
	return nouveauPoint;
}

TTV_Point memoriserPosition(Point pointContour, TTV_Point Tab_Contour){
	Tab_Contour = ajouter_element_TTV_Point(Tab_Contour, pointContour);
	return Tab_Contour;
}
