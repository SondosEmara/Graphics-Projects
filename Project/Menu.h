#pragma once
#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

//////////////////////////////////////MakeMenus///////////////////////////////////////////
void makeMenues(HWND hwnd)
{
    //hmenuObj --> is handle menu object.(Main menu).
    HMENU hmenu = CreateMenu();
    HMENU hColorMenu = CreateMenu();
    HMENU hLineMenu = CreateMenu();
    HMENU hCircleMenu = CreateMenu();
    HMENU hFileMenu = CreateMenu();
    HMENU hFillingMenu = CreateMenu();
    HMENU hClippingMenu = CreateMenu();
    HMENU hCurveMenu = CreateMenu();
    HMENU hEllipseMenu = CreateMenu();

    //File Menu-------------------------------------------------------
    AppendMenu(hFileMenu, MF_STRING, SAVE, "Save");
    AppendMenu(hFileMenu, MF_STRING, LOAD, "Load");
    AppendMenu(hFileMenu, MF_STRING, CLEAR, "Clear");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");

    //Circle Menu------------------------------------------
    AppendMenu(hCircleMenu, MF_STRING, Circle_Direct, "Circle_Direct");
    AppendMenu(hCircleMenu, MF_STRING, Circle_Polar, "Circle_Polar");
    AppendMenu(hCircleMenu, MF_STRING, Circle_IterativePolar, "Circle_IterativePolar");
    AppendMenu(hCircleMenu, MF_STRING, Circle_Midpoint_BeforeModify, "Circle_Midpoint_BeforeModify");
    AppendMenu(hCircleMenu, MF_STRING, Circle_Midpoint_AfterModify, "Circle_Midpoint_AfterModify");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hCircleMenu, "Circle");

    //Ellipse Menu------------------------------------------
    AppendMenu(hEllipseMenu, MF_STRING, ellipse_polar, "PolarEllipse");
    AppendMenu(hEllipseMenu, MF_STRING, ellipse_Midpoint, "MidpointEllipse");
    AppendMenu(hEllipseMenu, MF_STRING, ellipse_direct, "DirectEllipse");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hEllipseMenu, "Ellipse");


    //Line Menu-----------------------------------------------
    AppendMenu(hLineMenu, MF_STRING, Line_Parametric, "Parametric");
    AppendMenu(hLineMenu, MF_STRING, Line_Midpoint, "Midpoint");
    AppendMenu(hLineMenu, MF_STRING, Line_DDA, "DDA");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hLineMenu, "Line");

    AppendMenu(hCurveMenu, MF_STRING, SplineCurves, "Spline Curves");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hCurveMenu, "Curve");

    //Filling Menu

    AppendMenu(hFillingMenu, MF_STRING, NONRecursiveFloodFill, "NON Recursive FloodFill");
    AppendMenu(hFillingMenu, MF_STRING, RecursiveFloodFill, "Recursive FloodFill");
    AppendMenu(hFillingMenu, MF_STRING, NonConfixFilling, "NON Convex Filling");
    AppendMenu(hFillingMenu, MF_STRING, ConfixFilling, "Convex Filling");
    AppendMenu(hFillingMenu, MF_STRING, RFillingB, "Rectangle with Bezier");
    AppendMenu(hFillingMenu, MF_STRING, SFillingH, "Square With HermiteCurve");
    AppendMenu(hFillingMenu, MF_STRING, CFillingC, "Circle With Circles");
    AppendMenu(hFillingMenu, MF_STRING, CFillingL, "Circle With Lines");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hFillingMenu, "Filling");


    //Clipping algorithms using Rectangle as Clipping Window[Point ,Line, Polygon
    //Clipping Menu

    AppendMenu(hClippingMenu, MF_STRING, RectanglePoint, "Rectangle Point");
    AppendMenu(hClippingMenu, MF_STRING, RectangleLine, "Rectangle Line");
    AppendMenu(hClippingMenu, MF_STRING, RectanglePolygon, "Rectangle Polygon");
    AppendMenu(hClippingMenu, MF_STRING, CirclePoint, "Circle Point");
    AppendMenu(hClippingMenu, MF_STRING, CircleLine, "Circle Line");
    AppendMenu(hClippingMenu, MF_STRING, SquarePoint, "Square Point");
    AppendMenu(hClippingMenu, MF_STRING, SquareLine, "Square Line");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hClippingMenu, "Clipping");


    //Color Menu---------------------------------------------
    AppendMenu(hColorMenu, MF_STRING, Blue, "Blue");
    AppendMenu(hColorMenu, MF_STRING, Black, "Black");
    AppendMenu(hColorMenu, MF_STRING, Red, "Red");
    AppendMenu(hmenu, MF_POPUP, (UINT_PTR)hColorMenu, "Color");

    //hwnd-->handle the wwindow
    //to set the menu in window
    SetMenu(hwnd, hmenu);
}



#endif // MENU_H_INCLUDED

