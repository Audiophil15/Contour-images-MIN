#include <stdio.h>
#include <stdlib.h>
#include "shapeTools.h"
#include "image_pbm.h"
#include "geometrie2D.h"

int main(int argc, char *argv[]){

	Image image = lire_fichier_image(argv[1]);
	ecrire_image(image);
	Point premierPixelNoir = trouverPremierPixelNoir(image, 1, 1);
	Orientation orientation = Est;
	Point positionInitiale = {premierPixelNoir.x-1, premierPixelNoir.y-1};
	Point position = positionInitiale;
	int flag = 1;
	while (flag){
		memoriserPosition(position);
		position = avancer(orientation, position);
		orientation = nouvelleOrientation(image, position, orientation);

		if((position.x == positionInitiale.x && position.y == positionInitiale.y && orientation == Est)){
			flag = 0;
		}
	}
	memoriserPosition(position);

	return 0;
}
