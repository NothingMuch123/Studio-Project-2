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
void CShopper::WalkTo(Vector3 TargetPos)
{
	if(TargetPos.z==this->getTranslate().z)
	{
		if(TargetPos.x>this->getTranslate().x)
		{
			this->setTranslate(Vector3(this->getTranslate().x+0.5,this->getTranslate().y,this->getTranslate().z));
		}
		else if(TargetPos.x<this->getTranslate().x)
		{
			this->setTranslate(Vector3(this->getTranslate().x-0.5,this->getTranslate().y,this->getTranslate().z));
		}
		else
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z));
		}
	}
	else 
	{
		if(TargetPos.z>this->getTranslate().z)
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z+0.5));
		}
		else if(TargetPos.z<this->getTranslate().z)
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z-0.5));
		}
		else
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z));
		}
	}
}

void CShopper::updateChar(bool getIsControlled,double dt)
{
}

CShopper::~CShopper(void)
{
}