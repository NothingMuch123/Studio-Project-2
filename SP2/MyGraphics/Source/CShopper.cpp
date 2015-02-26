#include "CShopper.h"


CShopper::CShopper(void)
{
	
}

CShopper::CShopper(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius)
{
	this->setInteractionBound(camPosition,radius);
	this->setRole(3);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}

void CShopper::updateChar(bool getIsControlled,double dt)
{
}

CShopper::~CShopper(void)
{
}