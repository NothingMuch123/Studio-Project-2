/******************************************************************************/
/*!
\file	Camera3.h
\author Koh Fang Shu
\par	
\brief
Header file for Camera3 Class. First person camera
*/
/******************************************************************************/
#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"
#include "Mtx44.h"
#include <vector>
#include "Obj.h"

/******************************************************************************/
/*!
		Class Camera3:
\brief	Defines the default values of the Camera's properties (position, target, up, view) and its various states (Init, Update, Reset).
*/
/******************************************************************************/
class Camera3 : public Camera
{
public:
	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 defaultView;

	Mtx44 rotation;
	int current; // 0 - Nothing | 1 - Car | 2 - Trolley
	Vector3 maxBound, minBound;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt, Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj **_hands, int floorNum, std::vector<CObj*> &_objList2);
	virtual void Reset();
	bool boundCheck(Vector3 &_outerSkyboxMaxBound, Vector3 &_outerSkyboxMinBound, std::vector<CObj*> &_objList, CObj **_hands, int floorNum, std::vector<CObj*> &_objList2);
};

#endif