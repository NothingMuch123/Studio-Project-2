#ifndef CAR_H
#define CAR_H

#include "Obj.h"
#include "Camera3.h"

class CCar : public CObj
{
public:
	CCar(void);
	CCar(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);
	~CCar(void);
	Camera3 carCamera;
	virtual void calcBound();
	void setCamera();
};

#endif