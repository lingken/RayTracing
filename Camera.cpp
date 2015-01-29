#include"Camera.h"
#include "stdafx.h"

Vertex Camera::real_pixel_pos(int x, int y){
	view_direction.normalize();
	up_direction.normalize();
	Vector right_direction = Cross(view_direction, up_direction);

	//printf("logic: x:%d y:%d\n", x, y);

	Vertex center = view_position + (view_direction * dist);
	
	//cout << center << endl;
	
	Vertex pos = center;
	pos +=  right_direction * ((y - 0.5 * SCREEN_WIDTH) * pixel_width + 0.5 * pixel_width);
	pos +=  up_direction * ((x - 0.5 * SCREEN_HEIGHT) * pixel_height + 0.5 * pixel_height);
	
	//cout << pos << endl;
	return pos;
}

Vector Camera::get_out_direction(Vertex start, int x, int y){
	return (real_pixel_pos(x, y) - start).normalize();
}