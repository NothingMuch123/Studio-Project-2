#ifndef SHELF_H
#define SHELF_H

#include "Obj.h"
#include "Item.h"
#include <vector>

class CShelf : public CObj
{
public:
	CShelf(void);
	CShelf(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size, int _limit);
	virtual ~CShelf(void);
	std::vector<CItem*> itemList;
	int limit;
	virtual void calcBound();
};

#endif