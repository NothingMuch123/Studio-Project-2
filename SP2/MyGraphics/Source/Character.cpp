#include "Character.h"


CCharacter::CCharacter(void)
{
	this->IsControlled = false;
}

void CCharacter::setIsControlled(bool Choice)
{
	this-> IsControlled = Choice;
}

void CCharacter::setRole(int Role)
{
	this-> Role = Role;
}

void CCharacter::setInteractionBound(Vector3 Position,int Radius)
{
	if(((this->getTranslate())-Position).Length()<Radius)
	{
		this->InteractionBound = true;
	}
	else
	{
		this->InteractionBound = false;
	}
}
void CCharacter::setScript(string Word,bool withinIB)
{
	if(withinIB = true)
	{
		this->Script = Word;
	}
}
bool CCharacter::getInteractionBound()
{
	return InteractionBound;
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

string CCharacter::getScript()
{
	return Script;
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