#include "Obj.h"


CObj::CObj(void)
{
	translateX = translateY = translateZ = rotateX = rotateY = rotateZ = 0;
	scaleX = scaleY = scaleZ = 1;
	shape = -1;
}

CObj::CObj(Mesh* _obj, float _translateX, float _translateY, float _translateZ, float _rotateX, float _rotateY, float _rotateZ, float _scaleX, float _scaleY, float _scaleZ, int _shape)
{
	obj = _obj;
	translateX = _translateX;
	translateY = _translateY;
	translateZ = _translateZ;
	rotateX = _rotateX;
	rotateY = _rotateY;
	rotateZ = _rotateZ;
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	shape = _shape;
}

CObj::~CObj(void)
{
}

void CObj::init()
{
	float offset = 5;

	// Calculate maxBound and minBound
	if (shape == S_CUBE) // No rotation
	{
		// Assuming unit cube
		Vector3 originBound(translateX, translateY, translateZ);
		Vector3 lengthBound(scaleX, scaleY, scaleZ);
		maxBound.Set(originBound.x + (scaleX / 2) + offset, originBound.y + (scaleY / 2) + offset, originBound.z + (scaleZ / 2) + offset);
		minBound.Set(originBound.x - (scaleX / 2) - offset, originBound.y - (scaleY / 2) - offset, originBound.z - (scaleZ / 2) - offset);
	}
	else if (shape == S_MONSTER)
	{
		Vector3 monsterSize(10, 15, 10);
		Vector3 originBound(translateX, translateY, translateZ);
		Vector3 lengthBound(scaleX, scaleY, scaleZ);
		maxBound.Set(originBound.x + ((monsterSize.x * scaleX) / 2) + offset, 30, originBound.z + ((monsterSize.z * scaleZ) / 2) + offset);
		minBound.Set(originBound.x - ((monsterSize.x * scaleX) / 2) - offset, -30, originBound.z - ((monsterSize.z * scaleZ) / 2) - offset);
		interactMaxBound.Set(maxBound.x + (offset * 5), 0, maxBound.z + (offset * 5));
		interactMinBound.Set(minBound.x - (offset * 5), 0, minBound.z - (offset * 5));
		monsterJump = false;
	}
	else if (shape == S_CHEST)
	{
		offset += 10;
		Vector3 chestSize(1.7, 1.3, 1);
		Vector3 originBound(translateX, translateY, translateZ);
		Vector3 lengthBound(scaleX, scaleY, scaleZ);
		maxBound.Set(originBound.x + ((chestSize.x * scaleX) / 2) + offset, 30 /*originBound.y + ((chestSize.y * scaleY)) + offset*/, originBound.z + ((chestSize.z * scaleZ) / 2) + offset);
		minBound.Set(originBound.x - ((chestSize.x * scaleX) / 2) - offset, -30/*originBound.y - offset*/, originBound.z - ((chestSize.z * scaleZ) / 2) - offset);
	}
	else if (shape == S_TROPHY)
	{
		Vector3 trophySize(15, 15, 15);
		Vector3 originBound(translateX, translateY, translateZ);
		Vector3 lengthBound(scaleX, scaleY, scaleZ);
		maxBound.Set(originBound.x + ((trophySize.x * scaleX) / 2) + offset, 30 /*originBound.y + ((chestSize.y * scaleY)) + offset*/, originBound.z + ((trophySize.z * scaleZ) / 2) + offset);
		minBound.Set(originBound.x - ((trophySize.x * scaleX) / 2) - offset, -30/*originBound.y - offset*/, originBound.z - ((trophySize.z * scaleZ) / 2) - offset);
	}
}

float CObj::getTranslateX()
{
	return translateX;
}

float CObj::getTranslateY()
{
	return translateY;
}

float CObj::getTranslateZ()
{
	return translateZ;
}

float CObj::getRotateX()
{
	return rotateX;
}

float CObj::getRotateY()
{
	return rotateY;
}

float CObj::getRotateZ()
{
	return rotateZ;
}

float CObj::getScaleX()
{
	return scaleX;
}

float CObj::getScaleY()
{
	return scaleY;
}

float CObj::getScaleZ()
{
	return scaleZ;
}

Mesh *CObj::getObj()
{
	return obj;
}

Vector3 CObj::getMaxBound()
{
	return maxBound;
}

Vector3 CObj::getMinBound()
{
	return minBound;
}

int CObj::getShape()
{
	return shape;
}

Vector3 CObj::getInteractMaxBound()
{
	return interactMaxBound;
}

Vector3 CObj::getInteractMinBound()
{
	return interactMinBound;
}

void CObj::setTranslateY(float _translateY)
{
	translateY = _translateY;
}

void CObj::setMonsterJump(bool _monsterJump)
{
	monsterJump = _monsterJump;
}

bool CObj::getMonsterJump()
{
	return monsterJump;
}

void CObj::setRotateY(float _rotateY)
{
	rotateY = _rotateY;
}