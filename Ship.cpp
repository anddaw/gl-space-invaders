#include "Ship.h"

const float Ship::forceCoef = 0.01f;
const float Ship::maxV = 0.7;
const float Ship::maxBank = 30;
const float Ship::step = 5;


void Ship::update() {
  v+=forceCoef*bank;
  Borders::checkVal(v,maxV);

  x+=v;
  Borders::checkVal(x,Borders::minX,Borders::maxX);
}

bool Ship::hit(Missile &m) {
  if((type==PLAYER && m.type==Missile::Type::PLAYER) ||
     (type==ENEMY && m.type==Missile::Type::ENEMY)) return false;

  

}
