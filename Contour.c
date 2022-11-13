#include <stdio.h>
#include <stdlib.h>
#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"
#include "TTVpoint.h"
#include "TTVcontour.h"

int main(int argc, char *argv[]){

	if (argc != 5){
		printf("Usage : programme image.pbm sortie.contour sortie.eps optionEPS\n");
		return -1;
	}

	// Initialisation du travail d'extraction
	Image image = lire_fichier_image(argv[1]);
	ecrire_image(image);
	Image masque = creer_image_masque(image);
	ecrire_image(masque);
	Point premierPixelNoir = trouverPremierPixelNoir(masque, 1, 1);
	Orientation orientation = Est;
	Point positionInitiale = {premierPixelNoir.x-1, premierPixelNoir.y-1};
	Point position = positionInitiale;
	TTV_Point points_Contour = creer_TTV_Point_vide();
	TTV_Contour tabContours = creer_TTV_Contour_vide();
	int nbPointsTotal=0;

	int flag = 1;
	while (flag){
		points_Contour = memoriserPosition(position, points_Contour);
		if(orientation == Est){
			masque.tab[(int)(INDICE_PIXEL(masque, position.x+1, position.y+1))] = BLANC;
		}
		position = avancer(orientation, position);
		orientation = nouvelleOrientation(image, position, orientation);

		if((position.x == positionInitiale.x && position.y == positionInitiale.y && orientation == Est)){
			tabContours = ajouter_element_TTV_Contour(tabContours, points_Contour);
			// On stocke le tableau de points et on recommence avec un nouveau
			points_Contour = creer_TTV_Point_vide();
			// On touve le prochain px noir qui sera le prochain de but de contour
			premierPixelNoir = trouverPremierPixelNoir(masque, premierPixelNoir.x, premierPixelNoir.y);
			position.x = premierPixelNoir.x-1;
			position.y = premierPixelNoir.y-1;
			// On actualise la "premiere position" qui n'est plus la meme pour un nouveau contour
			positionInitiale.x = position.x;
			positionInitiale.y = position.y;
			if (position.x<-1){
				flag = 0;
			}
		}
	}
	printf("%d\n", tabContours.nb);
	enregistrer_TTV_Contour(argv[2], tabContours);
	enregistrer_TTV_Contour_EPS(argv[3], image, tabContours, argv[4][0]); //[4][0] car on a un probleme de liste/type sinon

	int i;
	for (i=0; i<tabContours.nb; i++){
		nbPointsTotal += tabContours.tab[i].nb;
	}
	printf("Fait : %d points de contour enregistres.\n", nbPointsTotal);
	printf("Premier point enregistre : %.1f, %.1f\nDernier point enregistre : %.1f, %.1f\n", positionInitiale.x, positionInitiale.y, tabContours.tab[tabContours.nb-1].tab[tabContours.tab[tabContours.nb-1].nb-1].x, tabContours.tab[tabContours.nb-1].tab[tabContours.tab[tabContours.nb-1].nb-1].y);

	supprimer_image(&masque);
	supprimer_image(&image);
	supprimer_TTV_Point(&points_Contour);
	supprimer_TTV_Contour(&tabContours);

	return 0;
}
