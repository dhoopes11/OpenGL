//============================================================================
// Name        : Cube.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

//Danielle Hoopes


#include <GL/glut.h>

/*Depth and tessellation settings */
void applyDepthSetting()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);   //Set background color black/opaque
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

/*Implements Display Callback Handler */
void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Clears color and depth buffers
	glMatrixMode(GL_MODELVIEW);                         //Activates the model-View matrix

	glLoadIdentity();
	glTranslatef(-0.0f, 0.0f, -8.0f);  //move model to the center of the world with a z depth of -7
	glRotatef(45.0f, 0.4f ,-1.0f, -0.1f); //Rotate the model on x, y and z

//Creates Cube

glBegin(GL_QUADS);


//Set front face color red and vertex coords

glColor3f(1.0f, 0.0f, 0.0f);
glVertex3f( 0.5f, 1.0f, 1.0f);
glVertex3f(-0.5f, 1.0f, 1.0f);
glVertex3f(-1.0f, -1.0f, 1.0f);
glVertex3f(1.0f, -1.0f, 1.0f);


//Set right face color green and vertex coords

glColor3f(0.0f, 1.0f, 0.0f);
glVertex3f(0.5f, 1.0f, -1.0f);
glVertex3f(0.5f, 1.0f, 1.0f);
glVertex3f(1.0f, -1.0f, 1.0f);
glVertex3f(1.0f, -1.0f, -1.0f);

//Set top face color blue and vertex coords

glColor3f(0.0f, 0.0f, 1.0f);
glVertex3f(0.5f, 1.0f, -1.0f);
glVertex3f(0.5f, 1.0f, 1.0f);
glVertex3f(-0.5f, 1.0f, 1.0f);
glVertex3f(-0.5f, 1.0f, 1.0f);

//Set left face color yellow and vertex coords

glColor3f(1.0f, 1.0f, 0.0f);
glVertex3f(-1.0f, -1.0f, -1.0f);
glVertex3f(-1.0f, -1.0f, 1.0f);
glVertex3f(-0.5f, 1.0f, 1.0f);
glVertex3f(-0.5f, 1.0f, -1.0f);

//Set back face color dull green and vertex coords

glColor3f(0.0f, 0.5f, 0.4f);
glVertex3f(0.5f, 1.0f, -1.0f);
glVertex3f(-0.5f, 1.0f, -1.0f);
glVertex3f(-1.0f, -1.0f, -1.0f);
glVertex3f(1.0f, -1.0f, -1.0f);

//Set bottom face color grey and vertex coords

glColor3f(0.5f, 0.5f, 0.5f);
glVertex3f(1.0f, -1.0f, 1.0f);
glVertex3f(1.0f, -1.0f, 1.0f);
glVertex3f(-1.0f, -1.0f, -1.0f);
glVertex3f(-1.0f, -1.0f, 1.0f);

glEnd();

glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
	if (height == 0) height =1;
	  GLfloat aspect = (GLfloat)width / (GLfloat)height;

	  glViewport(0,0, width, height); //set aspect ratio of the clipping volume to match the viewport

	  glMatrixMode(GL_PROJECTION);    //Create projection matrix
	  glLoadIdentity();               //Reset projection matrix

	  gluPerspective(45.0f, aspect, 0.1f, 100.0f); //Set perspective projection, fov, aspect, xNear and zFar clipping
}

	  int main(int argc, char** argv)
	  {
		  glutInit(&argc, argv);            //Initializes freeglut library
		  glutInitDisplayMode(GLUT_DOUBLE); //Enable double buffered mode
		  glutInitWindowSize(640, 480);     //Specifies the window's width and height
		  glutInitWindowPosition(0 , 0);    //Specifies top-left corner
		  glutCreateWindow("Danielle Hoopes"); //Create Window and Title
		  glutDisplayFunc(display);            //Sets the display callback for the screen re-paint
		  glutReshapeFunc(reshape);            //Sets the display callback for the window re-resize
		  applyDepthSetting();                 //Apply depth settings
		  glutMainLoop();                      //Enter the infinite event-processing loop
		  return 0;


	  }

