#ifndef LIGHT_H_
#define LIGHT_H_

#include"Defination.h"

class Light
{
public:
	Vertex position;
	Color color;
public:
	Light(Vertex position, Color color);
};

#endif