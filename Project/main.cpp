#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include "math.h"
#include "Ids.h"
#include "Common.h"
#include "Line.h"
#include "Circle.h"
#include "Menu.h"
#include "Filling.h"
#include "File.h"
#include "Clipping.h"
#include "Curve.h"
#include "Ellipse.h"

///////////////////////////////////Varaibles///////////////////////////
static bool lineParametric = false, lineMidpoint = false, lineDDA = false, cDirect = false,
            cPolar = false, citerativePolar = false, cMidpointB = false, cMidePointA = false,
            cfillingc = false, cfillingl = false, sfillingh = false, confixfilling = false, nconfixfilling = false,
            recursiveFloodFill = false, nRFloodFill = false, rFillingb = false,
            rectanglepoint = false, rectangleline = false, rectanglepolygon = false,
            circlepoint = false, circleline = false, squarepoint = false, squareline = false, splinecurves = false,
            ellipsePolar = false, ellipseDirect = false, ellipseMidPoint = false;
int  quarterNum = 1, lenght = 100;
COLORREF colorShape = RGB(34, 139, 34);
int xCenter, yCenter, xRadius, yRadius ;


///////////////////////////////////Read From Console/////////////////////////////////////
//the part of make connection between the console and the window.
int readFromConsole()
{
    char szReadBuffer[40000];

    DWORD dwlenght, dwWrite, dwRead;
    HANDLE hIn = 0;
    HANDLE hOut = 0;

    hIn = GetStdHandle(STD_INPUT_HANDLE);

    dwlenght = sizeof(szReadBuffer);
    printf("Enter the Number \n");
    ReadConsole(hIn, szReadBuffer, dwlenght, &dwRead, NULL);
    return atoi(szReadBuffer);
}


LRESULT WINAPI changeStatus(WPARAM wp, HWND hwnd, UINT mcode, LPARAM lp)
{

    //to know what the user is select by using the ids that was defined above for each icon in the window.
    switch (wp)
    {
    case Red:
        colorShape = RGB(255, 0, 0);
        break;
    case Black:
        colorShape = RGB(0, 0, 0);
        break;
    case Blue:
        colorShape = RGB(0, 0, 255);
        break;
    case Line_DDA:
        lineDDA = true;
        break;
    case Line_Midpoint:
        lineMidpoint = true;
        break;
    case Line_Parametric:
        lineParametric = true;
    case Circle_Direct:
        cDirect = true;
        break;
    case Circle_Polar:
        cPolar = true;
        break;
    case Circle_IterativePolar:
        citerativePolar = true;
        break;
    case Circle_Midpoint_BeforeModify:
        cMidpointB = true;
        break;
    case Circle_Midpoint_AfterModify:
        cMidePointA = true;
        break;
    case CLEAR:
        InvalidateRect(hwnd, NULL, TRUE);
        break;
    case SAVE:
        Save_To_File();
        break;
    case LOAD:
        LoadFromFile();
        break;
    case CFillingC:
        //First we will get the quarter from the user.
        quarterNum = readFromConsole();
        cfillingc = true;
        break;
    case CFillingL:
        //First we will get the quarter from the user.
        quarterNum = readFromConsole();
        cfillingl = true;
        break;
    case SFillingH:
        lenght = readFromConsole();
        sfillingh = true;
        break;
    case ConfixFilling:
        confixfilling = true;
        break;
    case NonConfixFilling:
        nconfixfilling = true;
        break;
    case RecursiveFloodFill:
        recursiveFloodFill = true;
        break;
    case NONRecursiveFloodFill:
        nRFloodFill = true;
        break;
    case RectanglePoint:
        rectanglepoint = true;
        break;
    case RectangleLine:
        rectangleline = true;
        break;
    case RectanglePolygon:
        rectanglepolygon = true;
        break;
    case CirclePoint:
        circlepoint = true;
        break;
    case CircleLine:
        circleline = true;
        break;
    case SquarePoint:
        squarepoint = true;
        break;
    case SquareLine:
        squareline = true;
        break;
    case RFillingB:
        rFillingb = true;
        break;
    case SplineCurves:
        splinecurves = true;
        break;
    case ellipse_Midpoint:
        ellipseMidPoint = true;
        break;
    case ellipse_polar:
        ellipsePolar = true;
        break;
    case ellipse_direct:
        ellipseDirect = true;
        break;

    default:
        return DefWindowProc(hwnd, mcode, wp, lp);
    }
}



////////////////////////////Paint///////////////////////////////////
void selectWhatPaint(HDC hdc, HWND hwnd)
{

    ////////////////////////////Line//////////////////////////////////////////////
    if (lineDDA == true && index == 2)
    {
        line_DDA(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        index = 0;
        lineDDA = false;
    }
    else if (lineMidpoint == true && index == 2)
    {
        line_Midpoint(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        index = 0;
        lineMidpoint = false;
    }
    else if (lineParametric == true && index == 2)
    {
        line_Parametric(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        index = 0;
        lineParametric = false;
    }
    /////////////////////////////Circle///////////////////////////////////////////

    else if (cDirect == true && index == 2)
    {

        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));

        circleDirect(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        index = 0;
        cDirect = false;
    }
    else if (citerativePolar == true && index == 2)
    {

        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));

        Iterative_PolarCircit(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        index = 0;
        citerativePolar = false;
    }
    else if (cPolar == true && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        circlePolar(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        index = 0;
        cPolar = false;
    }
    else if (cMidePointA == true && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        circleMidpointA(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        index = 0;
        cMidePointA = false;
    }
    else if (cMidpointB == true && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        circleMidpointB(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        index = 0;
        cMidpointB = false;
    }

    ////////////////////////////Filling//////////////////////////////////////////
    else if (cfillingc == true && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        circleDirect(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        makeCircleFillingCircle(hdc, points[0][0], points[0][1], Round(radius), colorShape, quarterNum);
        index = 0;
        cfillingc = false;
    }
    else if (cfillingl == true && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        circleDirect(hdc, points[0][0], points[0][1], Round(radius), colorShape);
        CircleFillingLine(hdc, points[0][0], points[0][1], Round(radius), colorShape, quarterNum);
        index = 0;
        cfillingl = false;
    }
    else if (sfillingh && index == 1)
    {
        DrawSquare(hdc, points[0][0], points[0][1], lenght, colorShape);
        index = 0;
        sfillingh = false;
    }
    else if (confixfilling && index == 4)
    {
        ConvexFill(hdc, points, 4, colorShape);
        confixfilling = false;
        index = 0;
    }

    else if (nconfixfilling && index == 6)
    {
        polygon(hdc, points, 6, colorShape);
        nconfixfilling = false;
        index = 0;
    }

    else if (recursiveFloodFill && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));
        CirclemidpointChange(hdc, points[0][0], points[0][1], Round(radius), RGB(0, 0, 250), colorShape);
        recursiveFloodFill = false;
        index = 0;
    }

    else if (nRFloodFill && index == 2)
    {
        double radius =
            sqrt((points[0][0] - points[1][0]) * (points[0][0] - points[1][0])
                 + (points[0][1] - points[1][1]) * (points[0][1] - points[1][1]));

        CirclemidpointChange(hdc, points[0][0], points[0][1], Round(radius), RGB(250, 0, 0));
        NonRecFloodFill(hdc, points[0][0], points[0][1], RGB(250, 0, 0), colorShape);
        index = 0;
        nRFloodFill = false;
    }
    else if (rFillingb && index == 2)
    {
        DrawAndFillRec(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape, colorShape);
        rFillingb = false;
        index = 0;
    }

    ///////////////////////////Draw Spline Curve///////////////////////////////////////
    else if (splinecurves && index == 4)
    {
        DrawCardinalSpline(hdc, points, 4, 3, colorShape);
        splinecurves = false;
        index = 0;
    }

    ////////////////////////////////Clipping////////////////////////////////////
    else if (rectanglepoint)
    {
        if (index == 2)
            drawWindow(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        else if (index == 3)
        {
            RecClipingPoint(hwnd, hdc, colorShape);
            rectanglepoint = false;
            index = 0;
        }
    }

    else if (rectangleline)
    {
        if (index == 2)
            drawWindow(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        else if (index == 4)
        {
            RecClipingLine(hwnd, hdc, colorShape);
            rectangleline = false;
            index = 0;
        }
    }

    else if (rectanglepolygon)
    {
        if (index == 2)
        {
            DrawRectangle(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        }
        else if (index == 7)
        {
            makeclippingPolygon(hwnd, hdc);
            rectanglepolygon = false;
            index = 0;
        }
    }

    else if (circlepoint)
    {
        if (index == 2)
        {
            makeClippingPointC(colorShape, 1, hwnd, hdc);
        }
        else if (index == 3)
        {
            //printf("KKKKKKK\n");
            makeClippingPointC(colorShape, 0, hwnd, hdc);
            circlepoint = false;
            index = 0;
        }

    }

    else if (circleline)
    {
        if (index == 2)
        {
            makeClippingLineC(colorShape, 1, hwnd, hdc);
        }
        else if (index == 4)
        {
            makeClippingLineC(colorShape, 0, hwnd, hdc);
            circleline = false;
            index = 0;
        }

    }


    else if (squarepoint)
    {

        if (index == 2)
            makeClippingPointS(colorShape, 1, hwnd, hdc);
        else if (index == 3)
        {
            makeClippingPointS(colorShape, 0, hwnd, hdc);
            squarepoint = false;
            index = 0;
        }
    }

    else if (squareline)
    {
        if (index == 2)
            makeClippingLineS(colorShape, 1, hwnd, hdc);
        else if (index == 4)
        {
            makeClippingLineS(colorShape, 0, hwnd, hdc);
            squarepoint = false;
            index = 0;
        }
    }
    /////////Draw Ellipse(Mid_Point,Polar,Direct).
    else if (ellipseMidPoint && index ==2 )
    {
        DrawMidpointEllipse(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        ellipseMidPoint = false;
        index = 0;
    }
    else if (ellipsePolar && index ==2 )
    {
        DrawPolarEllipse(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        ellipsePolar = false;
        index = 0;
    }
    else if (ellipseDirect&& index ==2)
    {
        DrawDirectEllipse(hdc, points[0][0], points[0][1], points[1][0], points[1][1], colorShape);
        ellipseDirect = false;
        index = 0;
    }


    ////////////////////////////////////
    /*lineParametric=false,lineMidpoint=false,lineDDA=false,cDirect=false,
            cPolar=false,citerativePolar=false,cMidpointB=false,cMidePointA=false;*/

    ///////////////////////////////////////





}



////////////////////////////////MyWndProc////////////////////////////

LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{



    static HDC hdc;

    hdc = GetDC(hwnd);
    switch (mcode)
    {
    case WM_CREATE:
        makeMenues(hwnd);
        break;
    case WM_COMMAND:
        changeStatus(wp, hwnd, mcode, lp);
        break;
    case WM_RBUTTONDOWN:
        if (index < 7)
        {
            points[index] = Vector(LOWORD(lp), HIWORD(lp));
            index++;
        }
        break;
    case WM_PAINT:
        selectWhatPaint(hdc, hwnd);
        break;
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
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
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hInstance = hinst;
    wc.lpfnWndProc = MyWndProc;
    wc.lpszClassName = "MyClass";
    wc.lpszMenuName = NULL;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    RegisterClass(&wc);
    HWND hwnd = CreateWindow("MyClass", "Graph Project", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);
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
