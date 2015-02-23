#ifndef ITEM_H
#define ITEM_H

#include "Obj.h"
#include "Mesh.h"

class CItem : public CObj
{
public:

	CItem(void);
	CItem(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, Mesh *_item);
	virtual ~CItem(void);

	Mesh *getItem();
	virtual void calcBound();

private:
	Mesh *item;
};

#endif