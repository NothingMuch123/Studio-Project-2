#include "CCashier.h"

/******************************************************************************/
/*!
\brief
CCashier constructor
*/
/******************************************************************************/
CCashier::CCashier(void) 
{
}
/******************************************************************************/
/*!
\brief
CCashier overloaded constructor.
*/
/******************************************************************************/
CCashier::CCashier(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius)
{
	this-> setInteractionBound(camPosition,radius);
	this-> setRole(1);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}
/******************************************************************************/
/*!
\brief
updates and chooses which script is suppose to return
*/
/******************************************************************************/
string CCashier::updateScript()
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
			string temp("Can i have your Items?");
			return temp;
		}
	case 3:
		{
			string temp("That would be $420 Sir");
			return temp;
		}
	case 4:
		{
			string temp("Would you like some of our homegrown weed?");
			return temp;
		}
	case 5:
		{
			string temp("You must be under 18 to buy Cigarettes!");
			return temp;
		}
	case 6:
		{
			string temp("Do you want to build a Meshman?");
			return temp;
		}
	case 7:
		{
			string temp("I used to be a shopper like you, then i took an arrow to the wallet");
			return temp;
		}
	case 8:
		{
			string temp("Everything used to be peaceful around here, until the Great Singapore Sale attacked");
			return temp;
		}
	case 9:
		{
			string temp("I started working last month, same as the promoter!");
			return temp;
		}
	case 10:
		{
			string temp("Slicing Meat has a certain.. technique to it, don't you think?");
			return temp;
		}

	}
}
/******************************************************************************/
/*!
\brief
CCar deconstructor.
*/
/******************************************************************************/
CCashier::~CCashier(void)
{
}