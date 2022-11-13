#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"

#define COORD(point) printf("Point/Vecteur %s : (%f, %f)\n", #point, point.x, point.y);


int main()
{
	Point P1, P2, P3, P4;
	P1 = set_point(2, 4);
	P2 = set_point(1, 5);
	P3 = add_point(P1, P2);
	P4 = set_point(0, 0);

	COORD(P1)
	COORD(P2)
	COORD(P3)
	COORD(P4)

	Vecteur V13 = vect_bipoint(P1, P3);
	Vecteur V24 = vect_bipoint(P2, P4);
	Vecteur Vsum = add_vect(V13, V24);
	Vecteur Vprod = produit_vecteur(2.5, V13);

	COORD(V13)
	COORD(V24)
	COORD(Vsum)
	COORD(Vprod)

	printf ("Produit scalaie de V13 et V24 : %f\n", produit_scalaire(V13, V24));
	printf("Norme de Vsum : %f\n", norme_vecteur(Vsum));
	printf("Norme de Vprod : %f\n", norme_vecteur(Vprod));
	printf("Distance entre P1 et P3 : %f\n", distance_points(P1, P3));

	return 0;
}
