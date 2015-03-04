#include "CSecurityGuard.h"

CSecurityGuard::CSecurityGuard(void)
{
	
}

CSecurityGuard::CSecurityGuard(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius)
{
	this->setInteractionBound(camPosition,radius);
	this->setRole(2);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}
string CSecurityGuard::updateScript()
{
	switch(this->getScript())
	{
	case 1:
		{
			string temp("hi");
			return temp;
		}
	case 2:
		{
			string temp("sup");
			return temp;
		}
	case 3:
		{
		}
	case 4:
		{
		}
	case 5:
		{
		}
	case 6:
		{
		}
	case 7:
		{

		}
	case 8:
		{
		}
	case 9:
		{
		}
	case 10:
		{
		}
	default:
		{
			string temp("Do i know you?...");
			return temp;
		}
	}
}
void CSecurityGuard::updateChar(bool getIsControlled,double dt)
{
}

CSecurityGuard::~CSecurityGuard(void)
{
}