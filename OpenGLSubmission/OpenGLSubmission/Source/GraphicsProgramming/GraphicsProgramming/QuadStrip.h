#pragma once
#include "PrimativeShape.h"
#include <vector>
#include "Vector3.h"
using namespace std;
class QuadStrip :
	public PrimativeShape
{
public:
	QuadStrip();

	QuadStrip(Vector3 pos)
		:PrimativeShape(pos)
	{

	}

	~QuadStrip();
	void make_plane(int rows, int columns, float *vertices, int *indices);
	void Render();

	void getVertices();
	void getIndices();
	void Setup(int width, int height);
	int NumIndices();

	int m_width;
	int m_height;
};

