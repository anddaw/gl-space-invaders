/* Model */
#include "Model.h"


void Model::start() {
  gameState=RUNNING;
  playerShip = Ship(0,0,Ship::Type::PLAYER);
  
  //ustawianie statków przeciwnika
  enemyShips.resize(24);

  for(int j=0; j<8; ++j)
    for(int i=0; i<3; ++i)
      enemyShips[3*j+i] = Ship(-6+4*j,60-5*i,Ship::Type::ENEMY);
  //stan przeciwnika
  enemyState=MOVE_L;
  enemyStateCounter=0;

  missiles.clear();
}

void Model::step() {

  //gra nie dziala nic nie rob
  if(gameState!=RUNNING) return;
  
  if((leftKey && rightKey) || (!leftKey&&!rightKey))
    playerShip.noBank();
  else if(leftKey)
    playerShip.bankLeft();
  else if(rightKey)
    playerShip.bankRight();
  leftKey=rightKey=false;

  playerShip.update();
  
  //trafienia
  for(auto& ship:enemyShips)
    if(ship.getType()!=Ship::Type::DESTROYED)
      for(auto& missile:missiles)
	ship.hit(missile);

  for(auto& missile:missiles)
    if(playerShip.hit(missile)) gameState=OVER;
       
  //Przeciwnik
  updateEnemy();
  //Pociski
  updateMissiles();
}


void Model::updateEnemy() {

  for(int i=0; i<8; i++)
    for(int j=2; j>=0; j--) {
      if(enemyShips[3*i+j].getType()!=Ship::Type::DESTROYED) {
	fireRand(enemyShips[3*i+j]); break;
      }
    };
  
  
  switch(enemyState) {

  case MOVE_L:
    if(enemyStateCounter >= 160) {
      enemyStateCounter = 0;
      enemyState=MOVE_R;
    } else {
      for(auto& ship: enemyShips)
	ship.setV(-0.1);
      enemyStateCounter++;
    }
    break;

    
  case MOVE_R:
    if(enemyStateCounter >= 160) {
      enemyStateCounter = 0;
      enemyState=MOVE_L;
    } else {
      for(auto& ship: enemyShips)
  	ship.setV(0.1);
      enemyStateCounter++;
    }
    break;

  }//switch

  for(auto& ship: enemyShips) {
    ship.update();
  }
  
}


void Model::updateMissiles() {
  for(auto& missile:missiles)
    missile.update();
  missiles.remove_if([](Missile &m) {return m.getType()==Missile::Type::VOID;});
}


void Model::fire(Ship &ship) {
  Missile::Type t;
  float adj;
  
  if (ship.getType() == Ship::Type::PLAYER) {t=Missile::Type::PLAYER; adj=3;}
  if (ship.getType() == Ship::Type::ENEMY) {t=Missile::Type::ENEMY; adj=-3;}

  missiles.push_back(Missile(ship.getX(),ship.getY()+adj,t));

}


void Model::fireKeyPressed() {
    if(gameState==OVER) {
      start();
    } else if(!fired) {
      fire(playerShip); fired=true;
    }
}

void Model::pauseKeyPressed() {
  if(!paused) {
    std::cout << "paused\n";
    paused=true;
    if(gameState==RUNNING)
      gameState=PAUSED;
    else if(gameState==PAUSED)
      gameState=RUNNING;
  }
}
void Model::pauseKeyNotPressed() {
  paused=false;
}


