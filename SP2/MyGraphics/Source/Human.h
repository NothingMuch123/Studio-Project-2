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
		GEO_HUMAN_ARM,
		GEO_HUMAN_HAND,
		GEO_HUMAN_LEG,

		NUM_GEOMETRY,
	};
	Mesh *human[NUM_GEOMETRY];
};

#endif