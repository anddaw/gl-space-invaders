#ifndef MODEL_H
#define MODEL_H

#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <list>
#include <cstdlib>

class Model {
  enum EnemyState {MOVE_L,MOVE_R};
  EnemyState enemyState;
  int enemyStateCounter;
  
public:
  Ship playerShip;
  std::vector<Ship> enemyShips;
  std::list<Missile> missiles;

  bool leftKey;
  bool rightKey;

  bool fired;
  
  void leftKeyPressed() {leftKey=true;}
  void rightKeyPressed() {rightKey=true;}
  void fireKeyPressed() {if(!fired) {fire(playerShip); fired=true;};}
  void fireKeyNotPressed() {fired=false;}
  void step();

  void fire(Ship &ship);
  void fireRand(Ship &ship) {if(std::rand()%480==0) fire(ship);}

  void updateEnemy();
  void updateMissiles();

  Model();
};

#endif
