#include "Disc.h"

/*	uses cos and sin to work out the vertex's
	for two points around the radius, then increments
	them till a full disc is created
	
	multiplications are worked out by starting at the center point (0,0)
	and adding the radius * interval 
	
	*/



//constructor (default)
Disc::Disc()
{
}

//deconstructor
Disc::~Disc()
{
}

//creates disc geometry
void Disc::GenDisc(int segments, float radius)
{
	//pushback center normal
	m_normals.push_back(0.0f);
	m_normals.push_back(0.0f);
	m_normals.push_back(1.0f);

	//pushback center point
	m_verts.push_back(0.0f + m_pos.x);
	m_verts.push_back(0.0f + m_pos.y);
	m_verts.push_back(0.0f + m_pos.z);

	//for each segment passed in
	for (int i = 0; i < segments; i++)
	{
		//theta intervals
		float theta = (2.0f * 3.1415926f / float(segments))* float(i);
		float thetaInterval = (2.0f * 3.1415926f / float(segments))* float(i + 1);


		//first point is segments * i
		m_x = (radius * cosf(theta)) + m_pos.x;
		m_y = (radius * sinf(theta)) + m_pos.y;
		m_z = 0 + m_pos.z;

		//second point is segments * (i+1) 
		m_x2 = radius * cosf(thetaInterval) + m_pos.x;
		m_y2 = radius * sinf(thetaInterval) + m_pos.y;
		m_z2 = 0 + m_pos.z;


		//normals for our two vertex
		m_normals.push_back(0.0f);
		m_normals.push_back(0.0f);
		m_normals.push_back(1.0f);
		m_normals.push_back(0.0f);
		m_normals.push_back(0.0f);
		m_normals.push_back(1.0f);

		//pushback the two vertex points
		m_verts.push_back(m_x);
		m_verts.push_back(m_y);
		m_verts.push_back(m_z);
		m_verts.push_back(m_x2);
		m_verts.push_back(m_y2);
		m_verts.push_back(m_z2);
	}
}

//draws disc verts and normals
void Disc::RenderDisc()
{
	//enable client states
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//draw disc using relevant vertex data
	glVertexPointer(3, GL_FLOAT, 0, m_verts.data());
	glNormalPointer(GL_FLOAT, 0, m_normals.data());
	glDrawArrays(GL_TRIANGLE_FAN, 0, m_verts.size() / 3);

	//disable client states
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}