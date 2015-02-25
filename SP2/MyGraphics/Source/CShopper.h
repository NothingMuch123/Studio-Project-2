#ifndef CSHOPPER_H
#define CSHOPPER_H

#include "Character.h"

class CShopper : public CCharacter
{
private:

public:
	CShopper(void);
	CShopper(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size);

	bool InteractionBound(Vector3 Position);

	string script(bool getIsControlled);
	
	void updateChar(bool getIsControlled,double dt);

	~CShopper(void);
};


#endif 