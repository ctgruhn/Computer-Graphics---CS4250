#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;


int windowSizeXWidth = 400, windowSizeYWidth = 300; // size of the window
int mouseX = 0, mouseY = 0;         // current mouse position
int initialWindPosnXcoord = 0, initialWindPosnYcoord = 0;

#define MaxNoOfPointsConstant   123
int ptListX[MaxNoOfPointsConstant]; // X coordinate ot the input points 
int ptListY[MaxNoOfPointsConstant]; // Y coordinate of the input points

int noOfPts = 0;      // number of input points
int closed = 0;       // marke polygon "closed"

void Display() {
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	if (noOfPts)
	{
		glLineWidth(5.0);
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < noOfPts; ++i)
			glVertex2f((float)ptListX[i], (float)ptListY[i]);
		if (closed)
			glVertex2f((float)ptListX[0], (float)ptListY[0]);
		else
			glVertex2f((float)mouseX, (float)mouseY);
		glEnd();
	}

	glFlush();

}

//int main(int argc, char **argv) {
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
//
//	glutInitWindowSize(windowSizeXWidth, windowSizeYWidth);
//	glutInitWindowPosition(initialWindPosnXcoord, initialWindPosnYcoord);
//
//	glutCreateWindow("Click Mouse & Draw Polygon - Open/(Closed R Click) ");
//	gluOrtho2D(0, windowSizeXWidth, windowSizeYWidth, 0); // flip Y
//
//	glutDisplayFunc(Display);
//	glutMouseFunc(mouseCollectPoints);
//	glutPassiveMotionFunc(trackMouseMove);
//	glutMainLoop();
//}

//int main(int argc, char* argv[]) {
//	glutInit(&argc, argv);
//
//	glutInitWindowSize(500, 500);
//	glutInitWindowPosition(0, 0);
//	glutInitDisplayMode(GLUT_RGB);
//
//	/* create and set up a window */
//	glutCreateWindow("Test 6E wip: Modeling, Viewing, and Projection Transforms");
//	glutDisplayFunc(display);
//	glutReshapeFunc(reshape);
//
//	/* tell GLUT to wait for events */
//	glutMainLoop();
//}