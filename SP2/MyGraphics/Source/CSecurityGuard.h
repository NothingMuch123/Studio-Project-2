#ifndef CSECURITYGUARD_H
#define CSECURITYGUARD_H

#include "Character.h"

class CSecurityGuard : public CCharacter
{
private:

public:
	CSecurityGuard(void);
	CSecurityGuard(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);
	
	void updateChar(bool getIsControlled,double dt);

	~CSecurityGuard(void);
};


#endif 