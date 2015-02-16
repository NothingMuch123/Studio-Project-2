#ifndef OBJ_H
#define OBJ_H

#include "Vector3.h"
#include "Mesh.h"

class CObj
{
public:
	enum SHAPES
	{
		S_CUBE, // Wall
		S_MONSTER,
		S_CHEST,
		S_TROPHY,
	};
	CObj(void);
	CObj(Mesh* _obj, float _translateX, float _translateY, float _translateZ, float _rotateX, float _rotateY, float _rotateZ, float _scaleX, float _scaleY, float _scaleZ, int _shape);
	~CObj(void);
	void init();
	
	float getTranslateX();
	float getTranslateY();
	float getTranslateZ();
	float getRotateX();
	float getRotateY();
	float getRotateZ();
	float getScaleX();
	float getScaleY();
	float getScaleZ();
	Mesh *getObj();
	Vector3 getMaxBound();
	Vector3 getMinBound();
	Vector3 getInteractMaxBound();
	Vector3 getInteractMinBound();
	int getShape();
	void setTranslateY(float _translateY);
	void setMonsterJump(bool _monsterJump);
	bool getMonsterJump();
	void setRotateY(float _rotateY);

private:
	Mesh *obj; // Make sure everything is a unit
	float translateX, translateY, translateZ;
	float rotateX, rotateY, rotateZ;
	float scaleX, scaleY, scaleZ;
	Vector3 maxBound, minBound;
	Vector3 interactMaxBound, interactMinBound;
	int shape; // Tells what shape it is by enum
	bool monsterJump;
};

#endif