#ifndef _SP2_H_
#define _SP2_H_

#include "Scene.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"

#include "Item.h"
#include "Car.h"
#include "Shelf.h"

class SP2 : public Scene
{
	enum OBJ_ID
	{
		OBJ_CAR,
		OBJ_TROLLEY,
		OBJ_ITEM,
		OBJ_AI,
		OBJ_SHELF,
		OBJ_SUPERMARKET_WALL,
		OBJ_TABLE,
		OBJ_CAMERA,
		OBJ_SCREEN,
		OBJ_SHOPPER,
		OBJ_POLICE,
		OBJ_STAFF,
		OBJ_PLAYER,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TEXT,

		// Outer skybox
		GEO_OUTER_FRONT,
		GEO_OUTER_BACK,
		GEO_OUTER_LEFT,
		GEO_OUTER_RIGHT,
		GEO_OUTER_TOP,
		GEO_OUTER_BOTTOM,

		// Car
		GEO_CAR,
		GEO_CAR_TYRE,
		GEO_CAR_SCREEN,
		
		//SuperMarket
		GEO_SM,
		//SuperMarketDoor
		GEO_SMD,
		//SuperMarket Items
		GEO_CASHIERT,
		GEO_CAMERA,
		GEO_SCREEN,
		GEO_SHELF,
		GEO_ITEM_1,
		GEO_ITEM_2,
		GEO_ITEM_3,
		GEO_ITEM_4,
		GEO_ITEM_5,
		GEO_ITEM_6,
		GEO_ITEM_7,
		GEO_ITEM_8,
		GEO_ITEM_9,
		GEO_ITEM_10,

		//Human
		//SHOPPER
		GEO_HUMAN_SHOPPER_BODY,
		GEO_HUMAN_SHOPPER_ARM,
		GEO_HUMAN_SHOPPER_HAND,
		GEO_HUMAN_SHOPPER_LEG,
		//POLICE
		GEO_HUMAN_POLICE_BODY,
		GEO_HUMAN_POLICE_ARM,
		GEO_HUMAN_POLICE_HAND,
		GEO_HUMAN_POLICE_LEG,
		//STAFF
		GEO_HUMAN_STAFF_BODY,
		GEO_HUMAN_STAFF_ARM,
		GEO_HUMAN_STAFF_HAND,
		GEO_HUMAN_STAFF_LEG,

		

		//Size referance - unit cube
		GEO_CUBE,

		//player
		GEO_PLAYER,

		NUM_GEOMETRY,
	};
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		// Light 1
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,
		// Light 2
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	SP2();
	~SP2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Camera3 camera, saved;
	MS modelStack, viewStack, projectionStack;
	Light lights[2];
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void setLights();
	void getHandle();
	void lightParameters();
	void initValues();
	
	void initOuterSkybox();
	void renderOuterSkybox();
	void renderText();
	
	void initSuperMarket();
	void updateSuperMarket(double dt);
	void renderSuperMarket();

	void initCar();
	void updateCar(double dt);
	void renderCar();

	void initHuman();
	void updateHuman(double dt);
	void renderHuman(int type); // 1 - shopper , 2 - police , 3 - staff

	void initItems();
	void updateItems();
	void renderItems(int GEO_ITEM);

	void initShelf(int Choice,Vector3 _translateY);
	void updateShelf();
	void renderShelf();

	void initHands();
	void updateHands(double dt);
	void renderHands();

	bool togglelight;
	double fps;

	// Supermarket variables
	bool isDoorOpen; // Automated Door Check
	float translateX;
	Vector3 supermarketSize, supermarketPosition, supermarketScale, supermarketDoorMaxBound, supermarketDoorMinBound;

	// Skybox variables
	Vector3 outerSkyboxSize, outerSkyboxMaxBound, outerSkyboxMinBound;
	float skyboxOffset;

	// Car variables
	std::vector<CCar*> carList;
	CCar* inCar;		// NULL - Not inside

	// CObj variables
	std::vector<CObj*> objList;		// Holds every obj except for CItem || CItems will be stored in CShelf
	CObj *pObj;						// Points to an obj from the list

	std::vector<CShelf*> shelfList;

	//Hand variables
	float rotateHandX, rotateHandY;
};

#endif