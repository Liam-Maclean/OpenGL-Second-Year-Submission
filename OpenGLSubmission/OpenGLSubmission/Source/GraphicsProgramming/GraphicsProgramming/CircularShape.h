#pragma once
#include "PrimativeShape.h"

//circular shape inherits from primativeshape
class CircularShape :
	public PrimativeShape
{
public:
	//constructor
	CircularShape();

	//inherited constructor
	CircularShape(Vector3 pos)
		:PrimativeShape(pos)
	{
	}

	//deconstructor
	~CircularShape();


	//variables
	vector <float> m_verts;
	vector <float> m_normals;
	vector <float> m_uvs;
	float m_x, m_x2, m_x3, m_x4;
	float m_y, m_y2, m_y3, m_y4;
	float m_z, m_z2, m_z3, m_z4;
	float m_u, m_v;
	float m_u2, m_v2;
	float m_u3, m_v3;
	float m_u4, m_v4;
};

