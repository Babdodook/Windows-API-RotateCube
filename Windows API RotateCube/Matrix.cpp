#include"Matrix.h"

Matrix::Matrix()
{
	Xaxis = Vector3D(1, 0, 0, 0);
	Yaxis = Vector3D(0, 1, 0, 0);
	Zaxis = Vector3D(0, 0, 1, 0);
	Pos = Vector3D(0, 0, 0, 1);
}

Matrix::Matrix(Vector3D _Xaxis, Vector3D _Yaxis, Vector3D _Zaxis, Vector3D _Pos)
{
	Xaxis = _Xaxis;
	Yaxis = _Yaxis;
	Zaxis = _Zaxis;
	Pos = _Pos;
}

Matrix::~Matrix()
{

}

Matrix Matrix::MatrixTranslation(Matrix pOut, float x, float y, float z)
{

}

Matrix Matrix::MatrixScaling(Matrix pOut, float x, float y, float z)
{

}

Matrix Matrix::MatrixRotationX(Matrix pOut, float Angle)
{

}

Matrix Matrix::MatrixRotationY(Matrix pOut, float Angle)
{

}

Matrix Matrix::MatrixRotationZ(Matrix pOut, float Angle)
{

}

Matrix Matrix::MatrixRotationYawPitchRoll(Matrix pOut, float Yaw, float Pitch, float Roll)
{

}

Matrix Matrix::MatrixTRS()
{

}

Matrix& Matrix::operator*(const Matrix& other)
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
