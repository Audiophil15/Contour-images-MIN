#include <stdio.h>
#include <stdlib.h>
#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"
#include "TTVpoint.h"


int main(int argc, char *argv[]){

	if (argc != 5){
		printf("Usage : programme image.pbm sortie.contour sortie.eps optionEPS\n");
		return -1;
	}

	// Initialisation du travail d'extraction
	Image image = lire_fichier_image(argv[1]);
	ecrire_image(image);
	Image masque = creer_image_masque(image);
	Point premierPixelNoir = trouverPremierPixelNoir(masque, 1, 1);
	Orientation orientation = Est;
	Point positionInitiale = {premierPixelNoir.x-1, premierPixelNoir.y-1};
	Point position = positionInitiale;
	TTV_Point points_Contour = creer_TTV_Point_vide();
	TTV_Contour tabContours = creer_TTV_Contour_vide();

	int flag = 1;
	while (flag){
		points_Contour = memoriserPosition(position, points_Contour);
		if(orientation == Est){
			masque.tab[INDICE_PIXEL(masque, position.x+1, position.y+1)] = BLANC;
		}
		position = avancer(orientation, position);
		orientation = nouvelleOrientation(image, position, orientation);

		if((position.x == positionInitiale.x && position.y == positionInitiale.y && orientation == Est)){
			ajouter_element_TTV_Contour(tabContour, points_Contour);
			points_Contour = creer_TTV_Point_vide();
			premierPixelNoir = trouverPremierPixelNoir(masque, premierPixelNoir.x, premierPixelNoir.y);
			position.x = premierPixelNoir.x-1;
			position.y = premierPixelNoir.y-1;
			if (position.x<-1){
				flag = 0;
			}
		}
	}
	points_Contour = memoriserPosition(position, points_Contour);
	enregistrer_TTV_Point(argv[2], points_Contour);
	enregistrer_TTV_Point_EPS(argv[3], image, points_Contour, argv[4][0]);
	printf("Fait : %d points de contour enregistres.\n", points_Contour.nb);
	printf("Premier point enregistre : %.1f, %.1f\nDernier point enregistre : %.1f, %.1f\n", positionInitiale.x, positionInitiale.y, points_Contour.tab[points_Contour.nb-1].x, points_Contour.tab[points_Contour.nb-1].y);
	return 0;
}
