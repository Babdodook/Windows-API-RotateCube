#pragma once

#include"Vector3D.h"

class Matrix {
public:
	Matrix();
	Matrix(Vector3D _Xaxis, Vector3D _Yaxis, Vector3D _Zaxis, Vector3D Pos);
	~Matrix();

	// Scaling * Rotation(z - x - y) * Translation
	Matrix MatrixTranslation(Matrix pOut, float x, float y, float z);
	Matrix MatrixScaling(Matrix pOut, float x, float y, float z);

	Matrix MatrixRotationX(Matrix pOut, float Angle);
	Matrix MatrixRotationY(Matrix pOut, float Angle);
	Matrix MatrixRotationZ(Matrix pOut, float Angle);

	// Roll(Rz) -> Pitch(Rx) -> Yaw(Ry)
	Matrix MatrixRotationYawPitchRoll(Matrix pOut, float Yaw, float Pitch, float Roll);

	Matrix MatrixTRS();

	Vector3D Xaxis;
	Vector3D Yaxis;
	Vector3D Zaxis;
	Vector3D Pos;

	Matrix& operator*(const Matrix& other);
};