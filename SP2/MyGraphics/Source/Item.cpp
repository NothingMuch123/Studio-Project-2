#include "Item.h"


CItem::CItem(void) : item(0)
{
}

CItem::CItem(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, Mesh *_item) : item(_item), CObj(_ID, _translate, _rotate, _scale, _size)
{

}

CItem::~CItem(void)
{
}

Mesh *CItem::getItem()
{
	return item;
}

void CItem::calcBound()
{
	float offset = 0;
	maxBound.Set(((size.x * scale.x) / 2) + translate.x + offset, ((size.y * scale.y) / 2) + translate.y + offset, ((size.z * scale.z) / 2) + translate.z + offset);
	minBound.Set(((size.x * scale.x) / 2) - translate.x - offset, ((size.y * scale.y) / 2) - translate.y - offset, ((size.z * scale.z) / 2) - translate.z - offset);
	//interactMaxBound.Set(((size.x * scale.x) / 2) + translate.x + offset, ((size.y * scale.y) / 2) + translate.y + offset, ((size.z * scale.z) / 2) + translate.z + offset);
	//interactMinBound.Set(((size.x * scale.x) / 2) - translate.x - offset, ((size.y * scale.y) / 2) - translate.y - offset, ((size.z * scale.z) / 2) - translate.z - offset);
}