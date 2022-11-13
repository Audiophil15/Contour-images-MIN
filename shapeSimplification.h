#ifndef _SHAPE_SIMPLIFICATION_
#define _SHAPE_SIMPLIFICATION_
#include "TTVpoint.h"

TTV_Point simplification_segments(TTV_Point contour, int j1, int j2, int d);
TTV_Point supprimerDoublons(TTV_Point ttv);

#endif // _SHAPE_SIMPLIFICATION_