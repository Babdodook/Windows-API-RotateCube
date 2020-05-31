#include"RectTransform.h"
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

	matTRS.Init();
	matTRS.TransformWorldPosition = position;
}

void RectTransform::SetFormValue(Vector3D translate, Vector3D Angle, Vector3D scale)
{
	Vector3D ViewPort_position[4];

	for (int i = 0; i < 4; i++)
	{
		ViewPort_position[i] = Vertex[i];

		ViewPort_position[i].x = position.x - ViewPort_position[i].x;
		ViewPort_position[i].y = (position.y - ViewPort_position[i].y);
		ViewPort_position[i].y *= -1;

		Vertex[i] = matTRS.Matrix4X4TRS(translate, Angle, scale) * ViewPort_position[i];
	}

	for (int i = 0; i < 4; i++)
	{
		Vertex[i].x = (position.x + Vertex[i].x);
		Vertex[i].y *= -1;
		Vertex[i].y = (position.y + Vertex[i].y);
	}
}

void RectTransform::DrawRect(HDC hdc)
{
	PlotLine(hdc, Vertex[0], Vertex[1]);
	PlotLine(hdc, Vertex[0], Vertex[2]);
	PlotLine(hdc, Vertex[1], Vertex[3]);
	PlotLine(hdc, Vertex[2], Vertex[3]);
}