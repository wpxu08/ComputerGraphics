//#include<GL/freeglut.h>
//#include<math.h>
//#include<string>
//#include <iostream>
//using namespace std;
//const int POINTNUM = 5;
//
//typedef struct XET {
//    int x;
//    int dx, ymax;
//    struct XET* next;
//}AET, NET;
//
//struct Point {
//    int x;
//    int y;
//    Point() {}
//    Point(int x, int y) {
//        this->x = x;
//        this->y = y;
//    }
//}polypoint[POINTNUM];
//
//int MaxY, MinY;//多边形顶点沿Y轴的最小值和最大值
//
//void Init() {
//    polypoint[0] = Point(100, 100);
//    polypoint[1] = Point(100, 300);
//    polypoint[2] = Point(200, 200);
//    polypoint[3] = Point(300, 300);
//    polypoint[4] = Point(300, 100);
//
//    MaxY = polypoint[0].y;
//    MinY = polypoint[0].y;
//    for (int i = 0; i < POINTNUM; i++) {
//        if (polypoint[i].y > MaxY) {
//            MaxY = polypoint[i].y;
//        }
//        if (polypoint[i].y < MinY) {
//            MinY = polypoint[i].y;
//        }
//    }
//}
//
//void PolyScan() {
//    glBegin(GL_POINTS);
//    glColor3f(0.0, 1.0, 0.0);//设置颜色的函数
//    //初始化AET NET表
//    AET* pAET = new AET;
//    pAET->next = NULL;
//    NET* pNET[1024];
//    for (int i = MinY; i <= MaxY; i++) {
//        pNET[i] = new NET;
//        pNET[i]->next = NULL;
//    }
//    //填NET表
//    for (int i = MinY; i <= MaxY; i++)
//    {
//        for (int j = 0; j < POINTNUM; j++)
//        {
//            if (polypoint[j].y == i)
//            {
//                if (polypoint[(j - 1 + POINTNUM) % POINTNUM].y > polypoint[j].y) //左边的点
//                {
//                    NET* p = new NET;
//                    p->x = polypoint[j].x;
//                    p->ymax = polypoint[(j - 1 + POINTNUM) % POINTNUM].y;
//                    p->dx = (polypoint[(j - 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j - 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
//                    p->next = pNET[i]->next;
//                    pNET[i]->next = p;
//                }
//                if (polypoint[(j + 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)  //右边的点
//                {
//                    NET* p = new NET;
//                    p->x = polypoint[j].x;
//                    p->ymax = polypoint[(j + 1 + POINTNUM) % POINTNUM].y;
//                    p->dx = (polypoint[(j + 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j + 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
//                    p->next = pNET[i]->next;
//                    pNET[i]->next = p;
//                }
//            }
//        }
//    }
//    //建立更新AET
//    for (int i = MinY; i <= MaxY; i++) {
//        //计算新的交点x，更新AET
//        NET* p = pAET->next;
//        while (p != NULL)
//        {
//            p->x = p->x + p->dx;
//            p = p->next;
//        }
//        //更新后新AET先排序
//        //断表排序,不再开辟空间
//        AET* tq = pAET;
//        p = pAET->next;
//        tq->next = NULL;
//        while (p != NULL)  //按x排序
//        {
//            while (tq->next != NULL && p->x >= tq->next->x)
//            {
//                tq = tq->next;
//            }
//            NET* s = p->next;
//            p->next = tq->next;
//            tq->next = p;
//            p = s;
//            tq = pAET;
//        }
//        AET* q = pAET;
//        p = q->next;
//        while (p != NULL)
//        {
//            if (p->ymax == i)
//            {
//                q->next = p->next;
//                delete p;
//                p = q->next;
//            }
//            else
//            {
//                q = q->next;
//                p = q->next;
//            }
//        }
//        //将NET中的新点加入AET,并用插入法按X值递增排序
//        p = pNET[i]->next;
//        q = pAET;
//        while (p != NULL)
//        {
//            while (q->next != NULL && p->x >= q->next->x)
//            {
//                q = q->next;
//            }
//            NET* s = p->next;
//            p->next = q->next;
//            q->next = p;
//            p = s;
//            q = pAET;
//        }
//        p = pAET->next;
//        while (p && p->next)
//        {
//            for (float j = p->x; j <= p->next->x; j++)
//                glVertex2f(j, i);
//            p = p->next->next;//考虑端点情况
//        }
//    }
//    NET* phead = NULL;
//    NET* pnext = NULL;
//    //释放活跃边表
//    phead = pAET;
//    while (phead != NULL)
//    {
//        pnext = phead->next;
//        delete phead;
//        phead = pnext;
//    }
//    glEnd();
//
//}
//
//void LineGL(int i) {
//    glBegin(GL_LINES);
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex2f(polypoint[i].x, polypoint[i].y);
//    glVertex2f(polypoint[i + 1].x, polypoint[i + 1].y);
//    if (i == POINTNUM - 2) {
//        glVertex2f(polypoint[0].x, polypoint[0].y);
//        glVertex2f(polypoint[i + 1].x, polypoint[i + 1].y);
//    }
//    glEnd();
//}
//
//void MyDisplay()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    for (int i = 0; i < POINTNUM - 1; i++) {
//        LineGL(i);
//    }
//    PolyScan();
//
//    glFlush();
//}
//
//void MyReshape(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);//窗口的初始化
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//窗口谋模式的设定
//    glutInitWindowPosition(100, 100);//窗口位置的设定
//    glutInitWindowSize(400, 400);//窗口大小的设定
//    glutCreateWindow("多边形的扫描填充");
//    Init();
//    glutDisplayFunc(MyDisplay);
//    glutReshapeFunc(MyReshape);
//    glutMainLoop();
//
//    return 0;
//}
//


////第二关  边缘填充法
//
//// 提示：写完代码请保存之后再进行评测
//#include<GL/freeglut.h>
//#include<math.h>
//#include<string>
//#include <iostream>
//using namespace std;
//
//const int POINTNUM = 5;
//
//struct Point {
//    int x;
//    int y;
//    Point() {}
//    Point(int x, int y) {
//        this->x = x;
//        this->y = y;
//    }
//}polypoint[POINTNUM];
//
//int MaxY, MinY;//多边形顶点沿Y轴的最小值和最大值
//
//int vis[400][400];//判断该坐标的点是否为填充色，0为背景色，1为填充色
//
//void Init() {
//    polypoint[0] = Point(100, 100);
//    polypoint[1] = Point(100, 300);
//    polypoint[2] = Point(200, 200);
//    polypoint[3] = Point(300, 300);
//    polypoint[4] = Point(300, 100);
//}
//void EdgeFilling() {
//    int i, j, x, y, t;
//    float k;
//    for (i = 0; i < POINTNUM; i++) {
//        if (i == 0)
//            t = POINTNUM - 1;
//        else
//            t = i - 1;
//        if (polypoint[t].y <= polypoint[i].y) {
//            MinY = polypoint[t].y;
//            MaxY = polypoint[i].y;
//            j = polypoint[t].x;
//            if (polypoint[t].x == polypoint[i].x) {
//                k = 0;
//            }
//            else
//                k = (float)(polypoint[i].y - polypoint[t].y) / (float)(polypoint[i].x - polypoint[t].x);
//        }
//        else {
//            MinY = polypoint[i].y;
//            MaxY = polypoint[t].y;
//            j = polypoint[i].x;
//            if (polypoint[t].x == polypoint[i].x) {
//                k = 0;
//            }
//            else
//                k = (float)(polypoint[t].y - polypoint[i].y) / (float)(polypoint[t].x - polypoint[i].x);
//        }
//        for (y = MinY; y < MaxY; y++) {
//            for (x = j; x < 400; x++) {
//                if (vis[x][y] == 1)
//                    vis[x][y] = 0;
//                else
//                    vis[x][y] = 1;
//            }
//            j += k;
//        }
//    }
//    glBegin(GL_POINTS);
//    glColor3f(0.0, 1.0, 0.0);//设置颜色的函数
//    for (x = 0; x < 400; x++) {
//        for (y = 0; y < 400; y++) {
//            if (vis[x][y] == 1) {
//                glVertex2f(x, y);
//            }
//        }
//    }
//    glEnd();
//}
//
//
//void LineGL(int i) {
//    glBegin(GL_LINES);
//    glColor3f(0.0f, 1.0f, 0.0f);
//    glVertex2f(polypoint[i].x, polypoint[i].y);
//    glVertex2f(polypoint[i + 1].x, polypoint[i + 1].y);
//    if (i == POINTNUM - 2) {
//        glVertex2f(polypoint[0].x, polypoint[0].y);
//        glVertex2f(polypoint[i + 1].x, polypoint[i + 1].y);
//    }
//    glEnd();
//}
//
//void MyDisplay()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    for (int i = 0; i < POINTNUM - 1; i++) {
//        LineGL(i);
//    }
//    EdgeFilling();
//
//    glFlush();
//}
//
//void MyReshape(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);//窗口的初始化
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//窗口谋模式的设定
//    glutInitWindowPosition(100, 100);//窗口位置的设定
//    glutInitWindowSize(400, 400);//窗口大小的设定
//    glutCreateWindow("多边形的扫描填充");
//
//    Init();
//    glutDisplayFunc(MyDisplay);//调用函数
//    glutReshapeFunc(MyReshape);
//    glutMainLoop();
//
//    return 0;
//}



//
//第三关 区域四连通种子填充算法
//
#include<GL/freeglut.h>
#include<math.h>
#include<string>
#include<vector>
#include<queue>
#include <iostream>
using namespace std;

const int POINTNUM = 5;

struct Point {
    int x;
    int y;
    Point() {}
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }
}polypoint[POINTNUM];

int MaxY, MinY;//多边形顶点沿Y轴的最小值和最大值

int vis[400][400] = {0};//判断该坐标的点是否为填充色，0为背景色，1为填充色
vector< vector<int> > vtVis(400, vector<int>(400, 0));

void Init() {
    polypoint[0] = Point(100, 100);
    polypoint[1] = Point(100, 300);
    polypoint[2] = Point(200, 200);
    polypoint[3] = Point(300, 300);
    polypoint[4] = Point(300, 100);

    //int t = 150;
    //polypoint[0] = Point(100, 100);
    //polypoint[1] = Point(100, t);
    //polypoint[2] = Point(125, 125);
    //polypoint[3] = Point(t, t);
    //polypoint[4] = Point(t, 100);
}

void BoundaryFill4(int x, int y) {
 //    请在此添加你的代码
   /********** Begin ********/
    //if (vis[x][y] == 0) {
    if (vtVis[x][y] == 0) {
        //glPointSize(5);
        glVertex2f(x, y);
        //vis[x][y] = 1;
        vtVis[x][y] = 1;
        //if(x >=1 && x < 400 && y>=0 && y <400)
            BoundaryFill4(x - 1, y);
        //if (x >= 1 && x < 399 && y >= 0 && y < 400)
            BoundaryFill4(x + 1, y);
        //if (x >= 0 && x < 400 && y >= 1 && y < 400)
            BoundaryFill4(x, y - 1);
        //if (x >= 1 && x < 400 && y >= 1 && y < 400)
            BoundaryFill4(x, y + 1);
    }

    /********** End **********/
}

typedef  float Color[3];
bool rgbColorEqual(Color c1, Color c2)
 {
        if (abs(c1[1] - c2[1]) < 0.001 && abs(c1[2] - c2[2]) < 0.001 && abs(c1[0] - c2[0]) < 0.001)
            return true;
        else
            return false;
 }

 void setPixel(GLint x, GLint y)
    {
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }

    void getPixel(GLint x, GLint y, Color c)
    {
        glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, c);
    }

    void BoundaryFill4New(int x, int y, Color fillColor, Color borderColor)
    {
        Color currentColor;
        getPixel(x, y, currentColor);
        if ((!rgbColorEqual(currentColor, fillColor)) && (!rgbColorEqual(currentColor, borderColor)))
        {
            //setColor(fillColor);
            setPixel(x, y);
            BoundaryFill4New(x + 1, y, fillColor, borderColor);
            BoundaryFill4New(x - 1, y, fillColor, borderColor);
            BoundaryFill4New(x, y + 1, fillColor, borderColor);
            BoundaryFill4New(x, y - 1, fillColor, borderColor);
        }
    }

void BoundaryPoly() {
    int i, t, k, x, y;
    for (i = 0; i < POINTNUM; i++) {
        i == 0 ? t = POINTNUM - 1 : t = i - 1;
        if (polypoint[i].y >= polypoint[t].y) {
            MinY = polypoint[t].y;
            MaxY = polypoint[i].y;
            x = polypoint[t].x;
            if (polypoint[t].x == polypoint[i].x) {
                k = 0;
            }
            else
                k = (float)(polypoint[i].y - polypoint[t].y) / (float)(polypoint[i].x - polypoint[t].x);
        }
        else
        {
            MinY = polypoint[i].y;
            MaxY = polypoint[t].y;
            x = polypoint[i].x;
            if (polypoint[t].x == polypoint[i].x) {
                k = 0;
            }
            else
                k = (float)(polypoint[t].y - polypoint[i].y) / (float)(polypoint[t].x - polypoint[i].x);
        }
        for (y = MinY; y < MaxY; y++) {
            glVertex2f(x, y);
            //vis[x][y] = 1;
            vtVis[x][y] = 1;
            x += k;
        }
        if (polypoint[t].y == polypoint[i].y && polypoint[i].x > polypoint[t].x) {
            for (x = polypoint[t].x; x < polypoint[i].x; x++) {
                glVertex2f(x, polypoint[t].y);
                //vis[x][y] = 1;
                vtVis[x][y] = 1;
            }
        }
        else if (polypoint[t].y == polypoint[i].y && polypoint[i].x < polypoint[t].x) {
            for (x = polypoint[i].x; x < polypoint[t].x; x++) {
                glVertex2f(x, polypoint[t].y);
                //vis[x][y] = 1;
                vtVis[x][y] = 1;
            }
        }
    }
}

void MyDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    //vis[400][400] = { 0 };
    glPointSize(1);
    glBegin(GL_POINTS);
    glColor3f(1.0, 0.0, 0.0);//设置颜色的函数
 //   将边界用像素表示并输出；
    BoundaryPoly();

    //glVertex2f(105, 102);
    //BoundaryFill4(200, 150);
    //BoundaryFill4(105, 102);
    BoundaryFill4(125, 115);
    glEnd();
    glFlush();

    //Color a = { 1.0,0.0,0.0 }, b = { 0.0,1.0,1.0 };
    //glColor3fv(b);
    //glClear(GL_COLOR_BUFFER_BIT);
    ////设置边界线宽，否则填充时会溢出
    //glLineWidth(1.0);
    ////绘制多边形区域
    //glBegin(GL_LINE_LOOP);
    //glVertex2i(polypoint[0].x, polypoint[0].y);
    //glVertex2i(polypoint[1].x, polypoint[1].y);
    //glVertex2i(polypoint[2].x, polypoint[2].y);
    //glVertex2i(polypoint[3].x, polypoint[3].y);
    //glVertex2i(polypoint[4].x, polypoint[4].y);
    //glEnd();
    //glColor3fv(a);

    ////setPixel(200, 150);
    ////BoundaryFill4New(200, 150, a, b);
    //BoundaryFill4New(105, 102, a, b);
    //glFlush();
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
    glutInit(&argc, argv);//窗口的初始化
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//窗口谋模式的设定
    glutInitWindowPosition(100, 100);//窗口位置的设定
    glutInitWindowSize(640, 480);//窗口大小的设定
    glutCreateWindow("多边形的扫描填充");

    Init();
    glutDisplayFunc(MyDisplay);//调用函数
    glutReshapeFunc(MyReshape);
    glutMainLoop();

    return 0;
}


//第四关 区域扫描线种子填充算法


//#include<GL/freeglut.h>
//#include<math.h>
//#include<string>
//#include <iostream>
//#include<stack>
//using namespace std;
//
//const int POINTNUM = 5;
//
//struct Point {
//    int x;
//    int y;
//    Point() {}
//    Point(int x, int y) {
//        this->x = x;
//        this->y = y;
//    }
//}polypoint[POINTNUM];
//
//int MaxY, MinY;//多边形顶点沿Y轴的最小值和最大值
//
//int vis[400][400];//判断该坐标的点是否为填充色，0为背景色，1为填充色
//
//void Init() {
//    polypoint[0] = Point(100, 100);
//    polypoint[1] = Point(100, 300);
//    polypoint[2] = Point(200, 200);
//    polypoint[3] = Point(300, 300);
//    polypoint[4] = Point(300, 100);
//}
//
//void FindNewSeed(stack<Point>& s, int left, int right, int y) {
//    for (int i = left + 1; i < right; i++) {
//        if (vis[i][y] == 0) {
//            int j = i + 1;
//            while (vis[j][y] == 0)
//                j++;
//            i = j--;
//            s.push(Point(j, y));
//        }
//    }
//}
//
//void ScanLineFlood(int x, int y) {
//    stack<Point> s;
//    Point p;
//    int left, right;
//    s.push(Point(x, y));
//    while (!s.empty()) {
//        //栈顶元素出栈
//        p = s.top();
//        s.pop();
//        //向左填充
//        for (left = p.x; vis[left][p.y] != 1; left--) {
//            glVertex2f(left, p.y);
//            vis[left][p.y] = 1;
//        }
//        //向右填充
//        for (right = p.x + 1; vis[right][p.y] != 1; right++) {
//            glVertex2f(right, p.y);
//            vis[right][p.y] = 1;
//        }
//        //在当前行的下一行寻找确定新的种子点
//        FindNewSeed(s, left, right, p.y - 1);
//        //在当前行的上一行寻找确定新的种子点
//        FindNewSeed(s, left, right, p.y + 1);
//    }
//}
//
//void BoundaryPoly() {
//    int i, t, k, x, y;
//    for (i = 0; i < POINTNUM; i++) {
//        i == 0 ? t = POINTNUM - 1 : t = i - 1;
//        if (polypoint[i].y >= polypoint[t].y) {
//            MinY = polypoint[t].y;
//            MaxY = polypoint[i].y;
//            x = polypoint[t].x;
//            if (polypoint[t].x == polypoint[i].x) {
//                k = 0;
//            }
//            else
//                k = (float)(polypoint[i].y - polypoint[t].y) / (float)(polypoint[i].x - polypoint[t].x);
//        }
//        else
//        {
//            MinY = polypoint[i].y;
//            MaxY = polypoint[t].y;
//            x = polypoint[i].x;
//            if (polypoint[t].x == polypoint[i].x) {
//                k = 0;
//            }
//            else
//                k = (float)(polypoint[t].y - polypoint[i].y) / (float)(polypoint[t].x - polypoint[i].x);
//        }
//        for (y = MinY; y < MaxY; y++) {
//            glVertex2f(x, y);
//            vis[x][y] = 1;
//            x += k;
//        }
//        if (polypoint[t].y == polypoint[i].y && polypoint[i].x > polypoint[t].x) {
//            for (x = polypoint[t].x; x < polypoint[i].x; x++) {
//                glVertex2f(x, polypoint[t].y);
//                vis[x][y] = 1;
//            }
//        }
//        else if (polypoint[t].y == polypoint[i].y && polypoint[i].x < polypoint[t].x) {
//            for (x = polypoint[i].x; x < polypoint[t].x; x++) {
//                glVertex2f(x, polypoint[t].y);
//                vis[x][y] = 1;
//            }
//        }
//    }
//}
//
//void MyDisplay()
//{
//    glClear(GL_COLOR_BUFFER_BIT);
//    glColor3f(1.0f, 1.0f, 1.0f);
//    glBegin(GL_POINTS);
//    glColor3f(0.0, 1.0, 0.0);//设置颜色的函数
//    //将边界用像素表示并输出；
//    BoundaryPoly();
//    ScanLineFlood(200, 150);
//    glEnd();
//    glFlush();
//}
//
//void MyReshape(int w, int h)
//{
//    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
//}
//
//int main(int argc, char* argv[])
//{
//    glutInit(&argc, argv);//窗口的初始化
//    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);//窗口谋模式的设定
//    glutInitWindowPosition(100, 100);//窗口位置的设定
//    glutInitWindowSize(400, 400);//窗口大小的设定
//    glutCreateWindow("多边形的扫描填充");
//
//    Init();
//    glutDisplayFunc(MyDisplay);//调用函数
//    glutReshapeFunc(MyReshape);
//    glutMainLoop();
//
//    return 0;
//}