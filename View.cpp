#include "View.h"
#include <iostream>


void View::display() {

  keysUpdate();

  
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -camera.getRadius());
  glRotatef(camera.getXAngle(), 1.0f, 0.0f, 0.0f);
  glRotatef(camera.getYAngle(), 0.0f, 1.0f, 0.0f);
  glTranslatef(camera.getX(), 0, -camera.getZ());

  // Ship ship1(-2,60,Ship::Type::ENEMY);
  // Ship ship2(2,60,Ship::Type::ENEMY);
  // Ship ship3(0,0,Ship::Type::PLAYER);
  // drawShip(ship1);
  // drawShip(ship2);
  // drawShip(ship3);

  //  glPushMatrix();
  //  glTranslatef(0,-1,-105);
  // glScalef(15,0.01,21);
  //glutSolidCube(10);
  //glPopMatrix();


  drawModel();
  glPopMatrix();
  
  glFlush(); // Flush the OpenGL buffers to the window
  glutSwapBuffers();
}//display

void View::idle() {
  if(timer.elapsed() > 1.0/FPS) {
    timer.restart();
    display();
    keysUpdate();
    model.step();
    // std::cout << camera.getXAngle() << " " << camera.getYAngle() << " "
    // 	      << camera.getRadius() << std::endl; 
  }
}

void View::reshape(int width, int height) {
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 1000.0);
  glMatrixMode(GL_MODELVIEW);
}//reshape

void View::keyUp (unsigned char key, int, int){
  keysPressed[key] = false;
  //Test
}

void View::specialKeyUp (unsigned char key, int, int){
}

void View::keyPressed (unsigned char key, int, int){
  keysPressed[key] = true;
  //Test
}

void View::specialKeyPressed (unsigned char key, int, int){
}


void View::keysUpdate() {
  if(keysPressed['j'])
    camera.moveLeft();
  
  if(keysPressed['l'])
    camera.moveRight();
  
  if(keysPressed['i'])
    camera.moveUp();

  if(keysPressed['k'])
    camera.moveDown();
  
  if(keysPressed['='])
    camera.zoomIn();

  if(keysPressed['-'])
      camera.zoomOut();

  if(keysPressed['a'])
    model.leftKeyPressed();
     
  if(keysPressed['d'])
    model.rightKeyPressed();

  if(keysPressed[' '])
    model.fireKeyPressed();
  else
    model.fireKeyNotPressed();

  if(keysPressed['p'])
    model.pauseKeyPressed();
  else
    model.pauseKeyNotPressed();
  
}


void View::drawShip(Ship &ship) {
  if(ship.getType()==Ship::Type::DESTROYED) return;
  
  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);
  glEnableClientState(GL_COLOR_ARRAY);
  glEnable(GL_COLOR_MATERIAL);

  //pass the vertex pointer:
  glVertexPointer( 3,   //3 components per vertex (x,y,z)
		   GL_FLOAT,
		   0,
		   PlayerShipVertices);
  glNormalPointer( GL_FLOAT,
		   0,
		   PlayerShipNormals);

  if(ship.getType()==Ship::Type::PLAYER) {
  
  glColorPointer(  3,   //3 components per vertex (r,g,b)
		   GL_FLOAT,
		   0,
		   PlayerShipColors);  //Pointer to the first color
  } else if(ship.getType()==Ship::Type::ENEMY) {
  
  glColorPointer(  3,   //3 components per vertex (r,g,b)
		   GL_FLOAT,
		   0,
		   EnemyShipColors);  //Pointer to the first color
  }

  glPushMatrix();
  glTranslatef(xToViewX(ship.getX()), 0, yToViewZ(ship.getY()));
  glRotatef(ship.getBank(),0,0,-1);
  if(ship.getType()==Ship::Type::ENEMY) {
      glTranslatef(0.0f, 0.0f, -11.0f);
      glRotatef(180, 0.0f, 1.0f, 0.0f);
  }
  glDrawElements(GL_TRIANGLES, PlayerShipIndNb*3, GL_UNSIGNED_BYTE, PlayerShipIndices);
  glPopMatrix();
  
  glDisable(GL_COLOR_MATERIAL);
  glDisableClientState(GL_COLOR_ARRAY);
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  
}

void View::drawMissile(Missile &missile) {
  glPushMatrix();
  //glScalef(10,10,10); //TEST


  glEnableClientState(GL_VERTEX_ARRAY);
  glEnableClientState(GL_NORMAL_ARRAY);

  glVertexPointer(3,GL_FLOAT,0,missileVertices);
  glNormalPointer(GL_FLOAT,0,missileNormals);

  glTranslatef(xToViewX(missile.getX()), 0, yToViewZ(missile.getY()));
  if(missile.getType()==Missile::Type::ENEMY) {
      glTranslatef(0.0f, 0.0f, -5.0f);
      glRotatef(180, 0.0f, 1.0f, 0.0f);
      glMaterialfv(GL_FRONT,GL_EMISSION,enemyMissileEmission); 
  } else if (missile.getType()==Missile::Type::PLAYER)
    {
      glMaterialfv(GL_FRONT,GL_EMISSION,playerMissileEmission); 
    }

  glDrawElements(GL_TRIANGLES, PlayerShipIndNb*3, GL_UNSIGNED_BYTE, missileIndices);
  
  
  glDisableClientState(GL_NORMAL_ARRAY);
  glDisableClientState(GL_VERTEX_ARRAY);
  glMaterialfv(GL_FRONT,GL_EMISSION,defaultEmission);
  
  glPopMatrix();
	     

}

void View::drawModel(){
  drawShip(model.playerShip);
  for (auto& ship: model.enemyShips)
    drawShip(ship);
  for (auto& missile: model.missiles)
    drawMissile(missile);
}

GLfloat* View::getNormals(const GLfloat *vert, const GLubyte *ind, int v, int f) {
  Vector faceVectors[f];
  Vector vertexVectors[v];

  //znajduje normalne dla trojkatow
  for(int i=0; i<f; i++) {
    GLfloat ax = vert[3*ind[3*i]];
    GLfloat ay = vert[3*ind[3*i]+1];
    GLfloat az = vert[3*ind[3*i]+2];

    GLfloat bx = vert[3*ind[3*i+1]];
    GLfloat by = vert[3*ind[3*i+1]+1];
    GLfloat bz = vert[3*ind[3*i+1]+2];

    GLfloat cx = vert[3*ind[3*i+2]];
    GLfloat cy = vert[3*ind[3*i+2]+1];
    GLfloat cz = vert[3*ind[3*i+2]+2];

    Vector v1(bx-cx,by-cy,bz-cz);
    Vector v2(cx-ax,cy-ay,cz-az);

    faceVectors[i] = Vector::cross(v1,v2);
    faceVectors[i].normalize();
  }

  //znajduje normalne dla wierzcholkow
  for(GLubyte i=0; i<v; i++){
    for(int j=0; j<f*3; j++) {
      if(ind[j]==i) vertexVectors[i] = vertexVectors[i]+faceVectors[j/3];
    }
    vertexVectors[i].normalize();
  }

  GLfloat *tmp = new GLfloat[3*v];

  for(int i=0; i < v; i++) {
    tmp[3*i] = vertexVectors[i].x;
    tmp[3*i+1] = vertexVectors[i].y;
    tmp[3*i+2] = vertexVectors[i].z;
  }

  return tmp;

}


const GLfloat View::PlayerShipVertices[] = {
  //dziob
  0, 0, -11, //0

  -2, 0.5, -6, //1
  -1, 1, -6, //2
  1, 1, -6, //3
  2, 0.5, -6, //4
  2, -0.5, -6, //5
  1, -1, -6, //6
  -1, -1, -6, //7
  -2, -0.5, -6, //8

  -1, 0.25, 0, //9
  -0.5, 0.5, 0, //10
  0.5, 0.5, 0, //11
  1, 0.25, 0, //12
  1, -0.25, 0, //13
  0.5, -0.5, 0, //14
  -0.5, -0.5, 0, //15
  -1, -0.25, 0, //16

  //P. skrzydlo
  2,0,-6, //17
  1, -0.25, 0, //18
  1, 0.25, 0, //19
  5,-1,2, //20
  //L skrzydło
  -2,0,-6, //21
  -1,-0.25, 0, //22
  -1,0.25,0, //23
  -5,-1,2 //24
};

const int View::PlayerShipVertNb = 25;

const GLubyte View::PlayerShipIndices[] = {
  //Dziob - 8
  0,1,2,
  0,2,3,
  0,3,4,
  0,4,5,
  0,5,6,
  0,6,7,
  0,7,8,
  0,8,1,
  //Kadlub - 16
  1,2,9,
  2,9,10,
  2,3,10,
  3,10,11,
  3,4,11,
  4,11,12,
  4,5,12,
  5,12,13,
  5,6,13,
  6,13,14,
  6,7,14,
  7,14,15,
  7,8,15,
  8,15,16,
  8,1,16,
  1,16,9,
  //Rufa - 6
  16,10,9,
  16,15,10,
  15,10,11,
  15,14,11,
  14,12,11,
  14,13,12,
  //P. Skrzydlo - 4
  17,19,20,
  20,19,18,
  20,18,17,
  19,18,17,
  //L. Skrzydło - 4
  24,23,21,
  21,13,22,
  21,24,22,
  24,22,23
};

const int View::PlayerShipIndNb = 38;

const GLfloat View::PlayerShipColors[] = {
  0.3, 0.3, 0.7,

  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,

  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,

  0,0,1,
  0,0,0.1,
  0,0,0.1,
  0.5,0.5,1,

  0,0,1,
  0,0,0.1,
  0,0,0.1,
  0.5,0.5,1  
};

const GLfloat View::EnemyShipColors[] = {
  0.7, 0.3, 0.3,

  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,
  0.5,0.5,0.5,

  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,
  0.7,0.7,0.7,

  1,0,0,
  0.1,0,0,
  0.1,0,0,
  1,0.7,0,

  1,0,0,
  0.1,0,0,
  0.1,0,0,
  1,0.7,0,


};

const GLfloat View::playerMissileEmission[] = {0,1,0,1};
const GLfloat View::enemyMissileEmission[] = {1,0,0,1};
const GLfloat View::defaultEmission[] = {0,0,0,1};

const int View::missileVertNb = 12;

const GLfloat View::missileVertices[] = {

  -0.15,0.2,0,
  0.15,0.2,0,
  0.2,0,0,
  0.15,-0.2,0,
  -0.15,-0.2,0,
  -0.2, 0, 0,

  -0.15,0.2,5,
  0.15,0.2,5,
  0.2,0,5,
  0.15,-0.2,5,
  -0.15,-0.2,5,
  -0.2, 0, 5

};

const int View::missileIndNb = 12;
const GLubyte View::missileIndices[] = {
  0,1,6,
  1,6,7,
  1,2,7,
  2,7,8,
  2,3,8,
  3,8,9,
  3,4,9,
  4,9,10,
  4,5,10,
  5,10,11,
  5,0,11,
  0,11,6
};


