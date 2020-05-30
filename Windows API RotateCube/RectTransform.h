#pragma once
#define _USE_MATH_DEFINES

#include"Matrix.h"
#include<Windows.h>
#include<math.h>

class RectTransform {
public:
	RectTransform();
	RectTransform(Vector3D _position, float _Width, float _Height);
	~RectTransform();

	void SetValue(Vector3D _position, float _Width, float _Height);

	
	void XRotate();
	void YRotate();
	//Vector3D ZRotate(Vector3D other);
	

	// 이동, 회전, 크기 변환
	void Translate(Vector3D other);
	void Scale(Vector3D other);

	void ViewPort_Convert();
	void Screen_Convert();

	void DrawRect(HDC hdc);

	Matrix XAxisRot;
	Matrix YAxisRot;
	Matrix ZAxisRot;

	Vector3D position;
	Vector3D Vertex[8];

	float Width;
	float Height;
};