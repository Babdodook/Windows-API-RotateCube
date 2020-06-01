#pragma once
#include"Matrix4X4.h"

Matrix4X4::Matrix4X4()
{
	Xaxis = Vector3D(1, 0, 0, 0);
	Yaxis = Vector3D(0, 1, 0, 0);
	Zaxis = Vector3D(0, 0, 1, 0);
	Pos = Vector3D(0, 0, 0, 1);
}


Matrix4X4::Matrix4X4(Vector3D _Xaxis, Vector3D _Yaxis, Vector3D _Zaxis, Vector3D _Pos)
{
	Xaxis = _Xaxis;
	Yaxis = _Yaxis;
	Zaxis = _Zaxis;
	Pos = _Pos;
}

Matrix4X4::~Matrix4X4()
{

}

void Matrix4X4::Init()
{
	Xaxis = Vector3D(1, 0, 0, 0);
	Yaxis = Vector3D(0, 1, 0, 0);
	Zaxis = Vector3D(0, 0, 1, 0);
	Pos = Vector3D(0, 0, 0, 1);
}

Vector3D Matrix4X4::ViewPort_Convert(Vector3D vertex)
{
	vertex.x = (TransformWorldPosition.x - vertex.x);
	vertex.y = (TransformWorldPosition.y - vertex.y);
	vertex.y *= -1;
	vertex.z = 0;

	return vertex;
}

Vector3D Matrix4X4::Screen_Convert(Vector3D vertex)
{
	vertex.x = vertex.x + TransformWorldPosition.x;
	vertex.y *= -1;
	vertex.y = vertex.y + TransformWorldPosition.y;

	return vertex;
}

Matrix4X4 Matrix4X4::Matrix4X4Translation(float x, float y, float z)
{
	Matrix4X4 pOut;
	pOut.Init();

	pOut.Pos.x = x;
	pOut.Pos.y = y;
	pOut.Pos.z = z;

	return pOut;
}

Matrix4X4 Matrix4X4::Matrix4X4Scaling(float x, float y, float z)
{
	Matrix4X4 pOut;
	pOut.Init();

	pOut.Xaxis.x *= x;
	pOut.Yaxis.y *= y;
	pOut.Zaxis.z *= z;
	pOut.Pos.x *= x;
	pOut.Pos.y *= y;
	pOut.Pos.z *= z;

	return pOut;
}

Matrix4X4 Matrix4X4::Matrix4X4RotationX(float Angle)
{
	Matrix4X4 pOut;
	pOut.Init();

	pOut.Yaxis.y = cosf(Angle * DEG2RAD);
	pOut.Yaxis.z = sinf(Angle * DEG2RAD);
	pOut.Zaxis.y = -sinf(Angle * DEG2RAD);
	pOut.Zaxis.z = cosf(Angle * DEG2RAD);

	return pOut;
}

Matrix4X4 Matrix4X4::Matrix4X4RotationY(float Angle)
{
	Matrix4X4 pOut;
	pOut.Init();

	pOut.Xaxis.x = cosf(Angle * DEG2RAD);
	pOut.Xaxis.z = -sinf(Angle * DEG2RAD);
	pOut.Zaxis.x = sinf(Angle * DEG2RAD);
	pOut.Zaxis.z = cosf(Angle * DEG2RAD);

	return pOut;
}

Matrix4X4 Matrix4X4::Matrix4X4RotationZ(float Angle)
{
	Matrix4X4 pOut;
	pOut.Init();

	pOut.Xaxis.x = cosf(Angle * DEG2RAD);
	pOut.Xaxis.y = sinf(Angle * DEG2RAD);
	pOut.Yaxis.x = -sinf(Angle * DEG2RAD);
	pOut.Yaxis.y = cosf(Angle * DEG2RAD);

	return pOut;
}

Matrix4X4 Matrix4X4::Matrix4X4RotationYawPitchRoll(float Yaw, float Pitch, float Roll)
{
	Matrix4X4 matRotateX;
	Matrix4X4 matRotateY;
	Matrix4X4 matRotateZ;

	matRotateX.Init();
	matRotateY.Init();
	matRotateZ.Init();

	matRotateX = Matrix4X4RotationX(Pitch);
	matRotateY = Matrix4X4RotationY(Yaw);
	matRotateZ = Matrix4X4RotationZ(Roll);

	// z * x * y
	return matRotateZ * matRotateX * matRotateY;
}

Matrix4X4 Matrix4X4::Matrix4X4TRS(Vector3D translate, Vector3D angle, Vector3D scale)
{
	Matrix4X4 TRS = (Matrix4X4Translation(translate.x, translate.y, translate.z) * Matrix4X4RotationYawPitchRoll(angle.y, angle.x, angle.z))* Matrix4X4Scaling(scale.x, scale.y, scale.z);

	return TRS;
}

Matrix4X4& Matrix4X4::operator*(const Matrix4X4& other)
{
	this->Xaxis = Vector3D
	(
		(Xaxis.x * other.Xaxis.x) + (Xaxis.y * other.Yaxis.x) + (Xaxis.z * other.Zaxis.x) + (Xaxis.w * other.Pos.x),
		(Xaxis.x * other.Xaxis.y) + (Xaxis.y * other.Yaxis.y) + (Xaxis.z * other.Zaxis.y) + (Xaxis.w * other.Pos.y),
		(Xaxis.x * other.Xaxis.z) + (Xaxis.y * other.Yaxis.z) + (Xaxis.z * other.Zaxis.z) + (Xaxis.w * other.Pos.z),
		(Xaxis.x * other.Xaxis.w) + (Xaxis.y * other.Yaxis.w) + (Xaxis.z * other.Zaxis.w) + (Xaxis.w * other.Pos.w)
	);

	this->Yaxis = Vector3D
	(
		(Yaxis.x * other.Xaxis.x) + (Yaxis.y * other.Yaxis.x) + (Yaxis.z * other.Zaxis.x) + (Yaxis.w * other.Pos.x),
		(Yaxis.x * other.Xaxis.y) + (Yaxis.y * other.Yaxis.y) + (Yaxis.z * other.Zaxis.y) + (Yaxis.w * other.Pos.y),
		(Yaxis.x * other.Xaxis.z) + (Yaxis.y * other.Yaxis.z) + (Yaxis.z * other.Zaxis.z) + (Yaxis.w * other.Pos.z),
		(Yaxis.x * other.Xaxis.w) + (Yaxis.y * other.Yaxis.w) + (Yaxis.z * other.Zaxis.w) + (Yaxis.w * other.Pos.w)
	);

	this->Zaxis = Vector3D
	(
		(Zaxis.x * other.Xaxis.x) + (Zaxis.y * other.Yaxis.x) + (Zaxis.z * other.Zaxis.x) + (Zaxis.w * other.Pos.x),
		(Zaxis.x * other.Xaxis.y) + (Zaxis.y * other.Yaxis.y) + (Zaxis.z * other.Zaxis.y) + (Zaxis.w * other.Pos.y),
		(Zaxis.x * other.Xaxis.z) + (Zaxis.y * other.Yaxis.z) + (Zaxis.z * other.Zaxis.z) + (Zaxis.w * other.Pos.z),
		(Zaxis.x * other.Xaxis.w) + (Zaxis.y * other.Yaxis.w) + (Zaxis.z * other.Zaxis.w) + (Zaxis.w * other.Pos.w)
	);

	this->Pos = Vector3D
	(
		(Pos.x * other.Xaxis.x) + (Pos.y * other.Yaxis.x) + (Pos.z * other.Zaxis.x) + (Pos.w * other.Pos.x),
		(Pos.x * other.Xaxis.y) + (Pos.y * other.Yaxis.y) + (Pos.z * other.Zaxis.y) + (Pos.w * other.Pos.y),
		(Pos.x * other.Xaxis.z) + (Pos.y * other.Yaxis.z) + (Pos.z * other.Zaxis.z) + (Pos.w * other.Pos.z),
		(Pos.x * other.Xaxis.w) + (Pos.y * other.Yaxis.w) + (Pos.z * other.Pos.w) + (Pos.w * other.Pos.w)
	);

	return *this;
}

/*
Vector3D Matrix4X4::operator*(const Vector3D& other)
{
	Vector3D newVector;
	newVector = other;

	newVector.x = ((other.x * Xaxis.x) + (other.y * Yaxis.x) + (other.z * Zaxis.x) + (other.w * Pos.x));
	newVector.y = ((other.x * Xaxis.y) + (other.y * Yaxis.y) + (other.z * Zaxis.y) + (other.w * Pos.y));
	newVector.z = ((other.x * Xaxis.z) + (other.y * Yaxis.z) + (other.z * Zaxis.z) + (other.w * Pos.z));
	newVector.w = ((other.x * Xaxis.w) + (other.y * Yaxis.w) + (other.z * Zaxis.w) + (other.w * Pos.w));

	return newVector;
}
*/

Vector3D Matrix4X4::operator*(const Vector3D other)
{
	Vector3D newVector;
	newVector = other;

	newVector.x = ((other.x * Xaxis.x) + (other.y * Yaxis.x) + (other.z * Zaxis.x) + (other.w * Pos.x));
	newVector.y = ((other.x * Xaxis.y) + (other.y * Yaxis.y) + (other.z * Zaxis.y) + (other.w * Pos.y));
	newVector.z = ((other.x * Xaxis.z) + (other.y * Yaxis.z) + (other.z * Zaxis.z) + (other.w * Pos.z));
	newVector.w = ((other.x * Xaxis.w) + (other.y * Yaxis.w) + (other.z * Zaxis.w) + (other.w * Pos.w));

	return newVector;
}