#ifndef CSECURITYGUARD_H
#define CSECURITYGUARD_H

#include "Character.h"
/******************************************************************************/
/*!
	Class CSecurityGuard:
\brief
Defines string
(updateScript)
*/
/******************************************************************************/
class CSecurityGuard : public CCharacter
{
private:

public:
	CSecurityGuard(void);
	CSecurityGuard(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);
	string updateScript();
	~CSecurityGuard(void);
};


#endif 