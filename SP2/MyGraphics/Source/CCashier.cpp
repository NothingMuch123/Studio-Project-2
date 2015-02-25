#include "CCashier.h"

CCashier::CCashier(void) 
{
}

CCashier::CCashier(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size)
{
	this->setRole(1);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}

bool CCashier::InteractionBound(Vector3 Position)
{
	return 0;
}

string CCashier::script(bool getIsControlled)
{
	return "hi";
}

void CCashier::updateChar(bool getIsControlled,double dt)
{
}

CCashier::~CCashier(void)
{
}