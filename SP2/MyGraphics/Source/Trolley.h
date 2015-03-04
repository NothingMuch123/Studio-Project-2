#ifndef TROLLEY_H
#define TROLLEY_H

#include "Obj.h"
#include "Camera3.h"
#include "Item.h"
#include "Character.h"

class CTrolley : public CObj
{
public:
	CTrolley(void);
	CTrolley(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);
	virtual ~CTrolley(void);
	void setCamera();
	void updatePosition();
	virtual void calcBound();
	Camera3 camera;
	std::vector<CItem*> itemList;
};

#endif