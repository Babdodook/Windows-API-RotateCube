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
	Vertex[0].z = 1;

	Vertex[1].x = position.x + _Width / 2;
	Vertex[1].y = position.y - _Height / 2;
	Vertex[1].z = 1;

	Vertex[2].x = position.x - _Width / 2;
	Vertex[2].y = position.y + _Height / 2;
	Vertex[2].z = 1;

	Vertex[3].x = position.x + _Width / 2;
	Vertex[3].y = position.y + _Height / 2;
	Vertex[3].z = 1;

	matTRS.Init();
	matTRS.TransformWorldPosition = position;
}

void RectTransform::SetFormValue(Vector3D translate, Vector3D Angle, Vector3D scale)
{
	//Matrix4X4 matT;
	//matT.Init();
	for (int i = 0; i < 4; i++)
	{
		Vertex[i].Viewport_Convert(position);

		//Vertex[i].x += translate.x;
		//Vertex[i].y += translate.y;
		//Vertex[i].z += translate.z;
		//matTRS=matTRS.Matrix4X4Translation(-50, 0, 0);
		//matT = matTRS.Matrix4X4Translation(translate.x, translate.y, translate.z);
		//Vertex[i] = matTRS * Vertex[i];
		//Vertex[i] = matTRS.Matrix4X4Translation(translate.x, translate.y, translate.z) * Vertex[i];

		Vertex[i] = matTRS.Matrix4X4TRS(translate, Angle, scale) * Vertex[i];
		Vertex[i].Screen_Convert(position);
	}
}

void RectTransform::DrawRect(HDC hdc)
{
	PlotLine(hdc, Vertex[0].x, Vertex[0].y, Vertex[1].x, Vertex[1].y);
	PlotLine(hdc, Vertex[0].x, Vertex[0].y, Vertex[2].x, Vertex[2].y);
	PlotLine(hdc, Vertex[1].x, Vertex[1].y, Vertex[3].x, Vertex[3].y);
	PlotLine(hdc, Vertex[2].x, Vertex[2].y, Vertex[3].x, Vertex[3].y);
}