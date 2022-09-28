#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

/////////////////////////line_Parametric//////////////////////////////
void line_Parametric(HDC hdc, int x1, int y1, int x2, int y2, COLORREF c)
{
    double x,y;
    for(double t=0; t<=1; t+=0.001)
    {
        x=x1+(x2-x1)*(t);
        y=y1+(y2-y1)*(t);
        SetPixel(hdc,Round(x),Round(y),c);
    }
}

//////////////////////////////////line_DDA////////////////////////////
void line_DDA(HDC hdc,int x1, int y1, int x2, int y2,COLORREF color)
{

    int dx = x2 - x1;
    int dy = y2 - y1;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc,x1,y1,color);
        int x = x1;
        double y=y1;
        while (x < x2)
        {
            x++;
            y =y+slope;
            SetPixel(hdc,x,Round(y),color);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc,x1, y1,color);
        int y = y1;
        double x=x1;
        while (y < y2)
        {
            y++;
            x = x+(double)1/slope;
            SetPixel(hdc,Round(x), y,color);
        }
    }

}


//////////////////////////line_Midpoint/////////////////////////////////
void line_Midpoint(HDC hdc,int x1, int y1, int x2, int y2,COLORREF color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    double d;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc,x1, y1,color);
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
            SetPixel(hdc,x,y,color);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc,x1,y1,color);
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
            SetPixel(hdc,x,y,color);
        }
    }
}
#endif // LINE_H_INCLUDED
