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
			string temp("Do not attempt to steal!");
			return temp;
		}
	case 2:
		{
			string temp("Stay safe around these parts");
			return temp;
		}
	case 3:
		{
			string temp("Oh I used to love shopping, then I grew up. You don't wanna do that.");
			return temp;
		}
	case 4:
		{
			string temp("Either THROW THAT BAG OF WEED AWAY, or share some with me");
			return temp;
		}
	case 5:
		{
			string temp("You're really nothing special arent you?");
			return temp;
		}
	case 6:
		{
			string temp("Oh i wish I could Time travel");
			return temp;
		}
	case 7:
		{
			string temp("*walkie-talkie crackles*");
			return temp;
		}
	case 8:
		{
			string temp("There are a string of murders in this town, it started last month");
			return temp;
		}
	case 9:
		{
			string temp("Don't stay out late at night");
			return temp;
		}
	case 10:
		{
			string temp("Nice erm, arms you have");
			return temp;
		}
	
	}
}
/*
void CSecurityGuard::updateChar(bool getIsControlled,double dt)
{
}
*/

CSecurityGuard::~CSecurityGuard(void)
{
}