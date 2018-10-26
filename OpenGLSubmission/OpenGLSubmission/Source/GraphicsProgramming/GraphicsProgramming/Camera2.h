#pragma once
#include "Vector3.h"
#include "Input.h"
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
class Camera2
{
public:
	Camera2();
	Camera2(Vector3 pos, float rotx, float roty, float rotz);
	~Camera2();

	void InitVectors();
	void InitRotations();

	void UpdateCCTV(Input* input);
	void Update(Input* input);
	void UpdateTopDown();

	void SetScale(Vector3 scale);
	void TranslateForward(float speed);
	void Rotate(float degrees, Vector3 axis);
	void SetRotation(Vector3 rotation);
	void Translate(Vector3 directionvector);
	void CameraControls();
	void UpdatePerspective();
	float m_aspectRatio = 1.0f;
	float m_fov = 45.0f;
	float m_near = 10.f;
	float m_far = 10000.f;

	Vector3 m_up;
	Vector3 m_forward;
	Vector3 m_right;
	Vector3 m_target;
	Vector3 m_position, m_scale, m_rotation, m_newRotation;

	float oldMousePosx, oldMousePosy, newMousePosx, newMousePosy;
	float CosY, SinY, CosP, SinP, CosR, SinR;

};

