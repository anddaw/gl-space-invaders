#ifndef MODEL_H
#define MODEL_H

#include "Ship.h"
#include <vector>

class Model {
  enum EnemyState {LEFT,RIGHT,MOVE_L,MOVE_R};
  EnemyState enemyState;
  int enemyStateCounter;
  
public:
  Ship playerShip;
  std::vector<Ship> enemyShips;

  bool leftKey;
  bool rightKey;
  
  void leftKeyPressed() {leftKey=true;}
  void rightKeyPressed() {rightKey=true;}
  void step();

  void updateEnemy();

  Model();
};

#endif
