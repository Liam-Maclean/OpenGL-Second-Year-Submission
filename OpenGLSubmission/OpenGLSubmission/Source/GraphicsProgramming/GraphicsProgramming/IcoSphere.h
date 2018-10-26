#pragma once
#include "CircularShape.h"
class IcoSphere :
	public CircularShape
{
public:
	IcoSphere();
	IcoSphere(Vector3 pos)
		:CircularShape(pos)
	{}
	~IcoSphere();


	void GenIsohederon();
	void subdivide(float *v1, float *v2, float *v3, long depth);
	void DrawIsohederon();
};

