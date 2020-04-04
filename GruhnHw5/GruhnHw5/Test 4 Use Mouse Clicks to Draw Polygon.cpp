/**
Draw polygon based on mouse click
Each left mouse click adds a vertex. Line drawn connecting it to the previous
vertex. Right click draws a closed polygon. To clear and start over, hit left.

Review it so you get a handle ont he fine details.
*/

/**
mouseCollectPoints function : Collects all points user clicks.
   Each left mouse hit: add its x and y coord as a point to the
		 array ptListX, ptListY
   If right mouse click => closed poly.     To clear and start over, hit left.

trackMouseMove function: tracks x,y coord of passive mouse move –
		no button press

Display function: Collects the points
  continuously (from the earlier ptListX, ptListY) and draws the line strip.

glutPassiveMotionFunc: registers the trackMouseMove function
glutMouseFunc: registers the mouseCollectPoints function

gluOrtho2D(0, wndSizwX, window SizeYWidth , 0);
	  Flips Y-Axis of the orthographic projection
	  to match the view space to the mouse coordinates

*/

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
void mouseCollectPoints(int button, int state, int x, int y) {
	mouseX = x;
	mouseY = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if (closed || noOfPts >= MaxNoOfPointsConstant - 1)
			noOfPts = 0; // restart the polygon
		closed = 0;
		ptListX[noOfPts] = mouseX;
		ptListY[noOfPts] = mouseY;
		noOfPts++;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		closed = 1;
}
void trackMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
	glutPostRedisplay();
}
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

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(windowSizeXWidth, windowSizeYWidth);
	glutInitWindowPosition(initialWindPosnXcoord, initialWindPosnYcoord);
	glutCreateWindow("Click Mouse & Draw Polygon - Open/(Closed R Click) ");
	gluOrtho2D(0, windowSizeXWidth, windowSizeYWidth, 0); // flip Y

	glutDisplayFunc(Display);
	glutMouseFunc(mouseCollectPoints);
	glutPassiveMotionFunc(trackMouseMove);
	glutMainLoop();
}
/**
Credit: From here! ...
https://stackoverflow.com/questions/48181748/not-getting-an-output-for-opengl-to-print-line-using-mouse-click

*/
