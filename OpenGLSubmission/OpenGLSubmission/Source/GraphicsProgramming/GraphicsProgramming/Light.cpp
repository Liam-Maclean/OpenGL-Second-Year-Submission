#include "Light.h"

//constructor (default)
Light::Light()
{
}

//constructor pointlight (variables)
Light::Light(GLenum GLLIGHT, GLfloat diffuse[4], GLfloat pos[4], GLfloat ambient[4])
{
	//store the light enum
	m_GLLIGHT = GLLIGHT;
	lType = pointLight;

	//loop through array
	for (int i = 0; i < 4; i++)
	{
		//store values
		Light_Position[i] = pos[i];
		Light_Ambient[i] = ambient[i];
		Light_Diffuse[i] = diffuse[i];
	}

	//sets the position of the gizmo
	gizmo.SetPosition(pos[0], pos[1], pos[2]);
}


//constructor for spotlight (variables)
Light::Light(GLenum GLLIGHT, GLfloat diffuse[4], GLfloat pos[4], GLfloat ambient[4], GLfloat spotDir[4], float sCutoff, float sExponent)
{
	//store the light enum
	m_GLLIGHT = GLLIGHT;

	lType = spotLight;

	//loop through array
	for (int i = 0; i < 4; i++)
	{
		//store values
		Light_Position[i] = pos[i];
		Light_Ambient[i] = ambient[i];
		Light_Diffuse[i] = diffuse[i];
		Spot_Direction[i] = spotDir[i];
	}

	SpotCutoff = sCutoff;
	SpotExponent = sExponent;

	//sets the position of the gizmo
	gizmo.SetPosition(pos[0], pos[1], pos[2]);
}


//deconstructor
Light::~Light()
{
}



//set up light attenuation
void Light::Attenuation(float conAtt, float linAtt, float quadAtt)
{
	glLightf(m_GLLIGHT, GL_CONSTANT_ATTENUATION, conAtt);
	glLightf(m_GLLIGHT, GL_LINEAR_ATTENUATION, linAtt);
	glLightf(m_GLLIGHT, GL_QUADRATIC_ATTENUATION, quadAtt);
}


//setup variables
void Light::SetUpLighting()
{
	//set up lighting
	glLightfv(m_GLLIGHT, GL_AMBIENT, Light_Ambient);
	glLightfv(m_GLLIGHT, GL_DIFFUSE, Light_Diffuse);
	glLightfv(m_GLLIGHT, GL_POSITION, Light_Position);
	if (lType == spotLight)
	{
		glLightf(m_GLLIGHT, GL_SPOT_CUTOFF, SpotCutoff);
		glLightfv(m_GLLIGHT, GL_SPOT_DIRECTION, Spot_Direction);
		glLightf(m_GLLIGHT, GL_SPOT_EXPONENT, SpotExponent);

	}
	//glLightf(m_GLLIGHT, GL_CONSTANT_ATTENUATION, 1.0);
	//glLightf(m_GLLIGHT, GL_LINEAR_ATTENUATION, 0.2);
	//glLightf(m_GLLIGHT, GL_QUADRATIC_ATTENUATION, 0.0);
	
	DrawGizmo();
}

//draws a gizmo to locate camera position
void Light::DrawGizmo()
{
	//draw cube
	gizmo.SetColor(Vector3(1.0f, 0.0f, 1.0f),1.0f);
	gizmo.DrawCube();
	//gizmo.GenSphere(10, 1.0f);
	//gizmo.RenderSphere();
}


//enable lighting on and off
void Light::EnableLighting(bool truefalse)
{
	//if passed in true
	if (truefalse)
	{
		//enable lighting 
		glEnable(m_GLLIGHT);
	}
	//otherwise
	else
	{
		//disable lighting
		glDisable(m_GLLIGHT);
	}
}
