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

static RECT window;
char Vertex1[50] = "";
char Vertex2[50] = "";
char Vertex3[50] = "";
char Vertex4[50] = "";
char Position[50] = "";
RectTransform rect;
Vector3D pos;

Vector3D Translate;
Vector3D Rotate;
Vector3D Scale;
Matrix4X4 TestMat;
Vector3D resultVector;

char mat1[50] = "";
char mat2[50] = "";
char mat3[50] = "";
char mat4[50] = "";
char resultVec[50] = "";

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage) {
	case WM_CREATE:
		GetClientRect(hWnd, &window);
		pos = Vector3D(window.right / 2, window.bottom / 2, 1);
		rect.SetValue(pos, 200, 200);
		Translate = Vector3D(0, 0, 0);
		Rotate = Vector3D(0, 0, 0);
		Scale = Vector3D(1, 1, 1);
		TestMat.Init();
		resultVector = Vector3D(rect.Vertex[0].x, rect.Vertex[0].y, rect.Vertex[0].z);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			//Translate.x = -1;
			//TestMat=TestMat.Matrix4X4Translation(-50, 0, 0);
			//resultVector = TestMat * resultVector;
			Rotate.z = 5;
			break;
		case VK_UP:
			//Translate.y = 1;
			Rotate.x = 5;
			break;
		case VK_RIGHT:
			//Translate.x = 1;
			Rotate.z = -5;
			break;
		case VK_DOWN:
			//Translate.y = -1;
			Rotate.x = -5;
			break;
		case VK_OEM_PLUS:
			Scale = Vector3D(1.096f, 1.096f, 1.096f);
			break;
		case VK_OEM_MINUS:
			Scale = Vector3D(0.96f, 0.96f, 0.96f);
			break;
		}

		rect.SetFormValue(Translate, Rotate, Scale);
		InvalidateRect(hWnd, NULL, TRUE);
		return 0;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_LEFT:
			Translate.x = 0;
			Rotate.z = 0;
			break;
		case VK_UP:
			Translate.y = 0;
			Rotate.x = 0;
			break;
		case VK_RIGHT:
			Translate.x = 0;
			Rotate.z = 0;
			break;
		case VK_DOWN:
			Translate.y = 0;
			Rotate.x = 0;
			break;
		case VK_OEM_PLUS:
			Scale = Vector3D(1, 1, 1);
			break;
		case VK_OEM_MINUS:
			Scale = Vector3D(1, 1, 1);
			break;
		}

		return 0;
		InvalidateRect(hWnd, NULL, TRUE);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

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

		/*
		sprintf(mat1, "mat1 (%.1f, %.1f, %.1f)", rect.matTRS.Xaxis.x, rect.matTRS.Xaxis.y, rect.matTRS.Xaxis.z);
		sprintf(mat2, "mat2 (%.1f, %.1f, %.1f)", rect.matTRS.Yaxis.x, rect.matTRS.Yaxis.y, rect.matTRS.Yaxis.z);
		sprintf(mat3, "mat3 (%.1f, %.1f, %.1f)", rect.matTRS.Zaxis.x, rect.matTRS.Zaxis.y, rect.matTRS.Zaxis.z);
		sprintf(mat4, "mat4 (%.1f, %.1f, %.1f)", rect.matTRS.Pos.x, rect.matTRS.Pos.y, rect.matTRS.Pos.z);
		sprintf(resultVec, "resultVec (%.1f, %.1f, %.1f)", resultVector.x, resultVector.y, resultVector.z);

		TextOut(hdc, 10, 100, mat1, strlen(mat1));
		TextOut(hdc, 10, 115, mat2, strlen(mat2));
		TextOut(hdc, 10, 130, mat3, strlen(mat3));
		TextOut(hdc, 10, 145, mat4, strlen(mat4));
		TextOut(hdc, 10, 160, resultVec, strlen(resultVec));
		*/

		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}