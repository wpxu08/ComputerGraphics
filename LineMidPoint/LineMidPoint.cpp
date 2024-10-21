#include <GL/glut.h>
#include<algorithm>
using namespace std;

void LineDDA(int x0, int y0, int x1, int y1/*,int color*/)
{
	int  x, dy, dx;
	float y, k;
	dx = x1 - x0;
	dy = y1 - y0;
	k = (float)dy / (float)dx;
	x = x0;
	y = y0;

	glColor3f(1.0f, 1.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	printf("%d, %d\n", x0, y0);
	for (x = x0+1; x <= x1; x++)
	{
		y += k;
		glVertex2i(x, (int)(y + 0.5));
		printf("%d, %d\n", x, (int)(y + 0.5));
	}
	glVertex2i(x1, y1);
	printf("%d, %d\n", x1, y1);
	glEnd();
}

void LineMidPoint(int x0, int y0, int x1, int y1)
{
	//请在这里填写你的代码
	int dx, dy, dt, db, d, x, y;
	dx = x1 - x0;
	dy = y1 - y0;
	d = dx - 2 * dy;
	dt = 2 * dx - 2 * dy;
	db = -2 * dy;
	x = x0; y = y0;
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(1);
	glVertex2i(x, y);
	printf("%d, %d\n", x, y);
	while (x < x1)
	{
		if (d < 0)
		{
			x++;
			y++;
			d += dt;
		}
		else
		{
			x++;
			d += db;
		}
		glVertex2i(x, y);
		printf("%d, %d\n", x, y);
	}
	glVertex2i(x1, y1);
	printf("%d, %d\n", x1, y1);
	glEnd();
}

void LineMidPointV1(int x0, int y0, int x1, int y1)
{
	//请在这里填写你的代码
	int dx, dy, dt, db, d, x, y;
	dx = x1 - x0;
	dy = y1 - y0;
	d = dx - 2 * dy;

	x = x0; y = y0;
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(1);
	glVertex2i(x, y);
	while (x < x1)
	{
		x++;
		d += -2 * dy;
		if (d < 0)
		{

			y++;
			d += 2 * dx;
		}

		glVertex2i(x, y);
	}
	glVertex2i(x1, y1);
	glEnd();
}

void LineWhileLoop(int x0, int y0, int x1, int y1)
{
	glPointSize(1);
	glBegin(GL_POINTS);
	glVertex2i(x0, y0);
	printf("%d, %d\n", x0, y0);

	int dx, dy, sx, sy, x, y;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	x = x0; y = y0;
	if (dx > dy)
	{
		int d = dx - 2 * dy;
		while (x != x1)
		{
			x += sx;
			if (d < 0)
			{
				y += sy;
				d += 2 * dx - 2 * dy;
			}
			else
			{
				d += -2 * dy;
			}
			glVertex2i(x, y);
			printf("%d, %d\n", x, y);
		}
	}
	else
	{
		int d = dy - 2 * dx;
		while (y != y1)
		{
			y += sy;
			if (d < 0)
			{
				x += sx;
				d += 2 * dy - 2 * dx;
			}
			else
			{
				d += -2 * dx;
			}
			glVertex2i(x, y);
			printf("%d, %d\n", x, y);
		}
	}

	glVertex2i(x1, y1);
	printf("%d, %d\n", x1, y1);
	glEnd();
}

void LineForLoop(int x0, int y0, int x1, int y1)
{
	// 请在此添加你的代码
	  /********** Begin ********/
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glPointSize(1);

	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	if (dx > dy) // x方向为步进方向
	{
		if (x0 > x1) //确保x0<x1，这样循环中x=x+1
		{
			swap(x0, x1);
			swap(y0, y1);
		}

		int d = dx - 2 * dy;
		int d1 = 2 * dx - 2 * dy;
		int d2 = -2 * dy;
		int x = x0;
		int y = y0;
		int yIncr = (y1 > y0) ? 1 : -1; // 比较两端点y值大小决定y的增量值
		glVertex2i(x, y);
		printf("%d, %d\n", x, y);
		for (int x = x0 + 1; x <= x1; x++)
		{
			if (d < 0)
			{
				y = y + yIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2i(x, y);
			printf("%d, %d\n", x, y);
		}
	}
	else
	{
		if (y0 > y1)
		{
			swap(x0, x1);
			swap(y0, y1);
		}

		int d = dy - 2 * dx;
		int d1 = 2 * dy - 2 * dx;
		int d2 = -2 * dx;
		int x = x0;
		int y = y0;
		int xIncr = (x1 > x0) ? 1 : -1;
		glVertex2i(x, y);
		printf("%d, %d\n", x, y);
		for (int y = y0 + 1; y <= y1; y++)
		{
			if (d < 0)
			{
				x = x + xIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2i(x, y);
			printf("%d, %d\n", x, y);
		}
	}
	glEnd();
	/********** End **********/
}

void LineWY(int x0, int y0, int x1, int y1)
{
	// 请在此添加你的代码
	  /********** Begin ********/
	glColor3f(0.0f, 1.0f, 0.0f);
	glPointSize(1);
	glBegin(GL_POINTS);
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	if (dx > dy)
	{
		if (x0 > x1)
		{
			swap(x0, x1);
			swap(y0, y1);
		}

		int d = dx - 2 * dy;
		int d1 = 2 * dx - 2 * dy;
		int d2 = -2 * dy;
		int x = x0;
		int y = y0;
		int yIncr = (y1 > y0) ? 1 : -1;
		glVertex2f(x, y);
		for (int x = x0; x <= x1;)
		{

			if (d < 0)
			{
				y = y + yIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2f(x, y);
			x++;
		}
	}
	else
	{
		if (y0 > y1)
		{
			swap(x0, x1);
			swap(y0, y1);
		}

		int d = dy - 2 * dx;
		int d1 = 2 * dy - 2 * dx;
		int d2 = -2 * dx;
		int x = x0;
		int y = y0;
		int xIncr = (x1 > x0) ? 1 : -1;
		glVertex2f(x, y);
		for (int y = y0; y <= y1;)
		{

			if (d < 0)
			{
				x = x + xIncr;
				d = d + d1;
			}
			else
				d = d + d2;

			glVertex2f(x, y);
			y++;
		}
	}
	glEnd();



	/********** End **********/
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);

	//LineForLoop(13, 20, 180, 140);
	//printf("!!!\n");
	//LineWhileLoop(13, 20, 180, 140);
	LineWY(13, 20, 180, 140);

	//LineDDA(13, 20, 180, 140);
	//printf("!!!\n");
	//LineMidPoint(13, 20, 180, 140);

	//Line(261, 215, 344, 275);
	//Line(344, 275, 429, 213);
	//Line(429, 213, 398, 319);
	//Line(398, 319, 477, 384);
	//Line(477, 384, 378, 384);
	//Line(378, 384, 344, 491);
	//Line(344, 491, 310, 384);
	//Line(310, 384, 209, 384);
	//Line(209, 384, 292, 319);
	//Line(292, 319, 261, 215);

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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello Line!");
	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(Reshape);
	glutMainLoop();
	return 0;
}