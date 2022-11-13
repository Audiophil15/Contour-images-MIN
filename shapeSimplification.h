#ifndef _SHAPE_SIMPLIFICATION_
#define _SHAPE_SIMPLIFICATION_
#include "TTVpoint.h"

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

TTV_Point simplification_segments(TTV_Point contour, int j1, int j2, int d);
TTV_Point supprimerDoublons(TTV_Point ttv);
Point calcul_Ct3(Bezier3 courbe, Point t);
Point calcul_Ct2(Bezier2 courbe, Point t);
Bezier3 conversion_bezier2to3(Bezier2 courbe2);
Bezier2 approx_bezier2(TTV_Point Contour, int j1, int j2);
#endif // _SHAPE_SIMPLIFICATION_
