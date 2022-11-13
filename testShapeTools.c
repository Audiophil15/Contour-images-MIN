#include <stdio.h>
#include <stdlib.h>
#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"

int main(int argc, char ** argv){
	Image I = lire_fichier_image(argv[1]);
	Orientation sens = Est;
	Point pixelNoir = trouverPremierPixelNoir(I, 1, 1);
	printf("Coordonnees premier pixel noir : %f, %f\n", pixelNoir.x, pixelNoir.y);
	memoriserPosition(pixelNoir);
	sens = nouvelleOrientation(I, pixelNoir, sens);
	printf("Orientation : %d", sens);
	Point newPoint = avancer(sens, pixelNoir);
	memoriserPosition(newPoint);
	return 0;
}
