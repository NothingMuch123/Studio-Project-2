#include "Obj.h"


CObj::CObj(void) : ID(-1), translate(0, 0, 0), rotate(0, 0, 0), scale(1, 1, 1), maxBound(0, 0, 0), minBound(0, 0, 0), size(1, 1, 1), render(true)
{
}

CObj::CObj(int _ID, Vector3 _translate, Vector3 _rotate, Vector3 _scale, Vector3 _size) : ID(_ID), translate(_translate), rotate(_rotate), scale(_scale), size(_size), render(true)
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
	float offset = 3;
	maxBound.Set(translate.x + ((size.x * scale.x) / 2) + offset, translate.y + (size.y * scale.y) + offset, translate.z + ((size.z * scale.z) / 2) + offset);
	minBound.Set(translate.x - ((size.x * scale.x) / 2) - offset, translate.y - (size.y * scale.y) - offset , translate.z - ((size.z * scale.z) / 2) - offset);
}

bool CObj::getRender()
{
	return render;
}

void CObj::setRender(bool _render)
{
	render = _render;
}

void CObj::setRotateY(float _rotateY)
{
	rotate.y = _rotateY;
}

void CObj::setTranslateX(float _translateX)
{
	translate.x = _translateX;
}

void CObj::setTranslate(Vector3 _translate)
{
	translate = _translate;
}