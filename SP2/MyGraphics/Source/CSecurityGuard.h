#ifndef CSECURITYGUARD_H
#define CSECURITYGUARD_H

#include "Character.h"

class CSecurityGuard : public CCharacter
{
private:

public:
	CSecurityGuard(void);
	CSecurityGuard(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);

	bool InteractionBound(Vector3 Position);

	string script(bool getIsControlled);
	
	void updateChar(bool getIsControlled,double dt);

	~CSecurityGuard(void);
};


#endif 