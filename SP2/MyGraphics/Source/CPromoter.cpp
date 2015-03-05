#include "CPromoter.h"

/******************************************************************************/
/*!
\brief
CPromoter default constructor
*/
/******************************************************************************/
CPromoter::CPromoter(void) 
{
}
/******************************************************************************/
/*!
\brief
CPromoter overloaded constructror
\param _ID
ID for human in objList
\param _translate - 
translation of CPromoter
\param _rotate - 
rotation of promoter
\param _scale - 
scale of promoter
\param _size - 
the size of human object model
\parma camPosition -
camera position from promoter
\param radius - 
the radius of the interaction bound for Promoter NPC
*/
/******************************************************************************/
CPromoter::CPromoter(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius)
{
	this -> setInteractionBound(camPosition, radius);
	this->setRole(4);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}
/******************************************************************************/
/*!
\brief
returns if camera is within interaction bound of promoter
\param Position - 
the position of the NPC
*/
/******************************************************************************/
bool CPromoter::InteractionBound(Vector3 Position)
{
	return 0;
}
/******************************************************************************/
/*!
\brief
returns the new script for the promoter NPC
*/
/******************************************************************************/
string CPromoter::updateScript()
{
	switch(this->getScript())
	{
	case 1:
		{
			string temp("Hi There!");
			return temp;
		}
	case 2:
		{
			string temp("Can i interest you in any items?");
			return temp;
		}
	case 3:
		{
			string temp("Perhaps you would like to look at this radio?");
			return temp;
		}
	case 4:
		{
			string temp("Perhaps you would like to look at this Iron?");
			return temp;
		}
	case 5:
		{
			string temp("Perhaps you would like to look at this Can of Beans?");
			return temp;
		}
	case 6:
		{
			string temp("How would you like to look at these knives?");
			return temp;
		}
	case 7:
		{
			string temp("The Knives just came in from Germany, very sharp, swift and clean cuts, especially to meat");
			return temp;
		}
	case 8:
		{
			string temp("*expertly flips knife");
			return temp;
		}
	case 9:
		{
			string temp("*skillfully flips fedora");
			return temp;
		}
	case 10:
		{
			string temp("This knife cut meat faster than paper cut you!");
			return temp;
		}
	
	}
}
/******************************************************************************/
/*!
\brief
CPromoter deconstructor
*/
/******************************************************************************/
CPromoter::~CPromoter(void)
{
}