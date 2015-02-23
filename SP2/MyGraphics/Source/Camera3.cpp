#include "Camera3.h"
#include "Application.h"
#include "SP2.h"
#include "GLFW/glfw3.h"
/******************************************************************************/
/*!
\brief
Camera3's constructor.
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Camera3's destructor.
*/
/******************************************************************************/
Camera3::~Camera3()
{
}

/******************************************************************************/
/*!
\brief
Initialize the various properties (position, target, up, view) and the rotation of Camera3.
\param pos
the location of the camera.
\param target
the location at which the camera is looking at.
\param up
the vertically up vector that is perpendicular to the camera.
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	defaultView = view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	IN_CAR = false;
	rotation.SetToIdentity();
}

/******************************************************************************/
/*!
\brief
Update the Camera's position, target, up and view location based on the time passed since the last update.
\param dt - 
the time passed since the last update.
*/
/******************************************************************************/
void Camera3::Update(double dt, Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj *_inCar)
{
	double xpos = 0;
	double ypos = 0;
	static const float CAMERA_SPEED = 30.f;
	static const float RUN_SPEED = 50.f;
	static const float CAR_SPEED = 70.f;
	static const float SANIC = 90.f;
	static const float ROTATION_SPEED = 100.f;
	if(Application::IsKeyPressed('C'))
	{
		IN_CAR = true;
	}
	if(Application::IsKeyPressed('V'))
	{
		IN_CAR = false;
	}
	//Walking Speedws 
	if(Application::IsKeyPressed('W'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}
	//Car Speed
	if(Application::IsKeyPressed('W') && IN_CAR == true)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAR_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}

		/*if (_objList.size() != 0)
		{
			for (int i = 0; i < _objList.size(); i++)
			{
				pObj = _objList[i];
				BoundMax = pObj->getMaxBound();
				BoundMin = pObj->getMinBound();
				if(boundCheck())
				{
					target = tempTarget;
					position = tempPosition;
				}
			}
		}
		else
		{
			if (boundCheck())
			{
				target = tempTarget;
				position = tempPosition;
			}
		}*/
	}
	//Sprint Speed
	if(Application::IsKeyPressed('W') && Application::IsKeyPressed(VK_SHIFT))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(RUN_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}

		/*if (_objList.size() != 0)
		{
			for (int i = 0; i < _objList.size(); i++)
			{
				pObj = _objList[i];
				BoundMax = pObj->getMaxBound();
				BoundMin = pObj->getMinBound();
				if(boundCheck())
				{
					target = tempTarget;
					position = tempPosition;
				}
			}
		}
		else
		{
			if (boundCheck())
			{
				target = tempTarget;
				position = tempPosition;
			}
		}*/
	}
	//GOTTA GO FEZ
	if(Application::IsKeyPressed('W') && Application::IsKeyPressed(VK_SHIFT) && IN_CAR == true)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(SANIC * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}

		/*if (_objList.size() != 0)
		{
			for (int i = 0; i < _objList.size(); i++)
			{
				pObj = _objList[i];
				BoundMax = pObj->getMaxBound();
				BoundMin = pObj->getMinBound();
				if(boundCheck())
				{
					target = tempTarget;
					position = tempPosition;
				}
			}
		}
		else
		{
			if (boundCheck())
			{
				target = tempTarget;
				position = tempPosition;
			}
		}*/
	}
	if(Application::IsKeyPressed('S'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed('A') && _inCar == NULL)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed('D') && _inCar == NULL)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed('Q') && _inCar == NULL)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		position += (position - newUp).Normalized() * yaw;
		target += (position - newUp).Normalized() * yaw;

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed('E') && _inCar == NULL)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		position += (position - newUp).Normalized() * yaw;
		target += (position - newUp).Normalized() * yaw;

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _inCar))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	// tilt up
	if(Application::IsKeyPressed(VK_UP) && _inCar == NULL)
	{
		Vector3 view = (target - position).Normalized();
		float theta = atan2(view.y,sqrt(view.x * view.x + view.z * view.z ));
		theta = Math::RadianToDegree(theta);

		if(theta < 70)
		{
			float pitch = (float)(CAMERA_SPEED * dt * 2);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			target = rotation* (target - position) + position;
		}
	}

	// tilt down
	if(Application::IsKeyPressed(VK_DOWN) && _inCar == NULL)
	{
		Vector3 view = (target - position).Normalized();
		float theta = atan2(view.y,sqrt(view.x * view.x + view.z * view.z ));
		theta = Math::RadianToDegree(theta);

		if(theta > -70)
		{
			float pitch = (float)(-CAMERA_SPEED * dt * 2);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			target = rotation * ( target - position) + position;
		}
	}

	// tilt left
	if(Application::IsKeyPressed(VK_LEFT))
	{
		float pitch = (float)(ROTATION_SPEED * dt);
		view = (target - position);
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}

	// tilt right
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float pitch = (float)(-ROTATION_SPEED * dt);
		view = (target - position);
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

/******************************************************************************/
/*!
\brief
Reset the position, target, up and view coordinates and rotation to the default values.
*/
/******************************************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
	view = defaultView;
	rotation.SetToIdentity();
}

bool Camera3::boundCheck(Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj *_inCar)
{
	if (_objList.size() != 0) // Obj & skybox check
	{
		for (int i = 0; i < _objList.size(); ++i)
		{
			CObj *pObj = _objList[i];
			if (pObj->getRender())
			{
				if (	// Skybox check
					(position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || position.y > _outerSkyboxMaxBound.y || position.y < _outerSkyboxMinBound.y || position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || 
					// Obj check
					(position.x < pObj->getMaxBound().x && position.x > pObj->getMinBound().x && position.y < pObj->getMaxBound().y && position.y > pObj->getMinBound().y && position.z < pObj->getMaxBound().z && position.z > pObj->getMinBound().z)
					)
				{
					return true;
				}
			}
		}
		return false;
	}
	else // No obj, skybox check only
	{
		if (position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || position.y > _outerSkyboxMaxBound.y || position.y < _outerSkyboxMinBound.y || position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}