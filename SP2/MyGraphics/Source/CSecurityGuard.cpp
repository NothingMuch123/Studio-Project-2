#include "CSecurityGuard.h"

CSecurityGuard::CSecurityGuard(void)
{
	
}

CSecurityGuard::CSecurityGuard(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size)
{
	this->setRole(2);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}

bool CSecurityGuard::InteractionBound(Vector3 Position)
{
	return 0;
}

string CSecurityGuard::script(bool getIsControlled)
{
	return "hi";
}

void CSecurityGuard::updateChar(bool getIsControlled,double dt)
{
}

CSecurityGuard::~CSecurityGuard(void)
{
}