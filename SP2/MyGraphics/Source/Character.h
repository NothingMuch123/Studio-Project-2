#ifndef CHARACTER_H
#define CHARACTER_H

#include "Obj.h"
#include "Camera3.h"
#include <vector>
#include "Mesh.h"
#include <string.h>

using std::string;
using std::vector;

class CCharacter : public CObj
{
private:

	bool IsControlled;

	bool InteractionBound;

	string Script;

	Mesh *Character;

	int Role;

public:

	CCharacter(void);

	void setIsControlled(bool Choice);
	bool getIsControlled();

	void setRole(int Role);
	int getRole();
	
	void setInteractionBound(Vector3 Position,int Radius);//calculate when user is in range to interact and how big the radius of bound would be
	bool getInteractionBound();
	
	void setScript(string Word,bool withinIB);//IB=Interaction Bound
	string getScript();

	Mesh* getCharacter();
		
	virtual void updateChar(bool getIsControlled,double dt);
	
	Camera3 AICamera;

	~CCharacter(void);
	
};

#endif