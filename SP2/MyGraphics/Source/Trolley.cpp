#include "Trolley.h"

/******************************************************************************/
/*!
\brief
CTrolley default constructor.
*/
/******************************************************************************/
CTrolley::CTrolley(void)
{
}

/******************************************************************************/
/*!
\brief
CTrolley overloaded constructor.
*/
/******************************************************************************/
CTrolley::CTrolley(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size) : CObj(_ID, _translate, _rotate, _scale, _size)
{
}

/******************************************************************************/
/*!
\brief
CTrolley destructor.
*/
/******************************************************************************/
CTrolley::~CTrolley(void)
{
}

/******************************************************************************/
/*!
\brief
Set camera for trolley during init stage
*/
/******************************************************************************/
void CTrolley::setCamera()
{
	Vector3 reverseDirection = (translate - (translate-Vector3(0,0,-1))).Normalized();
	camera.position = translate - (reverseDirection * (((scale.z * size.z) / 2) + 10));
	camera.position.y += 30;
	camera.target = camera.position + Vector3(0,0,-15);//(reverseDirection * (((scale.z * size.z) / 2) - 4));
	camera.up = Vector3(0,1,0);
}

/******************************************************************************/
/*!
\brief
Update trolley's position based on where the new camera position is
*/
/******************************************************************************/
void CTrolley::updatePosition()
{
	Vector3 cameraYTarget(camera.target);
	cameraYTarget.y = camera.position.y;
	Vector3 direction = (camera.position - cameraYTarget).Normalized();
	translate = camera.position - (direction * (((scale.z * size.z) / 2) + 10));
	translate.y -= 30;
}

/******************************************************************************/
/*!
\brief
Calculate bound with translate, size and scale
*/
/******************************************************************************/
void CTrolley::calcBound()
{
	float offset = 3;
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
}