#pragma once
#define _USE_MATH_DEFINES

#include<windows.h>
#include<list>
#include<math.h>
#include"Vector3D.h"

#define PI 3.14
#define DEG2RAD PI/180

void PlotLine(HDC hdc, Vector3D Start, Vector3D Destination);