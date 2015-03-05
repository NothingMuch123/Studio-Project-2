/******************************************************************************/
/*!
\file	CShopper.h
\author Team 8
\par	
\brief
Header file for CShopper Class
*/
/******************************************************************************/
#ifndef CSHOPPER_H
#define CSHOPPER_H

#include "Character.h"

/******************************************************************************/
/*!
	Class CShopper:
\brief
Defines string
(updateScript)
*/
/******************************************************************************/

class CShopper : public CCharacter
{
private:

public:

	CShopper(void);
	CShopper(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);
	string updateScript();
	~CShopper(void);
};


#endif 