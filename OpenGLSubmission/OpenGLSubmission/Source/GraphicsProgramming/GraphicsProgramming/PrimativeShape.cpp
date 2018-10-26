#include "PrimativeShape.h"

//constructor (default)
PrimativeShape::PrimativeShape()
{
	m_pos = Vector3(0, 0, 0);
}

//constructor (position)
PrimativeShape::PrimativeShape(Vector3 pos)
{
	m_pos = pos;
}

//deconstructor
PrimativeShape::~PrimativeShape()
{
}

//loads a texture
GLuint PrimativeShape::LoadTxr(const char* path)
{
	GLuint txr = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	return txr;
}

//set texture to one passed into path
void PrimativeShape::setTexture(const char* path)
{
	currTexture = LoadTxr(path);
}

//increments rotation degrees on each axis
void PrimativeShape::rotate()
{
		m_degrees.x++;
		m_degrees.y++;
		m_degrees.z++;
}

//sets the scale factor
void PrimativeShape::SetScale(Vector3 scale)
{
	m_scale = scale;
}

//loads materials (DOESN'T WORK)
bool PrimativeShape::MaterialLoader(const char* material)
{
	FILE *file = fopen("Materials.txt", "r");
	while (file == NULL){
		MessageBox(NULL, "File failed to load", "Failure", MB_OK);
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1){

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.
		else
		{
			if (strcmp(lineHeader, "A") == 0){
				fscanf(file, "%f %f %f\n", &m_material.mat_ambient[0], &m_material.mat_ambient[1], &m_material.mat_ambient[2]);
				m_material.mat_ambient[3] = 1.0f;
			}
			if (strcmp(lineHeader, "D") == 0){
				fscanf(file, "%f %f %f\n", &m_material.mat_diffuse[0], &m_material.mat_diffuse[1], &m_material.mat_diffuse[2]);
				m_material.mat_diffuse[3] = 1.0f;
			}
			if (strcmp(lineHeader, "SP") == 0){
				fscanf(file, "%f %f %f\n", &m_material.mat_specular[0], &m_material.mat_specular[1], &m_material.mat_specular[2]);
				m_material.mat_specular[3] = 1.0f;
			}
			if (strcmp(lineHeader, "SH") == 0){
				fscanf(file, "%f \n", &m_material.m_shininess);
			}
		}
	}

}


//sets materials of the object
void PrimativeShape::SetMaterials(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat emission[4])
{
	for (int i = 0; i < 4; i++)
	{
		m_material.mat_ambient[i] = ambient[i];
		m_material.mat_diffuse[i] = diffuse[i];
		m_material.mat_specular[i] = specular[i];
		m_material.mat_emission[i] = emission[i];
	}
}

//applies materials to the object and faces
void PrimativeShape::ApplyMaterials()
{
	
	glMaterialfv(GL_FRONT, GL_AMBIENT, m_material.mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, m_material.mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, m_material.mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, m_material.m_shininess);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}

//sets the color passed into the method
void PrimativeShape::SetColor(Vector3 color, float alpha)
{
	m_color = color;
	m_alpha = alpha;
}

//set the x rotation degrees
void PrimativeShape::SetRotationX(int degrees)
{
	m_degrees.x = degrees;
}

//set the y rotation degrees
void PrimativeShape::SetRotationY(int degrees)
{
	m_degrees.y = degrees;
}

//set the y rotation degrees
void PrimativeShape::SetRotationZ(int degrees)
{
	m_degrees.z = degrees;
}

//sets the position of the object manualy
void PrimativeShape::SetPosition(float x, float y, float z)
{
	m_pos = Vector3(x, y, z);
}

