#ifndef CCASHIER_H
#define CASHIER_H

#include "Character.h"

class CCashier : public CCharacter
{
private:

public:
	CCashier(void);
	CCashier(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);

	bool InteractionBound(Vector3 Position);

	string script(bool getIsControlled);
	
	void updateChar(bool getIsControlled,double dt);

	~CCashier(void);
};


#endif 