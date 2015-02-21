#ifndef CHARACTER_H
#define CHARACTER_H

#include "Obj.h"
#include "Camera3.h"

class CCharacter : public CObj
{
public:
	CCharacter(void);
	virtual ~CCharacter(void);

	void calcBound();
	Camera3 charCamera;
	void updateChar();
};

#endif