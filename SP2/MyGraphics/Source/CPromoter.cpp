#include "CPromoter.h"

CPromoter::CPromoter(void) 
{
}

CPromoter::CPromoter(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius)
{
	this -> setInteractionBound(camPosition, radius);
	this->setRole(4);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}

bool CPromoter::InteractionBound(Vector3 Position)
{
	return 0;
}

string CPromoter::script(bool getIsControlled)
{
	return "hi";
}

void CPromoter::updateChar(bool getIsControlled,double dt)
{
}

CPromoter::~CPromoter(void)
{
}