#pragma once
#define _USE_MATH_DEFINES

#include"Vector3D.h"
#include<math.h>

#define PI 3.14
#define DEG2RAD PI/180

class MATRIX4X4 {
public:
	MATRIX4X4();
	MATRIX4X4(const MATRIX4X4&);
	MATRIX4X4(float _11, float _12, float _13, float _14,
		float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34,
		float _41, float _42, float _43, float _44);
	~MATRIX4X4();

	union {
		struct {
			float        _11, _12, _13, _14;
			float        _21, _22, _23, _24;
			float        _31, _32, _33, _34;
			float        _41, _42, _43, _44;

		};
		float m[4][4];
	};

	void Identity();

	MATRIX4X4 operator*(const MATRIX4X4& other);
	Vector3D operator*(const Vector3D other);
};

MATRIX4X4 MATRIX4X4Translation(__inout MATRIX4X4& pOut, __in float x, __in float y, __in float z);
MATRIX4X4 MATRIX4X4Scaling(__inout MATRIX4X4& pOut, __in float x, __in float y, __in float z);

MATRIX4X4 MATRIX4X4RotationX(__inout MATRIX4X4& pOut, __in float Angle);
MATRIX4X4 MATRIX4X4RotationY(__inout MATRIX4X4& pOut, __in float Angle);
MATRIX4X4 MATRIX4X4RotationZ(__inout MATRIX4X4& pOut, __in float Angle);

// Roll(Rz) -> Pitch(Rx) -> Yaw(Ry)
MATRIX4X4 MATRIX4X4RotationYawPitchRoll(__inout MATRIX4X4& pOut, __in float Yaw, __in float Pitch, __in float Roll);

// Scaling * Rotation(z - x - y) * Translation
MATRIX4X4 MATRIX4X4TRS(__inout MATRIX4X4& pOut, __in Vector3D translate, __in Vector3D angle, __in Vector3D scale);