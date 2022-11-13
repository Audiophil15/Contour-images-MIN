#ifndef _TTV_POINT_H_
#define _TTV_POINT_H_

#include "geometrie2D.h"
#include "image_pbm.h"


typedef unsigned int UINT;

typedef struct TTV_Point_{
	UINT nb;
	UINT cap;
	UINT taille_elt;
	Point *tab;

} TTV_Point;

TTV_Point creer_TTV_Point_vide();

Point element_TTV_Point(TTV_Point T, UINT i);

UINT nb_elements_TTV_Point(TTV_Point T);

TTV_Point ajouter_element_TTV_Point(TTV_Point T, Point e);

TTV_Point concatener_TTV_Point(TTV_Point T1, TTV_Point T2);

void supprimer_TTV_Point(TTV_Point *ptr_T);

void enregistrer_TTV_Point(char* nomDeFichier, TTV_Point ContourTab);

void enregistrer_TTV_Point_EPS(char* nomDeFichier, Image I, TTV_Point ContourTab, char ModeEcriture);

#endif