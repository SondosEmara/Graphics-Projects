#ifndef CLIPPING_H_INCLUDED
#define CLIPPING_H_INCLUDED
#include <Windows.h>

#include <vector>
#include <math.h>

#include <tchar.h>

using namespace std;
static float xl;
static float xr;
static float yt;
static float yb;
static Vector rec[2];
static Vector p[1];
static Vector l[2];
COLORREF c2;
//////////////////////////////Clipping Point and line/////////////////////////////
void drawWindow(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c )
{
    DrawLine1(hdc, x1, y1, x2, y1,c);
    DrawLine1(hdc, x2, y1, x2, y2,c);
    DrawLine1(hdc, x2, y2, x1, y2,c);
    DrawLine1(hdc, x1, y2, x1, y1,c);
    xl = min(x1, x2);
    xr = max(x1, x2);
    yt = max(y1, y2);
    yb = min(y1, y2);
}
DWORD WINAPI clippingPoint(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;

    hdc = GetDC(hwnd);
    int x = p[0][0];
    int y = p[0][1];
    if (x >= xl && x <= xr && y >= yb && y <= yt)
    {
        SetPixel(hdc, x, y, RGB(255, 0, 0));
    }

    ReleaseDC(hwnd, hdc);
    return 0;
}
union OutCode
{
    unsigned  All : 4;
    struct
    {
        unsigned left : 1, top : 1, right : 1, bottom : 1;
    };
};
OutCode GetOutCode(double x, double y, int xleft, int ytop, int xright, int ybottom)
{
    OutCode out;
    out.All = 0;
    if (x < xleft)
        out.left = 1;
    else if (x > xright)
        out.right = 1;
    if (y > ytop)
        out.top = 1;
    else if (y < ybottom)
        out.bottom = 1;
    return out;
}
void VIntersect(double xs, double ys, double xe, double ye, int x, double* xi, double* yi)
{
    *xi = x;
    *yi = ys + (x - xs) * (ye - ys) / (xe - xs);
}
void HIntersect(double xs, double ys, double xe, double ye, int y, double* xi, double* yi)
{
    *yi = y;
    *xi = xs + (y - ys) * (xe - xs) / (ye - ys);
}
void CohenSuth(HDC hdc, int xf, int yf, int xs, int ys, int xleft, int ytop, int xright, int ybottom)
{
    COLORREF c =c2;
    double x1 = xf, y1 = yf, x2 = xs, y2 = ys;
    OutCode out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
    OutCode out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
    if (out1.All & out2.All)
        return;
    if (!out1.All && !out2.All)
    {
        DrawLine1(hdc, Round(x1), Round(y1), Round(x2), Round(y2), c );
        return;
    }
    while ((out1.All || out2.All) && !(out1.All & out2.All))
    {
        double xi, yi;
        if (out1.All)
        {
            if (out1.left)
                VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out1.top)
                HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out1.right)
                VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else
                HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x1 = xi;
            y1 = yi;
            out1 = GetOutCode(x1, y1, xleft, ytop, xright, ybottom);
        }
        else
        {
            if (out2.left)
                VIntersect(x1, y1, x2, y2, xleft, &xi, &yi);
            else if (out2.top)
                HIntersect(x1, y1, x2, y2, ytop, &xi, &yi);
            else if (out2.right)
                VIntersect(x1, y1, x2, y2, xright, &xi, &yi);
            else
                HIntersect(x1, y1, x2, y2, ybottom, &xi, &yi);
            x2 = xi;
            y2 = yi;
            out2 = GetOutCode(x2, y2, xleft, ytop, xright, ybottom);
        }
    }
    if (!out1.All && !out2.All)
    {
        DrawLine1(hdc, Round(x1), Round(y1), Round(x2), Round(y2), c );

    }

}
DWORD WINAPI clippingLine(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;
    hdc = GetDC(hwnd);
    CohenSuth(hdc, l[0][0], l[0][1], l[1][0], l[1][1], xl, yt, xr, yb);
}

void RecClipingPoint(HWND hwnd,HDC hdc,COLORREF c )
{

    rec[0]=points[0];
    rec[1]=points[1];
    p[0]=points[2];
    CreateThread(NULL, NULL, clippingPoint, hwnd, NULL, NULL);
}

void RecClipingLine(HWND hwnd,HDC hdc,COLORREF c )
{
    rec[0]=points[0];
    rec[1]=points[1];
    l[0]=points[2];
    l[1]=points[3];
    CreateThread(NULL, NULL, clippingLine, hwnd, NULL, NULL);
}


////////////////////////////////////Clipping Polygon////////////////////////////////

struct Vertex2
{
    double x, y;
    Vertex2(int x1 = 0, int y1 = 0)
    {
        x = x1;
        y = y1;
    }
};

typedef std::vector<Vertex2> Vertex2List;
typedef bool (*IsInFunc)(Vertex2& v, int edge);
typedef Vertex2(*IntersectFunc)(Vertex2& v1, Vertex2& v2, int edge);
static int n = 5;
static POINT* pp;
void DrawRectangle(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    DrawLine1(hdc, x1, y1, x2, y1,c);
    DrawLine1(hdc, x2, y1, x2, y2,c);
    DrawLine1(hdc, x2, y2, x1, y2,c);
    DrawLine1(hdc, x1, y2, x1, y1,c);
    xl = min(x1, x2);
    xr = max(x1, x2);
    yt = max(y1, y2);
    yb = min(y1, y2);
}
Vertex2List ClipWithEdge(Vertex2List p, int edge, IsInFunc In, IntersectFunc Intersect)
{
    Vertex2List OutList;
    Vertex2 v1 = p[p.size() - 1];
    bool v1_in = In(v1, edge);
    for (int i = 0; i < (int)p.size(); i++)
    {
        Vertex2 v2 = p[i];
        bool v2_in = In(v2, edge);
        if (v1_in && v2_in)
        {
            OutList.push_back(v2);
        }
        else if (v1_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
        }
        else if (v2_in)
        {
            OutList.push_back(Intersect(v1, v2, edge));
            OutList.push_back(v2);
        }

        v1 = v2;
        v1_in = v2_in;
    }
    return OutList;
}
bool InLeft(Vertex2& v, int edge)
{
    return v.x >= edge;
}
bool InRight(Vertex2& v, int edge)
{
    return v.x <= edge;
}
bool InTop(Vertex2& v, int edge)
{
    return v.y <= edge;
}
bool InBottom(Vertex2& v, int edge)
{
    return v.y >= edge;
}
Vertex2 VIntersect(Vertex2& v1, Vertex2& v2, int xedge)
{
    Vertex2 res;
    res.x = xedge;
    res.y = v1.y + (xedge - v1.x) * (v2.y - v1.y) / (v2.x - v1.x);
    return res;
}
Vertex2 HIntersect(Vertex2& v1, Vertex2& v2, int yedge)
{
    Vertex2 res;
    res.y = yedge;
    res.x = v1.x + (yedge - v1.y) * (v2.x - v1.x) / (v2.y - v1.y);
    return res;
}
void DrawPolygon(HDC hdc, Vertex2List vlist, COLORREF c)
{
    Vertex2 v1 = vlist[vlist.size() - 1];
    for (int i = 0; i < (int)vlist.size(); i++)
    {
        Vertex2 v2 = vlist[i];
        DrawLine1(hdc, v1.x, v1.y, v2.x, v2.y,c);
        v1 = v2;
    }
}
void PolygonClip(HDC hdc, POINT* p, int n, int xleft, int ytop, int xright, int ybottom, COLORREF c)
{

    Vertex2List vlist;
    for (int i = 0; i < n; i++)
        vlist.push_back(Vertex2(p[i].x, p[i].y));

    vlist = ClipWithEdge(vlist, xleft, InLeft, VIntersect);
    vlist = ClipWithEdge(vlist, ytop, InTop, HIntersect);
    vlist = ClipWithEdge(vlist, xright, InRight, VIntersect);
    vlist = ClipWithEdge(vlist, ybottom, InBottom, HIntersect);
    DrawPolygon(hdc, vlist, c);

}
DWORD WINAPI clippingPolygon(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;
    hdc = GetDC(hwnd);
    PolygonClip(hdc, pp, n, xl, yt, xr, yb, RGB(0, 0, 0));
}

void makeclippingPolygon(HWND hwnd,HDC hdc)
{

    pp = new POINT[n];
    pp[0].x=points[2][0];
    pp[0].y=points[2][1];

    pp[1].x=points[3][0];
    pp[1].y=points[3][1];

    pp[2].x=points[4][0];
    pp[2].y=points[4][1];

    pp[3].x=points[5][0];
    pp[3].y=points[5][1];

    pp[4].x=points[6][0];
    pp[4].y=points[6][1];

    CreateThread(NULL, NULL, clippingPolygon, hwnd, NULL, NULL);
}



////////////////////////////////////////////////Clipping circle Point ,Line////////////////////////////
static Vector c[2];
static Vector p2;
static double R;
static Vector l2[2];
void DrawCircle1(HDC hdc, double xc, double yc, int R,COLORREF c2)
{
    int x = 0;
    double y = R;
    Draw8Points(hdc, xc, yc, 0, R,c2);
    while (x < y)
    {
        x++;
        y = sqrt((double)R * R - x * x);
        Draw8Points(hdc, xc, yc, x, Round(y),c2);
    }

}

void DrawLine2(HDC hdc, int x1, int y1, int x2, int y2, COLORREF cr)
{
    int x_center = c[0][0];
    int y_center = c[0][1];
    int dx = x2 - x1;
    int dy = y2 - y1;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        if ((pow((x1 - x_center), 2) + pow((y1 - y_center), 2)) < R * R)
        {
            SetPixel(hdc, x1, y1, cr);
        }
        int x = x1;
        while (x < x2)
        {
            x++;
            double y = y1 + (double)(x - x1) * dy / dx;
            if ((pow((x - x_center), 2) + pow((Round(y) - y_center), 2)) < R * R)
                SetPixel(hdc, x, Round(y), cr);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        if ((pow((x1 - x_center), 2) + pow((y1 - y_center), 2)) < R * R)
            SetPixel(hdc, x1, y1, cr);
        int y = y1;
        while (y < y2)
        {
            y++;
            double x = x1 + (double)(y - y1) * dx / dy;
            if ((pow((Round(x) - x_center), 2) + pow((y - y_center), 2)) < R * R)
                SetPixel(hdc, Round(x), y, cr);
        }
    }

}

void makeClippingPointC(COLORREF c1,int flag,HWND hwnd,HDC hdc)
{

    if(flag)
    {

        c2=c1;
        c[0] =points[0];
        c[1]=points[1];
        R = sqrt(pow(c[1][0] - c[0][0], 2) + pow(c[1][1] - c[0][1], 2));
        DrawCircle1(hdc, c[0][0], c[0][1], R,c2);
    }
    else
    {
        p2=points[2];
        int x = p2[0];
        int y = p2[1];
        int x_center = c[0][0];
        int y_center = c[0][1];
        if ((pow((x - x_center), 2) + pow((y - y_center), 2)) < R * R)
        {
            SetPixel(hdc, x, y,c1);
        }
    }
}

void makeClippingLineC(COLORREF c1,int flag,HWND hwnd,HDC hdc)
{
    c2=c1;
    if(flag)
    {

        c[0] =points[0];
        c[1]=points[1];
        R = sqrt(pow(c[1][0] - c[0][0], 2) + pow(c[1][1] - c[0][1], 2));
        DrawCircle1(hdc, c[0][0], c[0][1], R,c2);
    }
    else
    {
        l2[0]=points[2];
        l2[1]=points[3];
        DrawLine2(hdc, l2[0][0], l2[0][1], l2[1][0], l2[1][1],c2);
    }
}



///////////////////////////////////////////////Clipping Square Point Line/////////////////////////////
static Vector squ[2];
static Vector p3[1];
static Vector l3[2];

void squaring(int& x1, int& y1, int& x2, int& y2)
{

    int d1 = abs(x1 - x2);
    int d2 = abs(y1 - y2);
    if (d1 > d2)
    {
        if (y2 < y1)
            y2 = y1 + d1;
        else
            y1 = y2 + d1;
    }
    else
    {
        if (x2 < x1)
            x2 = x1 + d2;
        else
            x1 = x2 + d2;

    }
}

void drawWindow3(HDC hdc, int x1, int y1, int x2, int y2,COLORREF c2)
{
    squaring(x1, y1, x2, y2);
    DrawLine1(hdc, x1, y1, x2, y1,c2);
    DrawLine1(hdc, x2, y1, x2, y2,c2);
    DrawLine1(hdc, x2, y2, x1, y2,c2);
    DrawLine1(hdc, x1, y2, x1, y1,c2);
    xl = min(x1, x2);
    xr = max(x1, x2);
    yt = max(y1, y2);
    yb = min(y1, y2);
}

DWORD WINAPI clippingPoint3(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;

    hdc = GetDC(hwnd);
    int x = p3[0][0];
    int y = p3[0][1];
    if (x >= xl && x <= xr && y >= yb && y <= yt)
    {
        SetPixel(hdc, x, y,c2);
    }

    ReleaseDC(hwnd, hdc);
    return 0;
}

DWORD WINAPI clippingLine3(void* lp)
{
    HWND hwnd = (HWND)lp;
    HDC hdc;
    hdc = GetDC(hwnd);
    CohenSuth(hdc, l3[0][0], l3[0][1], l3[1][0], l3[1][1], xl, yt, xr, yb);
    ReleaseDC(hwnd, hdc);
    return 0;
}

void makeClippingPointS(COLORREF c1,int flag,HWND hwnd,HDC hdc)
{
    c2=c1;
    if(flag)
    {
        squ[0] =points[0];
        squ[1]=points[1];
        drawWindow3(hdc, squ[0][0], squ[0][1], squ[1][0], squ[1][1],c1);
    }
    else
    {

        p3[0] = points[2];
        int x = p3[0][0];
        int y = p3[0][1];
        if (x >= xl && x <= xr && y >= yb && y <= yt)
        {
            SetPixel(hdc, x, y,c1);
        }
    }
}


void makeClippingLineS(COLORREF c1,int flag,HWND hwnd,HDC hdc)
{
    c2=c1;
    if(flag)
    {
        squ[0] =points[0];
        squ[1]=points[1];
        drawWindow3(hdc, squ[0][0], squ[0][1], squ[1][0], squ[1][1],c2);
    }
    else
    {

        l3[0] = points[2];
        l3[1] = points[3];
        CreateThread(NULL, NULL, clippingLine3, hwnd, NULL, NULL);
    }
}


#endif
