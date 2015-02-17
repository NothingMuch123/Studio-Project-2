#include "Obj.h"


CObj::CObj(void) : ID(-1), translate(0, 0, 0), rotate(0, 0, 0), scale(1, 1, 1), maxBound(0, 0, 0), minBound(0, 0, 0), interactMaxBound(0, 0, 0), interactMinBound(0, 0, 0), size(0, 0, 0)
{
}

CObj::CObj(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size) : ID(_ID), translate(_translate), rotate(_rotate), scale(_scale), size(_size)
{
}

CObj::~CObj(void)
{
}

Vector3 CObj::getTranslate()
{
	return translate;
}

Vector3 CObj::getRotate()
{
	return rotate;
}

Vector3 CObj::getScale()
{
	return scale;
}

Vector3 CObj::getMaxBound()
{
	return maxBound;
}

Vector3 CObj::getMinBound()
{
	return minBound;
}

Vector3 CObj::getInteractMaxBound()
{
	return interactMaxBound;
}

Vector3 CObj::getInteractMinBound()
{
	return interactMinBound;
}

Vector3 CObj::getSize()
{
	return size;
}

int CObj::getID()
{
	return ID;
}

void CObj::calcBound()
{
	float offset = 0;
	maxBound.Set(((size.x * scale.x) / 2) + translate.x + offset, ((size.y * scale.y) / 2) + translate.y + offset, ((size.z * scale.z) / 2) + translate.z + offset);
	minBound.Set(((size.x * scale.x) / 2) - translate.x - offset, ((size.y * scale.y) / 2) - translate.y - offset, ((size.z * scale.z) / 2) - translate.z - offset);
	interactMaxBound.Set(((size.x * scale.x) / 2) + translate.x + offset, ((size.y * scale.y) / 2) + translate.y + offset, ((size.z * scale.z) / 2) + translate.z + offset);
	interactMinBound.Set(((size.x * scale.x) / 2) - translate.x - offset, ((size.y * scale.y) / 2) - translate.y - offset, ((size.z * scale.z) / 2) - translate.z - offset);
}