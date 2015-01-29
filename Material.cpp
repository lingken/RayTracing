#include "stdafx.h"
#include "Material.h"

Color pattern_grid::get_color(Vertex pos){
	int width = 200;
	double y = pos.y, z = pos.z;
	double a = abs(y), b = abs(z);
	int p = a / width;
	int q = b / width;
	if ((y <= 0 && z <= 0) || (y > 0 && z > 0)) p += 1;
	if (p % 2 == q % 2) return Color(1, 1, 1);
	else return Color(0, 0, 0);
}

double pattern_grid::get_reflection(Vertex pos){
	int width = 200;
	double y = pos.y, z = pos.z;
	double a = abs(y), b = abs(z);
	int p = a / width;
	int q = b / width;
	if ((y <= 0 && z <= 0) || (y > 0 && z > 0)) p += 1;
	if (p % 2 == q % 2) return 0;
	else return 1;
}