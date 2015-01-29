#include "Scene.h"
#include "stdafx.h"
#include <Windows.h>
void Scene::init_scene(){
	//Light
	light.push_back(Light(Vertex(2000, 400, 0), Color(1, 1, 1)));
	//light.push_back(Light(Vertex(6000, 600, 500), Color(0.5, 0.5, 0.5)));

	//material
	material = new Material* [100];
	pattern_grid *grid = new pattern_grid;
	material[n_material ++] = grid;

	grid->set_color(Color(0, 1, 0));
	grid->set_paras(0.6, 0.7, 0.9, 0, 0);

	//object
	object = new Object *[5000];

	object[n_obj] = new Plane(Vertex(-300, 0, 0), Vector(1, 0, 0));//floor
	object[n_obj]->set_paras(1, 0, 0, 0, 1);
	object[n_obj]->set_color(Color(0.5, 0.5, 0.5));
	object[n_obj]->set_material(grid);
	n_obj ++;

	object[n_obj] = new Plane(Vertex(0, 0, 2500), Vector(0, 0, -1));//back wall
	object[n_obj]->set_paras(0.8, 0, 0, 0, 1);
	object[n_obj]->set_color(Color(0.2, 0.25, 0.2));
	n_obj ++;

	object[n_obj] = new Plane(Vertex(0, 4000, 0), Vector(0, -1, 0));//right wall
	object[n_obj]->set_paras(0.8, 0, 0, 0, 1);
	object[n_obj]->set_color(Color(0.2, 0.25, 0.2));
	n_obj ++;

	object[n_obj] = new Plane(Vertex(5000, 0, 0), Vector(-1, 0, 0));//cell wall
	object[n_obj]->set_paras(0.8, 0, 0, 0, 1);
	object[n_obj]->set_color(Color(0.2, 0.25, 0.2));
	n_obj ++;

	object[n_obj] = new Plane(Vertex(0, 0, -2000), Vector(0, 0, 1));//cell wall
	object[n_obj]->set_paras(0.8, 0, 0, 0, 1);
	object[n_obj]->set_color(Color(0.2, 0.25, 0.2));
	n_obj ++;

	object[n_obj] = new Plane(Vertex(0, -500, 0), Vector(0, 1, 0));//left wall
	object[n_obj]->set_paras(1, 0, 0.3, 0, 1);
	object[n_obj]->set_color(Color(0.2, 0.25, 0.2));
	n_obj ++;

	object[n_obj] = new Sphere(Vertex(300, -200, 500), 100);//transparency
	object[n_obj]->set_paras(0, 0, 0.1, 1, 1.5);
	object[n_obj]->set_color(Color(0.1, 0.6, 0.1));
	n_obj ++;

	object[n_obj] = new Sphere(Vertex(200, 400, 300), 100);//transparency in front
	object[n_obj]->set_paras(0, 0, 0.1, 1, 1.01);
	object[n_obj]->set_color(Color(0.1, 0.1, 0.1));
	n_obj ++;

	object[n_obj] = new Sphere(Vertex(200, 200, 1500), 200);//red
	object[n_obj]->set_paras(0.4, 0.5, 0.3, 0, 1);
	object[n_obj]->set_color(Color(1, 0.1, 0.1));
	n_obj ++;

	object[n_obj] = new Sphere(Vertex(-300, -500, 2500), 400);//corner
	object[n_obj]->set_paras(0.3, 0, 0.9, 0, 1);
	object[n_obj]->set_color(Color(0.1, 0.1, 0.8));
	n_obj ++;

	LoadFromObj("lk3.obj");
	//add object
}

bool Scene::LoadFromObj(const char* fn){
	if (object == NULL)
		return false;
	if (simple_obj.IsLoaded())
		return false;
	simple_obj.LoadFromObj(fn);

	//for (int i = 0; i < simple_obj.m_nVertices; i ++){
	//	cout << simple_obj.m_pVertexList[i] << endl;
	//}
	//cout << endl;
	//for (int i = 0; i < simple_obj.m_nTriangles; i ++){
	//	for (int j = 0; j < 3; j ++){
	//		cout << simple_obj.m_pTriangleList[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	//double lambda = 5;
	//Vector move = Vector(200, 200, 2000);
	double lambda = 5;
	Vector move = Vector(50, 100, 700);
	for (int i = 0; i < simple_obj.m_nTriangles; i ++){
		Vertex v1 = simple_obj.m_pVertexList[simple_obj.m_pTriangleList[i][0]];
		Vertex v2 = simple_obj.m_pVertexList[simple_obj.m_pTriangleList[i][1]];
		Vertex v3 = simple_obj.m_pVertexList[simple_obj.m_pTriangleList[i][2]];
		v1 = v1 * lambda; v2 = v2 * lambda; v3 = v3 * lambda;
		v1 += move; v2 += move; v3 += move;
		object[n_obj] = new Triangle(v1, v2, v3);
		object[n_obj]->set_color(Color(0.1, 0, 0.8));
		object[n_obj]->set_paras(0, 0, 0, 0.8, 2);
		n_obj ++;
	}

}

void Scene::set_pixel(int x, int y, double r, double g, double b){
	int pos = x * SCREEN_WIDTH * 3 + y * 3;
	camera.pixels[pos + 0] = r;
	camera.pixels[pos + 1] = g;
	camera.pixels[pos + 2] = b;
}

void Scene::set_pixel(int x, int y, Color &color){
	int pos = x * SCREEN_WIDTH * 3 + y * 3;
	camera.pixels[pos + 0] = color.x;
	camera.pixels[pos + 1] = color.y;
	camera.pixels[pos + 2] = color.z;
}

void Scene::render(){
	for (int x = 0; x < SCREEN_HEIGHT; x ++){
		for (int y = 0; y < SCREEN_WIDTH; y ++){
			Vertex pos = camera.real_pixel_pos(x, y);
			Vector out_direction = (pos - camera.view_position).normalize();
			Color color = trace(pos, out_direction, 0, 1);
			set_pixel(x, y, color.x, color.y, color.z);
		}
	}
}

Color Scene::trace(Vertex start, Vector view_direction, int bounce, bool outside){
	if (bounce >= 10)// >= 2 for reflection
		return Color(0, 0, 0);

	double t = INF;
	Object *obj = get_nearest_obj(start, view_direction, t);
	Vertex intersection = start + (view_direction * t);
	Vector view = (view_direction * (-1)).normalize();
	if (obj){
		//printf("got it!\n");
		return shade(intersection, view, obj, bounce, outside);
	}
	return BLACK;
}

Color Scene::shade(Vertex &intersection, Vector &view, Object *obj, int bounce, bool outside){
	//return Color(255, 0, 0);
	
	Color color(0, 0, 0);
	Color obj_color = obj->get_color(intersection);

	Vector normal;
	if (outside) normal = obj->get_normal(intersection);
	else normal = obj->get_normal(intersection) * (-1);
	if (outside){
	for (int i = 0; i < light.size(); i++){
		Vertex l_pos = light[i].position;
		Vector L = (l_pos - intersection).normalize();
		double t = INF;
		Object *tmp = get_nearest_obj(intersection, L, t);
		if (tmp && t < (l_pos - intersection).module()) continue; // in shadow
		// in light
		Vector h = (L + view).normalize();
		Vector l_R = L + (normal * (L * normal) - L) * 2.0;
		
		double diffuse, specular;
		diffuse = max(L * normal, 0.0) * 1.0;
		specular = pow(max(h * normal, 0.0), 300) * 1.0;

		//color = Color(0,1,0);
		color += (light[i].color ^ obj_color) * diffuse * obj->k_diffuse;
		color += light[i].color * specular * obj->k_specular;
	}
	// ambient light
	color += obj_color ^ AMBIENT;

	// reflection
	Vector R = view + (normal * (view * normal) - view) * 2.0;
	if (obj->get_reflection(intersection))
		color += trace(intersection, R, bounce + 1, outside) * obj->get_reflection(intersection);
	
	}

	//refraction

	double cos_1 = view * normal;
	Vector a1 = view - normal * cos_1;
	double sin_1 = sqrt(1 - cos_1 * cos_1);
	double n21 = 0;
	if (outside) n21 = obj->n_refraction;
	else n21 = 1.0 / obj->n_refraction;
	double cos_2 = sqrt(1 - (1.0 / (n21*n21))*(1 - cos_1 * cos_1));
	Vector Refr = (view * (-1.0 / n21) - normal * (cos_2 - (1/n21)*cos_1)).normalize();
	if (obj->k_refraction)
		color += trace(intersection, Refr, bounce + 1, !outside) * obj->k_refraction;

	return color;
}

Object* Scene::get_nearest_obj(Vertex start, Vector out_direction, double &t){
	t = INF;
	Object *obj = NULL;
	for (int i = 0; i < n_obj;i ++){
		double tmp_t = (object[i])->get_intersection_dist(start, out_direction);
		if (tmp_t > -EPS){
			if (tmp_t < t){
				t = tmp_t;
				obj = object[i];
			}
		}
	}
	return obj;
}