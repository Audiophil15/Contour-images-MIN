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

Point produit_point(double a, Point A);
//Multiplie les coordonnees d'un point par un scalaire
Vecteur vect_bipoint(Point A, Point B);

Vecteur add_vect(Vecteur V1, Vecteur V2);
//Ajoute deux vecteurs
Vecteur produit_vecteur(double a, Vecteur V);
//Renvoie un vecteur une fois multiplie par un scalaire
double produit_scalaire(Vecteur V1, Vecteur V2);

double norme_vecteur(Vecteur V);
//Calcule la norme d'un vecteur
double distance_points(Point P1, Point P2);
//Calcule la distance entre deux points
double distance_point_segment(Point P, Point A, Point B);
//Calcule la distance entre un point et un segment
#endif // !GEOMETRIE2D_H