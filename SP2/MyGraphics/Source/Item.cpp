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
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
}