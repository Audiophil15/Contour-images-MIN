#include<stdio.h>
#include<stdlib.h>
#include "TTVcontour.h"

TTV_Point creer_TTV_Point_vide(){
	TTV_Point T;
	T.nb = 0;
	T.cap = 10;
	T.taille_elt = sizeof(Point);
	T.tab = (Point*)malloc(sizeof(Point)*T.cap);
	if(T.tab == NULL){
		printf("Allocation du TTV_Point impossible\n");
		exit(1);
	}
	return T;
}

Point element_TTV_Point(TTV_Point T, UINT i){
	return T.tab[i];
}

UINT nb_elements_TTV_Point(TTV_Point T){
	return T.nb;
}

TTV_Point ajouter_element_TTV_Point(TTV_Point T, Point e){
	if (T.nb == T.cap){
		T.cap *= 2;
		T.tab = realloc(T.tab, T.taille_elt*T.cap);
		if (T.tab == NULL){
			printf("Reallocatioin du TTV_Point impossible\n");
			exit(1);
		}
	}
	T.tab[T.nb++] = e;
	return T;
}

TTV_Point concatener_TTV_Point(TTV_Point T1, TTV_Point T2){
	UINT i;
	if (T1.nb + T2.cap > T1.cap){
		T1.cap = T1.nb + T2.nb;
		T1.tab = realloc(T1.tab, T1.taille_elt*T1.cap);
		if (T1.tab == NULL){
			printf("Reallocation du TTV_Point impossible\n");
			exit(1);
		}
	}
	for (i=0; i<T2.nb; i++){
		T1.tab[T1.nb+i] = T2.tab[i];
	}
	T1.nb += T2.nb;
	return T1;
}

void supprimer_TTV_Point(TTV_Point *ptr_T){
	free(ptr_T->tab);
}

// Stocke les points enregistres dans un TTV dans un fichier.
void enregistrer_TTV_Point(char* nomDeFichier, TTV_Point ContourTab){
	int i;
	FILE* f = fopen(nomDeFichier, "w+");
	fprintf(f, "1\n\n");
	fprintf(f, "%d\n", ContourTab.nb);
	for (i = 0; i<ContourTab.nb; i++){
		fprintf(f, "%.1f %.1f\n", ContourTab.tab[i].x, ContourTab.tab[i].y);
	}
}