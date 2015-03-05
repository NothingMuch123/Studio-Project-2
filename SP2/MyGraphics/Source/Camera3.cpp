#include "Camera3.h"
#include "Application.h"
#include "SP2.h"
#include "GLFW/glfw3.h"
#include "Car.h"
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
void Camera3::Update(double dt, Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj **_hands, int floorNum, std::vector<CObj*> &_objList2)
{
	double xpos = 0;
	double ypos = 0;
	static const float NORMAL_SPEED = 30.f;
	static const float RUN_SPEED = 50.f;
	static const float CAR_SPEED = 70.f;
	static const float SANIC = 90.f;
	static const float ROTATION_SPEED = 100.f;
	static float CAMERA_SPEED = NORMAL_SPEED;
	bool boost = false;

	bool noclip = false;
	bool isTiptoeing = false;
	bool isCrouching = false;

	current = 0; // 0 - Nothing | 1 = Car | 2 - Trolley
	CObj *pObj;
	for (int i = 0; i < _objList.size(); ++i)
	{
		pObj = _objList[i];
		if (_hands[0] == pObj || _hands[1] == pObj)
		{
			if (pObj->getID() == SP2::GEOMETRY_TYPE::GEO_CAR)
			{
				current = 1;
				maxBound = pObj->getMaxBound();
				minBound = pObj->getMinBound();
				break;
			}
			else if (pObj->getID() == SP2::GEOMETRY_TYPE::GEO_TROLLEY)
			{
				current = 2;
				maxBound = pObj->getMaxBound();
				minBound = pObj->getMinBound();
				break;
			}
		}
	}

	if (current != 1)
	{
		CAMERA_SPEED = NORMAL_SPEED;
	}
	else
	{
		CAMERA_SPEED = CAR_SPEED;
	}

	if (Application::IsKeyPressed(VK_SHIFT))
	{
		boost = true;
	}
	else
	{
		boost = false;
	}

	if (boost)
	{
		CAMERA_SPEED += 20;
	}
	
	if(Application::IsKeyPressed('N') && noclip == true)
	{
		noclip = false;
	}
	else if(Application::IsKeyPressed('N'))
	{
		noclip = true;
	}

	if(Application::IsKeyPressed('W'))
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 zeroTarget = target;
		zeroTarget.y = position.y;
		view = (zeroTarget - position).Normalized();
		position += (view * yaw);
		target += (view * yaw);

		if (current == 1) // Car or trolley update bounds
		{
			static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}
		else if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;

			// Update position for car and trolley
			if (current == 1) // Car or trolley update bounds
			{
				static_cast<CCar*>(_hands[0])->carCamera.position = position;
				static_cast<CCar*>(_hands[0])->carCamera.target = target;
				static_cast<CCar*>(_hands[0])->carCamera.up = up;
				static_cast<CCar*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
			else if (current == 2) // Trolley update bounds
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
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

		if (current == 1) // Car or trolley update bounds
		{
			static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}
		else if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
			// Update position for car and trolley
			if (current == 1) // Car or trolley update bounds
			{
				static_cast<CCar*>(_hands[0])->carCamera.position = position;
				static_cast<CCar*>(_hands[0])->carCamera.target = target;
				static_cast<CCar*>(_hands[0])->carCamera.up = up;
				static_cast<CCar*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
			else if (current == 2) // Trolley update bounds
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
	}

	if(Application::IsKeyPressed('A') && current != 1)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
			// Update position for trolley
			if (current == 2) // Trolley update bounds
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
	}

	if(Application::IsKeyPressed('D') && current != 1)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		view = (target - position).Normalized();
		position += (view.Cross(up) * yaw);
		target += (view.Cross(up) * yaw);

		if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
			// Update position for trolley
			if (current == 2) // Trolley update bounds
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
	}

	if(Application::IsKeyPressed(VK_SPACE) && current == 0 && noclip == true)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		target += (position - newUp).Normalized() * yaw;
		position += (position - newUp).Normalized() * yaw;

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed(VK_SPACE) && current == 0 && noclip == false)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		if(position.y < 35)
		{
			target += (position - newUp).Normalized() * yaw;
			position += (position - newUp).Normalized() * yaw;
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed(VK_CONTROL) && current == 0)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		if(position.y > 20)
		{
			position += (position - newUp).Normalized() * yaw;
			target += (position - newUp).Normalized() * yaw;
		}
	}


	if(position.y >= 30 && Application::IsKeyPressed(VK_SPACE) && current == 0)
	{
		isTiptoeing = false;
	}
	else if(position.y >= 30 && current == 0)
	{
		isTiptoeing = true;
	}
	if(isTiptoeing == true)
	{
		position.y -= 2;
		target.y -= 2;
	}
	if(position.y <= 30 && Application::IsKeyPressed(VK_CONTROL) && current == 0)
	{
		isCrouching = false;
	}
	else if(position.y < 30 && current == 0)
	{
		isCrouching = true;
	}
	if(isCrouching == true)
	{
		position.y += 2;
		target.y += 2;
	}

	// tilt up
	if(Application::IsKeyPressed(VK_UP) && current != 1)
	{
		Vector3 view = (target - position).Normalized();
		float theta = atan2(view.y,sqrt(view.x * view.x + view.z * view.z ));
		theta = Math::RadianToDegree(theta);

		if(theta < 50)
		{
			float pitch = (float)(ROTATION_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			target = rotation* (target - position) + position;
			
			if (current == 2)
			{
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
			}
		}
	}

	// tilt down
	if(Application::IsKeyPressed(VK_DOWN) && current != 1)
	{
		Vector3 view = (target - position).Normalized();
		float theta = atan2(view.y,sqrt(view.x * view.x + view.z * view.z ));
		theta = Math::RadianToDegree(theta);

		if(theta > -50)
		{
			float pitch = (float)(-ROTATION_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			target = rotation * ( target - position) + position;
			
			if (current == 2)
			{
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
			}
		}
	}

	// tilt left
	if(Application::IsKeyPressed(VK_LEFT))
	{
		Vector3 tempTarget = target, tempPosition = position, tempUp = up;
		float pitch = (float)(ROTATION_SPEED * dt);
		view = (target - position);
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;

		if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
			_hands[0]->setRotateY(_hands[0]->getRotate().y + pitch);
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
			up = tempUp;
			_hands[0]->setRotateY(_hands[0]->getRotate().y - pitch);

			// Set camera for trolley
			if (current == 2)
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
	}

	// tilt right
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		Vector3 tempTarget = target, tempPosition = position, tempUp = up;
		float pitch = (float)(-ROTATION_SPEED * dt);
		view = (target - position);
		rotation.SetToRotation(pitch, 0, 1, 0);
		view = rotation * view;
		target = (position + view);
		up = rotation * up;

		if (current == 2) // Trolley update bounds
		{
			static_cast<CTrolley*>(_hands[0])->camera.position = position;
			static_cast<CTrolley*>(_hands[0])->camera.target = target;
			static_cast<CTrolley*>(_hands[0])->camera.up = up;
			static_cast<CTrolley*>(_hands[0])->updatePosition();
			_hands[0]->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
			_hands[0]->setRotateY(_hands[0]->getRotate().y + pitch);
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
			up = tempUp;
			_hands[0]->setRotateY(_hands[0]->getRotate().y - pitch);

			// Set camera for trolley
			if (current == 2)
			{
				static_cast<CTrolley*>(_hands[0])->camera.position = position;
				static_cast<CTrolley*>(_hands[0])->camera.target = target;
				static_cast<CTrolley*>(_hands[0])->camera.up = up;
				static_cast<CTrolley*>(_hands[0])->updatePosition();
				_hands[0]->calcBound();
			}
		}
	}

	if(Application::IsKeyPressed('R') && current == 0)
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


/******************************************************************************/
/*!
\brief
check for camera's bound and returning if camera has hit anything from any of the objects from objList and objList2
\param &_outerSkyboxMaxBound - 
the maximum value of X and z of the skybox occupy
\param &_outerSkyboxMinBound - 
the minimum value of x and z of the skybox occupy
\param &_objList - 
the list of objects that is on first floor of supermarket in scene
\param **_hands
used to check if player is using car or trolley
\param flooNum - 
which floor the camera is on
\param &_objList2 - 
the list of objects on 2nd floor
*/
/******************************************************************************/
bool Camera3::boundCheck(Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj **_hands, int floorNum, std::vector<CObj*> &_objList2)
{
	std::vector<CObj*> list;
	if (floorNum == 1)
	{
		list = _objList;
	}
	else if (floorNum == 2)
	{
		list = _objList2;
	}

	if (_objList.size() != 0) // Obj & skybox check
	{
		for (int i = 0; i < list.size(); ++i)
		{
			CObj *pObj = list[i];
			if (pObj->getRender())
			{
				if (current == NULL) // Point check
				{
					if	(	// Skybox check
						(position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || 
						// Obj check
						(position.x < pObj->getMaxBound().x && position.x > pObj->getMinBound().x && position.z < pObj->getMaxBound().z && position.z > pObj->getMinBound().z)
						)
					{
						return true;
					}
				}
				else // Car and trolley check
				{
					if (pObj != _hands[0] && pObj->getID() != SP2::GEOMETRY_TYPE::GEO_SUPERMARKET_CEILING)
					{
						if((position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || (minBound.x  < pObj->getMaxBound().x && maxBound.x > pObj->getMinBound().x && minBound.z < pObj->getMaxBound().z && maxBound.z > pObj->getMinBound().z))
						{
							return true;
						}
					}
				}
			}
		}
		return false;
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