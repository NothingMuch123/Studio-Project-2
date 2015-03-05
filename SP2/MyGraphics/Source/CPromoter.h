/******************************************************************************/
/*!
\file	CPromoter.h
\author Team 8
\par	
\brief
Header file for CPromoter Class
*/
/******************************************************************************/
#pragma once
#ifndef CPROMOTER_H
#define CPROMOTER

#include "Character.h"

/******************************************************************************/
/*!
	Class CPromoter:
\brief
Defines functions
(updateScript, InteractionBound)
*/
/******************************************************************************/

class CPromoter : public CCharacter
{
private:

public:
	CPromoter(void);
	CPromoter(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius);

	string updateScript();

	bool InteractionBound(Vector3 Position);
	
	//void updateChar(bool getIsControlled,double dt);

	~CPromoter(void);
};


#endif 