#include "Shelf.h"

/******************************************************************************/
/*!
\brief
Default constructor
*/
/******************************************************************************/
CShelf::CShelf(void) : limit(0)
{
}

/******************************************************************************/
/*!
\brief
Overloaded constructor
*/
/******************************************************************************/
CShelf::CShelf(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, int _limit) : limit(_limit), CObj(_ID, _translate, _rotate, _scale, _size)
{
}

/******************************************************************************/
/*!
\brief
Destructor
*/
/******************************************************************************/
CShelf::~CShelf(void)
{
}

/******************************************************************************/
/*!
\brief
Calculate bounds based on translate, size and scale
*/
/******************************************************************************/
void CShelf::calcBound()
{
	float offset = 0;
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
}