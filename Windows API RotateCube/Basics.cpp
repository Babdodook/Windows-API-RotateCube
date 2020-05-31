#pragma once
#include"Basics.h"

void PlotLine(HDC hdc, int StartX, int StartY, int EndX, int EndY)//Vector3D Start, Vector3D Destination)
{
	int dx = abs(EndX - StartX);
	int sx = StartX < EndX ? 1 : -1;
	int dy = -abs(EndY - StartY);
	int sy = StartY < EndY ? 1 : -1;
	int err = dx + dy;

	

	while (true)
	{
		SetPixel(hdc, StartX, StartY, RGB(0, 0, 255));
		
		if (StartX == EndX && StartY == EndY)
			break;

		int e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			StartX += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			StartY += sy;
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