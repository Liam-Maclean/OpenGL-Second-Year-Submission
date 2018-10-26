#pragma once
#include "PrimativeShape.h"
class Plane :
	public PrimativeShape
{
public:
	Plane();

	Plane(Vector3 pos)
		:PrimativeShape(pos)
	{

	}

	~Plane();


	void DrawPlane();
};

