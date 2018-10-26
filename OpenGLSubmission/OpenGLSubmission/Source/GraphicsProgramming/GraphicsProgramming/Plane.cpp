#include "Plane.h"

/*	simple quad mostly for testing and low poly objects
	(mirror on the floor)
														*/


//constructor
Plane::Plane()
{
}

//deconstructor
Plane::~Plane()
{
}

//draws a plane 
void Plane::DrawPlane()
{
	
	//contain transforms in push
	glPushMatrix();

	
	//move rotate scale and color 
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(m_degrees.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_degrees.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_degrees.z, 0.0f, 0.0f, 1.0f);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);
	

	//enable textures and bind existing stored texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currTexture);
	
	//begin quad draw
	glBegin(GL_QUADS);
	//apply materials
	ApplyMaterials();

	//creates normal, UV coord and vertex 
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-0.5f, 0.0f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(0.5f, 0.0f, 0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(+ 0.5f, 0.0f, -0.5f);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-0.5f,  0.0f, -0.5f);

	//stop drawing
	glEnd();

	//unbind texture, disable texturing
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	
	glPopMatrix();
}