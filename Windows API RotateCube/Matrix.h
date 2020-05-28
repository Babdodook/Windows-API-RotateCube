#pragma once

#include"Vector3D.h"

class Matrix {
public:
	Matrix();
	Matrix(Vector3D _Xaxis, Vector3D _Yaxis, Vector3D _Zaxis, Vector3D Pos);
	~Matrix();

	Vector3D Xaxis;
	Vector3D Yaxis;
	Vector3D Zaxis;
	Vector3D Pos;

	//Vector3D operator*(const Vector3D& vector);
};