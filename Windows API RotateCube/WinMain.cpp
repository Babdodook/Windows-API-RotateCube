#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <windows.h>	// ������ �������
#include<list>
#include<math.h>
#include"Basics.h"
#include"RectTransform.h"
#include"Vector3D.h"

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



void Viewport_Convert()
{
	
}

static RECT window;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	RectTransform rect;
	Vector3D pos;
	static Vector3D translate;

	
	pos = Vector3D(window.right / 2, window.bottom / 2, 1);
	rect.SetValue(pos, 200, 200);

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &window);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			translate = Vector3D(-10, 0, 0);
			break;
		case VK_UP:
			translate = Vector3D(0, 10, 0);
			break;
		case VK_RIGHT:
			translate = Vector3D(10, 0, 0);
			break;
		case VK_DOWN:
			translate = Vector3D(0, -10, 0);
			break;
		}
		rect.Translate(translate);		
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_PAINT:
		hdc = GetDC(hWnd);
		rect.DrawRect(hdc);
		ReleaseDC(hWnd, hdc);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}