#include "Character.h"
#include "SP2.h"

CCharacter::CCharacter(void)
{
	this->setMoveIsMax(false);
	this->setMovement(0);
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
void CCharacter::setScript(int choice)
{
	this->Script = choice;
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

int CCharacter::getScript()
{
	return this->getScript();
}

string CCharacter::updateScript()
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
	if(TargetPos.x==this->getTranslate().x)
	{
		if(TargetPos.z>this->getTranslate().z)
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z+0.5));
			this->setRotateY(0);
		}
		else if(TargetPos.z<this->getTranslate().z)
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z-0.5));
			this->setRotateY(180);
		}
		else
		{
			this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z));
		}
	}
	else 
	{
		if(TargetPos.x>this->getTranslate().x)
		{
			this->setTranslate(Vector3(this->getTranslate().x+0.5,this->getTranslate().y,this->getTranslate().z));
			this->setRotateY(90);
		}
		else if(TargetPos.x<this->getTranslate().x)
		{
			this->setTranslate(Vector3(this->getTranslate().x-0.5,this->getTranslate().y,this->getTranslate().z));
			this->setRotateY(-90);
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