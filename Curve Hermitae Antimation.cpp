#include <Windows.h>
int Round(double x)
{
	return (int)(x + 0.5);
}
struct Vector{
	double v[2];
	Vector(double x = 0, double y = 0)
	 { v[0] = x; v[1] = y; }
	double& operator[](int i){ return v[i];
	}
};
void DrawHermiteCurve(HDC hdc,Vector& p1, Vector& T1, Vector& p2, Vector& T2, COLORREF c)
{
	double a0 = p1[0], a1 = T1[0],
		a2 = -3 * p1[0] - 2 * T1[0] + 3 * p2[0] - T2[0],
		a3 = 2 * p1[0] + T1[0] - 2 * p2[0] + T2[0];
	double b0 = p1[1], b1 = T1[1],
		b2 = -3 * p1[1] - 2 * T1[1] + 3 * p2[1] - T2[1],
		b3 = 2 * p1[1] + T1[1] - 2 * p2[1] + T2[1];
	for (double t = 0; t <= 1; t += 0.001)
	{
		double t2 = t*t, t3 = t2*t;
		double x = a0 + a1*t + a2*t2 + a3*t3;
		double y = b0 + b1*t + b2*t2 + b3*t3;
		SetPixel(hdc, Round(x), Round(y), c);
		Sleep(10);
	}
}
static Vector p[4];
DWORD WINAPI MyThread(void *lp)
{
	HWND hwnd = (HWND)lp;
	HDC hdc;
	Vector T1(3 * (p[1][0] - p[0][0]), 3 * (p[1][1] - p[0][1]));
	Vector T2(3 * (p[3][0] - p[2][0]), 3 * (p[3][1] - p[2][1]));
	hdc = GetDC(hwnd);
	DrawHermiteCurve(hdc, p[0], T1, p[3], T2, RGB(255, 0, 0));
	ReleaseDC(hwnd, hdc);
	return 0;
}
LRESULT WINAPI MyWndProc(HWND hwnd, UINT mcode, WPARAM wp, LPARAM lp)
{
	static int index = 0;
	switch (mcode)
	{
	case WM_LBUTTONDOWN:
		p[index] = Vector(LOWORD(lp), HIWORD(lp));
		if (index == 3){
			CreateThread(NULL, NULL, MyThread, hwnd, NULL, NULL);
			index = 0;
		}
		else index++;
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default: return DefWindowProc(hwnd, mcode, wp, lp);
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
	HWND hwnd = CreateWindow("MyClass", "Curve Hermiate Animation", WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, NULL, hinst, 0);
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
