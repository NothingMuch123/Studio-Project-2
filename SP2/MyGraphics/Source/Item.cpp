#include "Item.h"

/******************************************************************************/
/*!
\brief
CItem default constructor
*/
/******************************************************************************/
CItem::CItem(void) : item(0)
{
}
/******************************************************************************/
/*!
\brief
CItem overloaded constructor
\param _ID -
ID for items in objList
\param _translate - 
translation for item 
\param _rotate - 
rotation for item
\param _scale -
the scaling of the item
\param _size -
the size of the item model
\parma *_item - 
pointer mesh of the item
*/
/******************************************************************************/
CItem::CItem(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, Mesh *_item) : item(_item), CObj(_ID, _translate, _rotate, _scale, _size)
{

}
/******************************************************************************/
/*!
\brief
CItem deconstructor
*/
/******************************************************************************/
CItem::~CItem(void)
{
}
/******************************************************************************/
/*!
\brief
returns the mesh pointer of item
*/
/******************************************************************************/
Mesh *CItem::getItem()
{
	return item;
}
/******************************************************************************/
/*!
\brief
using the size and scale of item to calculate the max and min bound of item
*/
/******************************************************************************/
void CItem::calcBound()
{
	float offset = 0;
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
}