#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"
#include "TTVcontour.h"
#include "TTVpoint.h"
#include "shapeSimplification.h"
#include "math.h"

TTV_Point simplification_segments(TTV_Point contour, int j1, int j2, double d){
	double dmax = 0;
	double dj;
	int k = j1;
	int j;
	for (j=j1+1; j <= j2; j++){
		dj = distance_point_segment(contour.tab[j], contour.tab[j1], contour.tab[j2]);
		if (dmax<dj) {
			dmax = dj;
			k = j;
		}
	}
	TTV_Point L = creer_TTV_Point_vide();

	//On simplifie par un segment
	if (dmax<=d){
		L = ajouter_element_TTV_Point(L, contour.tab[j1]);
		L = ajouter_element_TTV_Point(L, contour.tab[j2]);

	//On recommence en coupant au point le plus eloigne
	} else {
		TTV_Point L1;
		TTV_Point L2;
		L1 = simplification_segments(contour, j1, k, d);
		L2 = simplification_segments(contour, k, j2, d);
		L = concatener_TTV_Point(L1, L2);
	}

	return L;
}

TTV_Point simplification_bezier_2(TTV_Point contour, int j1, int j2, double d){
	int n = j2-j1;
	Bezier2 B = approx_bezier2(contour, j1, j2);
	double dmax = 0;
	double dj, ti;
	int k = j1;
	int i, j;
	for (j=j1+1; j <= j2; j++){
		i = j-j1;
		ti = (double)(i)/(double)n;
		dj = distance_point_bezier2(contour.tab[j], B, ti);
		if (dmax<dj) {
			dmax = dj;
			k = j;
		}
	}
	TTV_Point L = creer_TTV_Point_vide();

	//On siimplifie par une courbe de degre 2
	if (dmax<=d){
		L = ajouter_element_TTV_Point(L, B.C0);
		L = ajouter_element_TTV_Point(L, B.C1);
		L = ajouter_element_TTV_Point(L, B.C2);

	//On recommence en coupant au point le plus loin
	} else {
		TTV_Point L1, L2;
		L1 = simplification_bezier_2(contour, j1, k, d);
		L2 = simplification_bezier_2(contour, k, j2, d);
		L = concatener_TTV_Point(L1, L2);
	}

	return L;
}


TTV_Point simplification_bezier_3(TTV_Point C,UINT j1,UINT j2,double d){
	int n = j2-j1; 
	
	Bezier3 B = approx_bezier3(C,j1,j2);

	double dmax = 0 ; 
	UINT k = j1; 
	UINT j,i; 
	double dj;
	for  (j=j1+1; j<=j2; j++){
		i = j-j1;
		double ti = (double)i/(double)n;
		dj = distance_point_bezier3(C.tab[j], B, ti);
		if(dmax < dj){
			dmax = dj;
			k= j;
		}
	}
	
	TTV_Point L = creer_TTV_Point_vide();

	//On simplifie par une courbe de degre 3
	if(dmax<=d){
	  L = ajouter_element_TTV_Point(L, B.C0);
		L = ajouter_element_TTV_Point(L, B.C1);
		L = ajouter_element_TTV_Point(L, B.C2);
		L = ajouter_element_TTV_Point(L, B.C3);

	//On recommence en coupant au point le plus loin	
	}else{
		TTV_Point L1, L2;
		L1 = simplification_bezier_3(C,j1,k,d);
		L2 = simplification_bezier_3(C,k,j2,d);
		L = concatener_TTV_Point(L1,L2);
	}
	return L;
}


TTV_Point supprimerDoublons(TTV_Point ttv){
	TTV_Point LnoDoublon = creer_TTV_Point_vide();
	int j;
	//On n'ajoute un point que si celui qui le suit n'est pas le même
	for (j=0; j<ttv.nb-1; j++){
		if (!(ttv.tab[j].x == ttv.tab[j+1].x && ttv.tab[j].y == ttv.tab[j+1].y)){
			LnoDoublon = ajouter_element_TTV_Point(LnoDoublon, ttv.tab[j]);
		}
	}
	LnoDoublon = ajouter_element_TTV_Point(LnoDoublon, ttv.tab[ttv.nb-1]);
	return LnoDoublon;
}


Point calcul_pointC3(Bezier3 courbe, double t){
	return set_point(courbe.C0.x*(1-t)*(1-t)*(1-t) + courbe.C1.x*3*t*(1-t)*(1-t) + courbe.C2.x*(1-t)*3*t*t + courbe.C3.x*t*t*t, courbe.C0.y*(1-t)*(1-t)*(1-t) + courbe.C1.y*3*t*(1-t)*(1-t) + courbe.C2.y*(1-t)*3*t*t + courbe.C3.y*t*t*t);
}

Point calcul_pointC2(Bezier2 courbe, double t){
	return set_point(courbe.C0.x*(1-t)*(1-t) + courbe.C1.x*2*t*(1-t) + courbe.C2.x*t*t, courbe.C0.y*(1-t)*(1-t) + courbe.C1.y*2*t*(1-t) + courbe.C2.y*t*t );
}

Bezier2 approx_bezier2(TTV_Point Contour, int j1, int j2){
	Bezier2 Courbe;
	int n = j2-j1;
	Courbe.C0 = Contour.tab[j1];
	Courbe.C2 = Contour.tab[j2];
	if (n==1){
		Courbe.C1 = produit_point(0.5, add_point(Courbe.C0, Courbe.C2));
	} else {
		double alpha = (3.0*(double)n)/((double)n*(double)n-1.0);
		double beta = (1.0-2.0*(double)n)/(2.0*(double)n+2.0);
		int i;

		//Creation du point C1 de la courbe
		Point C1;
		C1.x = 0.0 ;
		C1.y = 0.0 ;
		for (i = j1+1; i<j2; i++){
			C1 = add_point(C1, Contour.tab[i]);
			}
		C1 = produit_point(alpha, C1);
		C1 = add_point(C1, produit_point(beta, add_point(Contour.tab[j1], Contour.tab[j2])));
		Courbe.C1 = C1;
	}
	return Courbe;
}

Bezier3 approx_bezier3(TTV_Point Contour, int j1, int j2){
	Bezier3 Courbe;
	int n = j2-j1;
	if (n < 3){
		Bezier2 B2;
		B2 = approx_bezier2(Contour, j1, j2);
		Courbe = conversion_bezier2to3(B2);
	}else{
		Courbe.C0 = Contour.tab[j1];
		Courbe.C3 = Contour.tab[j2];
		int i;

		double alpha, beta, lambda, gamma, k;	
		alpha = ((-15.0  *   n *   n *   n) + (5  *   n *   n) + (2  *   n) + 4 ) / (3.0  * (  n + 2 ) * (3  *   n *   n + 1 ));
		beta = ((10.0  *   n *   n *   n) + (-15.0  *   n *   n) + (  n + 2.0 )) / (3.0  * (  n + 2 ) * (3  *   n *   n + 1 ));
		lambda = ((70.0  *   n) / (3.0  * (  n *   n - 1 ) * (  n *   n - 4 ) * (3  *   n *   n + 1 )));
		
		//Creation du point C1 de la courbe
		Point P = set_point(0, 0);
		Point A = produit_point(alpha, Contour.tab[j1]);
		Point D = produit_point(beta, Contour.tab[j2]);
		for (i = 1; i < n; i++){
			k = (double)i;
			gamma = ((6  * (k * k * k * k)) - (8  *  n * k * k * k) + (6  * k * k) - (4  *  n * k) + ( n *  n *  n *  n) - ( n *  n));
			P = add_point(P, produit_point(gamma, Contour.tab[j1 + i]));
		}
		P = produit_point(lambda, P);
		Courbe.C1 = add_point(A, add_point(P, D));

		//Creation du point C2 de la courbe
		P = set_point(0, 0);
		A = produit_point(beta, Contour.tab[j1]);
		D = produit_point(alpha, Contour.tab[j2]);
		for (i = 1; i < n; i++){
			k = (double)(n - i);
			gamma = (double)((6  * (k * k * k * k)) - (8  *  n * k * k * k) + (6  * k * k) - (4  *  n * k) + ( n *  n *  n *  n) - ( n *  n));
			P = add_point(P, produit_point(gamma, Contour.tab[j1 + i]));
		}
		P = produit_point(lambda, P);
		Courbe.C2 = add_point(A, add_point(P, D));
	}
	return Courbe;
}

Bezier3 conversion_bezier2to3(Bezier2 courbe2){
	Bezier3 courbe3;
	courbe3.C0 = courbe2.C0;
	courbe3.C1 = set_point((courbe2.C0.x + 2*courbe2.C1.x)/3, (courbe2.C0.y + 2*courbe2.C1.y)/3);
	courbe3.C2 = set_point((courbe2.C2.x + 2*courbe2.C1.x)/3, (courbe2.C2.y + 2*courbe2.C1.y)/3);
	courbe3.C3 = courbe2.C2;
	return courbe3;
}

TTV_Point contour_bezier2to3(TTV_Point contour){
	int i;
	Bezier2 B;
	TTV_Point contourBis = creer_TTV_Point_vide();
	for (i=0; i<contour.nb; i+=3){ //Il y a normalement toujours 3*x points dans le tableau, x entier
		B.C0 = contour.tab[i];
		B.C1 = contour.tab[i+1];
		B.C2 = contour.tab[i+2];
		//On ajoute directement dans le tableau les 4 points crees par la conversion en courbe de degre 3 de la courbe B
		contourBis = ajouter_element_TTV_Point(contourBis, conversion_bezier2to3(B).C0);
		contourBis = ajouter_element_TTV_Point(contourBis, conversion_bezier2to3(B).C1);
		contourBis = ajouter_element_TTV_Point(contourBis, conversion_bezier2to3(B).C2);
		contourBis = ajouter_element_TTV_Point(contourBis, conversion_bezier2to3(B).C3);
	}
	return contourBis;
}

double distance_point_bezier2(Point P, Bezier2 Bezier, double ti){
	return distance_points(P, calcul_pointC2(Bezier, ti));
}

double distance_point_bezier3(Point P, Bezier3 Bezier, double ti){
  return distance_points(P, calcul_pointC3(Bezier, ti));
}