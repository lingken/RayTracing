#include "Object.h"
#include "stdafx.h"

double Sphere::get_intersection_dist(Vertex start, Vertex view_direction){
	Vector in_direction = (center-start).normalize();

	//double t_sc = (center - start).module();
	//if (t_sc - radius < EPS) return -1;
	//double t_sh = (center - start) * view_direction;
	//if (t_sh < EPS) return -1;
	//double t_ah2 = radius * radius - (t_sc * t_sc - t_sh * t_sh);
	//if (t_ah2 < EPS) return -1;
	//return t_sh - sqrt(t_ah2);

	double loc,tca,thc;
	loc = (center - start)*(center - start);
	if (loc - radius * radius < -EPS)return -1;
	tca = (center - start)*view_direction;
	if (tca < -EPS) return -1;
	thc = radius*radius - loc + tca*tca;
	if (thc < EPS) return -1;
	if (abs(tca - sqrt(thc)) < EPS)
		return tca + sqrt(thc);
	return tca - sqrt(thc);
}

double Triangle::get_intersection_dist(Vertex start, Vertex view_direction){
	double D = (v1 * normal) * (-1);
	double t = (D + normal * start) / (normal * view_direction) * (-1.0);
	if (t < EPS) return -1;

	Vector E1 = v1 - v2;
	Vector E2 = v1 - v3;
	Vector S = v1 - start;
	Vector tmp = Vector(Det(S, E1, E2), Det(view_direction, S, E2), Det(view_direction, E1, S)) / Det(view_direction, E1, E2);
	if (tmp.x > EPS && tmp.y > EPS && tmp.y <= 1 && tmp.z > EPS && tmp.z <= 1 && tmp.y + tmp.z <= 1)
		return t;
	return -1;

}

double Plane::get_intersection_dist(Vertex start, Vertex view_direction){
	double D = (v * normal) * (-1);
	double t = (D + normal * start) / (normal * view_direction) * (-1.0);
	if (t < EPS) return -1;
	return t;
}