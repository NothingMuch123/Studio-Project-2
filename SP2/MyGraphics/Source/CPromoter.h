#pragma once
#ifndef CPROMOTER_H
#define CPROMOTER

#include "Character.h"

class CPromoter : public CCharacter
{
private:

public:
	CPromoter(void);
	CPromoter(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition, int radius);

	bool InteractionBound(Vector3 Position);

	string script(bool getIsControlled);
	
	void updateChar(bool getIsControlled,double dt);

	~CPromoter(void);
};


#endif 