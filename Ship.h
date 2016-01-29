#ifndef SHIP_H
#define SHIP_H

#include <iostream>

class Ship {
  
public:
  enum Type {PLAYER, ENEMY};

private:
  float x;
  float y;
  //predkosc
  float v;
  //przechyl -- rownowazny sile
  float bank;

  Type type;
  
  // 1/m
  static const float forceCoef;
  static const float maxV;
  static const float maxBank;
  static const float maxX;
  static const float minX;
  static const float maxY;
  static const float minY;

  static const float step;
  
public:

  
  Ship(float x, float y, Type t) : x(x), y(y), v(0), bank(0), type(t) {}
  Ship(void) : x(0), y(0), v(0), bank(0), type(ENEMY) {}
  Ship(const Ship &ship) : x(ship.x), y(ship.y), v(ship.v),
			   bank(ship.bank), type(ship.type) {}
  Ship & operator=(const Ship &ship) {
    x=ship.x;
    y=ship.y;
    v=ship.v;
    bank=ship.bank;
    type=ship.type;
    return *this;
  }
  Type getType() {return type;}
  float getX() {return x;}
  float getY() {return y;}
  float getBank() {return bank;}

  void bankLeft() {
    bank-=step;
    checkVal(bank,maxBank);
  }

  void bankRight(){
    bank+=step;
    checkVal(bank,maxBank);
  }

  void noBank() {
    if(bank>-step && bank<step)
      bank=0;
    else if(bank<0) bank+=step;
    else if(bank>0) bank-=step;
  }

  void print() {std::cout << "v: " << v << "a: " << bank*forceCoef << "\n";}

  void update();
  
  //Sprawdza czy wartosc nalezy do okreslonego przedzialu,
  //jezeli nie, ustawia na wartosc minimalna lub maksymalna
  static void checkVal(float &f, float min, float max);
  static void checkVal(float &f, float absMax);
};

#endif
