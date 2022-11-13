#include "geometrie2D.h"
#include "shapeSimplification.h"
#include <math.h>

Point set_point(double x, double y){
	Point P = {x, y};
	return P;
}

Point add_point(Point P1, Point P2){
	return set_point(P1.x + P2.x, P1.y + P2.y);
}

Point produit_point(double a, Point A){
	return set_point(A.x*a, A.y*a);
}

Vecteur vect_bipoint(Point A, Point B){
	Vecteur V={B.x-A.x, B.y - A.y};
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

double distance_point_segment(Point P, Point A, Point B){
	if (A.x == B.x && A.y == B.y){
		return distance_points(A, P);
	}
	double lambda;
	Vecteur vectAB = vect_bipoint(A, B), vectAP = vect_bipoint(A, P);
	lambda = (produit_scalaire(vectAB, vectAP)/produit_scalaire(vectAB, vectAB));
	if (lambda<0){
		return norme_vecteur(vectAP);
	}
	if (lambda<=1){
		double x = distance_points(set_point(add_vect(produit_vecteur(lambda, vectAB), vect_bipoint(set_point(0,0), A)).x, add_vect(produit_vecteur(lambda, vectAB), vect_bipoint(set_point(0,0), A)).y), P);
		return x;
	}
	return distance_points(B, P);
}