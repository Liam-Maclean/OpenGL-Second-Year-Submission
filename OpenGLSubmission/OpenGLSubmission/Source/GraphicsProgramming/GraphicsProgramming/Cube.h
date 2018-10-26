#pragma once
#include "PrimativeShape.h"
class Cube :
	public PrimativeShape
{
public:

	Cube();
	Cube(Vector3 pos)
		:PrimativeShape(pos)
	{

	}
	~Cube();



	void DrawCube();
};

