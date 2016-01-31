#ifndef MODEL_H
#define MODEL_H

#include "Ship.h"
#include "Missile.h"
#include <vector>
#include <list>
#include <cstdlib>

class Model {
  enum EnemyState {MOVE_L,MOVE_R};
  enum GameState {RUNNING,PAUSED,OVER};

  GameState gameState;
  EnemyState enemyState;
  int enemyStateCounter;

  void start();
  
public:
  Ship playerShip;
  std::vector<Ship> enemyShips;
  std::list<Missile> missiles;

  bool leftKey;
  bool rightKey;

  bool fired;
  bool paused;
  
  void leftKeyPressed() {leftKey=true;}
  void rightKeyPressed() {rightKey=true;}
  void fireKeyPressed();
  void fireKeyNotPressed() {fired=false;}
  void pauseKeyPressed();
  void pauseKeyNotPressed();
  void step();

  void fire(Ship &ship);
  void fireRand(Ship &ship) {if(std::rand()%240==0) fire(ship);}

  void updateEnemy();
  void updateMissiles();

  Model() {start();}
};

#endif
