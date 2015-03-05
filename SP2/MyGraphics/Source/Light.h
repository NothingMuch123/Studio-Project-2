/******************************************************************************/
/*!
\file	Light.h
\author Team 8
\par	
\brief
Header file for Light Class
*/
/******************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H

/******************************************************************************/
/*!
	struct Light:
\brief
Defines 
Enums(LIGHT_POINT, LIGHT_DIRECTIONAL, LIGHT_SPOT)
Default Values
(positions, color, power, kC, kL, kQ, cosCutOff, cosInner, exponent)
*/
/******************************************************************************/
struct Light
{
	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	Light() // Constructor
	{

	}
	LIGHT_TYPE type;
	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};

#endif