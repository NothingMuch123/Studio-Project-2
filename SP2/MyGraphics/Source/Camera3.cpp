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
			if (pObj->getID() == SP2::OBJ_ID::OBJ_CAR)
			{
				current = 1;
				maxBound = pObj->getMaxBound();
				minBound = pObj->getMinBound();
				break;
			}
			else if (pObj->getID() == SP2::OBJ_ID::OBJ_TROLLEY)
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

		if (current != 0) // Car or trolley update bounds
		{
			static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
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

		if (current != 0) // Car or trolley update bounds
		{
			static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
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
			/*static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();*/
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
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
			/*static_cast<CCar*>(_hands[0])->carCamera.position = position;
			static_cast<CCar*>(_hands[0])->carCamera.target = target;
			static_cast<CCar*>(_hands[0])->carCamera.up = up;
			static_cast<CCar*>(_hands[0])->updatePosition();
			static_cast<CCar*>(_hands[0])->calcBound();*/
			maxBound = _hands[0]->getMaxBound();
			minBound = _hands[0]->getMinBound();
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed(VK_SPACE) && current != 1 && noclip == true)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		position += (position - newUp).Normalized() * yaw;
		target += (position - newUp).Normalized() * yaw;

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}

	if(Application::IsKeyPressed(VK_SPACE) && current != 1 && noclip == false)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(-CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		if(position.y < 35)
		{
			position += (position - newUp).Normalized() * yaw;
			target += (position - newUp).Normalized() * yaw;
		}

		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}
	


	

	if(Application::IsKeyPressed(VK_CONTROL) && current != 1)
	{
		Vector3 tempTarget = target, tempPosition = position;
		float yaw = (float)(CAMERA_SPEED * dt);
		Vector3 newUp(position.x, position.y + 1, position.z);
		if(position.y > 20)
		{
			position += (position - newUp).Normalized() * yaw;
			target += (position - newUp).Normalized() * yaw;
		}
		if (boundCheck(_outerSkyboxMaxBound, _outerSkyboxMinBound, _objList, _hands, floorNum, _objList2))
		{
			target = tempTarget;
			position = tempPosition;
		}
	}


	if(position.y >= 30 && Application::IsKeyPressed(VK_SPACE))
	{
		isTiptoeing = false;
	}
	else if(position.y >= 30)
	{
		isTiptoeing = true;
	}
	if(isTiptoeing == true)
	{
		position.y -= 2;
		target.y -= 2;
	}
	if(position.y <= 30 && Application::IsKeyPressed(VK_CONTROL))
	{
		isCrouching = false;
	}
	else if(position.y < 30)
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

		if(theta < 80)
		{
			float pitch = (float)(ROTATION_SPEED * dt);
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
	if(Application::IsKeyPressed(VK_DOWN) && current != 1)
	{
		Vector3 view = (target - position).Normalized();
		float theta = atan2(view.y,sqrt(view.x * view.x + view.z * view.z ));
		theta = Math::RadianToDegree(theta);

		if(theta > -80)
		{
			float pitch = (float)(-ROTATION_SPEED * dt);
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

bool Camera3::boundCheck(Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj **_hands, int floorNum, std::vector<CObj*> &_objList2)
{
	Vector3 topLeft(minBound.x, 0, minBound.z), 
			top(minBound.x + ((maxBound.x - minBound.x) / 2), 0, minBound.z), 
			topRight(maxBound.x, 0, minBound.x), 
			left(minBound.x, 0, minBound.z + ((maxBound.z - minBound.z) / 2)), 
			right(maxBound.x, 0, minBound.z + ((maxBound.z - minBound.z) / 2)), 
			bottomLeft(minBound.x, 0, maxBound.z), 
			bottom(minBound.x + ((maxBound.x - minBound.x) / 2), 0, maxBound.z), 
			bottomRight(maxBound.x, 0, maxBound.z);

	switch (floorNum)
	{
	case 1:
		{
			if (_objList.size() != 0) // Obj & skybox check
			{
				for (int i = 0; i < _objList.size(); ++i)
				{
					CObj *pObj = _objList[i];
					if (pObj->getRender())
					{
						if (current == NULL) // Point check
						{
							if	(	// Skybox check
								(position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || /*position.y > _outerSkyboxMaxBound.y || position.y < _outerSkyboxMinBound.y ||*/ position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || 
								// Obj check
								(position.x < pObj->getMaxBound().x && position.x > pObj->getMinBound().x && /*position.y < pObj->getMaxBound().y && position.y > pObj->getMinBound().y &&*/ position.z < pObj->getMaxBound().z && position.z > pObj->getMinBound().z)
								)
							{
								return true;
							}
						}
						else // Car and trolley check
						{
							if (pObj != _hands[0])
							{
								if(
										// Top left
										(topLeft.x < pObj->getMaxBound().x && topLeft.x > pObj->getMinBound().x && topLeft.z < pObj->getMaxBound().z && topLeft.z > pObj->getMinBound().z) ||
										// Top
										(top.x < pObj->getMaxBound().x && top.x > pObj->getMinBound().x && top.z < pObj->getMaxBound().z && top.z > pObj->getMinBound().z) ||
										// Top right
										(topRight.x < pObj->getMaxBound().x && topRight.x > pObj->getMinBound().x && topRight.z < pObj->getMaxBound().z && topRight.z > pObj->getMinBound().z) ||
										// Left
										(left.x < pObj->getMaxBound().x && left.x > pObj->getMinBound().x && left.z < pObj->getMaxBound().z && left.z > pObj->getMinBound().z) ||
										// Right
										(right.x < pObj->getMaxBound().x && right.x > pObj->getMinBound().x && right.z < pObj->getMaxBound().z && right.z > pObj->getMinBound().z) ||
										// Bottom left
										(bottomLeft.x < pObj->getMaxBound().x && bottomLeft.x > pObj->getMinBound().x && bottomLeft.z < pObj->getMaxBound().z && bottomLeft.z > pObj->getMinBound().z) ||
										// Bottom
										(bottom.x < pObj->getMaxBound().x && bottom.x > pObj->getMinBound().x && bottom.z < pObj->getMaxBound().z && bottom.z > pObj->getMinBound().z) ||
										// Bottom right
										(bottomRight.x < pObj->getMaxBound().x && bottomRight.x > pObj->getMinBound().x && bottomRight.z < pObj->getMaxBound().z && bottomRight.z > pObj->getMinBound().z)
									)
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
	case 2:
		{
			if (_objList2.size() != 0) // Obj & skybox check
			{
				for (int i = 0; i < _objList2.size(); ++i)
				{
					CObj *pObj = _objList2[i];
					if (pObj->getRender())
					{
						if (current == NULL) // Point check
						{
							if	(	// Skybox check
								(position.x > _outerSkyboxMaxBound.x || position.x < _outerSkyboxMinBound.x || /*position.y > _outerSkyboxMaxBound.y || position.y < _outerSkyboxMinBound.y ||*/ position.z > _outerSkyboxMaxBound.z || position.z < _outerSkyboxMinBound.z) || 
								// Obj check
								(position.x < pObj->getMaxBound().x && position.x > pObj->getMinBound().x && /*position.y < pObj->getMaxBound().y && position.y > pObj->getMinBound().y &&*/ position.z < pObj->getMaxBound().z && position.z > pObj->getMinBound().z)
								)
							{
								return true;
							}
						}
						else // Car and trolley check
						{
							if (pObj != _hands[0])
							{
								if(
										// Top left
										(topLeft.x < pObj->getMaxBound().x && topLeft.x > pObj->getMinBound().x && topLeft.z < pObj->getMaxBound().z && topLeft.z > pObj->getMinBound().z) ||
										// Top
										(top.x < pObj->getMaxBound().x && top.x > pObj->getMinBound().x && top.z < pObj->getMaxBound().z && top.z > pObj->getMinBound().z) ||
										// Top right
										(topRight.x < pObj->getMaxBound().x && topRight.x > pObj->getMinBound().x && topRight.z < pObj->getMaxBound().z && topRight.z > pObj->getMinBound().z) ||
										// Left
										(left.x < pObj->getMaxBound().x && left.x > pObj->getMinBound().x && left.z < pObj->getMaxBound().z && left.z > pObj->getMinBound().z) ||
										// Right
										(right.x < pObj->getMaxBound().x && right.x > pObj->getMinBound().x && right.z < pObj->getMaxBound().z && right.z > pObj->getMinBound().z) ||
										// Bottom left
										(bottomLeft.x < pObj->getMaxBound().x && bottomLeft.x > pObj->getMinBound().x && bottomLeft.z < pObj->getMaxBound().z && bottomLeft.z > pObj->getMinBound().z) ||
										// Bottom
										(bottom.x < pObj->getMaxBound().x && bottom.x > pObj->getMinBound().x && bottom.z < pObj->getMaxBound().z && bottom.z > pObj->getMinBound().z) ||
										// Bottom right
										(bottomRight.x < pObj->getMaxBound().x && bottomRight.x > pObj->getMinBound().x && bottomRight.z < pObj->getMaxBound().z && bottomRight.z > pObj->getMinBound().z)
									)
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
	}
}