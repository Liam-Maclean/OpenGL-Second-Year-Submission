#pragma once
#include "CircularShape.h"
class Disc :
	public CircularShape
{
public:
	Disc();
	Disc(Vector3 pos)
		:CircularShape(pos)
	{
	}
	~Disc();

	void RenderDisc();
	void GenDisc(int segments, float radius);

};

