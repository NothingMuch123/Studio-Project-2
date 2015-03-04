#include "Character.h"
#include "SP2.h"

CCharacter::CCharacter(void)
{
	this->IsControlled = false;
}

void CCharacter::setMoveIsMax(bool MoveIsMax)
{

	this->MoveIsMax = MoveIsMax;
}
bool CCharacter::getMoveIsMax()
{
	return this->MoveIsMax;
}

void CCharacter::setMovement(int Movement)
{
	this->Movement = Movement;
}

int CCharacter::getMovement()
{
	return this->Movement;
}

void CCharacter::UpdateMovement(int Max)
{
	cout<<this->Movement<<endl;
	if(Movement>Max)
	{
		setMoveIsMax(!(getMoveIsMax()));
	}
	if(Movement<-Max)
	{
		setMoveIsMax(!(getMoveIsMax()));
	}
	if(getMoveIsMax()==true)
	{
		int temp = this->getMovement();
		temp+=5;
		setMovement(temp);
	}
	if(getMoveIsMax()==false)
	{
		int temp = this->getMovement();
		temp-=5;
		setMovement(temp);
	}
}


void CCharacter::setIsControlled(bool Choice)
{
	this-> IsControlled = Choice;
}

Vector3 WalkTo(Vector3 WalkToLocation)
{
return WalkToLocation;
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

void CCharacter::setmoveX(int moveX)
{
	this->moveX = moveX;
}
int CCharacter::getmoveX()
{
	return moveX;
}

void CCharacter::setmoveZ(int moveZ)
{
	this->moveZ = moveZ;
}

int CCharacter::getmoveZ()
{
	return moveZ;
}

void CCharacter::setRouteID(int RouteID)
{
	this->RouteID = RouteID;
}

int CCharacter::getRouteID()
{
	return RouteID;
}

CCharacter::~CCharacter(void)
{
}

void CCharacter::WalkTo(Vector3 TargetPos)
{
	if(this->getInteractionBound()==true)
	{

	}
	else
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
}
//void CCharacter::calcBound()
//{
//	float offset = 5;
//	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
//	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, 0, translate.z - ((size.z * scale.z) / 2) - offset);
//}