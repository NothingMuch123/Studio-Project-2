#include "SecurityCamera.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CSecurityCamera::CSecurityCamera(void) 
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
CSecurityCamera::~CSecurityCamera(void)
{
}

/******************************************************************************/
/*!
\brief
Overloaded constructor
*/
/******************************************************************************/
CSecurityCamera::CSecurityCamera(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, Vector3 _target) : CObj(_ID, _translate , _rotate , _scale, _size)
{
	camera.position = _translate;
	camera.target = _target;
	camera.up = Vector3 (0,1,0);
}
