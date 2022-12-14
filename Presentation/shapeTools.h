#ifndef _CONTOURS_H_
# define _CONTOURS_H_

#include "image_pbm.h"
#include "geometrie2D.h"
#include "TTVpoint.h"

enum Orientation {
	Nord, Est, Sud, Ouest};
typedef enum Orientation Orientation;

Point trouverPremierPixelNoir(Image, int, int);
Orientation nouvelleOrientation(Image, Point, Orientation);
Point avancer(Orientation, Point);
TTV_Point memoriserPosition(Point pointContour, TTV_Point Tab_Contour);

#endif /* !CONTOURS_H_ */
