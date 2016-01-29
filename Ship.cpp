#include "Ship.h"

const float Ship::forceCoef = 0.01f;
const float Ship::maxV = 0.7;
const float Ship::maxBank = 30;
const float Ship::maxX = 25;
const float Ship::minX = -25;
const float Ship::maxY = 70;
const float Ship::minY = 0;
const float Ship::step = 5;


void Ship::checkVal(float &f, float min, float max) {
  if(f>max) f=max;
  else if(f<min) f=min;
}

void Ship::checkVal(float &f, float absMax) {
  if(f>absMax) f=absMax;
  else if(f<-absMax) f=-absMax;
}

void Ship::update() {
  v+=forceCoef*bank;
  checkVal(v,maxV);

  x+=v;
  checkVal(x,minX,maxX);
}
