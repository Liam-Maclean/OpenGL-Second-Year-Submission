#include "Cube.h"


Cube::Cube()
{
}


Cube::~Cube()
{
}

//draws a cube 
void Cube::DrawCube()
{

	glPushMatrix();
	glRotatef(m_degrees.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_degrees.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_degrees.z, 0.0f, 0.0f, 1.0f);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	
	//MaterialFunc();
	glBegin(GL_QUADS);

	ApplyMaterials();

	// front face
	glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f,-0.5f, 0.5f);


	// back face
	glColor3f(m_color.x, m_color.y, m_color.z);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f,  0.5f, -0.5f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(0.5f,0.5f, -0.5f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f( 0.5f, -0.5f,-0.5f);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f,-0.5f);


	//Left face
	glColor3f(m_color.x, m_color.y, m_color.z);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(+ -0.5f,  0.5f, 0.5f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f( -0.5f, 0.5f, -0.5f);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);


	//Top Face
	glColor3f(m_color.x, m_color.y, m_color.z);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f( 0.5f, 0.5f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f( 0.5f,  0.5f, -0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f( -0.5f,  0.5f, -0.5f);


	// right face
	glColor3f(m_color.x, m_color.y, m_color.z);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f,  0.5f, 0.5f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f,  0.5f, -0.5f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, -0.5f);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);



	// bottom face
	glColor3f(m_color.x, m_color.y, m_color.z);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f( 0.5f, -0.5f, -0.5f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f,-0.5f, -0.5f);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);

	glEnd();
	glPopMatrix();
}