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
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv); // Initialize GLUT
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
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
  glutIdleFunc(glutPostRedisplay);//Zmienić!
  
  glutMainLoop(); // Enter GLUT's main loop  
  
}
