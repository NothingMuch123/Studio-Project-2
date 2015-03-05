/******************************************************************************/
/*!
\file	SecurityCamera.h
\author Team 8
\par	
\brief
Header file for SecurityCamera Class
*/
/******************************************************************************/

#pragma once
#include "Obj.h"
#include "Camera3.h"

/******************************************************************************/
/*!
		Class CSecurityCamera:
\brief	Defines Default Values for Security Camera 
*/
/******************************************************************************/

class CSecurityCamera :
	public CObj
{
public:
	CSecurityCamera(void);
	virtual ~CSecurityCamera(void);
	CSecurityCamera(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, Vector3 _target);
	Vector3 getCameraPosition();
	Vector3 getCameraTarget();
	Vector3 getCameraUp();
	Camera3 camera;

};

