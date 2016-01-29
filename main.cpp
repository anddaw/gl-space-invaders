#include <thread>
#include <iostream>
#include "Model.h"
#include "Geometry.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include "View.h"

View view;

void display (void) {  
  view.display();
}

void idle (void) {
  view.idle();
}

void reshape(int width, int height) {
  view.reshape(width,height);
}

void keyPressed (unsigned char key, int x, int y) {
  view.keyPressed(key, x, y);
}

void keyUp (unsigned char key, int x, int y) {
  view.keyUp(key, x, y);
}

void init (void) {
  glShadeModel(GL_SMOOTH);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
  glEnable (GL_LIGHT1);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); // Initialize GLUT
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (800, 600); // Set the width and height of the window  
  glutInitWindowPosition (100, 100); // Set the position of the window  
  glutCreateWindow ("GKOM - Space Invaders"); // Set the title for the window

  init();

  //Obsluga klawiszy w XWindow
  glutIgnoreKeyRepeat(true);

  // GLUT Callbacks
  glutKeyboardFunc(keyPressed);
  glutKeyboardUpFunc(keyUp);
  glutDisplayFunc(display); 
  glutReshapeFunc(reshape); 
  glutIdleFunc(idle);
  
  glutMainLoop(); // Enter GLUT's main loop  

  // /** TESTY **/

  // View::Vector vector1 (2,3,4);
  // View::Vector vector2 (5,6,7);
  // //  vector1.normalize();
  // View::Vector c = View::Vector::cross(vector1, vector2);

  // c = c * -1;
  
  // std::cout << c.x << " " << c.y << " " << c.z << std::endl;
  
}
