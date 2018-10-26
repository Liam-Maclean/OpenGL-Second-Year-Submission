#pragma once
#include "PrimativeShape.h"
#include "Plane.h"
#include <string>
#include <iostream>
#include <Windows.h>
using namespace std;

class ImportedModel:
	public PrimativeShape
{

private:
	bool toggleShadowBool;
	vector<Vector3> m_vertices;
	vector<Vector3> m_uvs;
	vector<Vector3> m_normals;


public:
	//constructor
	ImportedModel();

	//shadow plane
	Plane imposter;

	//inherited constructor
	ImportedModel(Vector3 pos)
		:PrimativeShape(pos)
	{
		imposter.SetPosition(pos.x, -6 ,pos.z);
		imposter.SetScale(m_scale);
		imposter.SetColor(Vector3(1, 1, 1),1.0f);

		toggleShadowBool = false;

	}

	//deconstructor
	~ImportedModel();


	//methods
	void ToggleShadow(bool truefalse);
	void SetScale(Vector3 scale) override;
	void RenderImposter();
	void SetShadowTexture();
	bool LoadModel(const char * path);
	void RenderModel();
};

