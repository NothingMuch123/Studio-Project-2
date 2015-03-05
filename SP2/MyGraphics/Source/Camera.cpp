#include "Camera.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\brief
Camera's constructor.
*/
/******************************************************************************/
Camera::Camera()
{
	Reset();
}

/******************************************************************************/
/*!
\brief
Camera's destructor.
*/
/******************************************************************************/
Camera::~Camera()
{
}

/******************************************************************************/
/*!
\brief
Initialize the various properties (position, target, up, view) and the rotation of Camera.
\param pos
the location of the camera.
\param target
the location at which the camera is looking at.
\param up
the vertically up vector that is perpendicular to the camera.
*/
/******************************************************************************/
void Camera::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = pos;
	this->target = target;
	this->up = up;
}

/******************************************************************************/
/*!
\brief
Reset the position, target, up and view coordinates and rotation to the default values.
*/
/******************************************************************************/
void Camera::Reset()
{
	position.Set(1, 0, 0);
	target.Set(0, 0, 0);
	up.Set(0, 1, 0);
}

/******************************************************************************/
/*!
\brief
Update the Camera's position, target, up and view location based on the time passed since the last update.
\param dt - 
the time passed since the last update.
*/
/******************************************************************************/
void Camera::Update(double dt)
{
	static const float CAMERA_SPEED = 20.f;
	if(Application::IsKeyPressed(VK_LEFT) || Application::IsKeyPressed('A'))
	{
		position.x -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_RIGHT) || Application::IsKeyPressed('D'))
	{
		position.x += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_UP) || Application::IsKeyPressed('W'))
	{
		position.y += (float)(CAMERA_SPEED * 0.2 * dt);
	}
	if(Application::IsKeyPressed(VK_DOWN) || Application::IsKeyPressed('S'))
	{
		position.y -= (float)(CAMERA_SPEED * 0.2 * dt);
	}
}