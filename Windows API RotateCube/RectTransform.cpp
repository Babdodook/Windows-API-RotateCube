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

void RectTransform::SetFormValue(Vector3D translate, Vector3D scale, Vector3D Angle)
{
	for (int i = 0; i < 4; i++)
		Vertex[i] = matTRS.Matrix4X4TRS(translate, scale, Angle) * Vertex[i];
}

void RectTransform::DrawRect(HDC hdc)
{
	PlotLine(hdc, Vertex[0], Vertex[1]);
	PlotLine(hdc, Vertex[0], Vertex[2]);
	PlotLine(hdc, Vertex[1], Vertex[3]);
	PlotLine(hdc, Vertex[2], Vertex[3]);
}