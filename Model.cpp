/* Model */
#include "Model.h"


Model::Model() {

  playerShip = Ship(0,0,Ship::Type::PLAYER);
  
  //ustawianie statków przeciwnika
  enemyShips.resize(24);

  for(int j=0; j<3; ++j)
    for(int i=0; i<8; ++i)
      enemyShips[8*j+i] = Ship(-3+4*i,60-5*j,Ship::Type::ENEMY);
  //stan przeciwnika
  enemyState=MOVE_L;
  enemyStateCounter=0;
  
}

void Model::step() {

  if((leftKey && rightKey) || (!leftKey&&!rightKey))
    playerShip.noBank();
  else if(leftKey)
    playerShip.bankLeft();
  else if(rightKey)
    playerShip.bankRight();
  leftKey=rightKey=false;

  playerShip.update();


  //Przeciwnik
  updateEnemy();
}


void Model::updateEnemy() {

  switch(enemyState) {

  case MOVE_L:
    if(enemyStateCounter==0)
      for(auto& ship: enemyShips)
  	ship.bankLeft();
      
     if(enemyStateCounter==2)
      for(auto& ship: enemyShips)
  	ship.noBank();

      if(enemyStateCounter==198)
      for(auto& ship: enemyShips)
  	ship.bankRight();

      if(enemyStateCounter==200) {
	for(auto& ship: enemyShips)
	  ship.noBank();
	enemyStateCounter=0;
	enemyState=MOVE_R;
      } else {
	enemyStateCounter++;
      }
      break;

  case MOVE_R:
        if(enemyStateCounter==0)
      for(auto& ship: enemyShips)
  	ship.bankRight();
      
     if(enemyStateCounter==2)
      for(auto& ship: enemyShips)
  	ship.noBank();

      if(enemyStateCounter==198)
      for(auto& ship: enemyShips)
  	ship.bankLeft();

      if(enemyStateCounter==200) {
	for(auto& ship: enemyShips)
	  ship.noBank();
	enemyStateCounter=0;
	enemyState=MOVE_L;
      } else {
	enemyStateCounter++;
      }
    break;
  }//switch

  for(auto& ship: enemyShips) {
    ship.update();
    ship.print();
  }
  
}


