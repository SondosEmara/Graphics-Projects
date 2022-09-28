#ifndef FILLING_H_INCLUDED
#define FILLING_H_INCLUDED
#include<stdio.h>
#include <stack>
#include <list>
#include <math.h>
#include <limits.h>
#include "Curve.h"
using namespace std;
//Q is the quarter number.

//////////////////////////////////////Filling  Circle with lines///////////////////////////////////////
void DrawLine1(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	if (abs(dy) <= abs(dx))
	{
		if (x1 > x2) swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);
		int x = x1;
		while (x < x2)
		{
			x++;
			double y = y1 + (double)(x - x1) * dy / dx;
			SetPixel(hdc, x, Round(y), c);
		}
	}
	else {
		if (y1 > y2) swap(x1, y1, x2, y2);
		SetPixel(hdc, x1, y1, c);
		int y = y1;
		while (y < y2)
		{
			y++;
			double x = x1 + (double)(y - y1) * dx / dy;
			SetPixel(hdc, Round(x), y, c);
		}
	}

}

//circles
void Draw8PointsLine(HDC hdc, int xc, int yc, int x, int y, COLORREF c,int Q)
{
	if (Q == 1)
	{
		DrawLine1(hdc, xc, yc, xc + x, yc - y, c);
		DrawLine1(hdc, xc, yc, xc + y, yc - x, c);


	}
	else if (Q == 2)
	{
		DrawLine1(hdc, xc, yc, xc + x, yc + y, c);
		DrawLine1(hdc, xc, yc, xc + y, yc + x, c);
	}
	else if (Q == 3)
	{

		DrawLine1(hdc, xc, yc, xc - x, yc + y, c);
		DrawLine1(hdc, xc, yc, xc - y, yc + x, c);
	}
	else if (Q == 4)
	{
		DrawLine1(hdc, xc, yc, xc - y, yc - x, c),
		DrawLine1(hdc, xc, yc, xc - x, yc -y, c);

	}


}


void CircleFillingLine(HDC hdc, int xc, int yc, int R, COLORREF c,int Q)
{
    int x = 0, y = R;
    Draw8PointsLine(hdc, xc, yc, x, y, c,Q);
    while (x < y)
    {
        int d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - R * R;
        if (d < 0)
            x++;
        else
        {
            x++;
            y--;
        }
        Draw8PointsLine(hdc, xc, yc, x, y, c,Q);
    }
}


/////////////////////////////////////Filling Circle with other circles//////////////////////////////
void Draw8PointsCircle(HDC hdc, int xc, int yc, int x, int y, COLORREF c, int Q)
{
    if (Q == 1)
    {
        SetPixel(hdc, xc, yc, c);
        SetPixel(hdc,  xc + x, yc - y, c);
        SetPixel(hdc, xc + y, yc - x, c);
    }
    else if (Q == 2)
    {
        SetPixel(hdc,  xc + x, yc + y, c);
        SetPixel(hdc,  xc + y, yc + x, c);
    }
    else if (Q == 3)
    {

        SetPixel(hdc,  xc - x, yc + y, c);
        SetPixel(hdc, xc - y, yc + x, c);
    }
    else if (Q == 4)
    {
        SetPixel(hdc, xc - y, yc - x, c),
                 SetPixel(hdc, xc - x, yc - y, c);

    }
}



void CircleFillingcircle(HDC hdc, int xc, int yc, int R, COLORREF c, int Q)
{
    int x = 0, y = R;
    Draw8PointsCircle(hdc, xc, yc, x, y, c,Q);
    while (x < y)
    {
        int d = (x + 1) * (x + 1) + (y - 0.5) * (y - 0.5) - R * R;
        if (d < 0)
            x++;
        else
        {
            x++;
            y--;
        }
        Draw8PointsCircle(hdc, xc, yc, x, y, c,Q);
    }
}

void makeCircleFillingCircle(HDC hdc, int xc, int yc, int R, COLORREF c, int q)
{
    for (int i =0 ; i <=R; i++)
    {
        CircleFillingcircle(hdc, xc, yc,i,c,q);
    }

}
/////////////////////////////////////////////////////////////////////////////////



///////////////////////////////////////Filling Circle with Vertical With Hermite Curve////////////////////////

void FillingSquare(HDC hdc,int x1, int y1, int x2, int y2, COLORREF c)
{
	Vector P1, P2;

	for (double i = x1; i <= x2; i++)
	{
		P1[0] = i, P1[1] = y1, P2[0] = i, P2[1] = y2;
		Vector T1(3 * (P2[0] - P1[0]), 3 * (P2[1] - P1[1]));
		Vector T2(3 * (P2[0] - P1[0]) , 3 * (P2[1] - P1[1]));
		DrawHermiteCurve(hdc, P1, T1, P2, T2, c);
	}
}
void DrawSquare(HDC hdc, int x1, int y1, int len, COLORREF c)
{
	//int len = sqrt(pow((x1 - x2), 2) + pow((y1 - y2), 2));
	int x2 = x1 + len;
	int y2 = y1 + len;
	DrawLine1(hdc, x1, y1, x2, y1, c);
	DrawLine1(hdc, x1, y1, x1, y2, c);
	DrawLine1(hdc, x1, y2, x2, y2, c);
	DrawLine1(hdc, x2, y1, x2, y2, c);


	FillingSquare(hdc,x1,y1,x2,y2,c);

}


////////////////////////////////////////Filling Circle with Bezier////////////////////////
void DrawAndFillRec(HDC hdc, int x, int y, int sidelen1, int sidelen2, COLORREF c,COLORREF FC) {
	DrawLine1(hdc, x, y, x + sidelen1, y, c);
	DrawLine1(hdc, x, y + sidelen2, x + sidelen1, y + sidelen2, c);
	DrawLine1(hdc, x, y, x, y + sidelen2, c);
	DrawLine1(hdc, x + sidelen1, y + sidelen2, x + sidelen1, y, c);

	Vector p[4];

	p[0].v[0] = x+1;
    p[1].v[0] = x+1;
    p[2].v[0] = x+sidelen1-1;
	p[3].v[0] = x+sidelen1-1;

	int y1 = y+1;
	while (y1 < y+ sidelen2)
	{
		p[0].v[1] = y1;
		p[1].v[1] = y1;
		p[2].v[1] = y1;
		p[3].v[1] = y1;


		DrawBezierCurve(hdc, p[0], p[1], p[2], p[3], FC);
		y1++;
	}

}


////////////////////////////////////////Filling Convex//////////////////////////////////////////////////////
struct Entry
{
    int xmin, xmax;
};

void InitEntries(Entry table[])
{
    for (int i = 0; i <600; i++)
    {
        table[i].xmin = 15000;
        table[i].xmax = -15000;
    }
}

void TableEdge(POINT v1, POINT v2, Entry table[])
{
    if (v1.y == v2.y)
        return;
    if (v1.y > v2.y)
        swap(v1,v2);
    double minv = (double)(v2.x - v1.x) / (v2.y - v1.y);
    double x = v1.x;
    int y = v1.y;
    while (y < v2.y)
    {
        if (x < table[y].xmin)
            table[y].xmin = (int)ceil(x);
        if (x > table[y].xmax)
            table[y].xmax = (int)floor(x);
        y++;
        x += minv;
    }
}
void DrawLines(HDC hdc, Entry table[], COLORREF color)
{
    for (int y = 0; y < 600; y++)
        if (table[y].xmin < table[y].xmax)
            for (int x = table[y].xmin; x <= table[y].xmax; x++)
                SetPixel(hdc, x, y, color);
}

void ConvexFill(HDC hdc,Vector points[], int n, COLORREF color)
{
        POINT p[4];
        p[0].x = points[0][0];
        p[0].y = points[0][1];

        p[1].x = points[1][0];
        p[1].y = points[1][1];


        p[2].x =points[2][0];
        p[2].y =points[2][1];


        p[3].x = points[3][0];
        p[3].y = points[3][1];




    Entry* table = new Entry[600];
    InitEntries(table);
    POINT v1 = p[n - 1];
    for (int i = 0; i < n; i++)
    {
        POINT v2 = p[i];
        TableEdge(v1, v2, table);
        v1 = p[i];
    }
    DrawLines(hdc, table, color);
    delete table;
}



///////////////////////////////////////Non Convex Filling//////////////////////////////////////////////
typedef struct EdgeTable2 {
	int x_left, x_right;
} EdgeTable[800];

void swap(Vector& v1, Vector& v2)
{
	Vector tmp = v1;
	v1 = v2;
	v2 = tmp;

}

void initEdgeTable(EdgeTable tbl) {
	for (int i = 0; i < 800; i++) {
		tbl[i].x_left = INT_MAX;
		tbl[i].x_right = -INT_MAX;
	}
}

void Edge2Table(Vector p1, Vector p2, EdgeTable tbl) {
	if (p1.v[1] == p2.v[1]) { return; }
	if (p1.v[1] > p2.v[1]) {
		swap(p1, p2);
	}
	double minv = (p2.v[0] - p1.v[0]) / (double)(p2.v[1] - p1.v[1]);
	double x = p1.v[0];
	int y = p1.v[1];
	while (y < p2.v[1]) {
		if (x < tbl[y].x_left) {
			tbl[y].x_left = ceil(x);
		}
		if (x > tbl[y].x_right) {
			tbl[y].x_right = (int)floor(x);
		}
		y++;
		x += minv;
	}
}

void polygon2Table(Vector p[], int n, EdgeTable tbl) {
	Vector v1 = p[n - 1];
	for (int i = 0; i < n; i++) {
		Vector v2 = p[i];
		Edge2Table(v1, v2, tbl);
		v1 = v2;
	}
}

void Table2Screen(HDC hdc, EdgeTable tbl,COLORREF c) {
	for (int i = 0; i < 800; i++) {
		if (tbl[i].x_left < tbl[i].x_right) {
			DrawLine1(hdc, tbl[i].x_left, i, tbl[i].x_right, i,c);
		}
	}
}

void polygon(HDC hdc, Vector p[], int n, COLORREF c) {
	EdgeTable tbl;
	initEdgeTable(tbl);
	polygon2Table(p, n, tbl);
	Table2Screen(hdc, tbl,c);
}




//////////////////////////////////////////////////////Recursive  Flood Fill//////////////////////////////
void floodfill(HDC hdc,int x, int y,COLORREF bc,COLORREF fc) {
	COLORREF c = GetPixel(hdc,x,y);
		if (c == bc ||c == fc) {
			return;
		}
		SetPixel(hdc, x, y, fc);
		floodfill(hdc, x - 1, y, bc, fc);
		floodfill(hdc, x, y - 1, bc, fc);
		floodfill(hdc, x, y + 1, bc, fc);

}
void floodfill2(HDC hdc, int x, int y, COLORREF bc, COLORREF fc) {
	COLORREF c = GetPixel(hdc, x, y);
	if (c == bc || c == fc) {
		return;
	}
	SetPixel(hdc, x , y , fc);
	floodfill2(hdc, x + 1, y, bc, fc);
    floodfill2(hdc, x, y + 1, bc, fc);
    floodfill2(hdc, x, y - 1, bc, fc);
}
void CirclemidpointChange(HDC hdc, int xc, int yc, int R, COLORREF c,COLORREF FC)
{
	int x = 0, y = R;
	int d = 1 - R;
	Draw8Points(hdc, xc, yc, x, y, c);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		Draw8Points(hdc, xc, yc, x, y, c);
	}
	floodfill(hdc, xc, yc,c, FC);
	floodfill2(hdc, xc+1, yc+1, c, FC);
}





/////////////////////////////////////////////////////Non Recursive  Flood Fill//////////////////////////////
struct Vertex
{
	int x, y;
	Vertex(int x, int y) :x(x), y(y){}
};
void NonRecFloodFill(HDC hdc, int x, int y, COLORREF Cb, COLORREF Cf)
{
	stack<Vertex> S;
	S.push(Vertex(x, y));
	while (!S.empty())
	{
		Vertex v = S.top();
		S.pop();
		COLORREF c = GetPixel(hdc,v.x, v.y);
		if (c == Cb || c == Cf)continue;
		SetPixel(hdc, v.x, v.y, Cf);
		S.push(Vertex(v.x + 1, v.y));
		S.push(Vertex(v.x - 1, v.y));
		S.push(Vertex(v.x, v.y + 1));
		S.push(Vertex(v.x, v.y - 1));
	}
}
void CirclemidpointChange(HDC hdc, int xc, int yc, int R, COLORREF c)
{
	int x = 0, y = R;
	int d = 1 - R;
	Draw8Points(hdc, xc, yc, x, y, c);
	while (x < y)
	{
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
		Draw8Points(hdc, xc, yc, x, y, c);
	}
}


















#endif // FILLING_H_INCLUDED
