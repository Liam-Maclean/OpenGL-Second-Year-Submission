#pragma once
#include "CircularShape.h"
class Sphere :
	public CircularShape
{
public:
	Sphere();
	Sphere(Vector3 pos)
		:CircularShape(pos)
	{
	}
	~Sphere();

	void RenderSphere();
	void GenSphere(float segments, float radius);

};

