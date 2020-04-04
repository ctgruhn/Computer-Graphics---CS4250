#include <iostream>
#include <GL/glut.h>
//Test 7: Animation of a cube, with a time delay. Composite transformation as well    
GLfloat rotationAngleInDegrees;
#define animationMilliSeconds 10   //time gap b/w frames

void redisplayFunc(void) {
	glClear(GL_COLOR_BUFFER_BIT); //clear draw buffer
	// clear the identity matrix.
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -5.0); // translate by z = -5.0; z = -8 looks smaller
	glColor3f(0.9, 0.0, 0.0);	//some color, red
	glRotatef(rotationAngleInDegrees, 1.0, 0.0, 0.0); // rotation about X axis
	glScalef(1.0, 1.0, 1.0); // scaling transformation

	glutWireCube(1.0); // built-in (glut library) wire-cube
	glFlush();
	glutSwapBuffers(); // double buffering
}
void reshapeFunc(int x, int y) {
	//kicks in when user resizes window
	if (y == 0 || x == 0) return;  //Nothing is visible then, so return
	//Set a new projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Angle of view:40 degrees; aspect ratio = x/y
	//Near clipping plane distance: 0.5; far clip 20
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 20.0);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);  //Use the whole window for rendering
}
void animationFunction(int val) {
	rotationAngleInDegrees += 0.03; //rotate around X axis
	redisplayFunc();
	glutTimerFunc(animationMilliSeconds, animationFunction, 0);

}
int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //double buffer …
	glutInitWindowSize(350, 350);
	glutCreateWindow("Test 7: 3D cube animation");
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	rotationAngleInDegrees = 0.0;

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glutDisplayFunc(redisplayFunc);
	glutReshapeFunc(reshapeFunc);
	glutTimerFunc(animationMilliSeconds, animationFunction, 0);
	glutMainLoop();
}
