#include <stdio.h>
#include <stdlib.h>
#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"
#include "TTVcontour.h"


int main(int argc, char *argv[]){

	Image image = lire_fichier_image(argv[1]);
	ecrire_image(image);
	Point premierPixelNoir = trouverPremierPixelNoir(image, 1, 1);
	Orientation orientation = Est;
	Point positionInitiale = {premierPixelNoir.x-1, premierPixelNoir.y-1};
	Point position = positionInitiale;
	TTV_Point points_Contour = creer_TTV_Point_vide();

	int flag = 1;
	while (flag){
		points_Contour = memoriserPosition(position, points_Contour);
		position = avancer(orientation, position);
		orientation = nouvelleOrientation(image, position, orientation);

		if((position.x == positionInitiale.x && position.y == positionInitiale.y && orientation == Est)){
			flag = 0;
		}
	}
	points_Contour = memoriserPosition(position, points_Contour);
	enregistrer_TTV_Point(argv[2], points_Contour);
	printf("Fait : %d points de contour enregistres.\n", points_Contour.nb);
	printf("Premier point enregistre : %.1f, %.1f\nDernier point enregistre : %.1f, %.1f\n", positionInitiale.x, positionInitiale.y, points_Contour.tab[points_Contour.nb-1].x, points_Contour.tab[points_Contour.nb-1].y);
	return 0;
}
