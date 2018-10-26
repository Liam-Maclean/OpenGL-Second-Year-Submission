#include "Sphere.h"

//constructor (default)
Sphere::Sphere()
{
}

//deconstructor
Sphere::~Sphere()
{
}

//gens the sphere
void Sphere::GenSphere(float segments, float radius)
{
	//theta and delta using hacked PI values
	float Theta = (2.0f * 3.1415926f) / (float)segments;
	float Delta = 3.1415926f / (float)segments;
	float const u = 1. / (float)(segments-1);
	


	//loop for lattitude
	for (int y = 0; y < segments; y++)
	{
		//loop for longitude
		for (int x = 0; x < segments; x++)
		{

			//for vertices 
			float Theta3 = Theta * float(y + 1.0f);
			float Delta3 = Delta * float(x + 1.0f);
			float Theta2 = Theta * float(y);
			float Delta2 = Delta * float(x);

			//verts allocation
			m_x = (radius * cosf(Theta2)) * sinf(Delta2);
			m_y = (radius * cosf(Delta2));
			m_z = (radius * sinf(Theta2)) * sinf(Delta2);

			m_x2 = (radius * cosf(Theta3)) * sinf(Delta2);
			m_y2 = (radius * cosf(Delta2));
			m_z2 = (radius * sinf(Theta3)) * sinf(Delta2);

			m_x3 = (radius * cosf(Theta3)) * sinf(Delta3);
			m_y3 = (radius * cosf(Delta3));
			m_z3 = (radius * sinf(Theta3)) * sinf(Delta3);

			m_x4 = (radius * cosf(Theta2)) * sinf(Delta3);
			m_y4 = (radius * cosf(Delta3));
			m_z4 = (radius * sinf(Theta2)) * sinf(Delta3);

			//UVs for vert 1
			m_u = x*u;
			m_v = y*u;

			//Uvs for vert 2
			m_u2 = x*u;
			m_v2 = (y+1)*u;
			
			//Uvs for vert 3
			m_u3 = (x+1)*u;
			m_v3 = (y+1)*u;

			//UVs for vert 4
			m_u4 = (x+1)*u;
			m_v4 = y*u;
			
			//pushback UVs for an entire quad
			m_uvs.push_back(m_u);
			m_uvs.push_back(m_v);
			m_uvs.push_back(m_u2);
			m_uvs.push_back(m_v2);
			m_uvs.push_back(m_u3);
			m_uvs.push_back(m_v3);
			m_uvs.push_back(m_u4);
			m_uvs.push_back(m_v4);
			//push back vertices 1
			m_normals.push_back(m_x / radius);
			m_verts.push_back(m_x);
			m_normals.push_back(m_y / radius);
			m_verts.push_back(m_y);
			m_normals.push_back(m_z / radius);
			m_verts.push_back(m_z);

			//push back vertices 2
			m_normals.push_back(m_x2 / radius);
			m_verts.push_back(m_x2);
			m_normals.push_back(m_y2 / radius);
			m_verts.push_back(m_y2);
			m_normals.push_back(m_z2 / radius);
			m_verts.push_back(m_z2);

			//push back vertices 3
			m_normals.push_back(m_x3 / radius);
			m_verts.push_back(m_x3);
			m_normals.push_back(m_y3 / radius);
			m_verts.push_back(m_y3);
			m_normals.push_back(m_z3 / radius);
			m_verts.push_back(m_z3);

			//push back vertices 4
			m_normals.push_back(m_x4 / radius);
			m_verts.push_back(m_x4);
			m_normals.push_back(m_y4 / radius);
			m_verts.push_back(m_y4);
			m_normals.push_back(m_z4 / radius);
			m_verts.push_back(m_z4);

			
		}
	}
}

//gens the object using an array of verts
void Sphere::RenderSphere()
{
	//contain all the transforms
	glPushMatrix();
	//color
	glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);
	//move
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	//scale
	glScalef(m_scale.x, m_scale.y, m_scale.z);

	//set the texture filtering to linear
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//enable textures and bind the current texture stored
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, currTexture);

	//apply materials
	ApplyMaterials();
	
	//enable client states for vertex array drawing
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	//store the vertices, normal and UV data
	glTexCoordPointer(2, GL_FLOAT, 0, m_uvs.data());
	glVertexPointer(3, GL_FLOAT, 0, m_verts.data());
	glNormalPointer(GL_FLOAT, 0, m_normals.data());

	//draw the arrays
	glDrawArrays(GL_QUADS, 0, m_verts.size() / 3);

	//disable client states
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//unbind texture and disable textures
	glBindTexture(GL_TEXTURE_2D, NULL);
	glDisable(GL_TEXTURE_2D);
	

	glPopMatrix();
}
