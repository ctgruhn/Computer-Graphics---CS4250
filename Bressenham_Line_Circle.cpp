#include <GL/glut.h>
#include <iostream>
#include<string>


class Shape
{
public:
	virtual void displayImage() {}
	virtual std::string getTitle() { return "Shape and Inputs"; }
};

class Circle : public Shape
{
private:
	int xc, yc, r;
	void plotCircle(int, int);

public:
	Circle(int x, int y, int r0)
	{
		xc = x;
		yc = y;
		r = r0;
	}

	void displayImage();
	std::string getTitle()
	{
		return "Circle center/radius: (" + std::to_string(xc) + ", " + std::to_string(yc) + ", " + std::to_string(r) + ")";;
	}
};

class Line : public Shape
{
private:
	int xStart, xEnd;
	int yStart, yEnd;

public:
	Line(int xs, int ys, int xe, int ye)
	{
		xStart = xs;
		yStart = ys;
		xEnd = xe;
		yEnd = ye;
	}
	void displayImage();
	std::string getTitle()
	{
		return "Line begin/end: (" + std::to_string(xStart) + ", " + std::to_string(yStart) + ") (" + std::to_string(xEnd) + ", " + std::to_string(yEnd) + ")";
	}
};


void myInit() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 200.0, 0.0, 200.0);
}

void setPixel(int x, int y) {
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}

void Circle::plotCircle(int x, int y)

{
	//Set pixels in each octant based on center of circle
	setPixel(xc + x, yc + y);
	setPixel(xc - x, yc + y);
	setPixel(xc + x, yc - y);
	setPixel(xc - x, yc - y);
	setPixel(xc + y, yc + x);
	setPixel(xc - y, yc + x);
	setPixel(xc + y, yc - x);
	setPixel(xc - y, yc - x);
}

void Circle::displayImage()

{
	int x = 0;
	int y = r;
	int p = 1 - r;

	plotCircle(x, y);

	while (x < y)
	{
		if (p < 0)
		{
			x++;
			p = p + 2 * x + 1;
		}
		else
		{
			x++;
			y--;
			p = p + 2 * x + 1 - 2 * y;
		}
		plotCircle(x, y);

	}
}

void Line::displayImage()
{
	int x = xStart;
	int y = yStart;
	int dx = xEnd - xStart;
	int dy = yEnd - yStart;

	int p = 2 * dy - 2 * dx;
	for (int i = 1; i < dx; i++)
	{
		if (p < 0)
		{
			x++;
			p = p + 2 * (yEnd - y);
		}
		else
		{
			x++;
			y++;
			p = p + 2 * (yEnd - y) - 2 * (xEnd - x);
		}
		setPixel(x, y);
	}
}

void myDisplay() {
	glFlush();
}

int main(int argc, char** argv)
{

	std::string shapeRequested;
	std::string title;
	int xc, yc, r;
	int xStart, yStart, xEnd, yEnd;

	Shape* obj;



	std::cout << "Would you like to draw a circle or a line?" << std::endl;
	std::cin >> shapeRequested;

	if (shapeRequested == "line")

	{
		std::cout << "Enter starting coordinates (x and y):" << std::endl;
		std::cin >> xStart >> yStart;
		std::cout << "Enter ending coordinates (x and y):" << std::endl;
		std::cin >> xEnd >> yEnd;

		obj = new Line(xStart, yStart, xEnd, yEnd);
	}
	else if (shapeRequested == "circle")
	{
		std::cout << "Enter center coordinates and radius (x y and r):" << std::endl;
		std::cin >> xc >> yc >> r;

		obj = new Circle(xc, yc, r);

	}
	else
	{
		std::cout << "Not a valid input" << std::endl;
		return 0;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100);

	title = obj->getTitle();

	glutCreateWindow(title.c_str());

	myInit();

	obj->displayImage();

	glutDisplayFunc(myDisplay);
	glutMainLoop();
}