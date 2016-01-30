#ifndef MISSILE_AD
#define MISSILE_AD

#include "Geometry.h"

class Missile{
public:
  enum Type {PLAYER,ENEMY,VOID};
private:
  //wspolrzedne
  float x;
  float y;



  //predkosc
  static const float missileV;

public:
  Type type;
  Missile(void): x(0),y(4), type(PLAYER){}
  Missile(float x, float y, Type t): x(x),y(y), type(t) {}
  Missile(const Missile &m): x(m.x), y(m.y), type(m.type) {};
  Missile& operator=(const Missile& m) {
    x=m.x; y=m.y; type=m.type;
    return *this;
  }
  
  void update();

  float getX() {return x;}
  float getY() {return y;}
  Type getType() {return type;}
  
};

#endif
