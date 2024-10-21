#define NDEBUG
#include <GL/glut.h>
#include <iostream>
using namespace std;

void LineDDA(int x0, int y0, int x1, int y1)
{
	int  x; 
	float y, m;
	int dx = x1 - x0;
	int dy = y1 - y0;
	m = (float)dy / (float)dx;
	y = y0;

	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	for (x = x0 + 1; x < x1; x++)
	{
		y += m;
		glVertex2i(x, (int)(y + 0.5));
	}
	glVertex2i(x1, y1);
	glEnd();
}

void LineSimple(int x0, int y0, int x1, int y1)
{
	int  x;
	float y, m;
	int dx = x1 - x0;
	int dy = y1 - y0;
	m = (float)dy / (float)dx;
	float b = y0 - m*x0;

	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	b = b + 0.5;
	for (x = x0+1; x < x1; x++)
	{
		y = m * x + b;
		glVertex2i(x, (int)y);
		cout << "x=" << x << " y=" << (int)(y + 0.5) << endl;
	}
	glVertex2i(x1, y1);
	glEnd();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	//LineDDA(0, 0, 300, 200);
	LineSimple(0, 0, 300, 200);
	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}

void Reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello Line!");
	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}