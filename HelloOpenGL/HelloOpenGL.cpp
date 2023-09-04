// HelloOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <GL/glut.h>
void myDisplay(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	glPointSize(3);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);   glVertex2f(-0.4f, -0.4f);
	glColor3f(0.0f, 1.0f, 0.0f);   glVertex2f(0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);   glVertex2f(0.4f, 0.4f);
	glEnd();

	glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f);   
		glVertex2f(-0.4f, -0.4f);
		glColor3f(0.0f, 1.0f, 0.0f);   
		glVertex2f(0.0f, 0.0f);
	glEnd();


	glFlush();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Hello OpenGL!");
	glutDisplayFunc(&myDisplay);
	glutMainLoop();
	return 0;
}
