#include "Scene.h"
using namespace std;

//enum for current cam type
enum camType
{
	moveableCam,
	topdownCam,
	staticCam
};
camType camtype = moveableCam;

//used for creating a cubular 'tilemap'
int Currmap[10][10] = {
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 1 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

//for rotation
float degrees;

//base materials for most objects
GLfloat ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat diffuse[] = { 0.5, 1.0, 0.5, 0.5 };
GLfloat emission[] = { 0.3, 0.2, 0.2, 0.0 };
GLfloat specular[] = { 0.0, 0.0, 0.0, 0.1 };

//sphere materials
GLfloat sphereAmbient[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat sphereDiffuse[] = { 0.8, 0.8, 0.8, 1.0 };
GLfloat sphereEmission[] = { 0.0, 0.0, 0.0, 0.0 };
GLfloat sphereSpecular[] = { 1.0, 1.0, 1.0, 0.2 };


GLfloat MovingLightX;


//light 1 light materials
GLfloat Light_Diffuse[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat Light_Position[] = { -5.0f, 10.0f, -80.0f, 1.0f };
GLfloat Light_Ambient[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//light 2 light materials
GLfloat Light_Diffuse2[] = { 1.0f, 0.0f, 0.0f, 1.0f };
GLfloat Light_Position2[] = { 5.0f, 10.0f, -80.0f, 1.0f };
GLfloat Light_Ambient2[] = { 0.0f, 0.0f, 0.0f, 0.0f };

//light 3 light materials
GLfloat Light_Diffuse3[] = { 5.0f, 5.0f, 0.0f, 1.0f };
GLfloat Light_Position3[] = { -20.0f, 15.0f, -25.0, 1.0f };
GLfloat Light_Ambient3[] = { 0.0f, 0.0f, 0.0f, 0.0f };

// spot light 1 light materials
GLfloat Light_Diffuse4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Light_Position4[] = { 10.0f, 60.0f, -40.0f, 1.0f };
GLfloat Light_Ambient4[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat Spot_Direction[] = { 1.0f, 0.0f, 0.0f, 1.0f };

// spot light 2 light materials
GLfloat Light_Diffuse5[] = { 0.0f, 1.0f, 0.0f, 1.0f };
GLfloat Light_Position5[] = { 10.0f, 80.0f, -60.0f, 1.0f };
GLfloat Light_Ambient5[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat Spot_Direction2[] = { 1.0f, 0.0f, 0.0f, 1.0f };

// spot light 3 light materials
GLfloat Light_Diffuse6[] = { 1.0f, 0.0f, 1.0f, 1.0f };
GLfloat Light_Position6[] = { 10.0f, 80.0f, -20.0f, 1.0f };
GLfloat Light_Ambient6[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat Spot_Direction3[] = { 1.0f, 0.0f, 0.0f, 1.0f };

// spot light 4 light materials
GLfloat Light_Diffuse7[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat Light_Position7[] = { 5.0f, 15.0f,20.0f, 1.0f };
GLfloat Light_Ambient7[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat Spot_Direction4[] = { 0.0f, -1.0f, 0.0f, 1.0f };

// spot light 5 light materials
GLfloat Light_Diffuse8[] = { 0.5f, 0.5f, 1.0f, 1.0f };
GLfloat Light_Position8[] = { 10.0f, 80.0f, -40.0f, 1.0f };
GLfloat Light_Ambient8[] = { 0.0f, 0.0f, 0.0f, 0.0f };
GLfloat Spot_Direction5[] = { 1.0f, 0.0f, 0.0f, 1.0f };


//lights
Light spot(GL_LIGHT0, Light_Diffuse, Light_Position, Light_Ambient);
Light spot2(GL_LIGHT1, Light_Diffuse2, Light_Position2, Light_Ambient2);
Light spot3(GL_LIGHT2, Light_Diffuse3, Light_Position3, Light_Ambient3);
Light pLight(GL_LIGHT3, Light_Diffuse4, Light_Position4, Light_Ambient4,Spot_Direction, 25.0f, 60.0f);
Light pLight2(GL_LIGHT4, Light_Diffuse5, Light_Position5, Light_Ambient5, Spot_Direction2, 45.0f, 40.0f);
Light pLight3(GL_LIGHT5, Light_Diffuse6, Light_Position6, Light_Ambient6, Spot_Direction3, 90.0f, 70.0f);
Light pLight4(GL_LIGHT6, Light_Diffuse7, Light_Position7, Light_Ambient7, Spot_Direction4, 90.0f, 50.0f);
Light pLight5(GL_LIGHT7, Light_Diffuse8, Light_Position8, Light_Ambient8, Spot_Direction5, 70.0f, 30.0f);
double eqr[] = { 0.0f, -1.0f, 0.0f, 0.0f };


//imported models
ImportedModel Barrel(Vector3(0, -1.5f, -80));
ImportedModel tower(Vector3(-10, -1.5f, -20));
ImportedModel CoffinBench(Vector3(0, -1.5f, -90));
ImportedModel CoffinBenchFL(Vector3(-13, -1.5f, -80));
ImportedModel CoffinBenchFR(Vector3(13, -1.5f, -80));
ImportedModel CoffinBenchBR(Vector3(10, -1.5f, -55));
ImportedModel CoffinBenchBL(Vector3(-10, -1.5f, -55));
ImportedModel tree(Vector3(-4, -3, 0));

//spheres in the scene
vector<Sphere> spheres;


//rotating spheres on left
vector<IcoSphere> rotatingPlanets;

//textured objects
Sphere texturedSphere(Vector3(-20, 10, -20));
Plane texturedPlane(Vector3(-20, 5, -20));

//multiple primative objects
Sphere sphere1(Vector3(2, 0, 0));
IcoSphere icoSphere1(Vector3(5, 1, -80));
Plane plane1(Vector3(0, 0, 0));
QuadStrip RightWall(Vector3(40, 100, -80));
Plane TopWall(Vector3(0, 0, 0));
Disc disc1(Vector3(0, 0, 0));


//moveable cam
Camera2 Cam(Vector3(0,4,6), 0.0f, 0.0f, 0.0f);

//panning cam (light wall)
Camera2 Cam2(Vector3(-20, 80, -40), 0.0f, 90.0f, 0.0f);

//top down cam
Camera2 Cam3(Vector3(0, 200, -20), 270.0f, 0.0f, 0.0f);


float LightPosZ = -1.0f;
bool wireBool = false;
bool flatBool = false;


Scene::Scene(Input *in)
{
	// Store pointer for input class
	input = in;
		
	//OpenGL settings
	glShadeModel(GL_SMOOTH);
	glClearColor(0.7f, 0.7f, 0.7f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);	
	glClearStencil(0);// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	
	//turns on lighting for each light
	spot.EnableLighting(true);
	spot2.EnableLighting(true);
	spot3.EnableLighting(true);
	pLight.EnableLighting(true);
	pLight2.EnableLighting(true);
	pLight3.EnableLighting(true);
	pLight4.EnableLighting(true);
	pLight5.EnableLighting(true);


	//sets up attenuation for lights
	spot.Attenuation(1.0f, 0.0f, 0.015f);
	spot2.Attenuation(1.0f, 0.0f, 0.015f);
	spot3.Attenuation(1.0f, 0.0f, 0.015f);
	pLight.Attenuation(1.0f, 0.0f, 0.0f);
	pLight2.Attenuation(1.0f, 0.0f, 0.0f);
	pLight3.Attenuation(1.0f, 0.0f, 0.0f);
	pLight4.Attenuation(1.0f, 0.0f, 0.0f);


	//sets up rotating objects on the left
	for (int i = 1; i < 4; i++)
	{
		IcoSphere planetTemp;
		planetTemp.SetPosition(i * 2, 5, -20.f);
		planetTemp.SetScale(Vector3(2.f*i, 2.f*i,2.f*i));
		planetTemp.SetColor(Vector3(0.5f*i, 1.0f*i, 0.0f), 0.5f);

		rotatingPlanets.push_back(planetTemp);
	}


	//sets up multiple colored spheres on plane
	for (int i = 0; i < 12; i += 3)
	{
		Sphere currSphere(Vector3(i * -1 + 10, 2, 20));
		Sphere currSphere2(Vector3(i * -1 + 10, 2, 22));
		Sphere currSphere3(Vector3(i * -1 + 10, 2, 24));
		currSphere.SetScale(Vector3(1, 1, 1));
		currSphere2.SetScale(Vector3(1, 1, 1));
		currSphere3.SetScale(Vector3(1, 1, 1));
		currSphere.SetColor(Vector3(0.25f *i, 1.0f, 1.0f), 1.0f);
		currSphere2.SetColor(Vector3(1.0f, 0.25f * i, 1.0f), 1.0f);
		currSphere3.SetColor(Vector3(1.0f, 1.0f, 0.25f * i), 1.0f);
		spheres.push_back(currSphere);
		spheres.push_back(currSphere2);
		spheres.push_back(currSphere3);
	}

	//creates each sphere with 64 segments and a radius of 1
	for (int i = 0; i < spheres.size(); i++)
	{
		spheres[i].GenSphere(64, 1);
		spheres[i].SetMaterials(sphereAmbient, sphereDiffuse, sphereSpecular, sphereEmission);
	}


	/*==========================LOADING MODELS===============================*/
	Barrel.LoadModel("Models/Barrel.obj");
	Barrel.SetShadowTexture();
	Barrel.SetScale(Vector3(4.0, 4.0, 4.0));
	Barrel.SetColor(Vector3(1.0f, 1.0f, 0.5f), 1.0f);
	Barrel.MaterialLoader("Jade");

	CoffinBenchBL.LoadModel("Models/StoneBenchCoffin.obj");
	CoffinBenchBL.SetShadowTexture();
	CoffinBenchBL.SetScale(Vector3(4.0, 4.0, 4.0));
	CoffinBenchBL.SetColor(Vector3(1.6f, 0.6f, 0.6f),1.0f);
	CoffinBenchBL.SetRotationY(135);
	CoffinBenchBL.SetMaterials(ambient, diffuse, specular, emission);

	CoffinBenchFR.LoadModel("Models/StoneBenchCoffin.obj");
	CoffinBenchFR.SetShadowTexture();
	CoffinBenchFR.SetScale(Vector3(4.0, 4.0, 4.0));
	CoffinBenchFR.SetColor(Vector3(0.6f, 1.6f, 0.6f), 1.0f);
	CoffinBenchFR.SetRotationY(315);
	CoffinBenchFR.SetMaterials(ambient, diffuse, specular, emission);

	CoffinBenchBR.LoadModel("Models/StoneBenchCoffin.obj");
	CoffinBenchBR.SetShadowTexture();
	CoffinBenchBR.SetScale(Vector3(4.0, 4.0, 4.0));
	CoffinBenchBR.SetColor(Vector3(0.6f, 0.6f, 1.6f), 1.0f);
	CoffinBenchBR.SetRotationY(225);
	CoffinBenchBR.SetMaterials(ambient, diffuse, specular, emission);

	CoffinBenchFL.LoadModel("Models/StoneBenchCoffin.obj");
	CoffinBenchFL.SetShadowTexture();
	CoffinBenchFL.SetScale(Vector3(4.0, 4.0, 4.0));
	CoffinBenchFL.SetColor(Vector3(0.6f, 1.6f, 1.6f), 1.0f);
	CoffinBenchFL.SetRotationY(45);
	CoffinBenchFL.SetMaterials(ambient, diffuse, specular, emission);


	CoffinBench.LoadModel("Models/StoneBenchCoffin.obj");
	CoffinBench.SetShadowTexture();
	CoffinBench.SetScale(Vector3(4.0, 4.0, 4.0));
	CoffinBench.SetColor(Vector3(1.6f, 1.6f, 0.6f), 1.0f);
	CoffinBench.SetMaterials(ambient, diffuse, specular, emission);

	tower.LoadModel("Models/Tower.obj");
	tower.SetShadowTexture();
	tower.SetScale(Vector3(10, 10, 10)); 
	tower.SetColor(Vector3(1.6f, 1.6f, 0.5f), 1.0f);
	tower.SetMaterials(ambient, diffuse, specular, emission);

	// Initialise variables
	tree.LoadModel("Tree.obj");
	tree.SetScale(Vector3(2.0f, 2.0f, 2.0f));
	tree.SetColor(Vector3(0.0f, 1.0f, 0.0f), 1.0f);



	plane1.SetScale(Vector3(200, 1, 200));
	plane1.SetColor(Vector3(1.0f, 1.0f, 1.0f), 0.6f);

	RightWall.Setup(100,100);
	RightWall.SetRotationX(90);
	RightWall.SetRotationZ(90);
	RightWall.SetScale(Vector3(1, 1, 1));
	RightWall.SetColor(Vector3(0.0f, 1.0f, 1.0f), 1.0f);


	icoSphere1.SetScale(Vector3(4.0f, 4.0f, 4.0f)); 
	icoSphere1.SetColor(Vector3(0.0f, 0.0f, 1.0f),1.0f);
	icoSphere1.SetMaterials(ambient, diffuse, specular, emission);

	texturedSphere.SetScale(Vector3(2.0f, 2.0f, 2.0f));
	texturedSphere.setTexture("crate.png");
	texturedSphere.SetColor(Vector3(1.0f, 1.0f, 1.0f), 1.0f);
	texturedSphere.SetMaterials(ambient, diffuse, specular, emission);
	texturedSphere.GenSphere(80, 1);

	texturedPlane.SetScale(Vector3(5.0f, 5.0f, 5.0f));
	texturedPlane.setTexture("crate.png");
	texturedPlane.SetColor(Vector3(1.0f, 1.0f, 1.0f), 1.0f);


	sphere1.SetScale(Vector3(1.0f, 1.0f, 1.0f));
	sphere1.SetColor(Vector3(2.0f, 5.0f, 1.0f), 1.0f);
	sphere1.GenSphere(64, 1);
	sphere1.SetMaterials(ambient, diffuse, specular, emission);
	vector<int>::size_type i = 0;
	//cube1 = CubeGen(Vector3(0, 0, 0));
	//cube2 = CubeGen(Vector3(-1, -1, 0));
}

void Scene::update(float dt)
{
	// Handle user input
	// Update object and variables (camera, rotation, etc)
	degrees++;

	for (int i = 0; i < 3; i++)
	{
		rotatingPlanets[i].rotate();
	}

	//wireframe mode
	if (input->isKeyDown('c'))
	{
		//if wireframe is off 
		if (!wireBool)
		{
			//turn on
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			wireBool = true;
		}
		//if wireframe is on
		else if (wireBool)
		{
			//turn off
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			wireBool = false;
		}
		input->SetKeyUp('c');
	}

	if (input->isKeyDown('f'))
	{
		if (!flatBool)
		{
			glShadeModel(GL_FLAT);
			flatBool = true;
		}
		else if (flatBool)
		{
			glShadeModel(GL_SMOOTH);
			flatBool = false;
		}
		input->SetKeyUp('f');
	}

	if (input->isKeyDown('u'))
	{
		if (camtype == moveableCam)
		{
			camtype = staticCam;
		}
		else if (camtype == staticCam)
		{
			camtype = topdownCam;
		}
		else if (camtype == topdownCam)
		{
			camtype = moveableCam;
		}
		input->SetKeyUp('u');
	}


	if (input->isKeyDown('b'))
	{
		
		input->SetKeyUp('b');
	}
	if (input->isKeyDown('n'))
	{

		input->SetKeyUp('n');
	}



	// Calculate FPS
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	


	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

void Scene::render() {

	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();
	// Set the camera
	

	//updates depending on camtype
	if (camtype == moveableCam)
	{
		Cam.Update(input);
	}
	else if (camtype == staticCam)
	{
		Cam2.UpdateCCTV(input);
	}
	else if (camtype == topdownCam)
	{
		Cam3.UpdateTopDown();
	}

	
	// Render geometry here -------------------------------------
	//spot.DrawGizmo();
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glDisable(GL_DEPTH_TEST);
	plane1.DrawPlane();
	glEnable(GL_DEPTH_TEST);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glEnable(GL_CLIP_PLANE0);
	glClipPlane(GL_CLIP_PLANE0, eqr);


	

	spot.SetUpLighting();
	spot2.SetUpLighting();
	spot3.SetUpLighting();
	pLight.SetUpLighting();


	tower.SetPosition(-20, -1.5f, -10);
	CoffinBench.SetPosition(0, -3.0f, -90);
	CoffinBenchFL.SetPosition(-13, -3.0f, -80);
	CoffinBenchFR.SetPosition(13, -3.0f, -80);
	CoffinBenchBR.SetPosition(10, -3.0f, -55);
	CoffinBenchBL.SetPosition(-10, -3.0f, -55);
	
	for (int i = 0; i < spheres.size(); i += 3)
	{

		spheres[i].SetScale(Vector3(1, -1, 1));
		spheres[i + 1].SetScale(Vector3(1, -1, 1));
		spheres[i + 2].SetScale(Vector3(1, -1, 1));
		spheres[i].SetPosition(i* -1 + 10, -2, 20);
		spheres[i + 1].SetPosition(i * -1 + 10,-2,22);
		spheres[i + 2].SetPosition(i * -1 + 10, -2, 24);

		spheres[i].RenderSphere();
		spheres[i + 1].RenderSphere();
		spheres[i + 2].RenderSphere();
	}



	sphere1.SetPosition(0, -15.0f, -60);
	sphere1.RenderSphere();

	
	tower.SetScale(Vector3(10, -10, 10));
	CoffinBench.SetScale(Vector3(4, -4, 4));
	CoffinBenchBL.SetScale(Vector3(4, -4, 4));
	CoffinBenchFR.SetScale(Vector3(4, -4, 4));
	CoffinBenchFL.SetScale(Vector3(4, -4, 4));
	CoffinBenchBR.SetScale(Vector3(4, -4, 4));


	CoffinBench.RenderModel();
	CoffinBenchBL.RenderModel();
	CoffinBenchFR.RenderModel();
	CoffinBenchFL.RenderModel();
	CoffinBenchBR.RenderModel();

	glDisable(GL_CLIP_PLANE0);
	glDisable(GL_STENCIL_TEST);
	glEnable(GL_BLEND);
	glDisable(GL_LIGHTING);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	plane1.DrawPlane();

	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);

	spot.SetUpLighting();
	spot2.SetUpLighting();
	spot3.SetUpLighting();
	pLight.SetUpLighting();
	pLight2.SetUpLighting();
	pLight3.SetUpLighting();
	pLight4.SetUpLighting();
	pLight5.SetUpLighting();

	tower.SetPosition(-20, 1.5f, -10);
	CoffinBench.SetPosition(0, 3.0f, -90);
	CoffinBenchFL.SetPosition(-13, 3.0f, -80);
	CoffinBenchFR.SetPosition(13, 3.0f, -80);
	CoffinBenchBR.SetPosition(10, 3.0f, -55);
	CoffinBenchBL.SetPosition(-10, 3.0f, -55);

	
	tower.SetScale(Vector3(10, 10, 10));
	CoffinBench.SetScale(Vector3(4, 4, 4));
	CoffinBenchBL.SetScale(Vector3(4, 4, 4));
	CoffinBenchFR.SetScale(Vector3(4, 4, 4));
	CoffinBenchFL.SetScale(Vector3(4, 4, 4));
	CoffinBenchBR.SetScale(Vector3(4, 4, 4));
	
	//tower.RenderModel();
	RightWall.Render();
	CoffinBench.RenderModel();
	CoffinBenchBL.RenderModel();
	CoffinBenchFR.RenderModel();
	CoffinBenchFL.RenderModel();
	CoffinBenchBR.RenderModel();
	
	glPushMatrix();
	glTranslatef(-50, 80, -20);
		glRotatef(degrees, 1, 1, 1);
		rotatingPlanets[0].SetPosition(-20, 0, -20);
		rotatingPlanets[0].DrawIsohederon();
		glPushMatrix();
			glRotatef(degrees, -1, 1, -1);
			rotatingPlanets[1].DrawIsohederon();
			glPushMatrix();
				glRotatef(degrees, 1, -1, 1);
				rotatingPlanets[2].DrawIsohederon();
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();


	for (int i = 0; i < spheres.size(); i +=3)
	{

		spheres[i].SetScale(Vector3(1, 1, 1));
		spheres[i + 1].SetScale(Vector3(1, 1, 1));
		spheres[i + 2].SetScale(Vector3(1, 1, 1));
		spheres[i].SetPosition(i* -1 + 10, 2, 20);
		spheres[i + 1].SetPosition(i * -1 + 10, 2, 22);
		spheres[i + 2].SetPosition(i * -1 + 10, 2, 24);

		spheres[i].RenderSphere();
		spheres[i + 1].RenderSphere();
		spheres[i + 2].RenderSphere();
	}
	sphere1.SetPosition(0, 15.0f, -60);
	sphere1.RenderSphere();

	texturedPlane.DrawPlane();
	texturedSphere.RenderSphere();
	
	
	// Geometry rendering ends here -----------------------------


	// Render text, should be last object rendered.
	renderTextOutput();
	
	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

void Scene::resize(int w, int h) 
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 10000.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	if (camtype == moveableCam)
	{
		//free cam perspective
		Cam.UpdatePerspective();
	}
	else if (camtype == staticCam)
	{
		//panning cam perspective
		Cam2.UpdatePerspective();
	}
	else if (camtype == topdownCam)
	{
		//topdown cam perspective
		Cam3.UpdatePerspective();
	}



	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void Scene::renderTextOutput()
{
	glDisable(GL_LIGHTING);
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	sprintf_s(materialText, "Press the 'f' key to change material smoothness");
	sprintf_s(wireText, "Press the 'c' key to change to and from wireframe mode");
	displayText(-1.f, 0.96f, 1.f, 1.f, 1.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 1.f, 1.f, fps);
	displayText(-1.f, 0.84f, 1.f, 1.f, 1.f, wireText);
	displayText(-1.f, 0.78f, 1.f, 1.f, 1.f, materialText);

	//if the current cam is the freecam
	if (camtype == moveableCam)
	{
		//set the text on screen for freecam
		displayText(-1.0f, 0.72f, 1.0f, 1.0f, 1.0f, "Press the 'u' key to swap to Light cam");
		displayText(-1.0f, 0.66f, 1.0f, 1.0f, 1.0f, "Use W and S to move forward and backwards");
		displayText(-1.0f, 0.60f, 1.0f, 1.0f, 1.0f, "Use the mouse to rotate");
	}
	//if the current cam is the staticcam
	else if (camtype == staticCam)
	{
		//set the text on the screen for static cam
		displayText(-1.0f, 0.72f, 1.0f, 1.0f, 1.0f, "Press the 'u' key to swap to top down cam");
		displayText(-1.0f, 0.66f, 1.0f, 1.0f, 1.0f, "Use the A and D keys to rotate left and right");
		displayText(-1.0f, 0.60f, 1.0f, 1.0f, 1.0f, "Restricted to left and right rotations only");
	}
	//if the current cam is the top down cam
	else if (camtype == topdownCam)
	{
		//top down 
		displayText(-1.0f, 0.72f, 1.0f, 1.0f, 1.0f, "Press the 'u' key to swap to Free cam");
		displayText(-1.0f, 0.66f, 1.0f, 1.0f, 1.0f, "Static Topdown cam cannot move");
	}

	glEnable(GL_LIGHTING);
	
}

void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width/(float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
