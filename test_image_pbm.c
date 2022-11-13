#include <stdio.h>
#include <stdlib.h>
#include "image_pbm.h"

int main(int argc,char** argv){

	if (argc != 2){
		printf("Il faut entrer un nom de fichier (un seul)\n");
		return 1;
	}

	Image I;

	I = lire_fichier_image(argv[1]);
	ecrire_image(I);

	//Inverse la couleur du pixel du milieu
	if (get_pixel_image(I, I.L/2+1, I.H/2+1) == BLANC){
		set_pixel_image(I, I.L/2+1, I.H/2+1, NOIR);
	} else {
		set_pixel_image(I, I.L/2+1, I.H/2+1, BLANC);
	}

	ecrire_image(I);

	supprimer_image(&I);
	//Affiche a nouveau l'image pour verifier qu'elle a bien ete supprimee
	ecrire_image(I);

	return 0;
}
