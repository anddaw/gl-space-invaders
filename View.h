#ifndef VIEW_AD
#define VIEW_AD

#include <GL/gl.h>
#include <GL/glut.h>
#include "Model.h"
#include <math.h>
#include <boost/timer.hpp>

class View {

  class Camera {
  
    float xAngle;
    float yAngle;
    float radius;
    //Wspolrzedne punktu na ktory kamera patrzy
    float x;
    float z;

    const float STEP = 1;

  public:
    Camera(void): xAngle(66), yAngle(0), radius(166), x(0), z(-80) {}
    float getXAngle() {return xAngle;}
    float getYAngle() {return yAngle;}
    float getX() {return x;}
    float getZ() {return z;}
    float getRadius() {return radius;}
    void moveRight() {yAngle-=STEP;}
    void moveLeft() {yAngle+=STEP;}
    void moveUp() {xAngle+=STEP;}
    void moveDown() {xAngle-=STEP;}
    void zoomIn() {radius -=STEP; if(radius<0) radius=0;}
    void zoomOut() {radius +=STEP;}
  };

  
private:
  //Model
  Model model;
  
  //Kamera
  Camera camera;
  
  bool keysPressed[255];

  static const int PlayerShipVertNb;
  static const int PlayerShipIndNb;
  static const GLfloat PlayerShipVertices[];
  static const GLubyte PlayerShipIndices[];
  GLfloat *PlayerShipNormals;
  static const GLfloat PlayerShipColors[];
  static const GLfloat EnemyShipColors[];

  static const int missileVertNb;
  static const int missileIndNb;
  static const GLfloat missileVertices[];
  static const GLubyte missileIndices[];
  GLfloat *missileNormals;
  static const GLfloat playerMissileEmission[];
  static const GLfloat enemyMissileEmission[];
  static const GLfloat defaultEmission[];

  //Konwersja ze wspolrzednych modelu
  float xToViewX(float  x) {return 3.0*x;}
  float yToViewZ(float  y) {return -3.0*y;}
  
  
  //Rysuje statek
  void drawShip(Ship &ship);

  //Rysuje pocisk
  void drawMissile(Missile &missile);
  
  //Rysuje model
  void drawModel();

  //timer
  boost::timer timer;
  static const int FPS = 60;

  //Liczenie normalnych
  class Vector;
  static GLfloat* getNormals(const GLfloat *vert, const GLubyte *ind, int v, int f);
  
public:
  // GLUT callbacks

  //rysowanie
  void display();
  //zmiana rozmiaru okna
  void reshape(int, int);

  void idle();

  void keyPressed (unsigned char, int, int);
  void specialKeyPressed (unsigned char, int, int);
  void keyUp (unsigned char, int, int);
  void specialKeyUp (unsigned char, int, int);

  //Obsluga zdarzen klawiszy
  void keysUpdate();

  View() {
    for(int i=0; i<256; i++) keysPressed[i]=false;

    PlayerShipNormals = getNormals(PlayerShipVertices,
					 PlayerShipIndices,
					 PlayerShipVertNb,
					 PlayerShipIndNb);
    missileNormals = getNormals(missileVertices,
					 missileIndices,
					 missileVertNb,
					 missileIndNb);
  }
  
};




class View::Vector {
public:
  float x;
  float y;
  float z;

  Vector (void): x(0), y(0), z(0) {}
  Vector (float _x,float _y,float _z): x(_x), y(_y), z(_z) {}

  

  Vector (const Vector& vector): x(vector.x), y(vector.y), z(vector.z) {};

  float getLenght() {
    return sqrt(x*x+y*y+z*z);
  }
  
  void normalize() {
    float lenght = getLenght();
    x=x/lenght;
    y=y/lenght;
    z=z/lenght;
  }

  Vector operator+(const Vector& vector) {
    Vector tmp(x+vector.x, y+vector.y, z+vector.z);
    return tmp;
  }

  Vector &operator=(const Vector &vector) {
    x=vector.x;
    y=vector.y;
    z=vector.z;
    return *this;
  }

  static Vector cross(const Vector &a, const Vector &b)
  {
    Vector tmp(a.y*b.z-a.z*b.y,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);
    return tmp;
  }

  Vector operator*(const float s) {
    Vector tmp(x*s, y*s, z*s);
    return tmp;
  }
  
};
#endif
