/******************************************************************************/
/*!
\file	Material.h
\author Team 8
\par	
\brief
Header file for Material Class
*/
/******************************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H
/******************************************************************************/
/*!
	struct Component:
\brief
Defines default values ( r , g , b ) and sets the color of Mesh

*/
/******************************************************************************/
struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
};

/******************************************************************************/
/*!
	struct Material:      
\brief Sets default values kAmbient, kDiffuse, kSpecular and kShiniess
and uses those values to set Material of the Mesh
*/
/******************************************************************************/

struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	Material() // Constructor
	{
		kAmbient = kDiffuse = kSpecular = 0.1;
		kShininess = 1;
	}
};

#endif