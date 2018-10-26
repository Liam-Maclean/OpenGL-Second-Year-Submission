#pragma once
#include "Vector3.h"
#include "CubeGen.h"
#include "Cube.h"
#include <glut.h>
#include <string>
using namespace std;

//enum for lighttype 
enum LightType
{
	directional,
	spotLight,
	pointLight
};


//light class
class Light
{
private:
	GLenum m_GLLIGHT;
	LightType lType;
	Cube gizmo;
	Vector3 m_position;
	GLfloat Light_Diffuse[4];
	GLfloat Light_Position[4];
	GLfloat Light_Ambient[4];
	GLfloat Spot_Direction[4];

	float SpotCutoff;
	float SpotExponent;

public:
	Light();
	Light(GLenum GLLIGHT, GLfloat diffuse[4], GLfloat pos[4], GLfloat Ambient[4]);
	Light(GLenum GLLIGHT, GLfloat diffuse[4], GLfloat pos[4], GLfloat Ambient[4], GLfloat spotDir[4], float sCutoff, float sExponent);
	~Light();

	void Attenuation(float conAtt, float linAtt, float quadAtt);
	void EnableLighting(bool truefalse);
	void SpotLightDirection(GLfloat SLDirection[4]);
	void SetUpLighting();
	void DrawGizmo();
};

