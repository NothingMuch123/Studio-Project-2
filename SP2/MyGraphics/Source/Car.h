/******************************************************************************/
/*!
\file	Car.h
\author Team 8
\par	
\brief
Header file for car class
*/
/******************************************************************************/
#ifndef CAR_H
#define CAR_H

#include "Obj.h"
#include "Camera3.h"

/******************************************************************************/
/*!
	Class: Car
\brief Defines the default values of the Car's properties (position, target, up, view) and its various function (calcbound, setCamera, updatePosition).
*/
/******************************************************************************/

class CCar : public CObj
{
public:
	CCar(void);
	CCar(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);
	~CCar(void);
	virtual void calcBound();
	void setCamera();
	void updatePosition();
	Camera3 carCamera;
};

#endif