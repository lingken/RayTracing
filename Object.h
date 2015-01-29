#ifndef OBJECT_H_
#define OBJECT_H_

#include "Defination.h"
#include "Material.h"

class Object{
public:
	enum{
		SPHERE,
		TRIANGLE,
		PLANE
	};

	//Material
	Material *material;

	//double Ka;
	double k_diffuse;
	double k_specular;
	double k_reflection;
	double k_refraction;
	double n_refraction;
	Color m_color;
	
	Object(){k_diffuse = 0; k_specular = 0; k_reflection = 0; k_refraction = 0; n_refraction = 0; m_color = Color(0, 0, 0); material = NULL;}
	void set_paras(double k_d, double k_s, double k_rfl, double k_rfr, double n){k_diffuse = k_d; k_specular = k_s; k_reflection = k_rfl; k_refraction = k_rfr; n_refraction = n;}
	void set_color(Color color){m_color = color;}
	void set_material(Material *material){this->material = material;}

	virtual int get_type() = 0;
	virtual double get_intersection_dist(Vertex start, Vertex view_direction) = 0;
	virtual Vector get_normal(Vertex intersection) = 0;
	Color get_color(Vertex pos){
		if (material) return material->get_color(pos);
		return m_color;
	}
	double get_reflection(Vertex pos){
		if (material) return material->get_reflection(pos);
		return k_reflection;
	}
};

class Sphere: public Object{
public:
	Sphere(Vertex center, double r){this->center = center; this->radius = r;}
	~Sphere();

	int get_type(){return SPHERE;}
	double get_intersection_dist(Vertex start, Vertex view_direction);
	Vector get_normal(Vertex intersection){return (intersection - center).normalize();}
	//Color get_color(Vertex pos){return m_color;}
	
	Vertex center;
	double radius;
};

class Triangle: public Object{
public:
	// counter-clockwise
	Triangle(Vertex v1, Vertex v2, Vertex v3){
		this->v1 = v1; this->v2 = v2; this->v3 = v3;
		Vector t1 = v2 - v1;
		Vector t2 = v3 - v1;
		normal = Cross(t1, t2).normalize();
	}
	~Triangle();

	int get_type(){return TRIANGLE;}
	double get_intersection_dist(Vertex start, Vertex view_direction);
	Vector get_normal(Vertex intersection){return normal;}
	//Color get_color(Vertex pos){return m_color;}

	Vertex v1, v2, v3;
	Vector normal;
};

class Plane: public Object{
public:
	Plane(Vertex v, Vector normal){this->v = v; this->normal = normal;}

	int get_type(){return PLANE;}
	double get_intersection_dist(Vertex start, Vertex view_direction);
	Vector get_normal(Vertex intersection){return normal;}
	//Color get_color(Vertex pos){return m_color;}

	Vertex v;
	Vector normal;
};

#endif