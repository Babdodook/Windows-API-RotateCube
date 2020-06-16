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

void Vector3D::Viewport_Convert(Vector3D origin)
{
	this->x -= origin.x;
	this->y -= origin.y;
	this->y *= -1;
}

void Vector3D::Screen_Convert(Vector3D origin)
{
	this->x += origin.x;
	this->y *= -1;
	this->y += origin.y;
}

float Vector3D::Distance()
{
	return sqrtf(powf(x, 2) + powf(y, 2) + powf(z, 2));
}

Vector3D Vector3D::Normalize()
{
	Vector3D newVector;
	float distance = Distance();
	newVector.x = this->x / distance;
	newVector.y = this->y / distance;
	newVector.z = this->z / distance;

	return newVector;
}

float Vector3D::DotProduct(const Vector3D other)
{
	return this->x* other.x + this->y * other.y + this->z * other.z;
}

Vector3D Vector3D::CrossProduct(const Vector3D other)
{
	Vector3D newVector;
	newVector.x = (this->y * other.z) - (this->z * other.y);
	newVector.y = (this->z * other.x) - (this->x * other.z);
	newVector.z = (this->x * other.y) - (this->y * other.x);

	return newVector;
}

Vector3D& Vector3D::operator=(const Vector3D& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;

	return *this;
}

Vector3D& Vector3D::operator+(const Vector3D& other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;

	return *this;
}

Vector3D& Vector3D::operator-(const Vector3D& other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

	return *this;
}