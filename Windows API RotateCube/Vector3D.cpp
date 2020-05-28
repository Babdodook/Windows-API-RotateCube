#pragma once
#include"Vector3D.h"

Vector3D::Vector3D()
	: x(0), y(0), z(0), w(1)
{
}

Vector3D::Vector3D(float _x, float _y, float _z)
	: x(_x), y(_y), z(_z), w(1)
{
}

Vector3D::Vector3D(float _x, float _y, float _z, float _w)
	: x(_x), y(_y), z(_z), w(_w)
{
}

Vector3D::Vector3D(Vector3D& ref)
{
	this->x = ref.x;
	this->y = ref.y;
	this->z = ref.z;
	w = 1;
}

Vector3D::~Vector3D()
{

}

void Vector3D::SetPosition(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}