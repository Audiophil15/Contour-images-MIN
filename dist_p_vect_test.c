#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"

int main(){
	printf("Entrez les coordonnees de A, B, puis de C1, C2, et C3\nEntrez les deux coordonnees pour chaque point, separees d'un espace ou d'une virgule\n");
	double x, y;
	printf("A :\n");
	scanf("%lf %lf", &x, &y);
	Point A = set_point(x, y);
	printf("B :\n");
	scanf("%lf %lf", &x, &y);
	Point B = set_point(x, y);
	printf("C1 :\n");
	scanf("%lf %lf", &x, &y);
	Point C1 = set_point(x, y);
	printf("C2 :\n");
	scanf("%lf %lf", &x, &y);
	Point C2 = set_point(x, y);
	printf("C3 :\n");
	scanf("%lf %lf", &x, &y);
	Point C3 = set_point(x, y);

	printf("Distance a AB de :\nC1 : %f\nC2 : %f\nC3 : %f\n", distance_point_segment(C1,A,B), distance_point_segment(C2,A,B), distance_point_segment(C3,A,B));
	printf("distance de C1 au segment AA : %f\n", distance_point_segment(C1,A,A));
	return 0;
}
