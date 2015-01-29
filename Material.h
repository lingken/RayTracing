#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "Defination.h"
class Material{
public:
	double k_diffuse;
	double k_specular;
	double k_reflection;
	double k_refraction;
	double n_refraction;
	Color m_color;

	//virtual Color get_color(Vertex pos){return m_color;}
	virtual Color get_color(Vertex pos) = 0;
	virtual double get_reflection(Vertex pos){return k_reflection;}

	void set_paras(double k_d, double k_s, double k_rfl, double k_rfr, double n){k_diffuse = k_d; k_specular = k_s; k_reflection = k_rfl; k_refraction = k_rfr; n_refraction = n;}
	void set_color(Color color){m_color = color;}
};

class pattern_grid: public Material{
public:
	Color get_color(Vertex pos);
	double get_reflection(Vertex pos);
};

#endif