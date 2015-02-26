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
#include "CCashier.h"
#include "CSecurityGuard.h"
#include "CShopper.h"

#include <iostream>

using std::cout;
using std::endl;
#include "CPromoter.h"


class SP2 : public Scene
{
public:
	enum KEYPRESS
	{
		K_ENTER_CAR,
		K_EXIT_CAR,
		K_LEFT_PICK,
		K_LEFT_PLACE,
		K_RIGHT_PICK,
		K_RIGHT_PLACE,
		NUM_KEYPRESS,
	};
	/*enum OBJ_ID
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
     	OBJ_HUMAN,
		OBJ_PLAYER,
		OBJ_CUBE,
		OBJ_CEILING,
		OBJ_CABINET_T,
		OBJ_DOOR,
	};*/
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
		GEO_SUPERMARKET,
		GEO_SUPERMARKET_WALL, // No mesh
		GEO_SUPERMARKET_CEILING,
		GEO_SUPERMARKET_DOOR,
		GEO_PATCH,
		GEO_SMLD,
		GEO_CASHIER_TABLE,
		GEO_SECURITY_CAMERA,
		GEO_SECURITY_CAMERA_SCREEN,
		GEO_SHELF,
		GEO_CABINET,
		GEO_TROLLEY,
		GEO_ITEM,
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
		GEO_HUMAN, // No mesh
		GEO_HUMAN_SHOPPER_BODY,
		GEO_HUMAN_SHOPPER_ARM,
		GEO_HUMAN_SHOPPER_HAND,
		GEO_HUMAN_SHOPPER_LEG,
		//POLICE
		GEO_HUMAN_SECURITYGUARD_BODY,
		GEO_HUMAN_SECURITYGUARD_ARM,
		GEO_HUMAN_SECURITYGUARD_HAND,
		GEO_HUMAN_SECURITYGUARD_LEG,
		//STAFF
		GEO_HUMAN_STAFF_BODY,
		GEO_HUMAN_STAFF_ARM,
		GEO_HUMAN_STAFF_HAND,
		GEO_HUMAN_STAFF_LEG,

		

		//Size referance - unit cube
		GEO_CUBE,

		//player
		GEO_HAND,

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

	void initHuman(int type,Vector3 translation,Vector3 rotation,Vector3 camPosition,int radius); // type: 1 - cashier, 2 - SecurityGuard, 3 - Shopper 
	void updateHuman(double dt);
	void renderHuman(); 

	void initItems();
	void updateItems();
	void renderItems(int GEO_ITEM);

	void initShelf(int Choice,Vector3 _translate, Vector3 _rotate);
	void updateShelf();
	void renderShelf();

	void initCabinet();
	void renderCabinet();

	void initHands();
	void updateHands(double dt);
	void renderHands();

	void initPatch();
	void updatePatch();
	void renderPatch();

	bool cam;
	bool togglelight;
	double fps;
	bool keypressed[NUM_KEYPRESS];

	// Supermarket variables
	int floorNum ; // floor number
	float translateX; // main entrance movement
	Vector3 supermarketSize, supermarketPosition, supermarketScale, supermarketDoorMaxBound, supermarketDoorMinBound ;
	Vector3 screenMaxBound, screenMinBound ; // security tele interaction bounds

	//Promoter Variables
	Vector3 promoterMaxBound, promoterMinBound;

	//Lift variables
	Vector3 supermarketLiftSize, supermarketLiftScale , supermarketLiftPosition;
	Vector3 supermarketLiftMaxBound, supermarketLiftMinBound , supermarketLiftDoorMaxBound , supermarketLiftDoorMinBound;
	bool disableLiftDoor; // Automated Door Check
	float translateLiftX;

	// Skybox variables
	Vector3 outerSkyboxSize, outerSkyboxMaxBound, outerSkyboxMinBound;
	float skyboxOffset;

	// Car variables
	std::vector<CCar*> carList;

	// CObj variables // Holds every obj except for CItem || CItems will be stored in CShelf
	std::vector<CObj*> objList;		//	** FIRST FLOOR **
	std::vector<CObj*> objList2;	//	** SECOND FLOOR **
	CObj *pObj;						// Points to an obj from the list

	// Shelf variables
	std::vector<CShelf*> shelfList;

	//Hand variables
	float rotateHandX, rotateHandY;
	CObj *hands[2]; // 0 - Left, 1 - Right

	//human variables 
	float moveX , moveZ;
	float tempX, tempY, tempZ, tempPitch, tempYaw, tempTargetX, tempTargetY, tempTargetZ;
	//variable use for testing - constantly increasing
	float temp;
	CObj *tempP;
};

#endif