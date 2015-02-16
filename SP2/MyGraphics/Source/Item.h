#ifndef ITEM_H
#define ITEM_H

#include "Vector3.h"
#include "Mesh.h"

class CItem
{
public:
	enum ID
	{

	};
	CItem(void);
	CItem(int _itemID, Mesh *_item, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _maxBound, Vector3 _minBound, Vector3 _interactMaxBound, Vector3 _interactMinBound, Vector3 _itemSize);
	~CItem(void);

	Vector3 getTranslate(), getRotate(), getScale(), getMaxBound(), getMinBound(), getInteractMaxBound(), getInteractMinBound(), getItemSize();
	Mesh *getItem();
	int getItemID();

private:
	int itemID;
	Mesh *item;
	Vector3 translate, rotate, scale;
	Vector3 maxBound, minBound, interactMaxBound, interactMinBound;
	Vector3 itemSize;
};

#endif