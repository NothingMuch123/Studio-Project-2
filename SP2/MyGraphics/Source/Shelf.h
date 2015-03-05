/******************************************************************************/
/*!
\file	Shelf.h
\author Team 8
\par	
\brief
Header file for Shelf Class
*/
/******************************************************************************/

#ifndef SHELF_H
#define SHELF_H

#include "Obj.h"
#include "Item.h"
#include <vector>

/******************************************************************************/
/*!
		Class CShelf:
\brief	Defines Default Values for Shelf
*/
/******************************************************************************/

class CShelf : public CObj
{
public:
	CShelf(void);
	CShelf(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, int _limit);
	virtual ~CShelf(void);
	std::vector<CItem*> itemList;
	std::vector<Vector3> itemPosition;
	int limit;
	virtual void calcBound();
};

#endif