#pragma once
#include"Basics.h"

void PlotLine(HDC hdc, Vector3D Start, Vector3D Destination)
{
	float dx = abs(Destination.x - Start.x);
	float sx = Start.x < Destination.x ? 1 : -1;
	float dy = -abs(Destination.y - Start.y);
	float sy = Start.y < Destination.y ? 1 : -1;
	float err = dx + dy;

	int MaxIndex = Start.x;

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

void DrawLine(HDC hdc, Vector3D Start, Vector3D End)
{
	float x = Start.x;
	float y = Start.y;
	float m = 0;
	float b = 0;
	float MaxIndex = 0;
	
	bool xAxis = false;
	bool yAxis = false;

	if (Start.x == End.x)
	{
		xAxis = true;
		MaxIndex = (Start.y - End.y);
		x = Start.x;
	}
	else if (Start.y == End.y)
	{
		yAxis = true;
		MaxIndex = (End.x - Start.x);
		y = Start.y;
	}
	else
	{
		MaxIndex = (End.x - Start.x);
		m = (End.y - Start.y) / (End.x - Start.x);
		b = Start.y + m * (-Start.x);
	}

	float index = 0;
	while (MaxIndex > index)
	{
		SetPixel(hdc, x, y, RGB(0, 0, 255));

		//if (x == End.x && y == End.y)
			//break;

		if (xAxis)
		{
			y += 1;
		}
		else if (yAxis)
		{
			x += 1;
		}
		else
		{
			y = m * x + b;
			x += 1;
		}

		index += 1;
	}
}