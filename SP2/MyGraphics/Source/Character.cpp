#include "Character.h"


CCharacter::CCharacter(void)
{
}

void CCharacter::setIsControlled(bool Choice)
{
	this-> IsControlled = Choice;
}

void CCharacter::setRole(int Role)
{
	this-> Role = Role;
}
Mesh* CCharacter::getCharacter()
{
	return Character;
}
bool CCharacter::getIsControlled()
{
	return this->IsControlled;
}
int CCharacter::getRole()
{
	return Role;
}
bool CCharacter::InteractionBound(bool getIsControlled,Vector3 Position)//calculate when user is in range to interact
{
	return false;
}
string CCharacter::script(bool getIsControlled)
{
	return "a";
}
void CCharacter::updateChar(bool getIsControlled,double dt)
{
}

CCharacter::~CCharacter(void)
{
}
//void CCharacter::calcBound()
//{
//	float offset = 5;
//	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
//	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
//}