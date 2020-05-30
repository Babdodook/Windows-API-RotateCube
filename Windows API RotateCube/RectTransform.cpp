#include"RectTransform.h"
#include"Basics.h"
#include<string>

RectTransform::RectTransform()
{
	position = Vector3D(0, 0, 0);
	memset(Vertex, 0, sizeof(Vector3D) * 8);
}

RectTransform::RectTransform(Vector3D _position, float _Width, float _Height)
{
	position = _position;
	Vertex[0].x = position.x - _Width / 2;
	Vertex[0].y = position.y - _Height / 2;

	Vertex[1].x = position.x + _Width / 2;
	Vertex[1].y = position.y - _Height / 2;

	Vertex[2].x = position.x - _Width / 2;
	Vertex[2].y = position.y + _Height / 2;

	Vertex[3].x = position.x + _Width / 2;
	Vertex[3].y = position.y + _Height / 2;
}

RectTransform::~RectTransform()
{

}

void RectTransform::SetValue(Vector3D _position, float _Width, float _Height)
{
	position = _position;
	Vertex[0].x = position.x - _Width / 2;
	Vertex[0].y = position.y - _Height / 2;

	Vertex[1].x = position.x + _Width / 2;
	Vertex[1].y = position.y - _Height / 2;

	Vertex[2].x = position.x - _Width / 2;
	Vertex[2].y = position.y + _Height / 2;

	Vertex[3].x = position.x + _Width / 2;
	Vertex[3].y = position.y + _Height / 2;
}


void RectTransform::XRotate()
{
	ViewPort_Convert();

	Vector3D ViewPort_Postion[4];

	for (int i = 0; i < 4; i++)
		ViewPort_Postion[i] = Vertex[i];

	for (int i = 0; i < 4; i++)
	{
		ViewPort_Postion[i].x = (Vertex[i].x * cos(10 * DEG2RAD)) - (Vertex[i].y * sin(10 * DEG2RAD));
		ViewPort_Postion[i].y = (Vertex[i].x * sin(10 * DEG2RAD)) + (Vertex[i].y * cos(10 * DEG2RAD));

		Vertex[i].x = ViewPort_Postion[i].x;
		Vertex[i].y = ViewPort_Postion[i].y;
		Vertex[i].z = ViewPort_Postion[i].z;
	}

	//for (int i = 0; i < 4; i++)
		//Vertex[i] = ViewPort_Postion[i];

	Screen_Convert();
}

void RectTransform::YRotate()
{
	Vector3D ViewPort_Postion[4];

	for (int i = 0; i < 4; i++)
	{
		ViewPort_Postion[i] = Vertex[i];

		ViewPort_Postion[i].x = (int)(position.x - ViewPort_Postion[i].x);
		Vertex[i].z = 0;

		Vertex[i] = ViewPort_Postion[i];
	}

	for (int i = 0; i < 4; i++)
	{
		ViewPort_Postion[i].x = (Vertex[i].x * cos(10 * DEG2RAD)) + (Vertex[i].z * sin(10 * DEG2RAD));
		ViewPort_Postion[i].z = (Vertex[i].x * -sin(1 * DEG2RAD)) + (Vertex[i].z * cos(1 * DEG2RAD));

		Vertex[i].x = ViewPort_Postion[i].x;
		Vertex[i].y = ViewPort_Postion[i].y;
		Vertex[i].z = ViewPort_Postion[i].z;
	}

	for (int i = 0; i < 4; i++)
	{
		Vertex[i].x = (int)(Vertex[i].x + position.x);
	}
}

/*
Vector3D RectTransform::YRotate(Vector3D other)
{

}

Vector3D RectTransform::ZRotate(Vector3D other)
{

}
*/

void RectTransform::Translate(Vector3D other)
{
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].x += other.x;
		Vertex[i].y += other.y;
	}
	position.x += other.x;
	position.y += other.y;
}

void RectTransform::Scale(Vector3D other)
{
	ViewPort_Convert();

	for (int i = 0; i < 4; i++)
	{
		Vertex[i].x = (int)(Vertex[i].x * other.x);
		Vertex[i].y = (int)(Vertex[i].y * other.y);
		Vertex[i].z = (int)(Vertex[i].z * other.z);
	}

	Screen_Convert();
}

void RectTransform::DrawRect(HDC hdc)
{
	PlotLine(hdc, Vertex[0], Vertex[1]);
	PlotLine(hdc, Vertex[0], Vertex[2]);
	PlotLine(hdc, Vertex[1], Vertex[3]);
	PlotLine(hdc, Vertex[2], Vertex[3]);
}

void RectTransform::ViewPort_Convert()
{
	Vector3D ViewPort_Postion[4];

	for (int i = 0; i < 4; i++)
	{
		ViewPort_Postion[i] = Vertex[i];

		ViewPort_Postion[i].x = (int)(position.x - ViewPort_Postion[i].x);
		ViewPort_Postion[i].y = (int)(position.y - ViewPort_Postion[i].y);
		ViewPort_Postion[i].y *= -1;

		Vertex[i] = ViewPort_Postion[i];
	}
}

void RectTransform::Screen_Convert()
{
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].x = (int)(Vertex[i].x + position.x);
		Vertex[i].y *= -1;
		Vertex[i].y = (int)(Vertex[i].y + position.y);
	}
}