/******************************************************************************/
/*!
\file	Character.h
\author Team 8
\par	
\brief
Header file for Character Class
*/
/******************************************************************************/
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Obj.h"
#include "Camera3.h"
#include <vector>
#include "Mesh.h"
#include <string.h>

using std::string;
using std::vector;

/******************************************************************************/
/*!
	Class: CCharacter

\brief 
Defines default values of CCharacter's properties, 
(IsControlled, InteractionBound, Script, Role, moveX, moveZ, RouteID, MoveIsMax, Movement)

Functions,
(setMoveIsMax, getMoveIsMax, setMovement, getMovement, updateMovement, setIsControlled, getIsControlled, setRole, getRole, setInteractionBound, getInteractionBound, setScript, getScript, updateScript, setmoveX, getmoveX, setmoveZ, setRouteID, getRouteID, getCharacter, updateChar, WalkTo)

Vector
(AiRouteLocation)
*/
/******************************************************************************/

class CCharacter : public CObj
{
private:

	bool IsControlled;

	bool InteractionBound;

	int Script;

	Mesh *Character;

	int Role,moveX,moveZ,RouteID;

	bool MoveIsMax;

	int Movement;

public:

	void setMoveIsMax(bool MoveIsMax);
	bool getMoveIsMax();

	void setMovement(int Movement);
	int getMovement();

	void UpdateMovement(int Max);// the max angle the limbs can rotate up to

	vector <Vector3> AiRouteLocation;

	CCharacter(void);

	void setIsControlled(bool Choice);
	bool getIsControlled();

	void setRole(int Role);
	int getRole();
	
	void setInteractionBound(Vector3 Position,int Radius);//calculate when user is in range to interact and how big the radius of bound would be
	bool getInteractionBound();
	
	void setScript(int choice);//IB=Interaction Bound
	int getScript();
	virtual string updateScript();

	void setmoveX(int moveX);
	int getmoveX();

	void setmoveZ(int moveZ);
	int getmoveZ();

	void setRouteID(int RouteID);
	int getRouteID();

	Mesh* getCharacter();
		
	virtual void updateChar(bool getIsControlled,double dt);
	
	void WalkTo(Vector3 TargetPosition, std::vector<CObj*> _objList);

	Camera3 AICamera;

	~CCharacter(void);
	
};

#endif