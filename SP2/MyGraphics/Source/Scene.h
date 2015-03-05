/******************************************************************************/
/*!
\file	Scene.h
\author Team 8
\par	
\brief
Header file for Scene Class
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H

/******************************************************************************/
/*!
		Class Scene:
\brief	Stores Scene States
*/
/******************************************************************************/

class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif