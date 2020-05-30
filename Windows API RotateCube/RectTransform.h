#pragma once

#include"Basics.h"

class RectTransform {
public:
	RectTransform();
	RectTransform(Vector3D _position, float _Width, float _Height);
	~RectTransform();

	void SetValue(Vector3D _position, float _Width, float _Height);
	void SetFormValue(Vector3D translate, Vector3D scale, Vector3D Angle);

	void DrawRect(HDC hdc);

	Vector3D position;
	Vector3D Vertex[8];

	Matrix4X4 matTRS;

	float Width;
	float Height;
};