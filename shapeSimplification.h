#ifndef _SHAPE_SIMPLIFICATION_
#define _SHAPE_SIMPLIFICATION_
#include "TTVpoint.h"
#include "geometrie2D.h"

typedef struct {
	Point C0;
	Point C1;
	Point C2;
}Bezier2;

typedef struct {
	Point C0;
	Point C1;
	Point C2;
	Point C3;
}Bezier3;

TTV_Point simplification_segments(TTV_Point contour, int j1, int j2, double d);
//Simplifie un contour en une suite de segments
TTV_Point simplification_bezier_2(TTV_Point contour, int j1, int j2, double d);
//Simplifie un contour en une suite de courbes de Bezier de degre 2
TTV_Point simplification_bezier_3(TTV_Point C,UINT j1,UINT j2,double d);
//Simplifie un contour en une suite de courbes de Bezier de degre 3
TTV_Point supprimerDoublons(TTV_Point ttv);
//Supprime les doublons d'un tableau de points, suite a une simplification par segments
Point calcul_pointC3(Bezier3 courbe, double t);
//Calcule les coordonnees du point de parametre t dans une courbe de degre 3
Point calcul_pointC2(Bezier2 courbe, double t);
//Calcule les coordonnees du point de parametre t dans une courbe de degre 2
Bezier3 conversion_bezier2to3(Bezier2 courbe2);
//Convertit une coubre de degre 2 en degre 3
TTV_Point contour_bezier2to3(TTV_Point contour);
//Convertit un tableau de points de courbes de degre 2 en tableau de points de courbes de degre 3 grace a la fonction precedente
Bezier2 approx_bezier2(TTV_Point Contour, int j1, int j2);
//Calcule l'approximation en Bezier de degre 2 d'une suite de contours
Bezier3 approx_bezier3(TTV_Point Contour, int j1, int j2);
//Calcule l'approximation en Bezier de degre 3 d'une suite de contours
double distance_point_bezier2(Point P, Bezier2 Bezier, double ti);
//Calcule la distance entre un point de l'espace et un point sur une courbe de degre 2
double distance_point_bezier3(Point P, Bezier3 Bezier, double ti);
//Calcule la distance entre un point de l'espace et un point sur une courbe de degre 3

#endif // _SHAPE_SIMPLIFICATION_
