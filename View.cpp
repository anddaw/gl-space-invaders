#include "View.h"
#include <iostream>


void View::display() {

  keysUpdate();

  glClearColor (0.0,0.0,0.0,1.0);
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity(); // Load the Identity Matrix to reset our drawing locations

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, -10.0f);
  glRotatef(zAngle, 1.0f, 0.0f, 0.0f);
  glRotatef(yAngle, 0.0f, 1.0f, 0.0f);
  glutWireTeapot(3.0);
  glPopMatrix();
  
  glFlush(); // Flush the OpenGL buffers to the window
  glutSwapBuffers();
}//display

void View::reshape(int width, int height) {
  // Set our viewport to the size of our window  
  glViewport(0, 0, (GLsizei)width, (GLsizei)height);
  // Switch to the projection matrix so that we can manipulate how our scene is viewed  
  glMatrixMode(GL_PROJECTION);
  // Reset the projection matrix to the identity matrix so that we don't get any artifacts (cleaning up)
  glLoadIdentity();
  // Set the Field of view angle (in degrees), the aspect ratio of our window, and the new and far planes
  gluPerspective(60, (GLfloat)width / (GLfloat)height, 1.0, 100.0);
  // Switch back to the model view matrix, so that we can start drawing shapes correctly 
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
  if(keysPressed['a'])
    yAngle = (yAngle-2);

  if(keysPressed['d'])
      yAngle = (yAngle+2);

    if(keysPressed['w'])
    zAngle = (zAngle-2);

  if(keysPressed['s'])
      zAngle = (zAngle+2);
}
