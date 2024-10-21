// HelloOpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <GL/glut.h>
#include <algorithm>
using namespace std;

struct Vec2i
{
    int x, y;
};

//方法一：重心坐标法
struct Vec3f
{
    float x, y, z;
};
//CrossProduct
Vec3f CrossProduct3D(const Vec3f& v1, const Vec3f& v2)
{
    Vec3f v3;
    v3.x = v1.y * v2.z - v1.z * v2.y;
    v3.y = v1.z * v2.x - v1.x * v2.z;
    v3.z = v1.x * v2.y - v1.y * v2.x;
    return v3;
}
//Determine the point p coordinates are in the triangle abc
Vec3f Barycentre(Vec2i p, Vec2i a, Vec2i b, Vec2i c)
{
    // Please add your code here
    /********** Begin ********/
    Vec3f v1, v2, v3, v4;
    v1.x = c.x - a.x;   v1.y = b.x - a.x;   v1.z = a.x - p.x;
    v2.x = c.y - a.y;   v2.y = b.y - a.y;   v2.z = a.y - p.y;
    v3.x = -1;          v3.y = 1;           v3.z = 1;
    Vec3f u = CrossProduct3D(v1, v2);
    v4.x = 1.f - (u.x + u.y) / u.z;  v4.y = u.y / u.z;  v4.z = u.x / u.z;
    if (abs(u.z) < 1)
        return v3;
    return v4;
    /********** End ********/
}
// Please draw point to make a triangle in bounding box using BarycentricCoordinates
void TriangleBarycentricCoordinates(Vec2i t0, Vec2i t1, Vec2i t2)
{
    // Please add your code here
    /********** Begin ********/
    int minX = min(min(t0.x, t1.x), t2.x);
    int maxX = max(max(t0.x, t1.x), t2.x);
    int minY = min(min(t0.y, t1.y), t2.y);
    int maxY = max(max(t0.y, t1.y), t2.y);
    Vec2i P;

    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
        {

            P.x = i;
            P.y = j;
            Vec3f bc_screen = Barycentre(P, t0, t1, t2);
            if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0)
                continue;
            glVertex2i(i, j);
        }
    }
    glEnd();
    /********** End **********/
}

//方法二：同侧判断法
//Cross product 
float CrossProduct2D(Vec2i a, Vec2i b)
{
    return a.x * b.y - b.x * a.y;
}

//Determine if P1 and P2 are on the same side
bool SameSide(Vec2i p1, Vec2i p2, Vec2i a, Vec2i b)
{
    // Please add your code here
    /********** Begin ********/
    Vec2i i, j, k;
    i.x = b.x - a.x;    i.y = b.y - a.y;
    j.x = p1.x - a.x;   j.y = p1.y - a.y;
    k.x = p2.x - a.x;   k.y = p2.y - a.y;
    float cp1 = CrossProduct2D(i, j),
        cp2 = CrossProduct2D(i, k);
    if (cp1 * cp2 >= 0)
        return true;
    else
        return false;
    /********** End **********/
}

//Determine the point coordinates are in the triangle
float PointInTriangle(Vec2i p, Vec2i a, Vec2i b, Vec2i c)
{
    if (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b))
        return true;
    else
        return false;
}

// Please draw point in bounding box
void TriangleSameSide(Vec2i t0, Vec2i t1, Vec2i t2)
{
    // Please add your code here
    /********** Begin ********/
    int minX = min(min(t0.x, t1.x), t2.x);
    int maxX = max(max(t0.x, t1.x), t2.x);
    int minY = min(min(t0.y, t1.y), t2.y);
    int maxY = max(max(t0.y, t1.y), t2.y);
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = minX; i <= maxX; i++)
    {
        for (int j = minY; j <= maxY; j++)
        {
            Vec2i p;
            p.x = i;
            p.y = j;
            if (PointInTriangle(p, t0, t1, t2))
                glVertex2i(i, j);
        }
    }
    glEnd();
    /********** End **********/
}

//方法三：扫描填充法
void TriangleScanLine(Vec2i t0, Vec2i t1, Vec2i t2) {
    // Please add your code here
    /********** Begin ********/
    if (t0.y > t1.y) std::swap(t0, t1);
    if (t0.y > t2.y) std::swap(t0, t2);
    if (t1.y > t2.y) std::swap(t1, t2);
    int total_height = t2.y - t0.y;
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int y = t0.y; y <= t1.y; y++) {
        int segment_height = t1.y - t0.y + 1;  //be careful with divisions by zero
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t0.y) / segment_height;
        Vec2i A, B;
        A.x = t0.x + (t2.x - t0.x) * alpha;
        B.x = t0.x + (t1.x - t0.x) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int x = A.x; x <= B.x; x++)
        {
            glVertex2i(x, y);
        }
    }
    for (int y = t1.y; y <= t2.y; y++) {
        int segment_height = t2.y - t1.y + 1;
        float alpha = (float)(y - t0.y) / total_height;
        float beta = (float)(y - t1.y) / segment_height;
        Vec2i A, B;
        A.x = t0.x + (t2.x - t0.x) * alpha;
        B.x = t1.x + (t2.x - t1.x) * beta;
        if (A.x > B.x) std::swap(A, B);
        for (int x = A.x; x <= B.x; x++)
        {
            glVertex2i(x, y);
        }
    }
    glEnd();
}

void MyDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    //Vec2i t0 = { 25,50 }, t1 = { 200,200 }, t2 = { 100,350 };
    //Vec2i t0 = { 225,50 }, t1 = { 400,200 }, t2 = { 300,350 };
    //TriangleScanLine(t0, t1, t2);

    Vec2i t3 = { 225,50 }, t4 = { 400,200 }, t5 = { 300,350 };
    TriangleBarycentricCoordinates(t3, t4, t5);

    //Vec2i t6 = { 425,50 }, t7 = { 600,200 }, t8 = { 500,350 };
    //TriangleSameSide(t6, t7, t8);

    //Vec2i t0 = { 225,50 }, t1 = { 400,200 }, t2 = { 300,350 };
    //TriangleSameSide(t0, t1, t2);

	glFlush();
}

void Init()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//glShadeModel(GL_SMOOTH);
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
	glutInitWindowSize(640, 480);
	glutCreateWindow("Hello Triangle!");
	Init();
	glutDisplayFunc(MyDisplay);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
	return 0;
}
