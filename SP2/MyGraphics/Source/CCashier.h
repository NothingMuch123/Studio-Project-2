#ifndef CCASHIER_H
#define CASHIER_H

#include "Character.h"

class CCashier : public CCharacter
{
private:
	
public:
	CCashier(void);
	CCashier(int _ID,Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size,Vector3 camPosition,int radius);



	void setScript(bool getIsControlled,string Word); //IB=InteractionBound   1:Ai or User 2:Word to Pass In
	
	string getScript();

	void updateChar(bool getIsControlled,double dt);

	~CCashier(void);
};


#endif