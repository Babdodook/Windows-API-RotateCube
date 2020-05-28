#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <windows.h>	// ������ �������
#include<list>
#include<math.h>

// degree -> radian
#define DEG2RAD M_PI/180

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK ��ũ��
HINSTANCE g_hInst;					//�ν��Ͻ� �ڵ�
LPCTSTR lpszClass = TEXT("NONE");	 //���� ǥ���ٿ� ǥ�õǴ� ����

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)   //main �Լ�
{
	HWND hWnd;		//������ �ڵ� ����
	MSG Message;		 //�޼��� ����ü ���� ����
	WNDCLASS WndClass;	 //Windows Class ����ü ���� ����
	g_hInst = hInstance;    //hInstance���� �ܺο����� ����� �� �ֵ��� ���������� ���� ����

	WndClass.cbClsExtra = 0;	//���� ����. ������ ���X
	WndClass.cbWndExtra = 0;	//���� ����
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// �������� ��� ������ ����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //�������� Ŀ��(���콺������) ����� ����
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //�������� Ŀ�� ������ ��� ����
	WndClass.hInstance = hInstance;		 //������ Ŭ������ ����ϴ� ���α׷� ��ȣ
	WndClass.lpfnWndProc = WndProc;		//������ �޼��� ó�� �Լ� ����
	WndClass.lpszClassName = lpszClass;		//������ Ŭ������ �̸� ����
	WndClass.lpszMenuName = NULL;		//�� ���α׷��� �޴� ����
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//�������� ��Ÿ���� ����

	RegisterClass(&WndClass);			//WNDCLASS ����ü�� ������ ����


	//�����츦 �����ϰ� â�� ǥ���ϴ� ����� ����
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//�޼��� ������ ����
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue�� �ִ� �޼����� �о���δ�
		TranslateMessage(&Message);   //Ű���� �Է� �޼����� �����Ͽ� ���α׷����� ���� 
												//  ����� �� �ֵ���
		DispatchMessage(&Message);//�޼����� �������� �޼��� ó�� �Լ� WndProc�� ����
	}
	return (int)Message.wParam;				//Ż�� �ڵ�. ���α׷� ����
}

struct Point2D {
	float x, y;
	Point2D()
	{
		x = 0;
		y = 0;
	}
	Point2D(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	void over(Point2D newPoint)
	{
		x = newPoint.x;
		y = newPoint.y;
	}
};

static RECT window;
std::list<Point2D> LogicalPoints;
std::list<Point2D> SinGraphPoints;

std::list<Point2D>::iterator iter;
Point2D temp = Point2D(0, 0);

char str[10] = "";

float Gradient;			// ����
float axisIntercept;	// ����

void PlotLineEquation(Point2D dot1, Point2D dot2)		// ������ ������ ����
{
	Gradient = 0.0f;

	if (dot2.x != dot1.x)
		Gradient = (dot2.y - dot1.y) / (dot2.x - dot1.x);	// m = (y2-y1) / (x2-x1)

	axisIntercept = dot1.x - Gradient * dot1.x;			// b = y - mx
}

void PlotLine(HDC hdc, Point2D Start, Point2D Destination)
{
	float dx = abs(Destination.x - Start.x);
	float sx = Start.x < Destination.x ? 1 : -1;
	float dy = -abs(Destination.y - Start.y);
	float sy = Start.y < Destination.y ? 1 : -1;
	float err = dx + dy;

	while (true)
	{
		SetPixel(hdc, Start.x, Start.y, RGB(0, 0, 0));

		if (Start.x == Destination.x && Start.y == Destination.y)
			break;

		float e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			Start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			Start.y += sy;
		}
	}
}

void DrawField(HDC hdc, RECT window) // �簢�� �׸���
{
	Point2D rect_LeftTop = Point2D(window.right / 2 - 200, window.bottom / 2 - 200);
	Point2D rect_LeftBottom = Point2D(window.right / 2 - 200, window.bottom / 2 + 200);
	Point2D rect_RightTop = Point2D(window.right / 2 + 200, window.bottom / 2 - 200);
	Point2D rect_RightBottom = Point2D(window.right / 2 + 200, window.bottom / 2 + 200);

	PlotLine(hdc, rect_LeftTop, rect_RightTop);
	PlotLine(hdc, rect_RightTop, rect_RightBottom);
	PlotLine(hdc, rect_RightBottom, rect_LeftBottom);
	PlotLine(hdc, rect_LeftBottom, rect_LeftTop);
}

void DrawField2(HDC hdc, RECT window)
{
	Point2D rect_LeftTop = Point2D(window.right / 2 - 200, window.bottom / 2 - 200);
	Point2D rect_LeftBottom = Point2D(window.right / 2 - 200, window.bottom / 2 + 200);
	Point2D rect_RightTop = Point2D(window.right / 2 + 200, window.bottom / 2 - 200);
	Point2D rect_RightBottom = Point2D(window.right / 2 + 200, window.bottom / 2 + 200);
}

void DrawAxis(HDC hdc, RECT window)	// ��ǥ ��� �׸���
{
	Point2D CenterTop = Point2D(window.right / 2, window.bottom / 2 - 200);
	Point2D CenterBottom = Point2D(window.right / 2, window.bottom / 2 + 200);
	Point2D CenterLeft = Point2D(window.right / 2 - 200, window.bottom / 2);
	Point2D CenterRight = Point2D(window.right / 2 + 200, window.bottom / 2);

	PlotLine(hdc, CenterTop, CenterBottom);
	PlotLine(hdc, CenterLeft, CenterRight);
}

Point2D CenterOfViewPort;

Point2D MaxOfField;
Point2D MinOfField;
Point2D circlePoint;

void Viewport_ConvertY(Point2D point)
{
	Point2D LogicalPoint = Point2D();

	LogicalPoint.x = point.x - CenterOfViewPort.x;
	LogicalPoint.y = (point.y - CenterOfViewPort.y) * -1;

	LogicalPoints.push_back(LogicalPoint);

	temp.over(LogicalPoints.back());
	strcpy(str, " ");
	sprintf(str, "%.2f %.2f", temp.x, temp.y);
}

Point2D CheckInField(Point2D point)
{
	if (point.x < MinOfField.x)
		point.x = MinOfField.x;
	else if (point.x > MaxOfField.x)
		point.x = MaxOfField.x;

	if (point.y < MinOfField.y)
		point.y = MinOfField.y;
	else if (point.y > MaxOfField.y)
		point.y = MaxOfField.y;

	return point;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;

	Point2D mouse = Point2D();
	static RECT textRT;

	int x, y;
	int r = 100;		// ������

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &window);
		CenterOfViewPort = Point2D(window.right / 2, window.bottom / 2);
		MaxOfField = Point2D(window.right / 2 + 190, window.bottom / 2 + 190);
		MinOfField = Point2D(window.right / 2 - 190, window.bottom / 2 - 190);
		return 0;
		/*
	case WM_LBUTTONDOWN:
		mouse.x = LOWORD(lParam);
		mouse.y = HIWORD(lParam);

		mouse = CheckInField(mouse);
		Viewport_ConvertY(mouse);

		hdc = GetDC(hWnd);
		Ellipse(hdc, mouse.x - 10, mouse.y - 10, mouse.x + 10, mouse.y + 10);
		ReleaseDC(hWnd, hdc);


		//InvalidateRect(hWnd, &textRT, TRUE);
		return 0;
		*/
	case WM_PAINT:
		hdc = GetDC(hWnd);
		DrawField(hdc, window);
		DrawAxis(hdc, window);

		/*
		for (int i = 1; i < 360; i++)
		{
			if (i != 90)
			{
				x = cos(i * DEG2RAD) * r + window.right / 2;
				y = sin(i * DEG2RAD) * r + window.bottom / 2;
				SetPixel(hdc, x, y, RGB(0, 0, 0));
			}
		}

		for (int i = -200; i < 200; i++)
		{
			x = i + window.right / 2 + 200;
			y = sin(i * DEG2RAD) * r + window.bottom / 2;
			SetPixel(hdc, x, y, RGB(0, 0, 0));
		}
		*/

		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}