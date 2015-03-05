#include "CShopper.h"


CShopper::CShopper(void)
{

}

CShopper::CShopper(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius)
{
	this->setInteractionBound(camPosition,radius);
	this->setRole(3);
	this-> ID = _ID;
	this-> translate = _translate;
	this-> rotate = _rotate;
	this-> scale = _scale;
	this-> size = _size;
}

string CShopper::updateScript()
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
			string temp("What's your name?");
			return temp;
		}
	case 3:
		{
			string temp("OH I WOULD RECCOMMEND GETTING THOSE");
			return temp;
		}
	case 4:
		{
			string temp("Weed around these parts are widely considered the best in the world");
			return temp;
		}
	case 5:
		{
			string temp("I live down the street! How about you?");
			return temp;
		}
	case 6:
		{
			string temp("I have built many Meshmen in my lifetime");
			return temp;
		}
	case 7:
		{
			string temp("I was actually replaced by that cashier a month back, by force");
			return temp;
		}
	case 8:
		{
			string temp("These recent murders, they involve people who were last seen in this supermarket");
			return temp;
		}
	case 9:
		{
			string temp("*phone rings*");
			return temp;
		}
	case 10:
		{
			string temp("I miss civilisation");
			return temp;
		}
	}
}

/*
void CShopper::updateChar(bool getIsControlled,double dt)
{
}
*/
CShopper::~CShopper(void)
{
}