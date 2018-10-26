#include "IcoSphere.h"

/*  Big red book's method of creating an icosphere
	using a predetermined vertex and indices array
	and subdividing triangles to make each shape 
	identical size									*/

#define X .525731112119133606 
#define Z .850650808352039932
//vertex data
static GLfloat vdata[12][3] = {
	{ -X, 0.0, Z }, { X, 0.0, Z }, { -X, 0.0, -Z }, { X, 0.0, -Z },
	{ 0.0, Z, X }, { 0.0, Z, -X }, { 0.0, -Z, X }, { 0.0, -Z, -X },
	{ Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 }
};

//indices data
static GLuint tindices[20][3] = {
	{ 1, 4, 0 }, { 4, 9, 0 }, { 4, 5, 9 }, { 8, 5, 4 }, { 1, 8, 4 },
	{ 1, 10, 8 }, { 10, 3, 8 }, { 8, 3, 5 }, { 3, 2, 5 }, { 3, 7, 2 },
	{ 3, 10, 7 }, { 10, 6, 7 }, { 6, 11, 7 }, { 6, 0, 11 }, { 6, 1, 0 },
	{ 10, 1, 6 }, { 11, 0, 9 }, { 2, 11, 9 }, { 5, 2, 9 }, { 11, 2, 7 },
};

//constructor
IcoSphere::IcoSphere()
{
}

//deconstructor
IcoSphere::~IcoSphere()
{
}


//draw a triangle with 3 vertex given
void drawtriangle(float *v1, float *v2, float *v3)
{
	glBegin(GL_TRIANGLES);
	glNormal3fv(v1);
	glVertex3fv(v1);
	glNormal3fv(v2);
	glVertex3fv(v2);
	glNormal3fv(v3);
	glVertex3fv(v3);
	glEnd();
}

//draws icohederon
void IcoSphere::DrawIsohederon()
{
	
	//contain transforms with push
	glPushMatrix();

	//color
	glColor3f(m_color.x, m_color.y, m_color.z);
	//move
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	//scale
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	//rotate
	glRotatef(m_degrees.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_degrees.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_degrees.z, 0.0f, 0.0f, 1.0f);


	//begin draw
	glBegin(GL_TRIANGLES);
	ApplyMaterials();
	//for each vertex we have that currently exists in the array
	for (int i = 0; i < 20; i++) {
		//subdivide the indices
		subdivide(&vdata[tindices[i][0]][0],
			&vdata[tindices[i][1]][0],
			&vdata[tindices[i][2]][0],
			2);
	}
	//end draw 
	glEnd();
	glPopMatrix();
}

/* normalize a vector of non-zero length */
void normalize(GLfloat v[3])
{
	GLfloat d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	/* omit explict check for division by zero */

	v[0] /= d; v[1] /= d; v[2] /= d;
}

//subdivide function
void IcoSphere::subdivide(float *v1, float *v2, float *v3, long depth)
{
	//local variables
	GLfloat v12[3], v23[3], v31[3];
	GLint i;

	//if the subdivision is 0
	if (depth == 0) {
		//draw what triangles we already have stored (no need for subdivision)
		drawtriangle(v1, v2, v3);
		return;
	}
	//for each vertices of the triangle
	for (i = 0; i < 3; i++) {
		//make subdivision
		v12[i] = v1[i] + v2[i];
		v23[i] = v2[i] + v3[i];
		v31[i] = v3[i] + v1[i];
	}
	//normalise the values
	normalize(v12);
	normalize(v23);
	normalize(v31);

	//loop around again till depth is 0
	subdivide(v1, v12, v31, depth - 1);
	subdivide(v2, v23, v12, depth - 1);
	subdivide(v3, v31, v23, depth - 1);
	subdivide(v12, v23, v31, depth - 1);
}

