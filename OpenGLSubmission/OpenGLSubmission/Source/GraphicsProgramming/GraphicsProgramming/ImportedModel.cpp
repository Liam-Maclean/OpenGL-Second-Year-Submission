#include "ImportedModel.h"

//constructor
ImportedModel::ImportedModel()
{
	
}

//deconstructor
ImportedModel::~ImportedModel()
{
}

//sets the shadow imposter texture
void ImportedModel::SetShadowTexture()
{
	imposter.setTexture("imposter.png");
}


//loads the model with file location
bool ImportedModel::LoadModel(const char * path)
{
	//local variables
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector <Vector3> in_vertices;
	vector <Vector3> in_uvs;
	vector <Vector3> in_normals;

	FILE *file = fopen(path, "r");
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
			//store Vertex data
			if (strcmp(lineHeader, "v") == 0){
				Vector3 vertex;
				fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
				in_vertices.push_back(vertex);
			}
			//store UV data
			else if (strcmp(lineHeader, "vt") == 0){
				Vector3 uv;
				fscanf(file, "%f %f\n", &uv.x, &uv.y);
				in_uvs.push_back(uv);
			}
			//store normal data
			else if (strcmp(lineHeader, "vn") == 0){
				Vector3 normals;
				fscanf(file, "%f %f %f\n", &normals.x, &normals.y, &normals.z);
				in_normals.push_back(normals);

			}
			//store face data 
			else if (strcmp(lineHeader, "f") == 0){
				string vertex1, vertex2, vertex3;
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
				int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
				if (matches != 9){
					printf("File can't be read by our simple parser : ( Try exporting with other options\n");
					return false;
				}
				vertexIndices.push_back(vertexIndex[0]);
				vertexIndices.push_back(vertexIndex[1]);
				vertexIndices.push_back(vertexIndex[2]);
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}

			//for each vertex in vertex indices
			for (unsigned int i = 0; i < vertexIndices.size(); i++)
			{
				//store data
				unsigned int vertexIndex = vertexIndices[i];
				Vector3 vertex = in_vertices[vertexIndex - 1];
				m_vertices.push_back(vertex);
				m_uvs.push_back(vertex);
				m_normals.push_back(vertex);
			}
		}
	}
}


//sets scale of imposter shadow
void ImportedModel::SetScale(Vector3 scale)
{
	imposter.SetScale(scale);
	PrimativeShape::SetScale(scale);
}

//toggles if imposter shadow exists or not
void ImportedModel::ToggleShadow(bool truefalse)
{
	if (truefalse)
	{
		toggleShadowBool = true;
	}
	else
	{
		toggleShadowBool = false;
	}

}


//renders the imposter
void ImportedModel::RenderImposter()
{
	//disable lighting (can't light a shadow that'd be weird)
	glDisable(GL_LIGHTING);
	
	//enable blending for alpha
	glEnable(GL_BLEND);
	
	//disable depth test
	glDisable(GL_DEPTH_TEST);

	//set blend function
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//draw
	imposter.DrawPlane();

	//enable depth test
	glEnable(GL_DEPTH_TEST);

	//disable blend
	glDisable(GL_BLEND);

	//enable lighting
	glEnable(GL_LIGHTING);
}

//renders the model loaded
void ImportedModel::RenderModel()
{
	//if imposter shadow is toggled to be true
	if (toggleShadowBool)
	{
		//draw a shadow
		RenderImposter();
	}
	
	//contain transforms
	glPushMatrix();
	//apply materials
	ApplyMaterials();

	//color move and scale
	glColor4f(m_color.x, m_color.y, m_color.z, m_alpha);
	glTranslatef(m_pos.x, m_pos.y, m_pos.z);
	glRotatef(m_degrees.x, 1.0f, 0.0f, 0.0f);
	glRotatef(m_degrees.y, 0.0f, 1.0f, 0.0f);
	glRotatef(m_degrees.z, 0.0f, 0.0f, 1.0f);
	glScalef(m_scale.x, m_scale.y, m_scale.z);
	
	//enable client states for vertex array data and normals
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	//draw object using this information
	glVertexPointer(3, GL_FLOAT, 0, m_vertices.data());
	glNormalPointer(GL_FLOAT, 0, m_normals.data());
	glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());

	//disable client states
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glPopMatrix();
}