#pragma once
#include"Matrix4X4.h"

MATRIX4X4::MATRIX4X4()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

MATRIX4X4::MATRIX4X4(const MATRIX4X4& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			this->m[i][j] = other.m[i][j];
		}
	}
}

MATRIX4X4::MATRIX4X4(float _11, float _12, float _13, float _14,
	float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34,
	float _41, float _42, float _43, float _44)
{
	this->_11 = _11;
	this->_12 = _12;
	this->_13 = _13;
	this->_14 = _14;
	this->_21 = _21;
	this->_22 = _22;
	this->_23 = _23;
	this->_24 = _24;
	this->_31 = _31;
	this->_32 = _32;
	this->_33 = _33;
	this->_34 = _34;
	this->_41 = _41;
	this->_42 = _42;
	this->_43 = _43;
	this->_44 = _44;
}

MATRIX4X4::~MATRIX4X4()
{

}

void MATRIX4X4::Identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}

MATRIX4X4 MATRIX4X4Translation(__inout MATRIX4X4& pOut, __in float x, __in float y, __in float z)
{
	pOut.Identity();

	pOut.m[3][0] = x;
	pOut.m[3][1] = y;
	pOut.m[3][2] = z;

	return pOut;
}

MATRIX4X4 MATRIX4X4Scaling(__inout MATRIX4X4& pOut, __in float x, __in float y, __in float z)
{
	pOut.Identity();

	pOut.m[0][0] = x;
	pOut.m[1][1] = y;
	pOut.m[2][2] = z;

	return pOut;
}

MATRIX4X4 MATRIX4X4RotationX(__inout MATRIX4X4& pOut, __in float Angle)
{
	pOut.Identity();

	pOut.m[1][1] = cosf(Angle * DEG2RAD);
	pOut.m[1][2] = sinf(Angle * DEG2RAD);
	pOut.m[2][1] = -sinf(Angle * DEG2RAD);
	pOut.m[2][2] = cosf(Angle * DEG2RAD);

	return pOut;
}

MATRIX4X4 MATRIX4X4RotationY(__inout MATRIX4X4& pOut, __in float Angle)
{
	pOut.Identity();

	pOut.m[0][0] = cosf(Angle * DEG2RAD);
	pOut.m[0][2] = -sinf(Angle * DEG2RAD);
	pOut.m[2][0] = sinf(Angle * DEG2RAD);
	pOut.m[2][2] = cosf(Angle * DEG2RAD);

	return pOut;
}

MATRIX4X4 MATRIX4X4RotationZ(__inout MATRIX4X4& pOut, __in float Angle)
{
	pOut.Identity();

	pOut.m[0][0] = cosf(Angle * DEG2RAD);
	pOut.m[0][1] = sinf(Angle * DEG2RAD);
	pOut.m[1][0] = -sinf(Angle * DEG2RAD);
	pOut.m[1][1] = cosf(Angle * DEG2RAD);

	return pOut;
}

MATRIX4X4 MATRIX4X4RotationYawPitchRoll(__inout MATRIX4X4& pOut, float Yaw, float Pitch, float Roll)
{
	MATRIX4X4 matRotateX;
	MATRIX4X4 matRotateY;
	MATRIX4X4 matRotateZ;

	matRotateX.Identity();
	matRotateY.Identity();
	matRotateZ.Identity();

	matRotateX = MATRIX4X4RotationX(pOut, Pitch);
	matRotateY = MATRIX4X4RotationY(pOut, Yaw);
	matRotateZ = MATRIX4X4RotationZ(pOut, Roll);

	// z * x * y
	return matRotateZ * matRotateX * matRotateY;
}

MATRIX4X4 MATRIX4X4TRS(__inout MATRIX4X4& pOut, __in Vector3D translate, __in Vector3D angle, __in Vector3D scale)
{
	MATRIX4X4 TRS = (MATRIX4X4Translation(pOut, translate.x, translate.y, translate.z) * MATRIX4X4RotationYawPitchRoll(pOut, angle.y, angle.x, angle.z))* MATRIX4X4Scaling(pOut, scale.x, scale.y, scale.z);

	return TRS;
}

MATRIX4X4 MATRIX4X4::operator*(const MATRIX4X4& other)
{
	MATRIX4X4 newMatrix;

	float sum;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += this->m[i][k] * other.m[k][j];
			}
			newMatrix.m[i][j] = sum;
		}
	}

	return newMatrix;
}


Vector3D MATRIX4X4::operator*(const Vector3D other)
{
	float newVector[4];
	float tempVector[4];
	tempVector[0] = other.x;
	tempVector[1] = other.y;
	tempVector[2] = other.z;
	tempVector[3] = other.w;
	
	float sum;
	for (int i = 0; i < 4; i++)
	{
		sum = 0;
		for (int j = 0; j < 4; j++)
		{
			sum += tempVector[j] * this->m[j][i];
		}
		newVector[i] = sum;
	}

	Vector3D resultVector;
	resultVector.x = newVector[0];
	resultVector.y = newVector[1];
	resultVector.z = newVector[2];
	resultVector.w = newVector[3];

	return resultVector;
}