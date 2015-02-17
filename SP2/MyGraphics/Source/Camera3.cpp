#include "Camera3.h"
#include "Application.h"

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
void Camera3::Update(double dt, Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList)
{
	static const float CAMERA_SPEED = 5.f;
	static const float ROTATION_SPEED = 75.f;

	if(Application::IsKeyPressed('W'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position);
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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
		view = (zeroTarget - position);
		position += (view * yaw);
		target += (view * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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

	if(Application::IsKeyPressed('A'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		view = (target - position);
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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

	if(Application::IsKeyPressed('D'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		view = (target - position);
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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

	if(Application::IsKeyPressed('Q'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		view = (target - position);
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += (view.Cross(right) * yaw);
		target += (view.Cross(right) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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

	if(Application::IsKeyPressed('E'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		view = (target - position);
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += (view.Cross(right) * yaw);
		target += (view.Cross(right) * yaw);

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList))
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

	// tilt up
	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(ROTATION_SPEED * dt);
		view = (target - position);
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = (position + view);
	}

	// tilt down
	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-ROTATION_SPEED * dt);
		view = (target - position);
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalize();
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = (position + view);
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

bool Camera3::boundCheck(Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList)
{
	/*if ((target.x < BoundMax.x && target.x > BoundMin.x && target.y < BoundMax.y && target.y > BoundMin.y && target.z < BoundMax.z && target.z > BoundMin.z) || (target.x >= skyboxMaxBound.x || target.x <= skyboxMinBound.x || target.y >= skyboxMaxBound.y || target.y <= skyboxMinBound.y || target.z >= skyboxMaxBound.z || target.z <= skyboxMinBound.z))
	{
		return true;
	}
	else
	{
		return false;
	}*/
	if (_objList.size() != 0)
	{
		for (int i = 0; i < _objList.size(); ++i)
		{
			CObj *pObj = _objList[i];
			if ((position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || position.y > _outerSkyboxMaxBound.y || position.y < _outerSkyboxMinBound.y || position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || (position.x < pObj->getMaxBound().x && position.x > pObj->getMinBound().x && position.y < pObj->getMaxBound().y && position.y > pObj->getMinBound().y && position.z < pObj->getMaxBound().z && position.z > pObj->getMinBound().z))
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
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