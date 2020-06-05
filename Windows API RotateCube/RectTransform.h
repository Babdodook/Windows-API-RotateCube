#pragma once

#include"Basics.h"

class RectTransform {
public:
	RectTransform();
	RectTransform(Vector3D _position, float _Width, float _Height);
	~RectTransform();

	void SetValue(Vector3D _position, float _Width, float _Height);
	void SetFormValue(Vector3D translate, Vector3D angle, Vector3D scale);

	void DrawRect(HDC hdc);

	Vector3D position;
	Vector3D Vertex[8];

	MATRIX4X4 matTRS;

	float Width;
	float Height;
};