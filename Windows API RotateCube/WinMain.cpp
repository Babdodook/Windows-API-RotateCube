#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <windows.h>	// ������ �������
#include<list>
#include<math.h>
#include"Basics.h"
#include"RectTransform.h"
#include"Vector3D.h"

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