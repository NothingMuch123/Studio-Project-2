/******************************************************************************/
/*!
\file	CCashier.h
\author Team 8
\par	
\brief
Header file for Cashier Class
*/
/******************************************************************************/
#ifndef CCASHIER_H
#define CASHIER_H

#include "Character.h"

/******************************************************************************/
/*!
	Class CCashier:
\brief
Defines functions
(updateScript)
*/
/******************************************************************************/
class CCashier : public CCharacter
{
private:
	
public:
	CCashier(void);
	CCashier(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);

	string updateScript();

	//void setScript(int choice); //IB=InteractionBound   1:Ai or User 2:Word to Pass In
	
	//void updateChar(bool getIsControlled,double dt);

	~CCashier(void);
};


#endif