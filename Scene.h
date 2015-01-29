#ifndef SCENE_H_
#define SCENE_H_

#include "Defination.h"
#include "Light.h"
#include "Object.h"
#include "Camera.h"
#include "SimpleObject.h"
#include <vector>

class Scene{
public:
	Camera camera;
	SimpleOBJ::CSimpleObject simple_obj;

	int n_obj;
	int n_material;
	Object **object;
	Material **material;
	vector<Light> light;

	Scene(){n_obj = 0; n_material = 0;}
	~Scene(){delete [] object; delete [] material; object = NULL; material = NULL;}
	void init_scene();
	
	void change_view_position(Vertex v_pos){camera.set_view_position(v_pos);}
	void change_view_direction(Vertex v_dir){camera.set_view_direction(v_dir);}

	void set_pixel(int x, int y, double r, double g, double b);
	void set_pixel(int x, int y, Color &color);
	
	bool LoadFromObj(const char* fn);

	void render();
	Color trace(Vertex start, Vector view_direction, int bounce, bool outside);
	//Color shade(Vertex &intersection, Vector &out, Vector &normal, int bounce);
	Color shade(Vertex &intersection, Vector &view, Object *obj, int bounce, bool outside);
	Object *get_nearest_obj(Vertex start, Vector out_direction, double &t);
};

#endif