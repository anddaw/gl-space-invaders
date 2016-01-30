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



bool Borders::checkVal(float &f, float min, float max) {
  if(f>max) {f=max; return false;}
  else if(f<min) {f=min; return false;}
  else return true;
}

bool Borders::checkVal(float &f, float absMax) {
  return checkVal(f,-absMax,absMax);
}

const float Borders::maxX = 25;
const float Borders::minX = -25;
const float Borders::maxY = 70;
const float Borders::minY = 0;
