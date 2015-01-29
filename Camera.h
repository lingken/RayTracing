#ifndef CAMERA_H_
#define CAMERA_H_

#include"Defination.h"

class Camera{
public:
	Vertex view_position;
	Vector view_direction;
	Vector up_direction;

	double dist;
	double pixel_width;
	double pixel_height;
	double *pixels;
	
	Camera(){
		view_position = Vertex(0, 0, 0);
		view_direction = Vector(0, 0, 1).normalize();
		up_direction = Vector(1, 0, 0).normalize();

		dist = 1000;
		pixel_width = 1.0;
		pixel_height = 1.0;

		pixels = new double [SCREEN_WIDTH * SCREEN_HEIGHT * 3];
	}
	void set_view_position(Vertex v_pos){view_position = v_pos;}
	void set_view_direction(Vector v_dir){view_direction = v_dir.normalize();}
	Vertex real_pixel_pos(int x, int y);
	Vector get_out_direction(Vertex start, int x, int y);
};

#endif