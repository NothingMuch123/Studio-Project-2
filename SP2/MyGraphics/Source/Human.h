#ifndef _HUMAN_H
#define _HUMAN_H

#include "MeshBuilder.h"

class CHuman
{
public:
	CHuman(void);
	~CHuman(void);
	Mesh *GetHuman(int a);
	void InitShopper();
	void InitPolice();
	void InitStaff();
	
private:
	enum GEO_HUMAN
	{
		GEO_HUMAN_BODY,
		GEO_HUMAN_LARM,
		GEO_HUMAN_LHAND,
		GEO_HUMAN_LLEG,
		GEO_HUMAN_RARM,
		GEO_HUMAN_RHAND,
		GEO_HUMAN_RLEG,

		NUM_GEOMETRY,
	};
	Mesh *human[NUM_GEOMETRY];
};

#endif