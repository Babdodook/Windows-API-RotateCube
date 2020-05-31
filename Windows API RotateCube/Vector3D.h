#pragma once

//#include"Matrix4X4.h"

class Vector3D {
public:
	Vector3D();
	Vector3D(float _x, float _y, float _z);
	Vector3D(float _x, float _y, float _z, float _w);
	Vector3D(Vector3D& ref);
	~Vector3D();

	void SetPosition(float _x, float _y, float _z);
	void Viewport_Convert(Vector3D origin);
	void Screen_Convert(Vector3D origin);

	Vector3D& operator=(const Vector3D& other);
	//Vector3D& operator*(const Matrix4X4& other);

	float x;
	float y;
	float z;
	float w;
};