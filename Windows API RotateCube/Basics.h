#pragma once
#define _USE_MATH_DEFINES

#include<windows.h>
#include<list>
#include<math.h>
#include"Vector3D.h"
#include"Matrix4X4.h"

#define PI 3.14
#define DEG2RAD PI/180

void PlotLine(HDC hdc, int StartX, int StartY, int EndX, int EndY);
void DrawLine(HDC hdc, Vector3D Start, Vector3D End);