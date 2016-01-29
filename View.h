#ifndef VIEW_AD
#define VIEW_AD

#include <GL/gl.h>
#include <GL/glut.h>
#include "Model.h"
#include <math.h>

class View {

private:
  bool keysPressed[255];

  //Test
  float yAngle;
  float zAngle;

  static const int PlayerShipVertNb;
  static const int PlayerShipIndNb;
  static const GLfloat PlayerShipVertices[];
  static const GLubyte PlayerShipIndices[];
  GLfloat *PlayerShipNormals;
  
  static const GLfloat PlayerShipColors[];
  
  
  //Rysuje statek
  void drawShip(const Ship &ship);


  
public:
  class Vector;

  static GLfloat* getNormals(const GLfloat *vert, const GLubyte *ind, int v, int f);

  // GLUT callbacks

  //rysowanie
  void display();
  //zmiana rozmiaru okna
  void reshape(int, int);

  void keyPressed (unsigned char, int, int);
  void specialKeyPressed (unsigned char, int, int);
  void keyUp (unsigned char, int, int);
  void specialKeyUp (unsigned char, int, int);

  //Obsluga zdarzen klawiszy
  void keysUpdate();

  View() {
    for(int i=0; i<256; i++) keysPressed[i]=false;
    zAngle = yAngle = 0;

    PlayerShipNormals = getNormals(PlayerShipVertices,
					 PlayerShipIndices,
					 PlayerShipVertNb,
					 PlayerShipIndNb);
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
