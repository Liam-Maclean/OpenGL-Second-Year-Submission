#include "Camera2.h"


//standard constructor
Camera2::Camera2()
{
	InitRotations();
	InitVectors();
	gluPerspective(m_fov, m_aspectRatio, m_near, m_far);
}

//constructor with initial rotation values (for ease of initialisation
//not optimal
Camera2::Camera2(Vector3 pos, float rotx, float roty, float rotz)
{
	Rotate(rotx, Vector3(1, 0, 0));
	Rotate(roty, Vector3(0, 1, 0));
	Rotate(rotz, Vector3(0, 0, 1));
	m_position = pos;
	InitRotations();
	InitVectors();
	gluPerspective(m_fov, m_aspectRatio, m_near, m_far);
}

//deconstructor
Camera2::~Camera2()
{
}

//updates the perspective of current camera 
void Camera2::UpdatePerspective()
{
	gluPerspective(m_fov, m_aspectRatio, m_near, m_far);
}

//translates camera forwards
void Camera2::TranslateForward(float speed)
{
	m_position += m_forward * speed;
}

//translates in a vector3 direction
void Camera2::Translate(Vector3 directionvector)
{
	m_position += directionvector;
}

//sets the camera scale
void Camera2::SetScale(Vector3 scale)
{
	m_scale = scale;
}

//sets the rotation
void Camera2::SetRotation(Vector3 rotation)
{
	m_rotation = rotation;
}

//rotates the camera 
void Camera2::Rotate(float degrees, Vector3 axis)
{
	m_newRotation.x += (axis.x * degrees);
	m_newRotation.y += (axis.y * degrees);
	m_newRotation.z += (axis.z * degrees);
}

//updates the topdown camera type (this just passes glulookat to the scene)
void Camera2::UpdateTopDown()
{
	m_target = m_position + m_forward;

	InitRotations();
	InitVectors();
	if (!m_rotation.equals(m_newRotation))
	{
		m_rotation = m_newRotation;
	}

	gluLookAt(m_position.x, m_position.y, m_position.z,
		m_target.x, m_target.y, m_target.z,
		m_up.x, m_up.y, m_up.z);
}

//updates CCTV type camera (Handles input, and passed GluLookAt to the scene)
void Camera2::UpdateCCTV(Input* input)
{

	m_target = m_position + m_forward;




	InitRotations();
	InitVectors();

	//if d is pressed
	if (input->isKeyDown('d'))
	{
		//pan right
		Rotate(30 * 0.015f, Vector3(0, 1, 0));
	}
	//if the key isn't pressed
	else if (!input->isKeyDown('d'))
	{
		//set the keyup
		input->SetKeyUp('d');
	}
	//if a is pressed
	if (input->isKeyDown('a'))
	{
		//pan left
		Rotate(-30 * 0.015f, Vector3(0, 1, 0));
	}
	//if the key isn't pressed
	else if (!input->isKeyDown('a'))
	{
		//set the keyup
		input->SetKeyUp('a');
	}

	//if the rotation has changed
	if (!m_rotation.equals(m_newRotation))
	{
		//rotation applied
		m_rotation = m_newRotation;
	}

	//update glulookat 
	gluLookAt(m_position.x, m_position.y, m_position.z,
		m_target.x, m_target.y, m_target.z,
		m_up.x, m_up.y, m_up.z);
}


//updates the free roam camera (handles input, and passes glulookat to the scene)
void Camera2::Update(Input* input)
{
	//warps the pointer to the middle of the screen
	glutWarpPointer(400, 300);

	//sets the new mouse position to be used
	oldMousePosx = newMousePosx;
	oldMousePosy = newMousePosy;
	
	//new mouse position is set
	newMousePosx = input->getMouseX() - 400;
	newMousePosy = input->getMouseY() - 300;


	//rotates based on mouse position * delta time (0.015f)
	Rotate(newMousePosx * 0.015f, Vector3(0, 1, 0));
	Rotate(-newMousePosy * 0.015f, Vector3(1, 0, 0));
	


	/*	
		might look weird to do two checks however it prevents
		'stutering' on the first update of the movement and 
		makes movement smooth
															*/
	
	//if the w key is down
	if (input->isKeyDown('w'))
	{
		//translate forward
		TranslateForward(1.0f);
		
	}
	//if the w key is NOT down
	else if (!input->isKeyDown('w'))
	{
		//set the w key up
		input->SetKeyUp('w');
	}

	//if the s key is down
	if (input->isKeyDown('s'))
	{
		//translate backwards
		TranslateForward(-1.0f);
		
	}
	//if the s key is NOT down
	else if (!input->isKeyDown('s'))
	{
		//set the key up
		input->SetKeyUp('s');
	}

	//if the rotation has changed
	if (!m_rotation.equals(m_newRotation))
	{
		//store new rotation
		m_rotation = m_newRotation;
	}

	//set up variables again with new information
	InitRotations();
	InitVectors();
	m_target = m_position + m_forward;


	//update glulookat
	gluLookAt(m_position.x, m_position.y, m_position.z,
		m_target.x, m_target.y, m_target.z,
		m_up.x, m_up.y, m_up.z);


}


//sets up the vectors to work camera
void Camera2::InitVectors()
{
	m_up.x = (-CosY * SinR) - (SinY * SinP * CosR);
	m_up.y = CosP * CosR;
	m_up.z = (-SinY * SinR) - (SinP * CosR * -CosY);
	m_up.normalise();

	m_forward.x = SinY * CosP;
	m_forward.y = SinP;
	m_forward.z = CosP * -CosY;
	m_forward.normalise();

	m_right.x = ((m_up.y * m_forward.z) - (m_up.z * m_forward.y));
	m_right.y = ((m_up.z * m_forward.x) - (m_up.x * m_forward.z));
	m_right.z = ((m_up.x * m_forward.y) - (m_up.y * m_forward.x));
	m_right.normalise();
}

//sets up the rotations for camera
void Camera2::InitRotations()
{
	this->CosY = cosf(m_rotation.y * 3.1415f / 180); 
	this->SinY = sinf(m_rotation.y * 3.1415f / 180);

	this->CosP = cosf(m_rotation.x * 3.1415f / 180);
	this->SinP = sinf(m_rotation.x * 3.1415f / 180);

	this->CosR = cosf(m_rotation.z * 3.1415f / 180);
	this->SinR = sinf(m_rotation.z * 3.1415f / 180);
}

