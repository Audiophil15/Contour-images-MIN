
#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"
#include "TTVcontour.h"
#include "TTVpoint.h"

TTV_Point simplification_segments(TTV_Point contour, int j1, int j2, int d){
	int dmax = 0;
	int dj;
	int k = j1;
	int j;
	for (j=j1+1; j < j2; j++){
		dj = distance_point_segment(contour.tab[j], contour.tab[j1], contour.tab[j2]);
		if (dmax<dj) {
			dmax = dj;
			k = j;
		}
	}
	TTV_Point L = creer_TTV_Point_vide();
	if (dmax<=d){
		L = ajouter_element_TTV_Point(L, contour.tab[j1]);
		L = ajouter_element_TTV_Point(L, contour.tab[j2]);

	} else {
		TTV_Point L1 = creer_TTV_Point_vide();
		TTV_Point L2 = creer_TTV_Point_vide();
		L1 = simplification_segments(contour, j1, k, d);
		L2 = simplification_segments(contour, k, j2, d);
		L = concatener_TTV_Point(L1, L2);
	}

	return L;
}

TTV_Point supprimerDoublons(TTV_Point ttv){
	TTV_Point LnoDoublon = creer_TTV_Point_vide();
	int j;
	for (j=0; j<ttv.nb-1; j++){
		if (!(ttv.tab[j].x == ttv.tab[j+1].x && ttv.tab[j].y == ttv.tab[j+1].y)){
			LnoDoublon = ajouter_element_TTV_Point(LnoDoublon, ttv.tab[j]);
		}
	}
	LnoDoublon = ajouter_element_TTV_Point(LnoDoublon, ttv.tab[ttv.nb-1]);
	return LnoDoublon;
}
