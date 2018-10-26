#include "QuadStrip.h"
#include "glut.h"

/*	Slightly different from plane.
	creates a multi triangle face
	using triangle strips using				1 -2 -3 -4 -5 -6 -7 -8
	appropriate	indexing					| /| /| /| /| /| /| /|
											9-10-11-12-13-14-15-16
											| /| /| /| /| /| /| /|
											17-18-19-20-21-22-23-24
	
	takes two index's at a time when pushing,
	using (y * width) + x for the first one,
	and ((y*m_width) + x + width) for the second
	

	id1 = 1, 
	id2 = 9, 
	id3 = 2			
	id4 = 10		etc.
	*/									


//constructor
QuadStrip::QuadStrip()
{
}

//deconstructor
QuadStrip::~QuadStrip()
{
}


//creates the vertices for multiface plane
void QuadStrip::getVertices(){
	// Set up vertices
	int i = 0;

	//for height
	for (int y = 0; y < m_height; y++)
	{
		//for width
		for (int x = 0; x < m_width; x++)
		{
			//create verts and normals
			m_verts.push_back((float)x);
			m_verts.push_back(0.0f);
			m_verts.push_back((float)y);
			m_normals.push_back(0.0f);
			m_normals.push_back(1.0f);
			m_normals.push_back(0.0f);
		}
	}
}

//returns number of indices
int QuadStrip::NumIndices()
{
	return (m_width*m_height);
}

//creates index's to work strip with
void QuadStrip::getIndices()
{
	//for the height - 1
	for (int y = 0; y < m_height - 1; y++)
	{
		//for the width 
		for (int x = 0; x < m_width; x++)
		{
			//push indices
			m_indices.push_back((y * m_width) + x);
			m_indices.push_back((y * m_width) + m_width + x);
		}
		if (y < m_height - 1)
		{
			m_indices.push_back((y + 1) * m_width + (m_width - 1));
			m_indices.push_back((y + 1) * m_width);
		}
	}
}

//sets up quad with width height and creates data
void QuadStrip::Setup(int width, int height)
{
	m_width = width;
	m_height = height;
	getVertices();
	getIndices();
}

//renders strip quad
void QuadStrip::Render()
{

	//contains transforms in push
	glPushMatrix();

	//color, move, rotate and scale
	glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(m_degrees.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_degrees.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_degrees.z, 0.0f, 0.0f, 1.0f);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	
	//enable client states for vertex array and normal information
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//draws strip with relevant indexing
	glNormalPointer(GL_FLOAT, 0, m_normals.data());
	glVertexPointer(3, GL_FLOAT, 0, m_verts.data());
	glDrawElements(GL_TRIANGLE_STRIP, m_indices.size(), GL_UNSIGNED_INT, m_indices.data());
	
	//disable client states
	glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
}

 