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
#include "Trolley.h"
#include "CCashier.h"
#include "CSecurityGuard.h"
#include "CShopper.h"
#include "SecurityCamera.h"

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
		K_ENTER_TROLLEY,
		K_EXIT_TROLLEY,
		K_LEFT_PICK,
		K_LEFT_PLACE,
		K_RIGHT_PICK,
		K_RIGHT_PLACE,
		K_ENTER_CAM,
		K_EXIT_CAM,
		K_FIRST_FLOOR,
		K_SECOND_FLOOR,
		K_START_STORY,
		NUM_KEYPRESS,
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
		GEO_SUPERMARKET,
		GEO_SUPERMARKET_WALL, // No mesh
		GEO_SUPERMARKET_CEILING,
		GEO_SUPERMARKET_DOOR,
		GEO_PATCH,
		GEO_CASHIER_TABLE,
		GEO_SECURITY_CAMERA,
		GEO_SECURITY_CAMERA_SCREEN,
		GEO_SHELF,
		GEO_DISPLAY1,
		GEO_DISPLAY2,
		GEO_DISPLAY3,
		GEO_DISPLAY4,
		GEO_TROLLEY,
		GEO_POTATO,

		GEO_BAG,
		GEO_THOR,
		GEO_TARDIS,
		GEO_TARDIS_TOP,
		GEO_TARDIS_MID,
		GEO_TARDIS_SIGN,
		GEO_TARDIS_BOT,
		GEO_WUKONG,

		// Items
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
		// inventory picture of items - do not touch 
		GEO_INVENTORY_ITEM_1,
		GEO_INVENTORY_ITEM_2,
		GEO_INVENTORY_ITEM_3,
		GEO_INVENTORY_ITEM_4,
		GEO_INVENTORY_ITEM_5,
		GEO_INVENTORY_ITEM_6,
		GEO_INVENTORY_ITEM_7,
		GEO_INVENTORY_ITEM_8,
		GEO_INVENTORY_ITEM_9,
		GEO_INVENTORY_ITEM_10,
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

		//Game 3 security - used in game 3 , being controlled by player
		GEO_GAME3_BOB_BODY,
		GEO_GAME3_BOB_ARM,
		GEO_GAME3_BOB_HAND,
		GEO_GAME3_BOB_LEG,

		//Size referance - unit cube
		GEO_CUBE,

		//player
		GEO_HAND,
		GEO_INVENTORY,

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
	void Render2D(Mesh* mesh, float size, float x, float y);

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

	void updateTrolley(double dt);

	void initHuman(int type,Vector3 translation,Vector3 rotation,Vector3 camPosition,int radius); // type: 1 - cashier, 2 - SecurityGuard, 3 - Shopper 
	void updateHuman(double dt);
	void renderHuman(); 

	void initItems();
	
	void initSpecialItems();
	void updateSpecialItems();
	void renderSpecialItems();

	void initShelf(int Choice,Vector3 _translate, Vector3 _rotate);
	void updateShelf();
	void renderShelf();

	void initCabinet();
	void updateCabinet(double dt);
	void renderCabinet();

	void initCamera();
	void updateCamera(double dt);

	void initHands();
	void updateHands(double dt);
	void renderHands();

	void initPatch();
	void updatePatch();
	void renderPatch();

	void initGame(); 
	void renderGame(int a);
	void updateGame(double dt);
	bool updateBoundCheckGame3();

	bool aiTalk;
	float timer;

	bool togglelight;
	double fps;
	bool keypressed[NUM_KEYPRESS];

	// Supermarket variables
	std::vector<CTrolley*> trolleyList;
	int floorNum, newFloor; // floor number
	CObj *liftLeftDoor, *liftRightDoor;
	float translateX; // main entrance movement
	Vector3 supermarketSize, supermarketPosition, supermarketScale, supermarketDoorMaxBound, supermarketDoorMinBound ;
	Vector3 supermarketSecurityDoorMaxBound , supermarketSecurityDoorMinBound;
	float translateSecurityZ;
	std::vector<CItem*> checkoutList;

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

	//camera variables
	bool cam;
	int camNum;
	std::vector<CSecurityCamera*> cameraList;

	//Hand variables
	float rotateHandX, rotateHandY, trolleyRotateHandX;
	CObj *hands[2]; // 0 - Left, 1 - Right

	float tempX, tempY, tempZ, tempPitch, tempYaw, tempTargetX, tempTargetY, tempTargetZ;

	//variable use for testing - constantly increasing
	float temp;
	CObj *tempP;

	//Tardis Variables
	float rotTardis, tardisPitch, tardisY;
	bool pressed;
	// game bound variables
	bool ableStart; //display what to do to start game;
	int playerScore[3]; // individual for each game
	float timeFrame;
	float totalCost;
	int inGame;// in which game : 1 - treasure hunt(for now)

	//game1 variables - treasure hunt
	Vector3 game1MaxBound , game1MinBound; //search for items in list
	bool pickCorrect; // used to check if item put into trolley is correct item
	int randomItem; //generate random number to call from enum of geo items

	//game2 variables - the spaming cashier
	Vector3 game2MaxBound, game2MinBound;
	int itemLeft; // number of items left on cashier table in game 2
	std::vector<CItem*> bagList; // bottomless pit - used to store items
	
	//game3 variable - useless guard
	Vector3 game3MaxBound, game3MinBound;
	float bobMoveX, bobMoveZ, tempBobMoveX, tempBobMoveZ; // moving of security guard
	bool game3 , hitSomething;

	std::vector <CCharacter*> CharacterList;
};

#endif
