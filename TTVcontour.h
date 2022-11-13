#ifndef _TTV_CONTOUR_H_
#define _TTV_CONTOUR_H_

#include "geometrie2D.h"
#include "TTVpoint.h"
#include "image_pbm.h"

typedef unsigned int UINT;

typedef struct TTV_Contour_{
	UINT nb;
	UINT cap;
	UINT taille_elt;
	TTV_Point *tab;

} TTV_Contour;

TTV_Contour creer_TTV_Contour_vide();

TTV_Point element_TTV_Contour(TTV_Contour T, UINT i);

UINT nb_elements_TTV_Contour(TTV_Contour T);

TTV_Contour ajouter_element_TTV_Contour(TTV_Contour T, TTV_Point e);

TTV_Contour concatener_TTV_Contour(TTV_Contour T1, TTV_Contour T2);

void supprimer_TTV_Contour(TTV_Contour *ptr_T);

void enregistrer_TTV_Contour(char* nomDeFichier, TTV_Contour ContourTab);

void enregistrer_TTV_Contour_EPS(char* nomDeFichier, Image I, TTV_Contour ContourTab, char ModeEcriture);

void enregistrer_TTV_Contour_Bezier(char* nomDeFichier, Image I, TTV_Contour ContourTab, char ModeEcriture);

#endif