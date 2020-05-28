#pragma once
#include"Basics.h"

void PlotLine(HDC hdc, Vector3D Start, Vector3D Destination)
{
	float dx = abs(Destination.x - Start.x);
	float sx = Start.x < Destination.x ? 1 : -1;
	float dy = -abs(Destination.y - Start.y);
	float sy = Start.y < Destination.y ? 1 : -1;
	float err = dx + dy;

	while (true)
	{
		SetPixel(hdc, Start.x, Start.y, RGB(0, 0, 255));

		if (Start.x == Destination.x && Start.y == Destination.y)
			break;

		float e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			Start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			Start.y += sy;
		}
	}
}