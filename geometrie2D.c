#include "geometrie2D.h"
#include <math.h>

Point set_point(double x, double y){
	Point P = {x, y};
	return P;
}

Point add_point(Point P1, Point P2){
	return set_point(P1.x + P2.x, P1.y + P2.y);
}

Vecteur vect_bipoint(Point A, Point B){
	Vecteur V = {B.x - A.x, B.y - A.y};
	return V;
}

Vecteur add_vect(Vecteur V1, Vecteur V2){
	Vecteur V = {V1.x + V2.x, V1.y + V2.y};
	return V;
}

Vecteur produit_vecteur(double a, Vecteur V){
	Vecteur Vp = {V.x * a, V.y * a};
	return Vp;
}

double produit_scalaire(Vecteur V1, Vecteur V2){
	return V1.x * V2.x + V1.y * V2.y;
}

double norme_vecteur(Vecteur V){
	return sqrt(produit_scalaire(V, V));
}

double distance_points(Point P1, Point P2){
	return sqrt((P1.x-P2.x)*(P1.x-P2.x) + (P1.y-P2.y)*(P1.y-P2.y));
}