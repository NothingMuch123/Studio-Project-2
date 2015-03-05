/******************************************************************************/
/*!
\file	Camera.h
\author Team 8
\par	
\brief
Header file for Cashier Class
*/
/******************************************************************************/
#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Vector3.h"

/******************************************************************************/
/*!
	Class: Camera
\brief Defines the default values of the Camera's properties (position, target, up, view) and its various states (Init, Update, Reset).
*/
/******************************************************************************/

class Camera
{
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;
	Vector3 view;

	Camera();
	~Camera();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Reset();
	virtual void Update(double dt);
};

#endif