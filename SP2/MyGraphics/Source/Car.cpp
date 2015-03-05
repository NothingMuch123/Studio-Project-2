#include "Car.h"

/******************************************************************************/
/*!
\brief
CCar default constructor.
*/
/******************************************************************************/
CCar::CCar(void)
{
}

/******************************************************************************/
/*!
\brief
CCar overloaded constructor.
\param _ID - 
car ID 
\param _translate - 
Sets the translation of the car
\param _rotate - 
Set the rotation of the car
\param _scale - 
Set the scale of the car
\param _size - 
The size of the object car model
*/
/******************************************************************************/
CCar::CCar(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size) : CObj(_ID, _translate, _rotate, _scale, _size)
{
}

/******************************************************************************/
/*!
\brief
CCar destructor.
*/
/******************************************************************************/
CCar::~CCar(void)
{
}

/******************************************************************************/
/*!
\brief
Calculates bound based on translate, scale and size
*/
/******************************************************************************/
void CCar::calcBound()
{
	float offset = 5;
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
}

/******************************************************************************/
/*!
\brief
Sets values for camera for position and target when entered car
*/
/******************************************************************************/
void CCar::setCamera()
{
	carCamera.position = translate;
	carCamera.position.y += 30;
	carCamera.target = carCamera.position;
	carCamera.target.x += 15;
	carCamera.up.Set(0, 1, 0);
}

/******************************************************************************/
/*!
\brief
Update position based on car's camera
*/
/******************************************************************************/
void CCar::updatePosition()
{
	translate = carCamera.position;
	translate.y -= 30;
}