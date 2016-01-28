#ifndef VIEW_AD
#define VIEW_AD

#include <GL/gl.h>
#include <GL/glut.h>

class View {

private:
  bool keysPressed[255];

  //Test
  float yAngle;
  float zAngle;

  //Struct na potrzeby tworzenia VertexArray
  struct Vertex {
    //Wspolrzędne
    GLfloat x, y, z;
    //Kolory
    GLfloat r, g, b;
  };

  
public:
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
  }
  
};

#endif
