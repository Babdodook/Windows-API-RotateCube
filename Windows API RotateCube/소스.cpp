#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <windows.h>	// 윈도우 헤더파일
#include<list>
#include<math.h>

// degree -> radian
#define DEG2RAD M_PI/180

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	//CALLBACK 매크로
HINSTANCE g_hInst;					//인스턴스 핸들
LPCTSTR lpszClass = TEXT("NONE");	 //제목 표시줄에 표시되는 내용

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)   //main 함수
{
	HWND hWnd;		//윈도우 핸들 선언
	MSG Message;		 //메세지 구조체 변수 선언
	WNDCLASS WndClass;	 //Windows Class 구조체 변수 선언
	g_hInst = hInstance;    //hInstance값을 외부에서도 사용할 수 있도록 전역변수에 값을 저장

	WndClass.cbClsExtra = 0;	//예약 영역. 지금은 사용X
	WndClass.cbWndExtra = 0;	//예약 영역
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);// 윈도우의 배경 색상을 지정
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);    //윈도우의 커서(마우스포인터) 모양을 지정
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //윈도우의 커서 아이콘 모양 지정
	WndClass.hInstance = hInstance;		 //윈도우 클래스를 등록하는 프로그램 번호
	WndClass.lpfnWndProc = WndProc;		//윈도우 메세지 처리 함수 지정
	WndClass.lpszClassName = lpszClass;		//윈도우 클래스의 이름 지정
	WndClass.lpszMenuName = NULL;		//이 프로그램의 메뉴 지정
	WndClass.style = CS_HREDRAW | CS_VREDRAW;	//윈도우의 스타일을 정의

	RegisterClass(&WndClass);			//WNDCLASS 구조체의 번지를 전달


	//윈도우를 생성하고 창에 표시하는 기능을 수행
	hWnd = CreateWindow(lpszClass, lpszClass,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT
		/* 100,100,500,500*/, NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	//메세지 루프를 실행
	while (GetMessage(&Message, NULL, 0, 0)) {	//Queue에 있는 메세지를 읽어들인다
		TranslateMessage(&Message);   //키보드 입력 메세지를 가공하여 프로그램에서 쉽게 
												//  사용할 수 있도록
		DispatchMessage(&Message);//메세지를 윈도우의 메세지 처리 함수 WndProc로 전달
	}
	return (int)Message.wParam;				//탈출 코드. 프로그램 종료
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

float Gradient;			// 기울기
float axisIntercept;	// 절편

void PlotLineEquation(Point2D dot1, Point2D dot2)		// 직선의 방정식 구성
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

void DrawField(HDC hdc, RECT window) // 사각형 그리기
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

void DrawAxis(HDC hdc, RECT window)	// 좌표 평면 그리기
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
	int r = 100;		// 반지름

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