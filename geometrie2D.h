#ifndef _GEOMETRIE2D_H_
#define _GEOMETRIE2D_H_


struct Vecteur {
	double x, y;
};
typedef struct Vecteur Vecteur;

struct Point {
	double x, y;
};
typedef struct Point Point;

Point set_point(double x, double y);

Point add_point(Point P1, Point P2);

Vecteur vect_bipoint(Point A, Point B);

Vecteur add_vect(Vecteur V1, Vecteur V2);

Vecteur produit_vecteur(double a, Vecteur V);

double produit_scalaire(Vecteur V1, Vecteur V2);

double norme_vecteur(Vecteur V);

double distance_points(Point P1, Point P2);

#endif // !GEOMETRIE2D_H