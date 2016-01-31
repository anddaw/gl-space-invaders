#include "Ship.h"

const float Ship::forceCoef = 0.005f;
const float Ship::maxV = 0.7;
const float Ship::maxBank = 30;
const float Ship::step = 5;


void Ship::update() {
  v+=forceCoef*bank;
  Borders::checkVal(v,maxV);

  x+=v;
  if(!Borders::checkVal(x,Borders::minX,Borders::maxX))
    v=0;
}

bool Ship::hit(Missile &m) {
  if(type==DESTROYED||
     (type==PLAYER && m.type==Missile::Type::PLAYER) ||
     (type==ENEMY && m.type==Missile::Type::ENEMY)) return false;

  Rectangle r(x-1,y+1,2,3);

  if(r.isInside(m.getX(),m.getY())){
      m.type=Missile::Type::VOID;
      if(type==ENEMY) type=DESTROYED;
      return true;
    } else {
      return false;
    }
    
    

}
