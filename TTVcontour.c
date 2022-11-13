#include<stdio.h>
#include<stdlib.h>
#include"image_pbm.h"
#include "TTVcontour.h"
#include "TTVpoint.h"

TTV_Contour creer_TTV_Contour_vide(){
	TTV_Contour T;
	T.nb = 0;
	T.cap = 10;
	T.taille_elt = sizeof(TTV_Point);
	T.tab = (TTV_Point*)malloc(T.taille_elt*T.cap);

	if(T.tab == NULL){
		printf("Allocation du TTV_Contour impossible\n");
		exit(1);
	}
	return T;
}

TTV_Point element_TTV_Contour(TTV_Contour T, UINT i){
	return T.tab[i];
}

UINT nb_elements_TTV_Contour(TTV_Contour T){
	return T.nb;
}

TTV_Contour ajouter_element_TTV_Contour(TTV_Contour T, TTV_Point e){
	if (T.nb == T.cap){
		T.cap *= 2;
		T.tab = realloc(T.tab, T.taille_elt*T.cap);
		if (T.tab == NULL){
			printf("Reallocatioin du TTV_Contour impossible\n");
			exit(1);
		}
	}
	T.tab[T.nb++] = e ;
	return T;
}

TTV_Contour concatener_TTV_Contour(TTV_Contour T1, TTV_Contour T2){
	UINT i;
	if (T1.nb + T2.cap > T1.cap){
		T1.cap = T1.nb + T2.nb;
		T1.tab = realloc(T1.tab, T1.taille_elt*T1.cap);
		if (T1.tab == NULL){
			printf("Reallocation du TTV_Contour impossible\n");
			exit(1);
		}
	}
	for (i=0; i<T2.nb; i++){
		T1.tab[T1.nb+i] = T2.tab[i];
	}
	T1.nb += T2.nb;
	return T1;
}

void supprimer_TTV_Contour(TTV_Contour *ptr_T){
	int i;
	for (i=0; i<ptr_T->nb; i++){
		supprimer_TTV_Point(ptr_T->tab+i);
	}
}

// Stocke les points enregistres dans un TTV dans un fichier.
void enregistrer_TTV_Contour(char* nomDeFichier, TTV_Contour ContourTab){
	int i,j;
	FILE* f = fopen(nomDeFichier, "w+");
	fprintf(f, "%d\n\n", ContourTab.nb);
	// Ici faire un for dns un for pour recuperer les coordonnees pour chaque contour
	for (j=0; j< ContourTab.nb; j++){
		fprintf(f, "%d\n", ContourTab.tab[j].nb);
		for (i = 0; i<ContourTab.tab[j].nb; i++){
			fprintf(f, "%.1f %.1f\n", ContourTab.tab[j].tab[i].x, ContourTab.tab[j].tab[i].y);
		}

	}
}


// Il faut changer les boucles pour ajouter le gestion du TTV_Contour a la place du TTV_point

/*
void enregistrer_TTV_Contour_EPS(char* nomDeFichier, Image I, TTV_Contour ContourTab, char ModeEcriture){
	#define RESOLUTION 100
	int i;
	FILE* f = fopen(nomDeFichier, "w");
	fprintf(f, "%%!PS-Adobe-3.0 EPSF-3.0\n");
	fprintf(f, "%%%%BoundingBox: %d %d %i %i\n\n", -25, -25, (I.L)*RESOLUTION+25, (I.H)*RESOLUTION+25);
	// On place le point de depart avec moveto
	fprintf(f, "%f %f moveto\n\n", ContourTab.tab[0].x*RESOLUTION, (I.H-ContourTab.tab[0].y)*RESOLUTION);
	// On place tous les points successivements avec un for, on place les points en options avec un if
	for (i=1; i<ContourTab.nb; i++){
		fprintf(f, "%f %f lineto\n", ContourTab.tab[i].x*RESOLUTION, (I.H-ContourTab.tab[i].y)*RESOLUTION);
	}
	fprintf(f, "0.5 0.85 0.5 setrgbcolor\n");
	if (ModeEcriture == 'F'){
		fprintf(f, "fill\n");
	} else {
		fprintf(f, "stroke\n");
	}

	if (ModeEcriture == 'P'){
		for (i=1; i<ContourTab.nb; i++){
			fprintf(f, "newpath %f %f 5 0 360 arc fill\nclosepath\n", ContourTab.tab[i].x*RESOLUTION, (I.H-ContourTab.tab[i].y)*RESOLUTION);
		}
	}

	fprintf(f, "\nshowpage\n");
}
*/