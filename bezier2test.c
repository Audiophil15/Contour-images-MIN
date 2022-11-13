#include <stdio.h>
#include <stdlib.h>
#include "geometrie2D.h"
#include "TTVcontour.h"
#include "TTVpoint.h"
#include "shapeSimplification.h"
#include "math.h"

int main(){
	TTV_Point trigone = creer_TTV_Point_vide();
	trigone = ajouter_element_TTV_Point(trigone, set_point(0.0, 0.0));
	trigone = ajouter_element_TTV_Point(trigone, set_point(0.0, 10.0));
	
	Bezier2 approxN1 = approx_bezier2(trigone, 0, 1);
	printf("Approximation pour n =1 : (%f,%f), (%f,%f), (%f,%f)\n", approxN1.C0.x, approxN1.C0.y, approxN1.C1.x, approxN1.C1.y, approxN1.C2.x, approxN1.C2.y);

	trigone.nb = 0; //On vide trigone
	//Soit les points (0,0), (5,5), (0,10)
	//On construit un contour a partir de la courbe correspondant a ces points de controle
	Bezier2 troisPoints = {set_point(0,0), set_point(5,5), set_point(0,10)};
	int i;
	for (i=0; i<10; i++){
		trigone = ajouter_element_TTV_Point(trigone, calcul_pointC2(troisPoints, (double)i/9));
	}

	Bezier2 approxTP = approx_bezier2(trigone, 0, 9);
		printf("Points de base :\n(%f,%f), (%f,%f), (%f,%f)\n", troisPoints.C0.x, troisPoints.C0.y, troisPoints.C1.x, troisPoints.C1.y, troisPoints.C2.x, troisPoints.C2.y);
		printf("Points obtenus :\n(%f,%f), (%f,%f), (%f,%f)\n", approxTP.C0.x, approxTP.C0.y, approxTP.C1.x, approxTP.C1.y, approxTP.C2.x, approxTP.C2.y);

	return 0;

}