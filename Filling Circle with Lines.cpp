#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <math.h>
/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");
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

void DrawLine(HDC hdc,int x1, int y1, int x2, int y2,COLORREF color)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    double slope=(double)dy/dx;
    if (abs(dy) <= abs(dx))
    {
        if (x1 > x2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc,x1, y1,color);
        int x = x1;
        double y=y1;
        while (x < x2)
        {
            x++;
            y =y+slope;
            SetPixel(hdc, x, Round(y),color);
        }
    }
    else
    {
        if (y1 > y2)
            swap(x1, y1, x2, y2);
        SetPixel(hdc, x1, y1,color);
        int y = y1;
        double x=x1;
        while (y < y2)
        {
            y++;
            x = x+(double)1/slope;
            SetPixel(hdc, Round(x), y,color);
        }
    }
}
void Draw8Points(HDC hdc,int xc, int yc, int x, int y)
{
    DrawLine(hdc, xc,yc,xc + x, yc + y,RGB(178,34,34));
    DrawLine(hdc,xc,yc,xc + x, yc - y,RGB(50,205,50));
    DrawLine(hdc,xc,yc,xc - x, yc - y,RGB(124,252,0));
    DrawLine(hdc,xc,yc,xc - x, yc + y,RGB(0, 0, 139));
    DrawLine(hdc,xc,yc,xc + y, yc + x,RGB(178,34,34));
    DrawLine(hdc,xc,yc,xc + y, yc - x,RGB(0, 0, 139));
    DrawLine(hdc,xc,yc,xc - y, yc - x,RGB(50,50,50));
    DrawLine(hdc,xc,yc,xc - y, yc + x,RGB(34,139,34));

}

void DrawCircleBresenham(HDC hdc,int xc, int yc, int R)
{
    int x = 0;
    double y = R;
    int d=1-R;

    Draw8Points(hdc,xc, yc, 0, R);

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
        Draw8Points(hdc,xc, yc, x, Round(y));
    }
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WindowProcedure; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);

	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wc.lpszClassName = "WindowClass";
	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm		 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","Filling Circuit",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		640, /* width */
		480, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	/*
		This is the heart of our program where all input is processed and
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HDC hdc;
    static int counter=0,xCenter,yCenter,xRadius,yRadius;
    switch (message)                  /* handle the messages */
    {
    case WM_CREATE:
        hdc = GetDC(hwnd);
        break;
    case WM_LBUTTONDOWN:
        //Center Point of the circuit
        if(counter==0)
        {
            xCenter=LOWORD (lParam);
            yCenter=HIWORD (lParam);
            counter++;
        }
        break;

    case WM_RBUTTONDOWN:
        if(counter==1)
        {
            xRadius=LOWORD (lParam);
            yRadius=HIWORD (lParam);
            counter++;
        }
        break;
    case WM_PAINT:
        if(counter==2)
        {
            double radius=sqrt((xCenter-xRadius)*(xCenter-xRadius)+(yCenter-yRadius)*(yCenter-yRadius));
            DrawCircleBresenham(hdc,xCenter,yCenter,Round(radius));
            counter=0;
            ReleaseDC(hwnd, hdc);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
