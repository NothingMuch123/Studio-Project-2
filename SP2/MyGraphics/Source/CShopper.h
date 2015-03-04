#ifndef CSHOPPER_H
#define CSHOPPER_H

#include "Character.h"

class CShopper : public CCharacter
{
private:

public:

	CShopper(void);
	CShopper(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);
	
	string updateScript();

	void updateChar(bool getIsControlled,double dt);

	~CShopper(void);
};


#endif 