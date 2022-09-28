
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <Windows.h>
#include <gl\GL.h>
#include <gl\GLu.h>
#include <math.h>
#pragma comment(lib,"opengl32")
#pragma comment(lib,"glu32")


struct Vector
{

    double v[2];
    //like constructor
    Vector(double x=0,double y=0)
    {
        v[0]=x;
        v[1]=y;
    }

    //operator overload.
    double& operator[](int index)
    {
        return v[index];
    }
};

void swap(int& x1, int& y1, int& x2, int& y2)
{
    int tmp = x1;
    x1 = x2;
    x2 = tmp;
    tmp = y1;
    y1 = y2;
    y2 = tmp;
}
int Round(double x)
{
    return (int)(x + 0.5);
}
void DrawLine1(int x1, int y1, int x2, int y2)
{
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1)*dy / dx;
            glVertex2d( x, Round(y));
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int y = y1;
        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1)*dx / dy;
            glVertex2d( Round(x), y);
        }
    }

    glEnd();
    glFlush();
}

void DrawLine3_usingBerhansim_afterEnhance(int x1, int y1, int x2, int y2)
{
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    double d;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        glVertex2d(x1, y1);
        int x = x1;
        double y=y1;
        d=(double)(dx)/2-(dy);
        while (x < x2)
        {
            if(d<0) //under
            {
                d+=(dx)-(dy);
                y++;
            }
            else
                d+=-(dy);
            x++;
            glVertex2d( x,y);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int y = y1;
        double x=x1;
        d=(dx)-(double)dy/2;
        while (y < y2)
        {
            if(d>0) //left
            {
                d+=dx-dy;
                x++;
            }
            else
                d+=dx;
            y++;
            glVertex2d(x, y);
        }
    }

    glEnd();
    glFlush();
}


void DrawLine3_usingBerhansim_beforeEnhance(int x1, int y1, int x2, int y2)
{
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    double d;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        //midpoint (x+1,y+0.5);

        if (x1 > x2)
            swap(x1, y1, x2, y2);
        glVertex2d(x1, y1);
        int x = x1;
        double y=y1;
        while (x < x2)
        {
            d=(dx)*(y+0.5-y1)-(dy)*(x+1-x1);
            if(d<0)
            {
                y++;
            }
            x++;
            glVertex2d( x,y);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int y = y1;
        double x=x1;
        while (y < y2)
        {
            d=(dx)*(y+0.5-y1)-(dy)*(x+1-x1);
            if(d>0)
            {
                x++;
            }
            y++;
            glVertex2d(x, y);
        }
    }

    glEnd();
    glFlush();
}

void DrawLine2_usingIterative(int x1, int y1, int x2, int y2)
{
    glBegin(GL_POINTS);
    glColor3f(1, 0, 0);
    int dx = x2 - x1;
    int dy = y2 - y1;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int x = x1;
        double y=y1;
        while (x < x2)
        {
            x++;
            y =y+slope;
            glVertex2d( x, Round(y));
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        glVertex2d( x1, y1);
        int y = y1;
        double x=x1;
        while (y < y2)
        {
            y++;
            x = x+(double)1/slope;
            glVertex2d( Round(x), y);
        }
    }

    glEnd();
    glFlush();
}
void Draw8Points(int xc, int yc, int x, int y)
{
    glVertex2d(xc + x, yc + y);
    glVertex2d(xc + x, yc - y);
    glVertex2d(xc - x, yc - y);
    glVertex2d(xc - x, yc + y);
    glVertex2d(xc + y, yc + x);
    glVertex2d(xc + y, yc - x);
    glVertex2d(xc - y, yc - x);
    glVertex2d(xc - y, yc + x);
}
void DrawCircle1(int xc, int yc, int R)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    int x = 0;
    double y = R;
    Draw8Points(xc, yc, 0, R);
    while (x < y)
    {
        x++;
        y = sqrt((double)R*R - x*x);
        Draw8Points(xc, yc, x, Round(y));
    }
    glEnd();
    glFlush();
}

//Before enhancment.
void DrawCircleBresenham_beforeEnhance(int xc, int yc, int R)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    int x = 0;
    double y = R;
    double d;
    Draw8Points(xc, yc, 0, R);

    while (x < y)
    {
        d=(x+1)*(x+1)+(y-0.5)*(y-0.5)-R*R;
        if(d>0)
        {
            y--;
        }
        x++;
        Draw8Points(xc, yc, x, y);
    }
    glEnd();
    glFlush();
}

//V2 start with x=R y=0
void DrawCircleBresenham_beforeEnhanceV2(int xc, int yc, int R)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    int x = R;
    int y = 0;
    double d;
    Draw8Points(xc, yc, R,0);

    while (x > y)
    {
        d=(x-0.5)*(x-0.5)+(y+1)*(y+1)-R*R;
        //no change of structure conditions.
        if(d>0)
        {
            x--;
        }
        y++;
        Draw8Points(xc, yc, x, y);
    }
    glEnd();
    glFlush();
}

//v2 after enhancement but use x++ in first.
void CircleBresenham(int xc, int yc, int R)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    int x=0,y=R;
    int d=1-R;
    Draw8Points(xc,yc,x,y);
    while(x<y)
    {
        x++;
        if(d<0)
            d+=2*x+1;
        else
        {
            d+=2*(x-y)+3;
            y--;
        }

        Draw8Points(xc,yc,x,y);
    }
    glEnd();
    glFlush();
}


//DrawCircleBresenham_after enhancement.
//start with x=0 ,y=R.
void DrawCircleBresenham(int xc, int yc, int R)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    int x = 0;
    double y = R;
    int d=1-R;

    Draw8Points(xc, yc, 0, R);

    while (x < y)
    {

        if(d>=0)
        {
            d+=2*(x-y)+5;
            y--;
        }
        else
            d+=2*(x)+3;
        x++;
        Draw8Points(xc, yc, x, Round(y));
    }
    glEnd();
    glFlush();
}



//p1 is the x1,y1
//p2 is the x2,y2
//T1 is the u1,v1
//T2 is the u2,v2

void Draw_HermiteCurve_Algorithm1(Vector& P1,Vector& T1,Vector& P2,Vector& T2)
{
    //alepha
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1);
    double alepha0=P1[0];
    double alepha1=T1[0];
    double alepha2=-3*P1[0]-2*T1[0]+3*P2[0]-T2[0];
    double alepha3=2*P1[0]+T1[0]-2*P2[0]+T2[0];

    // for beta
    double beta0=P1[1];
    double beta1=T1[1];
    double bata2=-3*P1[1]-2*T1[1]+3*P2[1]-T2[1];
    double beta3=2*P1[1]+T1[1]-2*P2[1]+T2[1];

    for(double t=0; t<=1; t+=0.001)
    {

        double t2=t*t;
        double t3=t2*t;
        double x=alepha0+alepha1*t+alepha2*t2+alepha3*t3;
        double y=beta0+beta1*t+bata2*t2+beta3*t3;
        glVertex2d(Round(x),Round(y));
    }
     glEnd();
    glFlush();
}
HGLRC InitOpenGl(HDC hdc)
{
    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof(PIXELFORMATDESCRIPTOR),   // size of this pfd
        1,                     // version number
        PFD_DRAW_TO_WINDOW |   // support window
        PFD_SUPPORT_OPENGL |   // support OpenGL
        PFD_DOUBLEBUFFER,      // double buffered
        //double buffer because
        //the
        PFD_TYPE_RGBA,         // RGBA type
        24,                    // 24-bit color depth
        0, 0, 0, 0, 0, 0,      // color bits ignored
        0,                     // no alpha buffer
        0,                     // shift bit ignored
        0,                     // no accumulation buffer
        0, 0, 0, 0,            // accum bits ignored
        32,                    // 32-bit z-buffer
        0,                     // no stencil buffer
        0,                     // no auxiliary buffer
        PFD_MAIN_PLANE,        // main layer
        0,                     // reserved
        0, 0, 0                // layer masks ignored
    };
    int  iPixelFormat;
    iPixelFormat = ChoosePixelFormat(hdc, &pfd);
    SetPixelFormat(hdc, iPixelFormat, &pfd);
    HGLRC glrc = wglCreateContext(hdc);
    wglMakeCurrent(hdc, glrc);
    return glrc;
}
void AdjustWindowFor2D(HDC hdc,int w,int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, w, h);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    SwapBuffers(hdc);
}
void EndOpenGl(HGLRC glrc)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(glrc);
}
LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
    static HDC hdc;
    static HGLRC glrc;
    static Vector points[4];//4 points
    static int index=0;
    //make user click in four points.
    //calculate the slope between the first point and second point
    //calculate the slope between the third and fourth points.
    //get the slope because we do the hermiate algorithms


    switch (mcode)
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        glrc = InitOpenGl(hdc);
        break;
    case WM_SIZE:
        AdjustWindowFor2D(hdc,LOWORD(lp), HIWORD(lp));
        break;
    case WM_LBUTTONDOWN:
       // printf("kkkkk");
        points[index]=Vector(LOWORD(lp), HIWORD(lp));
        //Drawing
        if(index==3)
        {
            //calculate the T1 AND T2
            //call constructor
            //T1 between point 0 and point 1.
            //point 0 (X1,Y1);
            // POINT 1 (X2,Y2);
            //slope =dy/dx----- dy/dt  and dx/dt ---and dt will be (1/3)
            //the dt calculate because the p1 in t=0 and p2 at t=1
            Vector T1(3*(points[1][0]-points[0][0]),3*(points[1][1]-points[0][1]));
            Vector T2((points[3][2]-points[2][2]),(points[3][3]-points[2][3]));
            Draw_HermiteCurve_Algorithm1(points[0],T1,points[1],T2);
            index=0;
            glFlush();
            SwapBuffers(hdc);
        }
        else
            index++;

        //DrawLine3_usingBerhansim_afterEnhance(90,100,500, 400);
        // DrawCircleBresenham(400, 400, 100);
        // glFlush();
        //SwapBuffers(hdc);

        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        EndOpenGl(glrc);
        ReleaseDC(hwnd, hdc);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, mcode, wp, lp);
    }
    return 0;
}
int APIENTRY WinMain(HINSTANCE hinst, HINSTANCE pinst, LPSTR cmd, int nsh)
{
    WNDCLASS wc;
    wc.cbClsExtra = wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = MyWndProc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass","My First Window", WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 800, 600, NULL, NULL, hinst, 0);
    ShowWindow(hwnd, nsh);
    UpdateWindow(hwnd);
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}
