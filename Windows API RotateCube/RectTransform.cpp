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
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].Viewport_Convert(position);

		Vertex[i] = matTRS.Matrix4X4RotationZ(Angle.z) * Vertex[i];

		//Vertex[i] = matTRS.Matrix4X4TRS(translate, Angle, scale) * Vertex[i];
		Vertex[i].Screen_Convert(position);
	}
}

void RectTransform::DrawRect(HDC hdc)
{
	//SetPixel(hdc, Vertex[0].x, Vertex[0].y, RGB(0, 0, 255));
	//SetPixel(hdc, Vertex[1].x, Vertex[1].y, RGB(0, 0, 255));
	//SetPixel(hdc, Vertex[2].x, Vertex[2].y, RGB(0, 0, 255));
	//SetPixel(hdc, Vertex[3].x, Vertex[4].y, RGB(0, 0, 255));
	//PlotLine(hdc, Vertex[0], Vertex[1]);
	DrawLine(hdc, Vertex[0], Vertex[1]);
	//PlotLine(hdc, Vertex[0], Vertex[2]);
	//PlotLine(hdc, Vertex[1], Vertex[3]);
	//PlotLine(hdc, Vertex[2], Vertex[3]);
}