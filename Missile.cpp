#include "Missile.h"

const float Missile::missileV = 0.7;


void Missile::update() {

  switch (type) {
  case PLAYER:
    y+=missileV;
    break;
  case ENEMY:
    y-=missileV;
    break;
  default:
    break;
  }
  
    if(!Borders::checkVal(y,Borders::minY,Borders::maxY))
      type=VOID;
  }
