#pragma once
#ifndef ELLIPSE_H_INCLUDED
#define ELLIPSE_H_INCLUDED

void Draw4Points(HDC hdc, int xc, int yc, int a, int b, COLORREF color)
{

    SetPixel(hdc, xc + a, yc + b, color);
    SetPixel(hdc, xc - a, yc + b, color);
    SetPixel(hdc, xc - a, yc - b, color);
    SetPixel(hdc, xc + a, yc - b, color);
}
void DrawDirectEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{

    int x = 0;
    double y = B;
    Draw4Points(hdc, xc, yc, 0, B, c);

    while (x * B * B < y * A * A)
    {
        x++;
        y = B * sqrt(1 - (double)x * x / (A * A));
        Draw4Points(hdc, xc, yc, x, Round(y), c);
    }
    int x1 = A;
    double y1 = 0;
    Draw4Points(hdc, xc, yc, A, 0, c);

    while (x1 * B * B > y1 * A * A)
    {
        y1++;
        x1 = A * sqrt(1 - (double)y1 * y1 / (B * B));
        Draw4Points(hdc, xc, yc, Round(x1), y1, c);
    }

}
void DrawPolarEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF c)
{

    double theta = 0, x = A, y = 0;


    while (x > y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }
    while (x < y)
    {
        theta += 1.0 / max(A, B);
        x = A * cos(theta);
        y = B * sin(theta);
        Draw4Points(hdc, xc, yc, Round(x), Round(y), c);
    }
}

void DrawMidpointEllipse(HDC hdc, int xc, int yc, int A, int B, COLORREF color)
{
    int x = 0, y = B;
    Draw4Points(hdc, xc, yc, x, y, color);
    int a2 = A * A;
    int b2 = B * B;
    int d = (b2)-(a2 * B) + round(a2 / 4.0);
    int d1 = (3 * b2) - (2 * B * a2) + (2 * a2);
    int d2 = (3 * b2);
    int delta1 = 2 * b2 + 2 * a2;
    int delta2 = 2 * b2;
    while (d1 < A * A + B * B)
    {
        if (d > 0)
            y--, d += d1, d1 += delta1, d2 += delta2;
        else
            d += d2, d1 += delta2, d2 += delta2;
        x++;
        Draw4Points(hdc, xc, yc, x, y, color);
    }
    d1 = -2 * a2 * y + 3 * a2;
    d2 = 2 * b2 * x + 2 + d1;
    delta1 = 2 * a2;
    delta2 = 2 * (b2 + a2);
    while (y >= 0)
    {
        if (d > 0)
            d += d1, d1 += delta1, d2 += delta1;
        else
            x++, d += d2, d1 += delta1, d2 += delta2;
        y--;
        Draw4Points(hdc, xc, yc, x, y, color);
    }

}

#endif // ELLIPSE_H_INCLUDED
