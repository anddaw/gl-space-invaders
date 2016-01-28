/* Rectangle.h */
#include "Geometry.h"

bool Rectangle::isInside(double pointX, double pointY) {
  if (pointY-startY<height && pointY-startY>0
      && pointX-startX<width && pointX-startX>0)
    return true;
  else
    return false;
}//isInside

bool Rectangle::overlaps(Rectangle rect) {
  if(startX > rect.startX + rect.width || rect.startX > startX + width)
    return false;
  else if(startY > rect.startY + rect.height || rect.startY > startY + height)
    return false;
  else
    return true;
}//overlaps
