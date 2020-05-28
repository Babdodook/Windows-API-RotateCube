#pragma once
#include"Matrix.h"
#include<Windows.h>

class RectTransform {
public:
	RectTransform();
	RectTransform(Vector3D _position, float _Width, float _Height);
	~RectTransform();

	void SetValue(Vector3D _position, float _Width, float _Height);

	/*
	Vector3D XRotate(Vector3D other);
	Vector3D YRotate(Vector3D other);
	Vector3D ZRotate(Vector3D other);
	*/

	void Translate(Vector3D other);
	//Vector3D Scale(Vector3D other);

	void DrawRect(HDC hdc);

	Matrix XAxisRot;
	Matrix YAxisRot;
	Matrix ZAxisRot;

	Vector3D position;
	Vector3D Vertex[8];

	float Width;
	float Height;
};