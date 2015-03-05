#include "Character.h"
#include "SP2.h"
/******************************************************************************/
/*!
\brief
CCharacter default constructor.
*/
/******************************************************************************/
CCharacter::CCharacter(void)
{
	this->setMoveIsMax(false);
	this->setMovement(0);
	this->IsControlled = false;
}
/******************************************************************************/
/*!
\brief
setting if legs can continue to move
/param MoveIsMax - 
check if can continue to move
*/
/******************************************************************************/
void CCharacter::setMoveIsMax(bool MoveIsMax)
{
	this->MoveIsMax = MoveIsMax;
}
/******************************************************************************/
/*!
\brief
return bool if cannot continue to move
*/
/******************************************************************************/
bool CCharacter::getMoveIsMax()
{
	return this->MoveIsMax;
}
/******************************************************************************/
/*!
\brief
set movement of NPC movement leg
\param Movement - 
see if moving
*/
/******************************************************************************/
void CCharacter::setMovement(int Movement)
{
	this->Movement = Movement;
}
/******************************************************************************/
/*!
\brief
return movement of NPC leg
*/
/******************************************************************************/
int CCharacter::getMovement()
{
	return this->Movement;
}
/******************************************************************************/
/*!
\brief
update movement of NPC leg
\param Max - 
check if leg has hit max angle
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
return coordinates for the NPC to move to 
\param WalkToLocationd - 
give NPC the coordinates to walk to 
*/
/******************************************************************************/
Vector3 WalkTo(Vector3 WalkToLocation)
{
return WalkToLocation;
}
/******************************************************************************/
/*!
\brief
Set role of the NPC 
\param Role
using int to set roles
*/
/******************************************************************************/
void CCharacter::setRole(int Role)
{
	this-> Role = Role;
}
/******************************************************************************/
/*!
\brief
creates interaction bounds for NPC using NPC position and radius 
\param Position - 
position of the NPC
\param Radius - 
the radius of the interaction bound from the NPC position
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
sets the script of the NPC
\param Position - 
choice set which script the NPC is reading off
*/
/******************************************************************************/
void CCharacter::setScript(int choice)
{
	this->Script = choice;
}
/******************************************************************************/
/*!
\brief
returns if camera is in interaction bounds for NPC
*/
/******************************************************************************/
bool CCharacter::getInteractionBound()
{
	return InteractionBound;
}
/******************************************************************************/
/*!
\brief
return character mesh pointer
*/
/******************************************************************************/
Mesh* CCharacter::getCharacter()
{
	return Character;
}
/******************************************************************************/
/*!
\brief
return the role of the NPC
*/
/******************************************************************************/
int CCharacter::getRole()
{
	return Role;
}
/******************************************************************************/
/*!
\brief
return the script phrases
*/
/******************************************************************************/
int CCharacter::getScript()
{
	return this->Script;
}
/******************************************************************************/
/*!
\brief
updates and change the script
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
make the NPC move along the x aixs
\param moveX - 
amount of x units to move 
*/
/******************************************************************************/
void CCharacter::setmoveX(int moveX)
{
	this->moveX = moveX;
}
/******************************************************************************/
/*!
\brief
returns the number of units to move along X
*/
/******************************************************************************/
int CCharacter::getmoveX()
{
	return moveX;
}
/******************************************************************************/
/*!
\brief
make the NPC move along the z aixs
\param moveZ - 
amount of z units to move 
*/
/******************************************************************************/
void CCharacter::setmoveZ(int moveZ)
{
	this->moveZ = moveZ;
}
/******************************************************************************/
/*!
\brief
returns the number of units to move along X
*/
/******************************************************************************/
int CCharacter::getmoveZ()
{
	return moveZ;
}
/******************************************************************************/
/*!
\brief
Sets the route for NPC
\param RouteID - 
the points of interest to the NPC
*/
/******************************************************************************/
void CCharacter::setRouteID(int RouteID)
{
	this->RouteID = RouteID;
}
/******************************************************************************/
/*!
\brief
returns points of interest
*/
/******************************************************************************/
int CCharacter::getRouteID()
{
	return RouteID;
}
/******************************************************************************/
/*!
\brief
CCharacter deconstructor
*/
/******************************************************************************/
CCharacter::~CCharacter(void)
{
}
/******************************************************************************/
/*!
\brief
makes the NPC move towards the target locations
\param TargetPos - 
the target the NPC is moving towards
\param _objList - 
the objects on the first floor 
*/
/******************************************************************************/
void CCharacter::WalkTo(Vector3 TargetPos, std::vector<CObj*> _objList)
{
	Vector3 tempPosition = getTranslate();
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

			/*this->setTranslate(Vector3(this->getTranslate().x,this->getTranslate().y,this->getTranslate().z));

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
			}*/
		}
	}
	
	// Calculate new bound after moving
	calcBound();
	CObj *pObj;
	if (_objList.size() != 0)
	{
		for (int i = 0; i < _objList.size(); ++i)
		{
			pObj = _objList[i];
			if (minBound.x  < pObj->getMaxBound().x && maxBound.x > pObj->getMinBound().x && minBound.z < pObj->getMaxBound().z && maxBound.z > pObj->getMinBound().z && pObj->getID() == SP2::GEOMETRY_TYPE::GEO_TROLLEY)
			{
				setTranslate(tempPosition);
				calcBound();
				break;
			}
		}
	}
}