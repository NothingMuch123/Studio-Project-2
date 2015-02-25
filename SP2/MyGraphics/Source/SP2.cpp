#include "SP2.h"
#include "GL\glew.h"


#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <sstream>
#include <fstream>
#include <iostream>

SP2::SP2()
{
}

SP2::~SP2()
{
}

void SP2::Init()
{
	initValues();

	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable Stippling
	glEnable(GL_POLYGON_STIPPLE);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	//Initialize camera settings
	camera.Init(Vector3(0,30,300), Vector3(0,30,285), Vector3(0,1,0));

	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );

	getHandle();
	setLights();
	lightParameters();

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	//meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 1, 0);
	//meshList[GEO_LIGHTBALL2] = MeshBuilder::GenerateSphere("lightball2", Color(1, 1, 1), 1, 0);


	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateOBJ("cube" , "OBJ//Cube.obj");
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//MazeWall.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ( "player" , "OBJ//Cube.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//player_texture.tga");

	//initCabinet();
	initCar();
	initHuman(3,Vector3(30,0,30)); 

	initHuman(1,Vector3(-30,0,30)); 
	
	initHuman(2,Vector3(15,0,30)); 

	initOuterSkybox();
	initSuperMarket();
	initHands();
}

void SP2::initHands()
{
	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ( "player" , "OBJ//Cube.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//player_texture.tga");
	rotateHandX = 0;
	rotateHandY = 0;
	hands[0] = hands[1] = NULL;
}

void SP2::initShelf(int Choice,Vector3 _translate)
{
	initItems();
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("Shelf" , "OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//shelf.tga");

	CItem* pItem;

	pObj= new CShelf(OBJ_SHELF,_translate,Vector3(0,0,0),Vector3(11,11,11),Vector3(4,5,3),10);
	pObj->calcBound();

	switch(Choice)
	{
	case GEO_ITEM_1:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_1]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_2:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_2]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_3:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_3]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_4:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_4]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_5:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_5]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_6:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_6]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_7:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,0,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_7]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_8:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_8]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_9:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_9]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	case GEO_ITEM_10:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(OBJ_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_10]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
				}
			}
		}
		break;
	}


	objList.push_back(pObj);
	shelfList.push_back(static_cast<CShelf*>(pObj));
}

void SP2::initItems()
{
	meshList[GEO_ITEM_1] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-1.obj");
	meshList[GEO_ITEM_1]->textureID = LoadTGA("Image//ITEMS//box-1.tga");

	meshList[GEO_ITEM_2] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//can-2.obj");
	meshList[GEO_ITEM_2]->textureID = LoadTGA("Image//ITEMS//can-2.tga");

	meshList[GEO_ITEM_3] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-3.obj");
	meshList[GEO_ITEM_3]->textureID = LoadTGA("Image//ITEMS//box-3.tga");

	meshList[GEO_ITEM_4] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//can-4.obj");
	meshList[GEO_ITEM_4]->textureID = LoadTGA("Image//ITEMS//can-4.tga");

	meshList[GEO_ITEM_5] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-5.obj");
	meshList[GEO_ITEM_5]->textureID = LoadTGA("Image//ITEMS//box-5.tga");

	meshList[GEO_ITEM_6] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-6.obj");
	meshList[GEO_ITEM_6]->textureID = LoadTGA("Image//ITEMS//box-6.tga");

	meshList[GEO_ITEM_7] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-7.obj");
	meshList[GEO_ITEM_7]->textureID = LoadTGA("Image//ITEMS//box-7.tga");

	meshList[GEO_ITEM_8] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//can-8.obj");
	meshList[GEO_ITEM_8]->textureID = LoadTGA("Image//ITEMS//can-8.tga");

	meshList[GEO_ITEM_9] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//packet-9.obj");
	meshList[GEO_ITEM_9]->textureID = LoadTGA("Image//ITEMS//packet-9.tga");

	meshList[GEO_ITEM_10] = MeshBuilder::GenerateOBJ("item" , "OBJ//ITEMS//box-10.obj");
	meshList[GEO_ITEM_10]->textureID = LoadTGA("Image//ITEMS//box-10.tga");
}

void SP2::initCar()
{
	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("Car", "OBJ//Car.obj");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//CarTexture.tga");
	meshList[GEO_CAR]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_CAR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR]->material.kShininess = 1.f;

	meshList[GEO_CAR_TYRE] = MeshBuilder::GenerateOBJ("Car", "OBJ//CarTyre.obj");
	meshList[GEO_CAR_TYRE]->textureID = LoadTGA("Image//CarTyreTexture.tga");
	meshList[GEO_CAR_TYRE]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR_TYRE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_CAR_TYRE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR_TYRE]->material.kShininess = 1.f;

	meshList[GEO_CAR_SCREEN] = MeshBuilder::GenerateQuad("Car screen", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_CAR_SCREEN]->textureID = LoadTGA("Image//Driver'sScreenTexture[Test].tga");

	pObj = new CCar(OBJ_CAR, Vector3(-200,0,200), Vector3(0,0,0), Vector3(5,5,5), Vector3(17,8,17));
	pObj->calcBound();
	static_cast<CCar*>(pObj)->setCamera();
	objList.push_back(pObj);
	carList.push_back(static_cast<CCar*>(pObj));
}

void SP2::initCabinet()
{	
	//Special Display Cabinet_THE_TARDIS
	meshList[GEO_CABINET] = MeshBuilder::GenerateOBJ("Display Cabinet with Tardis", "OBJ//display_case.obj");
	meshList[GEO_CABINET] ->textureID = LoadTGA("Image//displayGallifrey.tga");
	pObj = new CObj(OBJ_CABINET_T, Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + .25 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(1 * supermarketScale.x,1 * supermarketScale.y,1 * supermarketScale.z), Vector3(3, .5 ,1));
	pObj-> calcBound();
	objList2.push_back(pObj);
	//Regular Display Cabinet 
}
void SP2::initSuperMarket()
{
	floorNum = 1; // start at first floor
	// Supermarket
	supermarketSize.Set(30,20,20);
	supermarketPosition.Set(0,-4,0);
	supermarketScale.Set(10,10,10);

	// Left wall
	Vector3 tempWallPosition(supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2), supermarketPosition.y, supermarketPosition.z);
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(5,supermarketSize.y * supermarketScale.y, supermarketSize.z * supermarketScale.z), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	// Right wall
	tempWallPosition.Set(supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2), supermarketPosition.y, supermarketPosition.z);
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(5,supermarketSize.y * supermarketScale.y, supermarketSize.z * supermarketScale.z), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	float halfLength = ((((supermarketScale.x * supermarketSize.x) / 2) - (2 * supermarketScale.x)) / 2); // Half length between corner to door along x-axis
	// Front left wall
	tempWallPosition.Set(((supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2)) + halfLength), supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor - need hole for toilet entrance

	// Front right wall
	tempWallPosition.Set(((supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2)) - halfLength), supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor - need space for toilet entrance

	// Back left wall
	tempWallPosition.Set(((supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2)) + halfLength), supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	// Back right wall
	tempWallPosition.Set(((supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2)) - halfLength), supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(OBJ_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	//lift left wall
	tempWallPosition.Set(supermarketPosition.x - ((supermarketScale.x * supermarketSize.x ) / 4 - halfLength / 1.7), supermarketPosition.y ,  supermarketPosition.z - (supermarketScale.z * supermarketSize.z) / 2  - halfLength / 2);
	pObj = new CObj(OBJ_SUPERMARKET_WALL , Vector3( tempWallPosition.x , tempWallPosition.y, tempWallPosition.z) , Vector3(0,0,0) , Vector3(5,supermarketSize.y * supermarketScale.y, halfLength) ,Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	//lift right wall 
	tempWallPosition.Set(supermarketPosition.x + ((supermarketScale.x * supermarketSize.x ) / 4 - halfLength / 1.7), supermarketPosition.y ,  supermarketPosition.z - (supermarketScale.z * supermarketSize.z) / 2  - halfLength / 2);
	pObj = new CObj(OBJ_SUPERMARKET_WALL , Vector3( tempWallPosition.x , tempWallPosition.y, tempWallPosition.z) , Vector3(0,0,0) , Vector3(5,supermarketSize.y * supermarketScale.y, halfLength) ,Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	//Lift back wall
	tempWallPosition.Set(supermarketPosition.x , supermarketPosition.y , supermarketPosition.z - (supermarketScale.z * supermarketSize.z ) + halfLength / 1.5 );
	pObj = new CObj (OBJ_SUPERMARKET_WALL , Vector3(tempWallPosition.x , tempWallPosition.y ,tempWallPosition.z) , Vector3 (0,0,0), Vector3(halfLength, supermarketSize.y * supermarketScale.y , 5 ), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	// Door (Interaction bounds)
	Vector3 doorPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	supermarketDoorMaxBound.Set(doorPosition.x + (3 * supermarketScale.x), doorPosition.y, doorPosition.z + (5 * supermarketScale.z));
	supermarketDoorMinBound.Set(doorPosition.x - (3 * supermarketScale.x), doorPosition.y, doorPosition.z - (5 * supermarketScale.z));
	translateX = 0;

	//Lift (Interaction bound)
	Vector3 liftPosition( supermarketPosition.x , supermarketPosition.y , supermarketPosition.z - (supermarketScale.z * supermarketSize.z ) + halfLength );
	supermarketLiftMaxBound.Set( liftPosition.x + ( 3 * supermarketScale.x), liftPosition.y , liftPosition.z + ( 3* supermarketScale.z));
	supermarketLiftMinBound.Set( liftPosition.x - ( 3 * supermarketScale.x), liftPosition.y , liftPosition.z - ( 1.5 * supermarketScale.z));

	// lift door (Interaction Bound)
	Vector3 liftDoorPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	supermarketLiftDoorMaxBound.Set(liftDoorPosition.x + (3 * supermarketScale.x), liftDoorPosition.y, liftDoorPosition.z + (5 * supermarketScale.z));
	supermarketLiftDoorMinBound.Set(liftDoorPosition.x - (3 * supermarketScale.x), liftDoorPosition.y, liftDoorPosition.z - (5 * supermarketScale.z));
	translateLiftX = 0;
	disableLiftDoor = false;

	//Supermarket OBJ
	meshList[GEO_SM] = MeshBuilder::GenerateOBJ("SuperMarket", "OBJ//supermarket.obj");
	meshList[GEO_SM]->textureID = LoadTGA("Image//SuperMarketTexture.tga");

	//Ceiling OBJ
	meshList[GEO_SUPERMARKET_CEILING] = MeshBuilder::GenerateOBJ("SuperMarket Ceiling", "OBJ//ceiling.obj");
	meshList[GEO_SUPERMARKET_CEILING]->textureID = LoadTGA("Image//ceiling_texture.tga");
	pObj = new CObj(OBJ_CEILING, Vector3(supermarketPosition.x, supermarketPosition.y + 10 * supermarketScale.y, supermarketPosition.z), Vector3(0,0,0), Vector3(supermarketScale.x,supermarketScale.y,supermarketScale.z), Vector3(1,1,1));
	//pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj);

	//Cashier Table OBJ
	meshList[GEO_CASHIERT] = MeshBuilder::GenerateOBJ("CashierTable" , "OBJ//cashiertable.obj");
	meshList[GEO_CASHIERT]->textureID = LoadTGA("Image//cashier table.tga");
	pObj = new CObj(OBJ_TABLE , Vector3(supermarketPosition.x + 4.1 * supermarketScale.x, supermarketPosition.x + 0.25 * supermarketScale.y, supermarketPosition.x + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x / 2, supermarketScale.y / 2, supermarketScale.z / 2), Vector3(4 , 5 , 11));
	pObj->calcBound();
	objList.push_back(pObj);

	//Camera OBJ
	meshList[GEO_CAMERA] = MeshBuilder::GenerateOBJ("Camera" , "OBJ//camera.obj");
	meshList[GEO_CAMERA]->textureID = LoadTGA("Image//camera_texture.tga");
	pObj = new CObj(OBJ_CAMERA , Vector3(supermarketPosition.x - 14.65 * supermarketScale.x, supermarketPosition.y + 9.6 * supermarketScale.y, supermarketPosition.z - 9.5 * supermarketScale.z), Vector3(0,0,0), Vector3(0.2 * supermarketScale.x,0.2 * supermarketScale.y,0.2 * supermarketScale.z), Vector3(2 ,1.5, 2));
	pObj->calcBound();
	objList.push_back(pObj);

	//CameraScreen OBJ
	meshList[GEO_SCREEN] = MeshBuilder::GenerateOBJ("Camera Screen" , "OBJ//cameraScreen.obj");
	meshList[GEO_SCREEN]->textureID = LoadTGA("Image//cameraScreen_texture.tga");
	pObj = new CObj(OBJ_SCREEN , Vector3 (supermarketPosition.x - 4.1 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(1 * supermarketScale.x,1 * supermarketScale.y,1 * supermarketScale.z), Vector3(3, .5 ,1));
	pObj->calcBound();
	objList2.push_back(pObj);

	// supermarket door
	meshList[GEO_SMD] = MeshBuilder::GenerateOBJ( "Door" ,"OBJ//SuperMarketDoor.obj");
	meshList[GEO_SMD]->textureID = LoadTGA("Image//SuperMarketDoorTexture.tga");

	//supermarket left lift door
	meshList[GEO_SMLD] = MeshBuilder::GenerateOBJ("lift door" , "OBJ//SuperMarketDoor.obj");
	meshList[GEO_SMLD]->textureID = LoadTGA("Image//SuperMarketDoorTexture.tga");
	pObj = new CObj(OBJ_DOOR, Vector3( supermarketPosition.x * supermarketScale.x + 15 , supermarketPosition.y * supermarketScale.y + 35, supermarketPosition.z * supermarketScale.z - 100 ) , Vector3(0,0,0) , Vector3( 1 * supermarketScale.x * 0.6, 1 * supermarketScale.y * 0.5, 1* supermarketScale.z * 0.5 ), Vector3( supermarketScale.x * 1 /2 , 1, 1) );
	objList.push_back(pObj);
	objList2.push_back(pObj);
	pObj = new CObj(OBJ_DOOR, Vector3( supermarketPosition.x * supermarketScale.x - 15 , supermarketPosition.y * supermarketScale.y + 35, supermarketPosition.z * supermarketScale.z - 100 ) , Vector3(0,0,0) , Vector3( 1 * supermarketScale.x * 0.6, 1 * supermarketScale.y * 0.5, 1* supermarketScale.z * 0.5 ), Vector3( supermarketScale.x * 1 /2 , 1, 1) );
	objList.push_back(pObj);
	objList2.push_back(pObj);

	

	initShelf(GEO_ITEM_10,Vector3(0,0,0));
	initShelf(GEO_ITEM_5,Vector3(0,14,0));
	initShelf(GEO_ITEM_2,Vector3(0,28,0));
}

void SP2::initHuman(int Choice,Vector3 translation) // only human body is stored in obj list 
{
	if(Choice ==1)
	{
		meshList[GEO_HUMAN_STAFF_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_STAFF_BODY]->textureID = LoadTGA("Image//staff_texture.tga");

		meshList[GEO_HUMAN_STAFF_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_STAFF_ARM]->textureID = LoadTGA ("Image//staff_texture.tga");

		meshList[GEO_HUMAN_STAFF_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
		meshList[GEO_HUMAN_STAFF_HAND]->textureID = LoadTGA ("Image//staff_texture.tga");

		meshList[GEO_HUMAN_STAFF_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
		meshList[GEO_HUMAN_STAFF_LEG]->textureID = LoadTGA ("Image//staff_texture.tga");

		pObj = new CCashier(OBJ_HUMAN,Vector3(0,10,0)+translation, Vector3(0,0,0),Vector3(4,4.5,4), Vector3(3, 4.6, 1.6));
		pObj->calcBound();
		objList.push_back(pObj);

	}

	else if(Choice==2)
	{
		meshList[GEO_HUMAN_SECURITYGUARD_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_BODY]->textureID = LoadTGA("Image//police_texture.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_ARM]->textureID = LoadTGA ("Image//police_texture.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_HAND]->textureID = LoadTGA ("Image//police_texture.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_LEG]->textureID = LoadTGA ("Image//police_texture.tga");


		pObj = new CSecurityGuard(OBJ_HUMAN,Vector3(0,10,0)+translation, Vector3(0,0,0),Vector3(4,4.5,4), Vector3(3, 4.6, 1.6));
		pObj->calcBound();
		objList.push_back(pObj);
	}

	else if(Choice ==3)
	{
		meshList[GEO_HUMAN_SHOPPER_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_SHOPPER_BODY]->textureID = LoadTGA("Image//shopper_texture.tga");

		meshList[GEO_HUMAN_SHOPPER_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_SHOPPER_ARM]->textureID = LoadTGA ("Image//shopper_texture.tga");

		meshList[GEO_HUMAN_SHOPPER_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
		meshList[GEO_HUMAN_SHOPPER_HAND]->textureID = LoadTGA ("Image//shopper_texture.tga");

		meshList[GEO_HUMAN_SHOPPER_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
		meshList[GEO_HUMAN_SHOPPER_LEG]->textureID = LoadTGA ("Image//shopper_texture.tga");

		pObj = new CShopper(OBJ_HUMAN,Vector3(0,10,0)+translation,Vector3(0,0,0),Vector3(5,5,5),Vector3(4,4.5,1));
		pObj->calcBound();
		objList.push_back(pObj);
	}
	else
	{
	}
}

void SP2::setLights()
{
	lights[0].type = Light::LIGHT_SPOT;
	lights[0].position.Set(0, 0, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 5;
	lights[0].kC = 1.0f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.000f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(5));
	lights[0].cosInner = cos(Math::DegreeToRadian(1));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0,1,0);

	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(0, 0, 0);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);
}

void SP2::getHandle()
{
	// Get a handle for our "MVP" uniform
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	// Light 2
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");
	glUseProgram(m_programID);
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);
}

void SP2::lightParameters()
{
	// Make sure you pass uniform parameters after glUseProgram()
	// Light 1
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);
	// Light 2
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);
}

void SP2::initValues()
{
	cam = false;
	fps = 60;
	togglelight = false;

	// Collision test cube
	/*pObj = new CObj(OBJ_CUBE, Vector3(100,25,200), Vector3(0,0,0), Vector3(50,50,50), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);*/
}

void SP2::initOuterSkybox()
{
	meshList[GEO_OUTER_FRONT] = MeshBuilder::GenerateQuad("Outer skybox front", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_FRONT]->textureID = LoadTGA("Image//OuterSkybox//front.tga");

	meshList[GEO_OUTER_BACK] = MeshBuilder::GenerateQuad("Outer skybox back", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_BACK]->textureID = LoadTGA("Image//OuterSkybox//back.tga");

	meshList[GEO_OUTER_LEFT] = MeshBuilder::GenerateQuad("Outer skybox left", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_LEFT]->textureID = LoadTGA("Image//OuterSkybox//left.tga");

	meshList[GEO_OUTER_RIGHT] = MeshBuilder::GenerateQuad("Outer skybox right", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_RIGHT]->textureID = LoadTGA("Image//OuterSkybox//right.tga");

	meshList[GEO_OUTER_TOP] = MeshBuilder::GenerateQuad("Outer skybox top", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_TOP]->textureID = LoadTGA("Image//OuterSkybox//top.tga");

	meshList[GEO_OUTER_BOTTOM] = MeshBuilder::GenerateQuad("Outer skybox bottom", Color(1,1,1), TexCoord(100,100));
	meshList[GEO_OUTER_BOTTOM]->textureID = LoadTGA("Image//OuterSkybox//bottom.tga");

	outerSkyboxSize.Set(10000,10000,10000);
	skyboxOffset = 10;
	outerSkyboxMaxBound.Set(outerSkyboxSize.x/2 - skyboxOffset*2, outerSkyboxSize.y/2 - skyboxOffset*2, outerSkyboxSize.z/2 - skyboxOffset*2);
	outerSkyboxMinBound.Set(-outerSkyboxSize.x/2 + skyboxOffset*2, skyboxOffset, -outerSkyboxSize.z/2 + skyboxOffset*2);
}

void SP2::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	// Interactions
	if(floorNum == 1)
	{
		for (int i = 0; i < objList.size(); ++i)
		{
			pObj = objList[i];
			if (pObj->getRender())
			{
				if (camera.target.x < pObj->getMaxBound().x && camera.target.x > pObj->getMinBound().x && camera.target.y < pObj->getMaxBound().y && camera.target.y > pObj->getMinBound().y && camera.target.z < pObj->getMaxBound().z && camera.target.z > pObj->getMinBound().z)
				{
					if (pObj->getID() == OBJ_CAR)
					{
						if (Application::IsKeyPressed('C') && hands[0] == NULL && hands[1] == NULL)
						{
							hands[0] = hands[1] = pObj;
							saved = camera;
							pObj->setRender(false);
							camera = static_cast<CCar*>(pObj)->carCamera;
							rotateHandX = 0;
							rotateHandY = hands[0]->getRotate().y -90;
						}
					}
				}
			}
		}
	}
	if(floorNum == 2) // 2nd floor
	{
	}

	if(Application::IsKeyPressed('T') && cam == false)
	{
		rotateHandY = 0;
		camera.position.x = -143;
		camera.position.y = 96;
		camera.position.z = -90;
		camera.target.x = 0;
		camera.target.y = 0;
		camera.target.z = 0;
		camera.up.Set(0, 1, 0);
		cam = true;
	}
	if(cam == false)
	{
		camera.Update(dt, outerSkyboxMaxBound, outerSkyboxMinBound, objList, hands, floorNum, objList2);
		tempX = camera.position.x;
		tempY = camera.position.y;
		tempZ = camera.position.z; 
		tempYaw = rotateHandY;
		tempPitch = rotateHandX;
		tempTargetX = camera.target.x;
		tempTargetY = camera.target.y;
		tempTargetZ = camera.target.z;
	}

	if (hands[0] != NULL && hands[1] != NULL)
	{
		if (hands[0]->getID() == OBJ_CAR && hands[1]->getID() == OBJ_CAR)
		{
			updateCar(dt);
		}
	}

	updateHuman(dt);
	updateSuperMarket(dt);
	updateShelf();
	updateItems();
	updateHands(dt);

	if(Application::IsKeyPressed('Z'))
	{
		togglelight = true;
	}
	if(Application::IsKeyPressed('X'))
	{
		togglelight = false;
	}
	//if(Application::IsKeyPressed('O')) // manual triggar for 2nd floor (temp check bounds) - Tim
	//{
	//	floorNum = 1;
	//}
	//if(Application::IsKeyPressed('P'))
	//{
	//	floorNum = 2;
	//}
	static double fpsRefresh;
	fpsRefresh += dt;
	if (fpsRefresh >= 1)
	{
		fps = 1 / dt;
		fpsRefresh = 0;
	}
}

void SP2::updateHands(double dt)
{
	static const float ROTATE_SPEED = 100.f;
	if (rotateHandY >= 360 ||rotateHandY <= -360)
	{
		rotateHandY = 0;
	}

	if(cam == false)
	{
		if (Application::IsKeyPressed(VK_LEFT))
		{
			rotateHandY += ROTATE_SPEED*dt;

		}
		if (Application::IsKeyPressed(VK_RIGHT))
		{
			rotateHandY -= ROTATE_SPEED*dt;
		}
	}
	if(Application::IsKeyPressed('Y') && cam == true)
	{
		floorNum = 1;
		cam = false;
		camera.position.x = tempX;
		camera.position.y = tempY;
		camera.position.z = tempZ;
		rotateHandX = tempPitch;
		rotateHandY = tempYaw;
		camera.target.x = tempTargetX;
		camera.target.y = tempTargetY;
		camera.target.z = tempTargetZ;
	}

	if (Application::IsKeyPressed(VK_UP) && rotateHandX < 30 && hands[0] == NULL)
	{
		rotateHandX += ROTATE_SPEED*dt;
	}
	if (Application::IsKeyPressed(VK_DOWN) && rotateHandX > -30 && hands[0] == NULL)
	{
		rotateHandX -= ROTATE_SPEED*dt;
	}
	if(Application::IsKeyPressed('R') && hands[0] == NULL)
	{
		rotateHandX = 0;
		rotateHandY = 0;
	}
}

void SP2::updateShelf()
{

}

void SP2::updateItems()
{
}

void SP2::updateSuperMarket(double dt)
{
	//lift door interaction (needed for both floors) [ always open unless want to go different floor ] 
	if(camera.position.x < supermarketLiftDoorMaxBound.x && camera.position.x > supermarketLiftDoorMinBound.x && camera.position.z < supermarketLiftDoorMaxBound.z && camera.position.z > supermarketLiftDoorMinBound.z)
	{
		if(disableLiftDoor == false)
		{
			if(translateLiftX < 2)
				translateLiftX += 0.1;
		}
	}
	else
	{
		if(disableLiftDoor == false)
		{
			if(translateLiftX > 0)
				translateLiftX -= 0.1;
		}
	}
	if(disableLiftDoor == true)
	{
		if(translateLiftX > 0)
			translateLiftX -= 0.1;
		if(translateLiftX == 0)
			disableLiftDoor = false;
	}
	// lift interaction - bring them to 2nd floor/ 1st floor
	if(camera.position.x < supermarketLiftMaxBound.x && camera.position.x > supermarketLiftMinBound.x && camera.position.z < supermarketLiftMaxBound.z && camera.position.z > supermarketLiftMinBound.z)
	{
		if(Application::IsKeyPressed('O'))
		{
				floorNum = 2;
				disableLiftDoor = true;
		}
		if(Application::IsKeyPressed('P'))
		{
				floorNum = 1;
				disableLiftDoor = true;
		}
	}
	if(floorNum == 1) //1st floor
	{
		if (camera.position.x < supermarketDoorMaxBound.x && camera.position.x > supermarketDoorMinBound.x && camera.position.z < supermarketDoorMaxBound.z && camera.position.z > supermarketDoorMinBound.z)
		{
			if(translateX<2)
			{
				translateX+=0.1;
			}
		}
		else
		{		
			if(translateX>0)
			{
				translateX-=0.1;
			}
		}
	}
	else if (floorNum == 2) // on 2nd floor
	{

	}

}

void SP2::updateCar(double dt)//updating car
{
	float ROTATE_SPEED = 100.f;
	if (Application::IsKeyPressed('V'))
	{
		static_cast<CCar*>(hands[0])->setRender(true);
		static_cast<CCar*>(hands[0])->carCamera = camera;
		camera = saved;
		Vector3 right = ((static_cast<CCar*>(hands[0])->carCamera.target - static_cast<CCar*>(hands[0])->carCamera.position).Cross(static_cast<CCar*>(hands[0])->carCamera.up)).Normalized();
		Mtx44 Rotation;
		Rotation.SetToRotation(90,0,1,0);
		//camera.Init(camera.position - (right * 65), (camera.position - (right * 65)) + ((Rotation * (camera.position - camera.target))), Vector3(0,1,0));
		camera.target = ((static_cast<CCar*>(hands[0])->carCamera.position - (right * 65)) + ((Rotation * (static_cast<CCar*>(hands[0])->carCamera.position - static_cast<CCar*>(hands[0])->carCamera.target))));
		camera.position = (static_cast<CCar*>(hands[0])->carCamera.position - (right * 65));
		camera.up.Set(0,1,0);
		static_cast<CCar*>(hands[0])->updatePosition();
		static_cast<CCar*>(hands[0])->calcBound();
		hands[0] = hands[1] = NULL;
		rotateHandX = 0;
		rotateHandY -= 90;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float rotateY = hands[0]->getRotate().y + (ROTATE_SPEED*dt);
		static_cast<CCar*>(hands[0])->setRotateY(rotateY);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float rotateY = hands[0]->getRotate().y - (ROTATE_SPEED*dt);
		static_cast<CCar*>(hands[0])->setRotateY(rotateY);
	}
}

void SP2::updateHuman(double dt)
{

}

void SP2::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	/*// Light 1
	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
	Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
	Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
	glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
	Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	// Light 2
	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
	Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
	Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
	glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
	Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}*/

	renderOuterSkybox();

	renderSuperMarket();

	if(floorNum == 1 ) //first floor
	{
		// Render objList
		for (int i = 0; i < objList.size(); ++i)
		{
			pObj = objList[i];
			if (pObj->getRender())
			{
				if (pObj->getID() == OBJ_CAR)
				{
					renderCar();
				}
				else if(pObj->getID() == OBJ_SHELF)
				{
					renderShelf();
				}
				else if(pObj->getID() == OBJ_HUMAN)
				{
					renderHuman();
				}
				else
				{
					modelStack.PushMatrix();
					modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
					modelStack.Rotate(pObj->getRotate().x, 1,0,0);
					modelStack.Rotate(pObj->getRotate().y, 0,1,0);
					modelStack.Rotate(pObj->getRotate().z, 0,0,1);
					modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
					if (pObj->getID() == OBJ_TABLE)
					{
						RenderMesh(meshList[GEO_CASHIERT], togglelight);
					}
					else if (pObj->getID() == OBJ_CUBE)
					{
						RenderMesh(meshList[GEO_CUBE], togglelight);
					}
					else if (pObj->getID() == OBJ_CEILING)
					{
						RenderMesh(meshList[GEO_SUPERMARKET_CEILING], togglelight);
					}
					else if (pObj->getID() == OBJ_CAMERA)
					{
						RenderMesh(meshList[GEO_CAMERA], togglelight);
					}
					else if (pObj->getID() == OBJ_SCREEN)
					{
						RenderMesh(meshList[GEO_SCREEN], togglelight);
					}
					modelStack.PopMatrix();
				}
			}
		}
	}
	if(floorNum == 2) // second floor
	{
		for( int i = 0 ; i < objList2.size(); ++i)
		{
			pObj = objList2[i];
			if(pObj->getRender())
			{
				if(pObj->getID() == OBJ_SHELF)
				{
					renderShelf();
				}
				/*
				else if(pObj->getID() == OBJ_CABINET_T)
				{
					modelStack.PushMatrix();
					RenderMesh(meshList[GEO_CABINET], togglelight);
					modelStack.PopMatrix();
				}*/
				else
				{
					modelStack.PushMatrix();
					modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
					modelStack.Rotate(pObj->getRotate().x, 1,0,0);
					modelStack.Rotate(pObj->getRotate().y, 0,1,0);
					modelStack.Rotate(pObj->getRotate().z, 0,0,1);
					modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
					if (pObj->getID() == OBJ_TABLE)
					{
						RenderMesh(meshList[GEO_CASHIERT], togglelight);
					}
					else if (pObj->getID() == OBJ_CUBE)
					{
						RenderMesh(meshList[GEO_CUBE], togglelight);
					}
					else if (pObj->getID() == OBJ_CEILING)
					{
						RenderMesh(meshList[GEO_SUPERMARKET_CEILING], togglelight);
					}
					else if (pObj->getID() == OBJ_CAMERA)
					{
						RenderMesh(meshList[GEO_CAMERA], togglelight);
					}
					else if (pObj->getID() == OBJ_SCREEN)
					{
						RenderMesh(meshList[GEO_SCREEN], togglelight);
					}
					modelStack.PopMatrix();
				}
			}
		}
	}

	// Car screen
	if (hands[0] != NULL && hands[1] != NULL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
		modelStack.Rotate(hands[0]->getRotate().y - 90, 0, 1, 0);
		modelStack.Scale(3.4 * hands[0]->getScale().x, 3 * hands[0]->getScale().y, 1);
		RenderMesh(meshList[GEO_CAR_SCREEN], togglelight);
		modelStack.PopMatrix();
	}
	else
	{
		renderHands();
	}

	// Target test
	
	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	modelStack.Scale(1,1,1);
	RenderMesh(meshList[GEO_CUBE], togglelight);
	modelStack.PopMatrix();

	RenderMesh(meshList[GEO_AXES], false);

	renderText();
}

void SP2::renderText()
{
	std::ostringstream sFPS, sOrient, sPitch, sX, sY, sZ, cH;
	sFPS << fps;
	sPitch << rotateHandX;
	sOrient << rotateHandY;
	sX << camera.position.x;
	sY << camera.position.y;
	sZ << camera.position.z;

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 1, 0), 2, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], sFPS.str(), Color(0, 1, 0), 2, 6, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "Orientation: ", Color(0, 1, 0), 2, 1, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], sOrient.str(), Color(0, 1, 0), 2, 20, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Pitch: ", Color(0, 1, 0), 2, 1, 6);
	RenderTextOnScreen(meshList[GEO_TEXT], sPitch.str(), Color(0, 1, 0), 2, 10, 6);  
	RenderTextOnScreen(meshList[GEO_TEXT], "X: ", Color(0, 1, 0), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], sX.str(), Color(0, 1, 0), 2, 4, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y: ", Color(0, 1, 0), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], sY.str(), Color(0, 1, 0), 2, 4, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z: ", Color(0, 1, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], sZ.str(), Color(0, 1, 0), 2, 4, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], "<o>", Color(1,1,1), 2, 19.2, 15);
}

void SP2::renderHands()
{
	if(cam == false)
	{
		// Left hands
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

		modelStack.Rotate(rotateHandY, 0, 1, 0);
		modelStack.Rotate(rotateHandX,1,0,0);
		modelStack.Scale(.4,.4,1.5);
		modelStack.PushMatrix();

		modelStack.Translate(1.5,-1.5,-1);
		RenderMesh(meshList[GEO_PLAYER], togglelight);
		modelStack.PopMatrix();

		modelStack.PopMatrix();

		// Right hands
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

		modelStack.Rotate(rotateHandY, 0, 1, 0);
		modelStack.Rotate(rotateHandX,1,0,0);
		modelStack.Scale(.4,.4,1.5);
		modelStack.PushMatrix();

		modelStack.Translate(-1.5,-1.5,-1);
		RenderMesh(meshList[GEO_PLAYER], togglelight);
		modelStack.PopMatrix();

		modelStack.PopMatrix();
	}
}

void SP2::renderShelf()
{
	modelStack.PushMatrix();

	modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Rotate(pObj->getRotate().x, 1,0,0);
	modelStack.Rotate(pObj->getRotate().y, 0,1,0);
	modelStack.Rotate(pObj->getRotate().z, 0,0,1);
	modelStack.PushMatrix();
	modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
	RenderMesh(meshList[GEO_SHELF], togglelight);
	modelStack.PopMatrix();
	modelStack.PushMatrix();

	CItem* pItem;

	for(int a = 0; a < static_cast<CShelf*>(pObj)->itemList.size();++a)
	{
		pItem = static_cast<CShelf*>(pObj)->itemList[a];

		modelStack.PushMatrix();
		modelStack.Translate(pItem->getTranslate().x, pItem->getTranslate().y, pItem->getTranslate().z);
		modelStack.Rotate(pItem->getRotate().x, 1,0,0);
		modelStack.Rotate(pItem->getRotate().y, 0,1,0);
		modelStack.Rotate(pItem->getRotate().z, 0,0,1);
		modelStack.Scale(pItem->getScale().x, pItem->getScale().y, pItem->getScale().z);
		RenderMesh(pItem->getItem(),togglelight);
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();
	modelStack.PopMatrix();


}
void SP2::renderItems(int choice)
{
	modelStack.PushMatrix();
	modelStack.Scale(5,5,5);

	switch (choice)
	{
	case 1:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_1], togglelight);
			modelStack.PopMatrix();
		}
	case 2:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_2], togglelight);
			modelStack.PopMatrix();
		}
	case 3:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_3], togglelight);
			modelStack.PopMatrix();
		}
	case 4:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_4], togglelight);
			modelStack.PopMatrix();
		}
	case 5:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_5], togglelight);
			modelStack.PopMatrix();
		}
	case 6:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_6], togglelight);
			modelStack.PopMatrix();
		}
	case 7:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_7], togglelight);
			modelStack.PopMatrix();
		}
	case 8:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_8], togglelight);
			modelStack.PopMatrix();
		}
	case 9:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_9], togglelight);
			modelStack.PopMatrix();
		}
	case 10:
		{
			modelStack.PushMatrix();
			RenderMesh(meshList[GEO_ITEM_10], togglelight);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();
}


void SP2::renderSuperMarket()
{

	modelStack.PushMatrix();
	modelStack.Translate(supermarketPosition.x,supermarketPosition.y,supermarketPosition.z);
	modelStack.Scale(supermarketScale.x,supermarketScale.y,supermarketScale.z);

	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_SM], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-1.55-translateX,0,10);
	modelStack.Scale(0.6,0.5,0.5);
	RenderMesh(meshList[GEO_SMD], togglelight);//right Door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(1.55+translateX,0,10);
	modelStack.Scale(0.6,0.5,0.5);
	RenderMesh(meshList[GEO_SMD], togglelight);//left Door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate( 1.55 + translateLiftX, 0 , -10);
	modelStack.Scale( 0.6,0.5,0.5);
	RenderMesh(meshList[GEO_SMLD] , togglelight); // lift left door
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate( -1.55 - translateLiftX, 0 , -10);
	modelStack.Scale( 0.6,0.5,0.5);
	RenderMesh(meshList[GEO_SMLD] , togglelight); // lift left door
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SP2::renderCar()
{
	modelStack.PushMatrix();								// Start of car
	modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y + 5, pObj->getTranslate().z);
	modelStack.Rotate(pObj->getRotate().x, 1,0,0);
	modelStack.Rotate(pObj->getRotate().y, 0,1,0);
	modelStack.Rotate(pObj->getRotate().z, 0,0,1);
	modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
	modelStack.PushMatrix();								// Start of car body
	RenderMesh(meshList[GEO_CAR], togglelight);
	modelStack.PopMatrix();									// End of car body
	for(int x = -5; x < 11; x += 10)						// Car tyres
	{
		for(int y = -3; y < 4; y += 6)
		{
			modelStack.PushMatrix();
			modelStack.Translate(x,0,y);
			RenderMesh(meshList[GEO_CAR_TYRE], togglelight);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();									// End of car
}

void SP2::renderHuman() 
{

	
	
	

	if(static_cast<CCharacter*>(pObj)->getRole()==1)
	{

		modelStack.PushMatrix();
		modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
		modelStack.Rotate(pObj->getRotate().x, 1,0,0);
		modelStack.Rotate(pObj->getRotate().y, 0,1,0);
		modelStack.Rotate(pObj->getRotate().z, 0,0,1);
		modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_HUMAN_STAFF_BODY], togglelight);
		modelStack.PopMatrix();
		// ================================ L_SHOULDERs =======================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2.8,0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight); 
		modelStack.PopMatrix();
	//=============================== L_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);

	modelStack.PopMatrix();
	
	// ================================ R_SHOULDER =======================
	modelStack.PushMatrix();
	modelStack.Translate(-1.5,2.8, 0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight);
		modelStack.PopMatrix();
	//=============================== R_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(-1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);
	modelStack.PopMatrix();

	
	// ================================== R_LEGS ========================
	modelStack.PushMatrix();
	modelStack.Translate(-0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_LEG] , togglelight);
	modelStack.PopMatrix();
	
	// =========================== L_LEGS ==============================
	modelStack.PushMatrix();
	modelStack.Translate(0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_STAFF_LEG], togglelight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	}
	else if(static_cast<CCharacter*>(pObj)->getRole()==2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
		modelStack.Rotate(pObj->getRotate().x, 1,0,0);
		modelStack.Rotate(pObj->getRotate().y, 0,1,0);
		modelStack.Rotate(pObj->getRotate().z, 0,0,1);
		modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_BODY], togglelight);
		modelStack.PopMatrix();
				// ================================ L_SHOULDERs =======================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2.8,0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_ARM], togglelight); 
		modelStack.PopMatrix();
	//=============================== L_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_HAND], togglelight);

	modelStack.PopMatrix();
	
	// ================================ R_SHOULDER =======================
	modelStack.PushMatrix();
	modelStack.Translate(-1.5,2.8, 0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_ARM], togglelight);
		modelStack.PopMatrix();
	//=============================== R_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(-1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_HAND], togglelight);
	modelStack.PopMatrix();

	
	// ================================== R_LEGS ========================
	modelStack.PushMatrix();
	modelStack.Translate(-0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_LEG] , togglelight);
	modelStack.PopMatrix();
	
	// =========================== L_LEGS ==============================
	modelStack.PushMatrix();
	modelStack.Translate(0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_LEG], togglelight);
	modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else if(static_cast<CCharacter*>(pObj)->getRole()==3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
		modelStack.Rotate(pObj->getRotate().x, 1,0,0);
		modelStack.Rotate(pObj->getRotate().y, 0,1,0);
		modelStack.Rotate(pObj->getRotate().z, 0,0,1);	
		modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
		modelStack.PushMatrix();
		RenderMesh(meshList[GEO_HUMAN_SHOPPER_BODY], togglelight);
		modelStack.PopMatrix();
				// ================================ L_SHOULDERs =======================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2.8,0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_ARM], togglelight); 
		modelStack.PopMatrix();
	//=============================== L_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_HAND], togglelight);

	modelStack.PopMatrix();
	
	// ================================ R_SHOULDER =======================
	modelStack.PushMatrix();
	modelStack.Translate(-1.5,2.8, 0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_ARM], togglelight);
		modelStack.PopMatrix();
	//=============================== R_HANDS =========================
	modelStack.PushMatrix();
		modelStack.Translate(-1.5,2,0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_HAND], togglelight);
	modelStack.PopMatrix();

	
	// ================================== R_LEGS ========================
	modelStack.PushMatrix();
	modelStack.Translate(-0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG] , togglelight);
	modelStack.PopMatrix();
	
	// =========================== L_LEGS ==============================
	modelStack.PushMatrix();
	modelStack.Translate(0.6,0.75,0);
	RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG], togglelight);
	modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	




	
	//if(type == 2)
	//{
	//	modelStack.PushMatrix();
	//	{
	//		//===================================== BODY ===========================
	//		RenderMesh(meshList[GEO_HUMAN_POLICE_BODY], togglelight); 
	//		modelStack.PushMatrix();
	//		{
	//			// ================================ L_SHOULDERs =======================
	//			modelStack.Translate(1.5,2.8,0);
	//			RenderMesh(meshList[GEO_HUMAN_POLICE_ARM], togglelight); 
	//			modelStack.PushMatrix();
	//			{
	//				//=============================== L_HANDS =========================
	//				modelStack.Translate(0,-0.9,0);
	//				RenderMesh(meshList[GEO_HUMAN_POLICE_HAND], togglelight);
	//			}
	//			modelStack.PopMatrix();
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// ================================ R_SHOULDER =======================
	//			modelStack.Translate(-1.5,2.8, 0);
	//			RenderMesh(meshList[GEO_HUMAN_POLICE_ARM], togglelight);
	//			modelStack.PushMatrix();
	//			{
	//				//=============================== R_HANDS =========================
	//				modelStack.Translate(0,-0.9,0);
	//				RenderMesh(meshList[GEO_HUMAN_POLICE_HAND], togglelight);
	//			}
	//			modelStack.PopMatrix();
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// ================================== R_LEGS ========================
	//			modelStack.Translate(-0.6,0.75,0);
	//			RenderMesh(meshList[GEO_HUMAN_POLICE_LEG] , togglelight);
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// =========================== L_LEGS ==============================
	//			modelStack.Translate(0.6,0.75,0);
	//			RenderMesh(meshList[GEO_HUMAN_POLICE_LEG], togglelight);
	//		}
	//		modelStack.PopMatrix();
	//	}
	//	modelStack.PopMatrix();
	//}
	//if(type == 3)
	//{
	//	modelStack.PushMatrix();
	//	{
	//		//===================================== BODY ===========================
	//		RenderMesh(meshList[GEO_HUMAN_STAFF_BODY], togglelight); 
	//		modelStack.PushMatrix();
	//		{
	//			// ================================ L_SHOULDERs =======================
	//			modelStack.Translate(1.5,2.8,0);
	//			RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight); 
	//			modelStack.PushMatrix();
	//			{
	//				//=============================== L_HANDS =========================
	//				modelStack.Translate(0,-0.9,0);
	//				RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);
	//			}
	//			modelStack.PopMatrix();
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// ================================ R_SHOULDER =======================
	//			modelStack.Translate(-1.5,2.8, 0);
	//			RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight);
	//			modelStack.PushMatrix();
	//			{
	//				//=============================== R_HANDS =========================
	//				modelStack.Translate(0,-0.9,0);
	//				RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);
	//			}
	//			modelStack.PopMatrix();
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// ================================== R_LEGS ========================
	//			modelStack.Translate(-0.6,0.75,0);
	//			RenderMesh(meshList[GEO_HUMAN_STAFF_LEG] , togglelight);
	//		}
	//		modelStack.PopMatrix();
	//		modelStack.PushMatrix();
	//		{
	//			// =========================== L_LEGS ==============================
	//			modelStack.Translate(0.6,0.75,0);
	//			RenderMesh(meshList[GEO_HUMAN_STAFF_LEG], togglelight);
	//		}
	//		modelStack.PopMatrix();
	//	}
	//	modelStack.PopMatrix();
	//}
	//modelStack.PopMatrix();
}

void SP2::renderOuterSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -outerSkyboxSize.z/2 + skyboxOffset);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_FRONT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, outerSkyboxSize.z/2 - skyboxOffset);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_BACK], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-outerSkyboxSize.z/2 + skyboxOffset, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_LEFT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(outerSkyboxSize.z/2 - skyboxOffset, 0, 0);
	modelStack.Rotate(-90,0,1,0);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_RIGHT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, outerSkyboxSize.y/2 - skyboxOffset, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_TOP], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(outerSkyboxSize.x, outerSkyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_BOTTOM], togglelight);
	modelStack.PopMatrix();

}

void SP2::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void SP2::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SP2::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SP2::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
