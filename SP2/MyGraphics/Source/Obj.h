/******************************************************************************/
/*!
\file	Obj.h
\author Team 8
\par	
\brief
Header file for Obj Class
*/
/******************************************************************************/
#ifndef OBJ_H
#define OBJ_H

#include "Vector3.h"

/******************************************************************************/
/*!
		Class CObj:
\brief	Stores Item Data 
*/
/******************************************************************************/

class CObj
{
public:
	CObj(void);
	CObj(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);
	Vector3 getTranslate(), getRotate(), getScale(), getMaxBound(), getMinBound()/*, getInteractMaxBound(), getInteractMinBound()*/, getSize();
	int getID();
	bool getRender();
	void setRender(bool _render);
	void setRotateY(float _rotateY);
	void setTranslateX(float _translateX);
	void setTranslate(Vector3 _translate);

	virtual void calcBound();
	virtual ~CObj(void);
protected:
	int ID;
	Vector3 translate, rotate, scale;
	Vector3 maxBound, minBound; //, interactMaxBound, interactMinBound;
	Vector3 size;
	bool render;
};

#endif