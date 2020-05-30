#pragma once
#define _USE_MATH_DEFINES

#include"Vector3D.h"
#include<math.h>

#define PI 3.14
#define DEG2RAD PI/180

class Matrix4X4 {
public:
	Matrix4X4();
	Matrix4X4(Vector3D _Xaxis, Vector3D _Yaxis, Vector3D _Zaxis, Vector3D Pos);
	~Matrix4X4();

	void Init();
	Vector3D ViewPort_Convert(Vector3D vertex);
	Vector3D Screen_Convert(Vector3D vertex);

	Matrix4X4 Matrix4X4Translation(float x, float y, float z);
	Matrix4X4 Matrix4X4Scaling(float x, float y, float z);

	Matrix4X4 Matrix4X4RotationX(float Angle);
	Matrix4X4 Matrix4X4RotationY(float Angle);
	Matrix4X4 Matrix4X4RotationZ(float Angle);

	// Roll(Rz) -> Pitch(Rx) -> Yaw(Ry)
	Matrix4X4 Matrix4X4RotationYawPitchRoll(float Yaw, float Pitch, float Roll);

	// Scaling * Rotation(z - x - y) * Translation
	Matrix4X4 Matrix4X4TRS(Vector3D translate, Vector3D angle, Vector3D scale);

	Vector3D Xaxis;
	Vector3D Yaxis;
	Vector3D Zaxis;
	Vector3D Pos;

	Vector3D TransformWorldPosition;

	Matrix4X4& operator*(const Matrix4X4& other);
	Vector3D operator*(const Vector3D& other);
};