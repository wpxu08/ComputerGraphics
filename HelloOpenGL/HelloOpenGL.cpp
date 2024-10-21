// HelloOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <GL/glut.h>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	// 请在此添加你的代码
	/********** Begin ********/
	glPointSize(5);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex2i(13, 20);
	glColor3f(0.0f, 1.0f, 0.0f);   glVertex2i(180, 140);
	glEnd();

	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex2i(13, 20);		glVertex2i(180, 140);
	glEnd();

	/********** End **********/

	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);
}

void myReshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Hello Point!");
	Init();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(myReshape);
	glutMainLoop();
	return 0;
}
