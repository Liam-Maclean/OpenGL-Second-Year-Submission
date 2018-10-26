#pragma once
#include <glut.h>
#include <gl/GL.h>
#include <gl/GLU.h>

class Material
{
public:
	Material();
	~Material();

	GLfloat mat_ambient[4];
	GLfloat mat_ambient_colour[4];
	GLfloat mat_diffuse[4];
	GLfloat m_shininess;
	GLfloat mat_specular[4];
	GLfloat mat_emission[4];

};

