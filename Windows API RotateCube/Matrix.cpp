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

/*
Vector3D Matrix::operator*(const Vector3D& vector)
{
	return vector;
}
*/