#include "Item.h"


CItem::CItem(void) : itemID(-1), item(0), translate(0, 0, 0), rotate(0, 0, 0), scale(0, 0, 0), maxBound(0, 0, 0), minBound(0, 0, 0), interactMaxBound(0, 0, 0), interactMinBound(0, 0, 0), itemSize(0, 0, 0)
{
}

CItem::CItem(int _itemID, Mesh *_item, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _maxBound, Vector3 _minBound, Vector3 _interactMaxBound, Vector3 _interactMinBound, Vector3 _itemSize) : itemID(_itemID), item(_item), translate(_translate), rotate(_rotate), scale(_scale), maxBound(_maxBound), minBound(_minBound), interactMaxBound(_interactMaxBound), interactMinBound(_interactMinBound), itemSize(_itemSize)
{
}

CItem::~CItem(void)
{
}

Vector3 CItem::getTranslate()
{
	return translate;
}

Vector3 CItem::getRotate()
{
	return rotate;
}

Vector3 CItem::getScale()
{
	return scale;
}

Vector3 CItem::getMaxBound()
{
	return maxBound;
}

Vector3 CItem::getMinBound()
{
	return minBound;
}

Vector3 CItem::getInteractMaxBound()
{
	return interactMaxBound;
}

Vector3 CItem::getInteractMinBound()
{
	return interactMinBound;
}

Vector3 CItem::getItemSize()
{
	return itemSize;
}

Mesh *CItem::getItem()
{
	return item;
}

int CItem::getItemID()
{
	return itemID;
}