
#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"
#include "TTVcontour.h"
#include "TTVpoint.h"
#include "shapeSimplification.h"
#include "math.h"

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
		//supprimer_TTV_Point(&LnoDoublon);
	}
	LnoDoublon = ajouter_element_TTV_Point(LnoDoublon, ttv.tab[ttv.nb-1]);
	return LnoDoublon;
}


Point calcul_Ct3(Bezier3 courbe, Point t){
	return set_point(courbe.C0.x*(1-t.x)*(1-t.x)*(1-t.x) + courbe.C1.x*3*t.x*(1-t.x)*(1-t.x) + courbe.C2.x*(1-t.x)*3*t.x*t.x + courbe.C3.x*t.x*t.x*t.x, courbe.C0.x*(1-t.y)*(1-t.y)*(1-t.y) + courbe.C1.y*3*t.y*(1-t.y)*(1-t.y) + courbe.C2.y*(1-t.y)*3*t.y*t.y + courbe.C3.y*t.y*t.y*t.y);
}

Point calcul_Ct2(Bezier2 courbe, Point t){
	return set_point(courbe.C0.x*(1-t.x)*(1-t.x) + courbe.C1.x*2*t.x*(1-t.x) + courbe.C2.x*(1-t.x)*(1-t.x), courbe.C0.y*(1-t.y)*(1-t.y) + courbe.C1.y*2*t.y*(1-t.y) + courbe.C2.y*(1-t.y)*(1-t.y)) ;
}

Bezier2 approx_bezier2(TTV_Point Contour, int j1, int j2){
	Bezier2 Courbe;
	Courbe.C0 = Contour.tab[j1];
	Courbe.C2 = Contour.tab[j2];
	if (j1-j2 == 1){
		Courbe.C1 = set_point((Contour.tab[j1].x+Contour.tab[j2].x)/2, (Contour.tab[j1].y+Contour.tab[j2].y)/2);
	} else {
		double n = j2-j1;
		double alpha = 3*n/(n*n-1);
		double beta = (1-2*n)/(2*n+2);
		int i;
		Point C1;
		C1.x = 0;
		C1.y = 0;
		for (i = j1; i<j2; i++){
			C1 = add_point(Contour.tab[i], produit_point(beta, add_point(Contour.tab[j1], Contour.tab[j2])));
			}
		C1 = produit_point(alpha, C1);
		Courbe.C1 = C1;
	}
	return Courbe;
};

Bezier3 conversion_bezier2to3(Bezier2 courbe2){
	Bezier3 courbe3;
	courbe3.C0 = courbe2.C0;
	courbe3.C1 = set_point((courbe2.C0.x + 2*courbe2.C1.x)/3, (courbe2.C0.y + 2*courbe2.C1.y)/3);
	courbe3.C2 = set_point((courbe2.C2.x + 2*courbe2.C1.x)/3, (courbe2.C2.y + 2*courbe2.C1.y)/3);
	courbe3.C3 = courbe2.C2;
	return courbe3;
}
