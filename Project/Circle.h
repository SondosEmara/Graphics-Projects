#ifndef CIRCLE_H_INCLUDED
#define CIRCLE_H_INCLUDED

///////////////////////////////////////Circle//////////////////////////////////////////////

void Draw8Points(HDC hdc,int xc, int yc, int x, int y,COLORREF color)
{
    SetPixel(hdc,xc + x, yc + y,color);
    SetPixel(hdc,xc + x, yc - y,color);
    SetPixel(hdc,xc - x, yc - y,color);
    SetPixel(hdc,xc - x, yc + y,color);
    SetPixel(hdc,xc + y, yc + x,color);
    SetPixel(hdc,xc + y, yc - x,color);
    SetPixel(hdc,xc - y, yc - x,color);
    SetPixel(hdc,xc - y, yc + x,color);
}
void circleDirect(HDC hdc,int xc, int yc, int R,COLORREF color)
{

    int x = 0;
    double y = R;
    Draw8Points(hdc,xc, yc, 0, R,color);
    while (x < y)
    {
        x++;
        y = sqrt((double)R*R - x*x);
        Draw8Points(hdc,xc, yc, x, Round(y),color);
    }
}


void circleMidpointB(HDC hdc,int xc, int yc, int R,COLORREF color)
{
    int x = 0;
    double y = R;
    double d;
    Draw8Points(hdc,xc, yc, 0, R,color);

    while (x < y)
    {
        d=(x+1)*(x+1)+(y-0.5)*(y-0.5)-R*R;
        if(d>0)
        {
            y--;
        }
        x++;
        Draw8Points(hdc,xc, yc, x, y,color);
    }
}

void circleMidpointA(HDC hdc,int xc, int yc, int R,COLORREF color)
{
    int x = 0;
    double y = R;
    int d=1-R;
    Draw8Points(hdc,xc, yc, 0, R,color);

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
        Draw8Points(hdc,xc, yc, x, Round(y),color);
    }
}

void circlePolar(HDC hdc, int xc, int yc, int R,COLORREF color)
{
    int x=R,y=0;// initial point
    double theta=0,dtheta=1.0/R;
    Draw8Points(hdc,xc,yc,x,y,color);
    while(x>y)
    {
        theta+=dtheta;
        x=(int)(R*cos(theta));
        y=(int)(R*sin(theta));
        Draw8Points(hdc,xc,yc,x,y,color);
    }
}

void Iterative_PolarCircit(HDC hdc,int xc, int yc,int R,COLORREF color)
{
    double x = R;
    double y = 0;
    double storeX=x;
    double dtheta=0;
    Draw8Points(hdc,xc, yc, R,0,color);
    //when start with (R,0);
    dtheta+=1.0/R;
    while (x>y)
    {
        x=storeX*cos(dtheta)-y*sin(dtheta);
        y=storeX*sin(dtheta)+y*cos(dtheta);
        storeX=x;
        Draw8Points(hdc,xc, yc,Round(x),Round(y),color);
    }
}

//////////////////////////////////////////////////////////////////////


#endif // CIRCLE_H_INCLUDED
