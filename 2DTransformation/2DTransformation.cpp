// HelloOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <GL/glut.h>
#include "geometry.h"
using namespace std;

const double PI = acos(-1.0);
Matrix translation(Vec2i v) {
	Matrix Tr = Matrix::identity(3);
	// Please add the code here
	/********** Begin ********/
	Tr[0][2] = v.x;
	Tr[1][2] = v.y;
	/********** End *********/
	return Tr;
}
Matrix scale(float factorX, float factorY)
{
	Matrix Z = Matrix::identity(3);
	/********** Begin ********/
	Z[0][0] = factorX;
	Z[1][1] = factorY;
	/********** End *********/
	return Z;
}
Matrix rotation(float angle)
{
	angle = angle * PI / 180;
	float sinangle = sin(angle);
	float cosangle = cos(angle);
	Matrix R = Matrix::identity(3);
	/********** Begin ********/
	R[0][0] = R[1][1] = cosangle;
	R[0][1] = -sinangle;
	R[1][0] = sinangle;
	/********** End *********/
	return R;
}

void BasicTransformation()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t = { 50, 50 };
	Matrix T = translation(t);
	Matrix S = scale(0.5, 0.5);
	Matrix R = rotation(30);
	for (int i = 0; i < 4; i++)
	{
		glColor3f(1.0f, 0.0f, 0.0f);
		Line(P[i], P[(i + 1) % 4]);

		Vec3f tP0 = T * P[i];
		Vec3f tP1 = T * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(tP0, tP1);

		Vec3f sP0 = S * P[i];
		Vec3f sP1 = S * P[(i + 1) % 4];
		glColor3f(0.0f, 0.0f, 1.0f);
		Line(sP0, sP1);

		Vec3f rP0 = R * P[i];
		Vec3f rP1 = R * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rP0, rP1);
	}
}

void CompositeTranslateScale()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t = { 50, 50 };
	Matrix T = translation(t);
	Matrix S = scale(0.5, 0.5);
	Matrix ST = T * S;
	Matrix TS = S * T;
	for (int i = 0; i < 4; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		Line(P[i], P[(i + 1) % 4]);

		Vec3f sP0 = S * P[i];
		Vec3f sP1 = S * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(sP0, sP1);

		Vec3f stP0 = TS * P[i];
		Vec3f stP1 = TS * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(stP0, stP1);

		Vec3f tP0 = T * P[i];
		Vec3f tP1 = T * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(tP0, tP1);

		Vec3f tsP0 = ST * P[i];
		Vec3f tsP1 = ST * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(tsP0, tsP1);
	}
}

void CompositeTranslateRotate()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t = { 50, 50 };
	Matrix T = translation(t);
	Matrix R = rotation(30);
	Matrix TR = R * T;
	Matrix RT = T * R;
	for (int i = 0; i < 4; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		Line(P[i], P[(i + 1) % 4]);

		Vec3f tP0 = T * P[i];
		Vec3f tP1 = T * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(tP0, tP1);

		Vec3f trP0 = TR * P[i];
		Vec3f trP1 = TR * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(trP0, trP1);

		Vec3f rP0 = R * P[i];
		Vec3f rP1 = R * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rP0, rP1);

		Vec3f rtP0 = RT * P[i];
		Vec3f rtP1 = RT * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rtP0, rtP1);
	}
}

void CompositeRotateScale()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t = { 50, 50 };
	Matrix T = translation(t);
	Matrix R = rotation(30);
	Matrix S = scale(0.5, 0.5);
	Matrix SR = R * S;
	Matrix RS = S * R;
	for (int i = 0; i < 4; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		Line(P[i], P[(i + 1) % 4]);

		Vec3f sP0 = S * P[i];
		Vec3f sP1 = S * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(sP0, sP1);

		Vec3f srP0 = SR * P[i];
		Vec3f srP1 = SR * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(srP0, srP1);

		Vec3f rP0 = R * P[i];
		Vec3f rP1 = R * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rP0, rP1);

		Vec3f rsP0 = RS * P[i];
		Vec3f rsP1 = RS * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rsP0, rsP1);
	}
}

void RotateOnPoint()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t1 = { -400, -300 };
	Vec2i t2 = { 400, 300 };
	Matrix T1 = translation(t1);
	Matrix T2 = translation(t2);
	Matrix R = rotation(30);
	Matrix TRT = T2 * R * T1;
	for (int i = 0; i < 4; i++)
	{
		glColor3f(1.0f, 1.0f, 1.0f);
		Line(P[i], P[(i + 1) % 4]);

		Vec3f trtP0 = TRT * P[i];
		Vec3f trtP1 = TRT * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(trtP0, trtP1);
	}
}

void ThreeRhombus()
{
	Vec3i P[4];
	P[0] = { 300, 200, 1 }, P[1] = { 500, 200, 1 }, P[2] = { 500, 400, 1 }, P[3] = { 300, 400, 1 };
	Vec2i t1 = { -400, -300 };
	Vec2i t2 = { 400, 300 };
	Matrix T1 = translation(t1);
	Matrix T2 = translation(t2);
	Matrix S = scale(1, 0.5);
	Matrix R = rotation(45);
	int d = sqrt(80000)/2;
	Vec2i t3 = { d, 0 };
	Matrix T3 = translation(t3);

	Matrix Rhombus0 = T3 * T2 * S * R * T1;
	Matrix Rhombus1 = T2 * rotation(-30) * T1 * Rhombus0;
	Matrix Rhombus2 = T2 * rotation(90) * T1 * Rhombus0;
	Matrix Rhombus3 = T2 * rotation(-150) * T1 * Rhombus0;
	for (int i = 0; i < 4; i++)
	{
		//glColor3f(1.0f, 1.0f, 1.0f);
		//Line(P[i], P[(i + 1) % 4]);

		//Vec3f rh0P0 = Rhombus0 * P[i];
		//Vec3f rh0P1 = Rhombus0 * P[(i + 1) % 4];
		//glColor3f(1.0f, 1.0f, 1.0f);
		//Line(rh0P0, rh0P1);

		Vec3f rh1P0 = Rhombus1 * P[i];
		Vec3f rh1P1 = Rhombus1 * P[(i + 1) % 4];
		glColor3f(1.0f, 0.0f, 0.0f);
		Line(rh1P0, rh1P1);

		Vec3f rh2P0 = Rhombus2 * P[i];
		Vec3f rh2P1 = Rhombus2 * P[(i + 1) % 4];
		glColor3f(0.0f, 1.0f, 0.0f);
		Line(rh2P0, rh2P1);

		Vec3f rh3P0 = Rhombus3 * P[i];
		Vec3f rh3P1 = Rhombus3 * P[(i + 1) % 4];
		glColor3f(1.0f, 1.0f, 0.0f);
		Line(rh3P0, rh3P1);
	}
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//BasicTransformation();
	//CompositeTranslateScale();
	//CompositeTranslateRotate();
	//CompositeRotateScale();
	//RotateOnPoint();
	ThreeRhombus();

	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
}

void MyReshape(int w, int h)
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
	glutInitWindowSize(800, 600);
	glutCreateWindow("Hello Square!");
	Init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}
