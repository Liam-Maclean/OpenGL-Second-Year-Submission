#pragma once
#include "Vector3.h"
#include <vector>
#include "SOIL.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Material.h"
using namespace std;
class PrimativeShape
{
public:
	PrimativeShape();
	PrimativeShape(Vector3 pos);
	~PrimativeShape();


	GLuint LoadTxr(const char* path);
	void SetRotationX(int degrees);
	void SetRotationY(int degrees);
	void SetRotationZ(int degrees);
	void rotate();
	void SetColor(Vector3 color, float alpha);
	void SetPosition(float x, float y, float z);
	virtual void SetScale(Vector3 scale);
	void SetMaterials(GLfloat ambient[4], GLfloat diffuse[4], GLfloat specular[4], GLfloat emission[4]);
	void ApplyMaterials();
	void setTexture(const char* path);
	bool MaterialLoader(const char* path);
	Vector3 m_scale;

	Vector3 m_color;
	float m_alpha;

	Vector3 m_pos;
	Vector3 m_rot;
	Vector3 m_degrees;

	Material m_material;

	GLuint currTexture;

	vector <float> m_verts;
	vector <int> m_indices;
	vector <float> m_normals;
	vector <float> m_uvs;
};

