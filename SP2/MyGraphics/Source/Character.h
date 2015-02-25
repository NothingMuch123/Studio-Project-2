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
	Mesh *Character;
	int Role;
	bool IsControlled;
public:
	CCharacter(void);


	void setIsControlled(bool Choice);
	void setRole(int Role);


	Mesh* getCharacter();
	bool getIsControlled();
	int getRole();

	virtual bool InteractionBound(bool getIsControlled,Vector3 Position);//calculate when user is in range to interact
	virtual string script(bool getIsControlled);
	virtual void updateChar(bool getIsControlled,double dt);

	Camera3 charCamera;
	
	~CCharacter(void);
	
};

#endif