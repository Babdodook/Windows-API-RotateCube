#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <windows.h>	// 윈도우 헤더파일
#include<list>
#include<math.h>
#include"Basics.h"
#include"RectTransform.h"
#include"Vector3D.h"

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



void Viewport_Convert()
{
	
}

static RECT window;
char Vertex1[50] = "";
char Vertex2[50] = "";
char Vertex3[50] = "";
char Vertex4[50] = "";
char Position[50] = "";
RectTransform rect;
Vector3D pos;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	
	static Vector3D translate;
	static Vector3D scale;
	static Vector3D Angle;

	//memset(str, 0, sizeof(str));

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &window);
		pos = Vector3D(window.right / 2, window.bottom / 2, 1);
		rect.SetValue(pos, 200, 200);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			translate = Vector3D(-10, 0, 0);
			Angle = Vector3D(0, 0, 10);
			scale = Vector3D(1, 1, 1);
			break;
		case VK_UP:
			translate = Vector3D(0, -1, 0);
			break;
		case VK_RIGHT:
			translate = Vector3D(1, 0, 0);
			break;
		case VK_DOWN:
			translate = Vector3D(0, 1, 0);
			break;
		case VK_OEM_PLUS:
			scale = Vector3D(1.096f, 1.096f, 1);
			break;
		case VK_OEM_MINUS:
			scale = Vector3D(0.96f, 0.96f, 1);
			break;
		}
		
		rect.SetFormValue(translate, Angle, scale);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		memset(Vertex1, 0, sizeof(Vertex1));
		memset(Vertex2, 0, sizeof(Vertex2));
		memset(Vertex3, 0, sizeof(Vertex3));
		memset(Vertex4, 0, sizeof(Vertex4));
		memset(Position, 0, sizeof(Position));

		sprintf(Position, "Position (%.1f, %.1f, %.1f)", rect.position.x, rect.position.y, rect.position.z);
		sprintf(Vertex1, "Vertex1 (%.1f, %.1f, %.1f)", rect.Vertex[0].x, rect.Vertex[0].y, rect.Vertex[0].z);
		sprintf(Vertex2, "Vertex2 (%.1f, %.1f, %.1f)", rect.Vertex[1].x, rect.Vertex[1].y, rect.Vertex[1].z);
		sprintf(Vertex3, "Vertex3 (%.1f, %.1f, %.1f)", rect.Vertex[2].x, rect.Vertex[2].y, rect.Vertex[2].z);
		sprintf(Vertex4, "Vertex4 (%.1f, %.1f, %.1f)", rect.Vertex[3].x, rect.Vertex[3].y, rect.Vertex[3].z);
		

		TextOut(hdc, 10, 10, Position, strlen(Position));
		TextOut(hdc, 10, 25, Vertex1, strlen(Vertex1));
		TextOut(hdc, 10, 40, Vertex2, strlen(Vertex2));
		TextOut(hdc, 10, 55, Vertex3, strlen(Vertex3));
		TextOut(hdc, 10, 70, Vertex4, strlen(Vertex4));
		rect.DrawRect(hdc);

		
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}