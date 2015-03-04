#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <sstream>
#include <ctime>
#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

SP2::SP2()
{
}

SP2::~SP2()
{
}

void SP2::Init()
{


	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
	camera.Init(Vector3(0,30,30), Vector3(0,30,15), Vector3(0,1,0));

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

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("Text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");

	// Test unit cube
	meshList[GEO_CUBE] = MeshBuilder::GenerateOBJ("Cube" , "OBJ//Cube.obj");
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//MazeWall.tga");

	srand(time(NULL));

	for(int a = 0;a<5;++a)
	{
	initHuman(3,Vector3(0,0,300),Vector3(0,90,0),camera.position,60);	
	}

	initHuman(2,Vector3(0,0,50),Vector3(0,90,0),camera.position,60);	

	initHuman(1,Vector3(80,0,40),Vector3(0,0,0),camera.position,60);

	initValues();
	initCar();
	initOuterSkybox();
	initSuperMarket();
	initPatch();
	initHands();
	initCabinet();
	initCamera();
	initGame();
	initSpecialItems();
}

void SP2::initHands()
{
	meshList[GEO_HAND] = MeshBuilder::GenerateOBJ( "Hand" , "OBJ//Cube.obj");
	meshList[GEO_HAND]->textureID = LoadTGA("Image//Hand.tga");
	rotateHandX = rotateHandY = trolleyRotateHandX = 0;
	hands[0] = hands[1] = NULL;
}

void SP2::initCamera()
{
	Vector3 cameraPosition( supermarketPosition.x - (15 * supermarketScale.x) , supermarketPosition.y + (10 * supermarketScale.y) , supermarketPosition.z - (8 * supermarketScale.z));
	Vector3 cameraTarget(0,0,0);
	camNum = 0;

	// camera 1
	pObj = new CSecurityCamera(GEO_SECURITY_CAMERA, cameraPosition, Vector3 (0,0,0), Vector3(1,1,1), Vector3(1,1,1) ,cameraTarget);
	cameraList.push_back(static_cast <CSecurityCamera*>(pObj));

	// camera 2
	cameraPosition.Set( supermarketPosition.x + (15 * supermarketScale.x) , supermarketPosition.y + (10 * supermarketScale.y) , supermarketPosition.z + (8 * supermarketScale.z));
	pObj = new CSecurityCamera(GEO_SECURITY_CAMERA, cameraPosition, Vector3 (0,0,0), Vector3 (1,1,1) , Vector3 (1,1,1), cameraTarget);
	cameraList.push_back(static_cast <CSecurityCamera*>(pObj));

	meshList[GEO_SECURITY_CAMERA_SCREEN] = MeshBuilder::GenerateOBJ("Security camera Screen" , "OBJ//Security_camera_screen.obj");
	meshList[GEO_SECURITY_CAMERA_SCREEN]->textureID = LoadTGA("Image//Security_camera_screen.tga");

	// Security camera screen - along back wall
	for(int x = 7.1 * supermarketScale.x ; x < supermarketPosition.x + (supermarketSize.x * supermarketScale.x)/2 ; x += 3 * supermarketScale.x)
	{
		for(int y = 0.2 * supermarketScale.y ; y < supermarketPosition.y + (supermarketSize.y * supermarketSize.y)/2 ; y += 2.5 * supermarketScale.y)
		{
			pObj = new CObj(GEO_SECURITY_CAMERA_SCREEN , Vector3( supermarketPosition.x +  x, supermarketPosition.y + y, supermarketPosition.z - (supermarketSize.z * supermarketScale.z)/2 + ( 0.2 * supermarketScale.z) ) , Vector3(0,0,0), supermarketScale, Vector3(3, 2.5 ,1));
			pObj->calcBound();
			objList2.push_back(pObj);
		}
	}
	// security camera screen - along right wall 
	for(int z = ( - supermarketSize.z * supermarketScale.z )/2 + 1.2 * supermarketScale.z ; z < supermarketPosition.z + (supermarketSize.z *supermarketScale.z )/2; z += 2.2 * supermarketScale.z)
	{
		for(int y = 0.2 * supermarketScale.y ; y < supermarketPosition.y + (supermarketSize.y * supermarketSize.y)/2 ; y += 2.5 * supermarketScale.y)
		{
			pObj = new CObj(GEO_SECURITY_CAMERA_SCREEN, Vector3(supermarketPosition.x + (supermarketScale.x * supermarketSize.x)/2 - 0.7  , supermarketPosition.y + y ,  supermarketPosition.z + z ), Vector3(0,-90,0), supermarketScale , Vector3(3,2.5,1));
			pObj->calcBound();
			objList2.push_back(pObj);
		}
	}

	//security camera screen - along front wall
	for(int x = 7.1 * supermarketScale.x ; x < supermarketPosition.x + (supermarketSize.x * supermarketScale.x)/2 ; x += 3 * supermarketScale.x)
	{
		for(int y = 0.2 * supermarketScale.y ; y < supermarketPosition.y + (supermarketSize.y * supermarketSize.y)/2 ; y += 2.5 * supermarketScale.y)
		{
			pObj = new CObj(GEO_SECURITY_CAMERA_SCREEN , Vector3( supermarketPosition.x +  x, supermarketPosition.y + y, supermarketPosition.z + (supermarketSize.z * supermarketScale.z)/2 - ( 0.2 * supermarketScale.z) ) , Vector3(0,180,0), supermarketScale, Vector3(3, 2.5 ,1));
			pObj->calcBound();
			objList2.push_back(pObj);
		}
	}

	//security room door
	pObj = new CObj(GEO_SUPERMARKET_DOOR , Vector3(supermarketPosition.x + (supermarketSize.x * supermarketScale.x) / 6, supermarketPosition.y , supermarketPosition.z) , Vector3(0,90,0),  Vector3(supermarketScale.x * 0.7,supermarketScale.y * 0.5,supermarketScale.z * 0.8), Vector3(7,10,2));

	Vector3 doorPosition(pObj->getTranslate().x , pObj->getTranslate().y , pObj->getTranslate().z);
	supermarketSecurityDoorMaxBound.Set(doorPosition.x + (3 * supermarketScale.x), doorPosition.y, doorPosition.z + (1 * supermarketScale.z));
	supermarketSecurityDoorMinBound.Set(doorPosition.x - (3 * supermarketScale.x), doorPosition.y, doorPosition.z - (1 * supermarketScale.z));
	translateSecurityZ = 0;
}

void SP2::initShelf(int Choice,Vector3 _translate, Vector3 _rotate)
{
	CItem* pItem;
	pObj = new CShelf(GEO_SHELF,supermarketPosition+(_translate),_rotate,Vector3(11,11,11),Vector3(3,1.5,3),9);
	pObj->calcBound();

	switch(Choice)
	{
	case GEO_ITEM_1:
		{
			for(int x = -10; x<=10 ;x+=10)
			{
				for(int z = -5;z<=5;z+=5)
				{
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_1]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_2]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,0,0),Vector3(10,10,10),Vector3(1,1,1),meshList[GEO_ITEM_3]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,0,0),Vector3(10,10,10),Vector3(1,1,1),meshList[GEO_ITEM_4]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_5]);
					static_cast<CShelf*> (pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_6]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,0,0),Vector3(6,6,6),Vector3(1,1,1),meshList[GEO_ITEM_7]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_8]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(4,4,4),Vector3(1,1,1),meshList[GEO_ITEM_9]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
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
					pItem = new CItem(GEO_ITEM,Vector3(x,3,z),Vector3(0,-90,0),Vector3(6,6,6),Vector3(1,1,1),meshList[GEO_ITEM_10]);
					static_cast<CShelf*>(pObj)->itemList.push_back(pItem);
					static_cast<CShelf*>(pObj)->itemPosition.push_back(pItem->getTranslate());
				}
			}
		}
		break;
	}

	objList.push_back(pObj);
	//shelfList.push_back(static_cast<CShelf*>(pObj));
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

	//inventory pic of items - in enum is 10 behind the original item
	meshList[GEO_INVENTORY_ITEM_1] = MeshBuilder::GenerateQuad("inven_item",Color(1,1,1),TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_1]->textureID = LoadTGA("Image//inventoryImages//inventory_box_1.tga");

	meshList[GEO_INVENTORY_ITEM_2] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_2]->textureID = LoadTGA ("Image//inventoryImages//inventory_can_2.tga");

	meshList[GEO_INVENTORY_ITEM_3] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_3]->textureID = LoadTGA("Image//inventoryImages//inventory_box_3.tga");

	meshList[GEO_INVENTORY_ITEM_4] = MeshBuilder::GenerateQuad ("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_4]->textureID = LoadTGA("Image//inventoryImages//inventory_can_4.tga");

	meshList[GEO_INVENTORY_ITEM_5] = MeshBuilder::GenerateQuad("inven_item", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_5]->textureID = LoadTGA("Image//inventoryImages//inventory_box_5.tga");

	meshList[GEO_INVENTORY_ITEM_6] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_6]->textureID = LoadTGA("Image//inventoryImages//inventory_box_6.tga");

	meshList[GEO_INVENTORY_ITEM_7] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_7]->textureID = LoadTGA("Image//inventoryImages//inventory_box_7.tga");

	meshList[GEO_INVENTORY_ITEM_8] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_8]->textureID = LoadTGA("Image//inventoryImages//inventory_can_8.tga");

	meshList[GEO_INVENTORY_ITEM_9] = MeshBuilder::GenerateQuad("inven_item" , Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_9]->textureID = LoadTGA("Image//inventoryImages//inventory_packet_9.tga");

	meshList[GEO_INVENTORY_ITEM_10] = MeshBuilder::GenerateQuad("inven_item", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_INVENTORY_ITEM_10]->textureID = LoadTGA("Image//inventoryImages//inventory_box_10.tga");
}

void SP2::initCar()
{
	meshList[GEO_CAR] = MeshBuilder::GenerateOBJ("Car", "OBJ//Car.obj");
	meshList[GEO_CAR]->textureID = LoadTGA("Image//Car.tga");
	meshList[GEO_CAR]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_CAR]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR]->material.kShininess = 1.f;

	meshList[GEO_CAR_TYRE] = MeshBuilder::GenerateOBJ("Car tyre", "OBJ//Car_tyre.obj");
	meshList[GEO_CAR_TYRE]->textureID = LoadTGA("Image//Car_tyre.tga");
	meshList[GEO_CAR_TYRE]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR_TYRE]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_CAR_TYRE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GEO_CAR_TYRE]->material.kShininess = 1.f;

	meshList[GEO_CAR_SCREEN] = MeshBuilder::GenerateQuad("Car screen", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_CAR_SCREEN]->textureID = LoadTGA("Image//Car_screen.tga");

	pObj = new CCar(GEO_CAR, Vector3(-200,0,300), Vector3(0,0,0), Vector3(2.5,5,5), Vector3(17.5,4,7));
	pObj->calcBound();
	static_cast<CCar*>(pObj)->setCamera();
	objList.push_back(pObj);
	carList.push_back(static_cast<CCar*>(pObj));
}

void SP2::initCabinet()
{	
	//Special Display Cabinet with the Tardis
	tardisY = 0;
	rotTardis = 0;
	tardisPitch = 0;
	meshList[GEO_DISPLAY1] = MeshBuilder::GenerateOBJ("Display Cabinet with Tardis", "OBJ//display_case.obj");
	meshList[GEO_DISPLAY1] ->textureID = LoadTGA("Image//displayGallifrey.tga");
	pObj = new CObj(GEO_DISPLAY1, Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + .25 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x ,supermarketScale.y *.3,supermarketScale.z * 0.75), Vector3(3, 3 ,3));
	//pObj->calcBound();
	objList2.push_back(pObj);
	//FangShu Display Cabinet
	meshList[GEO_DISPLAY2] = MeshBuilder::GenerateOBJ("Display Cabinet with Potato", "OBJ//display_case.obj");
	meshList[GEO_DISPLAY2] ->textureID = LoadTGA("Image//displayPotato.tga");
	pObj = new CObj(GEO_DISPLAY2, Vector3 (supermarketPosition.x -9 * supermarketScale.x, supermarketPosition.y + .25 * supermarketScale.y, supermarketPosition.z * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x ,supermarketScale.y*.3,supermarketScale.z * 0.75), Vector3(3, 3 ,3));
	//pObj->calcBound();
	objList2.push_back(pObj);
	//Tim Lin Display Cabinet
	meshList[GEO_DISPLAY3] = MeshBuilder::GenerateOBJ("Display Cabinet with Tim Lin's Item",  "OBJ//display_case.obj");
	meshList[GEO_DISPLAY3]->textureID = LoadTGA("Image//displaySilver.tga");
	pObj = new CObj(GEO_DISPLAY3, Vector3 (supermarketPosition.x -9 * supermarketScale.x, supermarketPosition.y + .25 * supermarketScale.y, supermarketPosition.z + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x ,supermarketScale.y*.3,supermarketScale.z * 0.75), Vector3(3, 3 ,3));
	//pObj->calcBound();
	objList2.push_back(pObj);
	//Rayson Display Cabinet
	meshList[GEO_DISPLAY4] = MeshBuilder::GenerateOBJ("Display Cabinet with Thor's Item",  "OBJ//display_case.obj");
	meshList[GEO_DISPLAY4]->textureID = LoadTGA("Image//displayCircuit.tga");
	pObj = new CObj(GEO_DISPLAY4, Vector3 (supermarketPosition.x  * supermarketScale.x, supermarketPosition.y + .25 * supermarketScale.y, supermarketPosition.z + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x ,supermarketScale.y*.3,supermarketScale.z * 0.75), Vector3(3, 3 ,3));
	//pObj->calcBound();
	objList2.push_back(pObj);
}

void SP2::initSpecialItems()
{
	//Time Potato
	meshList[GEO_POTATO] = MeshBuilder::GenerateOBJ("Potato", "OBJ//potato.obj");
	meshList[GEO_POTATO] ->textureID = LoadTGA("Image//potato.tga");
	pObj = new CObj(GEO_POTATO, Vector3 (supermarketPosition.x -9 * supermarketScale.x, supermarketPosition.y + 1.5 * supermarketScale.y, supermarketPosition.z * supermarketScale.z), Vector3(0,0,-45), Vector3(supermarketScale.x* .15 ,supermarketScale.y * .15,supermarketScale.z * .15), Vector3(3, 3 ,3)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//Mjolnir
	meshList[GEO_THOR] = MeshBuilder::GenerateOBJ("Mjolnir", "OBJ//mjolnir.obj");
	meshList[GEO_THOR]->textureID = LoadTGA("Image//mjolnir.tga");
	pObj = new CObj(GEO_THOR, Vector3 (supermarketPosition.x  * supermarketScale.x, supermarketPosition.y + .8 * supermarketScale.y, supermarketPosition.z + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .8 ,supermarketScale.y * .8,supermarketScale.z * .45886), Vector3(3, 3 ,3)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//WUKONG'S STAFF
	meshList[GEO_WUKONG] = MeshBuilder::GenerateOBJ("Jingu Bang", "OBJ//wukong_staff.obj");
	meshList[GEO_WUKONG]->textureID = LoadTGA("Image//wukong_staff.tga");
	pObj = new CObj(GEO_WUKONG, Vector3 (supermarketPosition.x -9 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .4 ,supermarketScale.y * .4,supermarketScale.z * .3), Vector3(3, 3 ,3)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//TARDIS
	//------------------------------------------------------------------------------TARDIS_BASE-------------------------------------------------------------------------------------------------
	meshList[GEO_TARDIS_BOT] = MeshBuilder::GenerateOBJ("Tardis Base", "OBJ//tardis//tardis_base.obj");
	meshList[GEO_TARDIS_BOT]->textureID = LoadTGA("Image//tardis//tardis_base.tga");
	pObj = new CObj(GEO_TARDIS_BOT,Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .3 ,supermarketScale.y * .3,supermarketScale.z * .225), Vector3(9, 9 ,9)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//------------------------------------------------------------------------------TARDIS_BODY------------------------------------------------------------------------------------------------
	meshList[GEO_TARDIS_MID] = MeshBuilder::GenerateOBJ("Tardis Body", "OBJ//tardis//tardis_body.obj");
	meshList[GEO_TARDIS_MID] -> textureID = LoadTGA("Image//tardis//tardis_body.tga");
	pObj = new CObj(GEO_TARDIS_MID,Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .3 ,supermarketScale.y * .3,supermarketScale.z * .225),  Vector3(9, 9 ,9)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//------------------------------------------------------------------------------TARDIS_SIGN-------------------------------------------------------------------------------------------------
	meshList[GEO_TARDIS_SIGN] = MeshBuilder::GenerateOBJ("Tardis Sign", "OBJ//tardis//tardis_police.obj");
	meshList[GEO_TARDIS_SIGN]->textureID = LoadTGA("Image//tardis//tardis_police.tga");
	pObj = new CObj(GEO_TARDIS_SIGN,Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .3 ,supermarketScale.y * .3,supermarketScale.z * .225), Vector3(9, 9 ,9)); 
	pObj->calcBound();
	objList2.push_back(pObj);
	//------------------------------------------------------------------------------TARDIS_TOP--------------------------------------------------------------------------------------------------
	meshList[GEO_TARDIS_TOP] = MeshBuilder::GenerateOBJ("Tardis Base", "OBJ//tardis//tardis_roof.obj");
	meshList[GEO_TARDIS_TOP]->textureID = LoadTGA("Image//tardis//tardis_base.tga");
	pObj = new CObj(GEO_TARDIS_TOP,Vector3 (supermarketPosition.x - 9 * supermarketScale.x, supermarketPosition.y + 1 * supermarketScale.y, supermarketPosition.z - 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x* .3 ,supermarketScale.y * .3,supermarketScale.z * .225),  Vector3(9, 9 ,9)); 
	pObj->calcBound();
	objList2.push_back(pObj);
}

void SP2::initSuperMarket()
{
	// Supermarket
	supermarketSize.Set(30,20,20);
	supermarketPosition.Set(0,0,0);
	supermarketScale.Set(11,11,14.85);
	supermarketLiftScale = supermarketScale;
	supermarketLiftSize.Set(5.5, 1, 6.6);
	supermarketLiftPosition.Set(supermarketPosition.x , supermarketPosition.y, supermarketPosition.z - (( supermarketScale.z * supermarketSize.z ) / 2) - ( supermarketLiftScale.z * supermarketLiftSize.z) / 2);

	initItems();
	// Supermarket shelf
	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("Shelf" , "OBJ//Shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//Shelf.tga");

	// Supermarket building
	meshList[GEO_SUPERMARKET] = MeshBuilder::GenerateOBJ("Supermarket", "OBJ//Supermarket.obj");
	meshList[GEO_SUPERMARKET]->textureID = LoadTGA("Image//Supermarket.tga");

	// Supermarket ceiling
	meshList[GEO_SUPERMARKET_CEILING] = MeshBuilder::GenerateOBJ("SuperMarket Ceiling", "OBJ//Ceiling.obj");
	meshList[GEO_SUPERMARKET_CEILING]->textureID = LoadTGA("Image//Ceiling.tga");

	// Cashier Table
	meshList[GEO_CASHIER_TABLE] = MeshBuilder::GenerateOBJ("Cashier table" , "OBJ//Cashier_table.obj");
	meshList[GEO_CASHIER_TABLE]->textureID = LoadTGA("Image//Cashier_table.tga");

	// Security camera
	meshList[GEO_SECURITY_CAMERA] = MeshBuilder::GenerateOBJ("Security camera" , "OBJ//Security_camera.obj");
	meshList[GEO_SECURITY_CAMERA]->textureID = LoadTGA("Image//Security_camera.tga");

	// Supermarket door
	meshList[GEO_SUPERMARKET_DOOR] = MeshBuilder::GenerateOBJ( "Supermarket door" ,"OBJ//Supermarket_door.obj");
	meshList[GEO_SUPERMARKET_DOOR]->textureID = LoadTGA("Image//Supermarket_door.tga");

	// Trolley
	meshList[GEO_TROLLEY] = MeshBuilder::GenerateOBJ("Trolley", "OBJ//Trolley.obj");
	meshList[GEO_TROLLEY]->textureID = LoadTGA("Image//trolleytexture.tga");

	//paper bag - used for game 2 cashier
	meshList[GEO_BAG] = MeshBuilder::GenerateOBJ("Bag" , "OBJ//bag.obj");
	meshList[GEO_BAG]->textureID = LoadTGA ("Image//bagTex.tga");

	pObj = new CObj(GEO_SUPERMARKET_CEILING, Vector3(supermarketPosition.x, supermarketPosition.y + 10 * supermarketScale.y, supermarketPosition.z), Vector3(0,0,0), Vector3(supermarketScale.x,supermarketScale.y,supermarketScale.z), Vector3(1,1,1));
	objList.push_back(pObj);
	objList2.push_back(pObj);

	pObj = new CObj(GEO_CASHIER_TABLE , Vector3(supermarketPosition.x + 4.1 * supermarketScale.x, supermarketPosition.y + 0.25 * supermarketScale.y, supermarketPosition.z + 6 * supermarketScale.z), Vector3(0,0,0), Vector3(supermarketScale.x / 2, supermarketScale.y / 2, supermarketScale.z / 2), Vector3(4 , 3.5 , 11));
	pObj->calcBound();
	objList.push_back(pObj);

	pObj = new CObj(GEO_SECURITY_CAMERA , Vector3(supermarketPosition.x - 14.65 * supermarketScale.x, supermarketPosition.y + 9.6 * supermarketScale.y, supermarketPosition.z - 9.5 * supermarketScale.z), Vector3(0,0,0), Vector3(0.2 * supermarketScale.x,0.2 * supermarketScale.y,0.2 * supermarketScale.z), Vector3(2 ,1.5, 2));
	pObj->calcBound();
	objList.push_back(pObj);

	// Left wall
	Vector3 tempWallPosition(supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2), supermarketPosition.y, supermarketPosition.z);
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(5,supermarketSize.y * supermarketScale.y, supermarketSize.z * supermarketScale.z), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	// Right wall
	tempWallPosition.Set(supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2), supermarketPosition.y, supermarketPosition.z);
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(5,supermarketSize.y * supermarketScale.y, supermarketSize.z * supermarketScale.z), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	float halfLength = ((((supermarketScale.x * supermarketSize.x) / 2) - (2 * supermarketScale.x)) / 2); // Half length between corner to door along x-axis
	// Front left wall
	tempWallPosition.Set(((supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2)) + halfLength), supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);

	// Front right wall
	tempWallPosition.Set(((supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2)) - halfLength), supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);

	//2nd floor front wall 
	tempWallPosition.Set(supermarketPosition.x , supermarketPosition.y , supermarketPosition.z + (supermarketScale.z * supermarketSize.z ) / 2);
	pObj = new CObj (GEO_SUPERMARKET_WALL , Vector3(tempWallPosition.x , tempWallPosition.y , tempWallPosition.z) ,Vector3(0,0,0) ,Vector3(supermarketSize.x * supermarketScale.x , supermarketScale.y * supermarketSize.y , 5) , Vector3(1,1,1));
	pObj->calcBound();
	objList2.push_back(pObj);

	// Back left wall
	tempWallPosition.Set(((supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2)) + halfLength), supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor

	// Back right wall
	tempWallPosition.Set(((supermarketPosition.x + ((supermarketScale.x * supermarketSize.x) / 2)) - halfLength), supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	pObj = new CObj(GEO_SUPERMARKET_WALL, Vector3(tempWallPosition.x, tempWallPosition.y, tempWallPosition.z), Vector3(0,0,0), Vector3(halfLength * 2,supermarketSize.y * supermarketScale.y, 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // for 2nd floor	

	//lift left wall
	tempWallPosition.Set(supermarketLiftPosition.x + (supermarketLiftScale.x * supermarketLiftSize.x)/2, supermarketLiftPosition.y, supermarketLiftPosition.z );
	pObj = new CObj(GEO_SUPERMARKET_WALL , Vector3( tempWallPosition.x , tempWallPosition.y, tempWallPosition.z) , Vector3(0,0,0) , Vector3(supermarketLiftSize.x / 5, supermarketScale.y * supermarketLiftSize.y, supermarketLiftScale.z * supermarketLiftSize.z ), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	//right lift wall
	tempWallPosition.Set(supermarketLiftPosition.x - (supermarketLiftScale.x * supermarketLiftSize.x)/2, supermarketLiftPosition.y, supermarketLiftPosition.z );
	pObj = new CObj(GEO_SUPERMARKET_WALL , Vector3( tempWallPosition.x , tempWallPosition.y, tempWallPosition.z) , Vector3(0,0,0) , Vector3(supermarketLiftSize.x / 5, supermarketScale.y * supermarketLiftSize.y, supermarketLiftScale.z * supermarketLiftSize.z ), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	//lift back wall
	tempWallPosition.Set(supermarketLiftPosition.x, supermarketLiftPosition.y, supermarketLiftPosition.z - (supermarketLiftSize.z * supermarketLiftScale.z)/3.2);
	pObj = new CObj(GEO_SUPERMARKET_WALL , Vector3( tempWallPosition.x , tempWallPosition.y, tempWallPosition.z) , Vector3(0,0,0) , Vector3(supermarketLiftSize.x * supermarketLiftScale.x , supermarketScale.y * supermarketLiftSize.y,supermarketLiftSize.z/ 5), Vector3(1,1,1));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj); // 2nd floor

	// Entrance door (Interaction bounds)
	Vector3 doorPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	supermarketDoorMaxBound.Set(doorPosition.x + (3 * supermarketScale.x), doorPosition.y, doorPosition.z + (5 * supermarketScale.z));
	supermarketDoorMinBound.Set(doorPosition.x - (3 * supermarketScale.x), doorPosition.y, doorPosition.z - (5 * supermarketScale.z));
	translateX = 0;

	//Lift (Interaction bound)
	Vector3 liftPosition(supermarketLiftPosition);
	supermarketLiftMaxBound.Set( liftPosition.x + ( supermarketLiftScale.x * supermarketLiftSize.x) / 2 , liftPosition.y , liftPosition.z + (supermarketLiftScale.z * supermarketLiftSize.z / 3) );
	supermarketLiftMinBound.Set( liftPosition.x - ( supermarketLiftScale.x * supermarketLiftSize.x) / 2, liftPosition.y , liftPosition.z - (supermarketLiftScale.z * supermarketLiftSize.z / 2) );

	// lift door (Interaction Bound)
	Vector3 liftDoorPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2));
	supermarketLiftDoorMaxBound.Set(liftDoorPosition.x + (3 * supermarketScale.x), liftDoorPosition.y, liftDoorPosition.z + (5 * supermarketScale.z));
	supermarketLiftDoorMinBound.Set(liftDoorPosition.x - (3 * supermarketScale.x), liftDoorPosition.y, liftDoorPosition.z - (5 * supermarketScale.z));
	translateLiftX = 0;
	disableLiftDoor = false;

	// Right lift door
	pObj = new CObj(GEO_SUPERMARKET_DOOR, supermarketPosition + Vector3(17.05,0, -148.5), Vector3(0,0,0), Vector3(supermarketScale.x * 0.6,supermarketScale.y * 0.5,supermarketScale.z * 0.5), Vector3(7,10,2));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj);
	liftRightDoor = pObj;

	// Left lift door
	pObj = new CObj(GEO_SUPERMARKET_DOOR, supermarketPosition + Vector3(-17.05,0, -148.5), Vector3(0,0,0), Vector3(supermarketScale.x * 0.6,supermarketScale.y * 0.5,supermarketScale.z * 0.5), Vector3(7,10,2));
	pObj->calcBound();
	objList.push_back(pObj);
	objList2.push_back(pObj);
	liftLeftDoor = pObj;

	// Trolley
	pObj = new CTrolley(GEO_TROLLEY, supermarketPosition + Vector3(-100,2,50), Vector3(0,0,0), Vector3(3,3,3), Vector3(5.3,7,5.3));
	pObj->calcBound();
	static_cast<CTrolley*>(pObj)->setCamera();
	objList.push_back(pObj);
	trolleyList.push_back(static_cast<CTrolley*>(pObj));

	//paper bag
	pObj = new CObj(GEO_BAG , supermarketPosition + Vector3( 45, 22, 95), Vector3(0,0,0), Vector3(2,2,2) , Vector3(3, 2, 1.5)); 
	pObj->calcBound();
	objList.push_back(pObj);

	Vector3 leftStartPosition(supermarketPosition.x - ((supermarketScale.x * supermarketSize.x) / 2) + (33 * 1.5), 0, supermarketPosition.z - ((supermarketScale.z * supermarketSize.z) / 2) + (33 * 1.5));
	// Left top row
	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(0 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(0 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(0 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(1 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(1 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_1,leftStartPosition+(Vector3(1 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	initShelf(GEO_ITEM_2,leftStartPosition+(Vector3(2 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_2,leftStartPosition+(Vector3(2 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_2,leftStartPosition+(Vector3(2 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	// Left bottom row
	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(0 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(0 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(0 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(1 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(1 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_3,leftStartPosition+(Vector3(1 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

	initShelf(GEO_ITEM_4,leftStartPosition+(Vector3(2 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_4,leftStartPosition+(Vector3(2 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_4,leftStartPosition+(Vector3(2 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

	// Right top row
	initShelf(GEO_ITEM_5,leftStartPosition+(Vector3(5 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_5,leftStartPosition+(Vector3(5 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_5,leftStartPosition+(Vector3(5 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	initShelf(GEO_ITEM_6,leftStartPosition+(Vector3(6 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_6,leftStartPosition+(Vector3(6 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_6,leftStartPosition+(Vector3(6 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	initShelf(GEO_ITEM_7,leftStartPosition+(Vector3(7 * 33, 0 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_7,leftStartPosition+(Vector3(7 * 33, 1 * 14.5, 1 * 33)), Vector3(0,180,0));
	initShelf(GEO_ITEM_7,leftStartPosition+(Vector3(7 * 33, 2 * 14.5, 1 * 33)), Vector3(0,180,0));

	// Right bottom row
	initShelf(GEO_ITEM_8,leftStartPosition+(Vector3(5 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_8,leftStartPosition+(Vector3(5 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_8,leftStartPosition+(Vector3(5 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

	initShelf(GEO_ITEM_9,leftStartPosition+(Vector3(6 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_9,leftStartPosition+(Vector3(6 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_9,leftStartPosition+(Vector3(6 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

	initShelf(GEO_ITEM_10,leftStartPosition+(Vector3(7 * 33, 0 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_10,leftStartPosition+(Vector3(7 * 33, 1 * 14.5, 2 * 33)), Vector3(0,0,0));
	initShelf(GEO_ITEM_10,leftStartPosition+(Vector3(7 * 33, 2 * 14.5, 2 * 33)), Vector3(0,0,0));

}

void SP2::initHuman(int Choice,Vector3 translation,Vector3 rotation,Vector3 camPosition,int radius) // only human body is stored in obj list 
{
	if(Choice ==1)//HUMAN STAFF
	{
		meshList[GEO_HUMAN_STAFF_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//HumanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_STAFF_BODY]->textureID = LoadTGA("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//HumanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_STAFF_ARM]->textureID = LoadTGA ("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//HumanModel_lefthand.obj");
		meshList[GEO_HUMAN_STAFF_HAND]->textureID = LoadTGA ("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//HumanModel_leftleg.obj");
		meshList[GEO_HUMAN_STAFF_LEG]->textureID = LoadTGA ("Image//Staff.tga");

		pObj = new CCashier(GEO_HUMAN,translation, rotation,Vector3(4,7,4), Vector3(3, 4.6, 3),camera.position,radius);//1.6));
		pObj->calcBound();
		objList.push_back(pObj);
		CharacterList.push_back(static_cast<CCharacter*>(pObj));
	}

	else if(Choice==2)//HUMAN SECURITY GUARD
	{
		meshList[GEO_HUMAN_SECURITYGUARD_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//HumanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_BODY]->textureID = LoadTGA("Image//Police.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//HumanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_ARM]->textureID = LoadTGA ("Image//Police.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//HumanModel_lefthand.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_HAND]->textureID = LoadTGA ("Image//Police.tga");

		meshList[GEO_HUMAN_SECURITYGUARD_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//HumanModel_leftleg.obj");
		meshList[GEO_HUMAN_SECURITYGUARD_LEG]->textureID = LoadTGA ("Image//Police.tga");


		pObj = new CSecurityGuard(GEO_HUMAN,translation, rotation,Vector3(4,7,4), Vector3(3, 4.6, 3),camera.position,radius);//1.6));
		pObj->calcBound();
		objList.push_back(pObj);
		CharacterList.push_back(static_cast<CCharacter*>(pObj));
	}

	else if(Choice ==3)//HUMAN SHOPPER
	{
		meshList[GEO_HUMAN_SHOPPER_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//HumanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_SHOPPER_BODY]->textureID = LoadTGA("Image//Shopper.tga");

		meshList[GEO_HUMAN_SHOPPER_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//HumanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_SHOPPER_ARM]->textureID = LoadTGA ("Image//Shopper.tga");

		meshList[GEO_HUMAN_SHOPPER_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//HumanModel_lefthand.obj");
		meshList[GEO_HUMAN_SHOPPER_HAND]->textureID = LoadTGA ("Image//Shopper.tga");

		meshList[GEO_HUMAN_SHOPPER_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//HumanModel_leftleg.obj");
		meshList[GEO_HUMAN_SHOPPER_LEG]->textureID = LoadTGA ("Image//Shopper.tga");

		pObj = new CShopper(GEO_HUMAN,translation,rotation,Vector3(5,7,5),Vector3(4,4.5,4),camera.position,radius);//1));
		pObj->calcBound();
		objList.push_back(pObj);
		CharacterList.push_back(static_cast<CCharacter*>(pObj));
	}
	else if(Choice == 4)//HUMAN PROMOTER
	{
		meshList[GEO_HUMAN_STAFF_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//HumanModel_bodyNhead.obj");
		meshList[GEO_HUMAN_STAFF_BODY]->textureID = LoadTGA("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_ARM] = MeshBuilder::GenerateOBJ( "p_arm" , "OBJ//HumanModel_leftshoulder.obj");
		meshList[GEO_HUMAN_STAFF_ARM]->textureID = LoadTGA ("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_HAND] = MeshBuilder::GenerateOBJ ( "p_hand" , "OBJ//HumanModel_lefthand.obj");
		meshList[GEO_HUMAN_STAFF_HAND]->textureID = LoadTGA ("Image//Staff.tga");

		meshList[GEO_HUMAN_STAFF_LEG] = MeshBuilder::GenerateOBJ( "p_leg" , "OBJ//HumanModel_leftleg.obj");
		meshList[GEO_HUMAN_STAFF_LEG]->textureID = LoadTGA ("Image//Staff.tga");

		pObj = new CPromoter(GEO_HUMAN,translation, Vector3(0,0,0),Vector3(4,7,4), Vector3(3, 4.6, 3), camera.position, radius);
		pObj->calcBound();
		objList2.push_back(pObj);
		CharacterList.push_back(static_cast<CCharacter*>(pObj));
	}

	//Promoter Interaction Bound
	//Vector3 promoterPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	//promoterMaxBound.Set(promoterPosition.x + (3 * supermarketScale.x), promoterPosition.y, promoterPosition.z + (5 * supermarketScale.z));
	//promoterMinBound.Set(promoterPosition.x - (3 * supermarketScale.x), promoterPosition.y, promoterPosition.z - (5 * supermarketScale.z));
}

void SP2::initPatch()
{
	meshList[GEO_PATCH] = MeshBuilder::GenerateOBJ("wallpatch",  "OBJ//wallpatcher.obj");
	meshList[GEO_PATCH] ->textureID = LoadTGA("Image//walltexture.tga");

	// patch up from entrance when 2nd floor
	pObj = new CObj(GEO_PATCH, Vector3( supermarketPosition.x, supermarketPosition.y , supermarketPosition.z + ( supermarketScale.z * 10 )  ) , Vector3(0,0,0) , Vector3( 1.5 * supermarketScale.x, 1.2 * supermarketScale.y, 1* supermarketScale.z), Vector3( supermarketScale.x * 1 /2 , 1, 1) );
	pObj->calcBound();
	objList2.push_back(pObj);

	// security room wall - right wall
	pObj = new CObj (GEO_PATCH , Vector3(supermarketPosition.x + (supermarketSize.x * supermarketScale.x) / 6, supermarketPosition.y, supermarketPosition.z + (supermarketScale.z * supermarketSize.z)/3.5 ), Vector3(0,90,0), supermarketScale * 3, Vector3(1,1,1));
	objList2.push_back(pObj);

	//wall bounds 
	Vector3 tempWallPosition(pObj->getTranslate());
	pObj = new CObj(GEO_SUPERMARKET_WALL , Vector3(tempWallPosition.x , tempWallPosition.y, tempWallPosition.z ) ,Vector3(0,0,0), supermarketScale , Vector3(1, supermarketSize.y , supermarketSize.z / 2));
	pObj->calcBound();
	objList2.push_back(pObj);

	//security room wall - left wall
	pObj = new CObj (GEO_PATCH , Vector3(supermarketPosition.x + (supermarketSize.x * supermarketScale.x) / 6, supermarketPosition.y ,supermarketPosition.z - (supermarketScale.z * supermarketSize.z)/ 3.5 ), Vector3(0,90,0), supermarketScale * 3, Vector3(1,1,1));
	objList2.push_back(pObj);

	// wall bound
	tempWallPosition.Set(pObj->getTranslate().x , pObj->getTranslate().y , pObj->getTranslate().z);
	pObj = new CObj(GEO_SUPERMARKET_WALL , Vector3(tempWallPosition.x , tempWallPosition.y, tempWallPosition.z ) ,Vector3(0,0,0), supermarketScale , Vector3(1, supermarketSize.y , supermarketSize.z / 2));
	pObj->calcBound();
	objList2.push_back(pObj);

	//security room wall - middle top
	tempWallPosition.Set(supermarketPosition.x + (supermarketScale.x * supermarketSize.x)/ 6  , supermarketPosition.y + (supermarketScale.y * supermarketSize.y) / 2 - (supermarketScale.y * 4.6) , supermarketPosition.z);
	pObj = new CObj(GEO_PATCH, tempWallPosition, Vector3 (0,-90,0), supermarketScale * 2, Vector3 ( 1, 1 ,supermarketSize.z / 2));
	objList2.push_back(pObj);

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
	floorNum = 1; // start at first floor
	newFloor = 1;
	cam = false;
	fps = 60;
	togglelight = false;
	aiTalk == false;
	timer = 0;




	for(int a = 0; a<objList.size();++a)
	{
		if(objList[a]->getID() == GEO_HUMAN)
		{
			if(static_cast <CCharacter*>(objList[a])->getRole()==1)//Cashier
			{
				static_cast<CCharacter*>(objList[a])->setRouteID(0);
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(70,0,65));
			}
			else if(static_cast <CCharacter*>(objList[a])->getRole()==2)//SecurityGuard
			{
				static_cast<CCharacter*>(objList[a])->setRouteID(0);
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(-150,0,40));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(-150,0,-130));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,-130));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,40));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,80));
			}
			else if(static_cast <CCharacter*>(objList[a])->getRole()==3)//Shopper
			{
				static_cast <CCharacter*>(objList[a])->setRouteID(0);
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,300));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(-150,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,-100));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,-100));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,-100));
			}
			else if(static_cast <CCharacter*>(objList[a])->getRole()==4)//Promo
			{
				static_cast <CCharacter*>(objList[a])->setRouteID(0);
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(-100,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(150,0,0));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(-100,0,-100));
				static_cast <CCharacter*>(objList[a])->AiRouteLocation.push_back(Vector3(0,0,-100));
				static_cast <CCharacter*>(objList[a])->AICamera.position=static_cast<CCharacter*>(objList[a])->getTranslate();
			}
		}
	}

	for(int i = 0; i < NUM_KEYPRESS; ++i)
	{
		keypressed[i] = false;
	}

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

void SP2::initGame()
{
	inGame = 0 ;
	//can be used for displaying and storing score - 
	playerScore[0] = 0; // 0-  for game 1
	playerScore[1] = 0; // 1 - for game 2
	playerScore[2] = 0; // 2 - for game 3
	timeFrame = 0; // time fame given to player can be used to display previous attempts
	totalCost = 0; // total amount that is given to player 

	// game 1 - shopper
	Vector3 game1Position(supermarketPosition.x - (3 * supermarketScale.z) , supermarketPosition.y , supermarketPosition.z + ( 3 * supermarketScale.z));
	game1MaxBound.Set( game1Position.x + ( 2 * supermarketScale.x ) , game1Position.y , game1Position.z + ( 2 * supermarketScale.z));
	game1MinBound.Set( game1Position.x - ( 2 * supermarketScale.x ) , game1Position.y , game1Position.z - ( 2 * supermarketScale.z));
	pickCorrect = false;
	randomItem = rand() % 10 + GEO_INVENTORY_ITEM_1; // generate random item - the inventory pic items

	//game2 - cashier
	Vector3 game2Position(supermarketPosition.x + 55, supermarketPosition.y , supermarketPosition.z + 75 );
	game2MaxBound.Set(game2Position.x + (2 * supermarketScale.x) , game2Position.y, game2Position.z + (2 * supermarketScale.z));
	game2MinBound.Set(game2Position.x - (2 * supermarketScale.x) , game2Position.y, game2Position.z - (2 * supermarketScale.z));
	itemLeft = 10; // item left to "check out

	//game 3 - security guard
	Vector3 game3Position(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z );
	game3MaxBound.Set(game3Position.x + (2 * supermarketScale.x) , game3Position.y , game3Position.z + ( 2 * supermarketScale.z));
	game3MinBound.Set(game3Position.x - (2 * supermarketScale.x) , game3Position.y , game3Position.z - ( 2 * supermarketScale.z));

	game3 = false; // to tell if is inside game 3, used by security cam and game 3
	bobMoveX = 0;
	bobMoveZ = 0;
	//initialize BOB - controllable security guard for game 3
	meshList[GEO_GAME3_BOB_BODY] = MeshBuilder::GenerateOBJ("Bob's Body" ,"OBJ//humanModel_bodyNhead.obj");
	meshList[GEO_GAME3_BOB_BODY]->textureID = LoadTGA("Image//Police.tga");
	meshList[GEO_GAME3_BOB_ARM] = MeshBuilder::GenerateOBJ("Bob's arm" , "OBJ//humanModel_leftshoulder.obj");
	meshList[GEO_GAME3_BOB_ARM]->textureID = LoadTGA("Image//Police.tga");
	meshList[GEO_GAME3_BOB_HAND] = MeshBuilder::GenerateOBJ("Bob's hand " , "OBJ//humanModel_lefthand.obj");
	meshList[GEO_GAME3_BOB_HAND]->textureID = LoadTGA("Image//Police.tga");
	meshList[GEO_GAME3_BOB_LEG] = MeshBuilder::GenerateOBJ("BOB's leg", "OBJ//humanModel_leftLeg.obj");
	meshList[GEO_GAME3_BOB_LEG]->textureID = LoadTGA("Image//Police.tga");
}

void SP2::Update(double dt)
{

	if(cam == false)
	{
		if(Application::IsKeyPressed('1')) //enable back face culling
			glEnable(GL_CULL_FACE);
		if(Application::IsKeyPressed('2')) //disable back face culling
			glDisable(GL_CULL_FACE);
		if(Application::IsKeyPressed('3'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
		if(Application::IsKeyPressed('4'))
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode
	}
	keypressed[K_EXIT_CAM] = keypressed[K_LEFT_PICK] = keypressed[K_EXIT_CAR] = Application::IsKeyPressed('Q');
	keypressed[K_LEFT_PLACE] = Application::IsKeyPressed('F');
	keypressed[K_START_STORY] = keypressed[K_ENTER_CAM] = keypressed[K_RIGHT_PICK] = keypressed[K_ENTER_CAR] = Application::IsKeyPressed('E');
	keypressed[K_RIGHT_PLACE] = Application::IsKeyPressed('G');
	keypressed[K_FIRST_FLOOR] = Application::IsKeyPressed('O');
	keypressed[K_SECOND_FLOOR] = Application::IsKeyPressed('P');
	keypressed[K_ENTER_TROLLEY] = Application::IsKeyPressed('C');
	keypressed[K_EXIT_TROLLEY] = Application::IsKeyPressed('V');

	// Interactions
	std::vector<CObj*> list;
	if(floorNum == 1)
	{
		list = objList;
	}
	else if (floorNum == 2)
	{
		list = objList2;
	}
	for (int i = 0; i < list.size(); ++i)
	{
		pObj = list[i];
		if (pObj->getRender())
		{
			// check if target is within the bound of the size with scale [ need calcbound() ]
			if (camera.target.x < pObj->getMaxBound().x && camera.target.x > pObj->getMinBound().x && camera.target.y < pObj->getMaxBound().y && camera.target.y > pObj->getMinBound().y && camera.target.z < pObj->getMaxBound().z && camera.target.z > pObj->getMinBound().z)
			{
				// only enter car when both hand empty
				if (pObj->getID() == GEO_CAR && keypressed[K_ENTER_CAR] && hands[0] == NULL && hands[1] == NULL) 
				{
					hands[0] = hands[1] = pObj;
					saved = camera;
					pObj->setRender(false);
					camera = static_cast<CCar*>(pObj)->carCamera;
					rotateHandX = 0;
					rotateHandY = hands[0]->getRotate().y -90;
				}
				else if (pObj->getID() == GEO_SHELF)
				{
					updateShelf();
				}
				else if (pObj->getID() == GEO_TROLLEY)
				{
					// TROLLEY STUFFS ====================================================
					if (keypressed[K_ENTER_TROLLEY] && hands[0] == NULL && hands[1] == NULL)
					{
						hands[0] = hands[1] = pObj;
						saved = camera;
						camera = static_cast<CTrolley*>(pObj)->camera;
						rotateHandX = trolleyRotateHandX;
						rotateHandY = hands[0]->getRotate().y;
					}
					if (keypressed[K_LEFT_PLACE] && hands[0] != NULL && hands[0]->getID() == GEO_ITEM)
					{
						static_cast<CTrolley*>(pObj)->itemList.push_back(static_cast<CItem*>(hands[0]));
						hands[0] = NULL;
					}
					if (keypressed[K_RIGHT_PLACE] && hands[1] != NULL && hands[1]->getID() == GEO_ITEM)
					{
						static_cast<CTrolley*>(pObj)->itemList.push_back(static_cast<CItem*>(hands[1]));
						hands[1] = NULL;
					}
					if (keypressed[K_LEFT_PICK] && hands[0] == NULL && static_cast<CTrolley*>(pObj)->itemList.size() > 0)
					{
						hands[0] = static_cast<CObj*>(static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]);
						static_cast<CTrolley*>(pObj)->itemList.pop_back();
					}
					if (keypressed[K_RIGHT_PICK] && hands[1] == NULL && static_cast<CTrolley*>(pObj)->itemList.size() > 0)
					{
						hands[1] = static_cast<CObj*>(static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]);
						static_cast<CTrolley*>(pObj)->itemList.pop_back();
					}
				}
				else if(pObj->getID() == GEO_SECURITY_CAMERA_SCREEN)
				{
					if(keypressed[K_ENTER_CAM] && cam == false && floorNum == 2)
					{
						saved = camera; // saving camera data
						camNum = 0;
						cam = true;
					}
				}
				// ========= paper bag ===================
				else if(pObj->getID() == GEO_BAG)
				{
					if (keypressed[K_LEFT_PLACE] && hands[0] != NULL && hands[0]->getID() == GEO_ITEM)
					{
						bagList.push_back(static_cast<CItem*>(hands[0]));
						hands[0] = NULL;
						if(inGame == 2 && itemLeft > 0) // cashier game 
						{
							itemLeft -= 1;
						}
					}
					if (keypressed[K_RIGHT_PLACE] && hands[1] != NULL && hands[1]->getID() == GEO_ITEM)
					{
						bagList.push_back(static_cast<CItem*>(hands[1]));
						hands[1] = NULL;
						if(inGame == 2 && itemLeft > 0) // cashier game 
						{
							itemLeft -= 1;
						}
					}
					if (keypressed[K_LEFT_PICK] && hands[0] == NULL && bagList.size() > 0)
					{
						hands[0] = static_cast<CObj*>(bagList[bagList.size() - 1 ]);
						bagList.pop_back();
					}
					if (keypressed[K_RIGHT_PICK] && hands[1] == NULL && bagList.size() > 0)
					{
						hands[1] = static_cast<CObj*> (bagList[bagList.size() - 1]);
						bagList.pop_back();
					}
				}
				// ======== cashier table ============
				else if (pObj->getID() == GEO_CASHIER_TABLE)
				{
					if (keypressed[K_LEFT_PLACE] && hands[0] != NULL && hands[0]->getID() == GEO_ITEM)
					{
						checkoutList.push_back(static_cast<CItem*>(hands[0]));
						// when in game1 - checking for correct item picked 
						if(inGame == 1 && static_cast<CItem*>(hands[0])->getItem() == meshList[randomItem -10])
						{
							pickCorrect = true;
						}
						hands[0] = NULL;
					}
					if (keypressed[K_RIGHT_PLACE] && hands[1] != NULL && hands[1]->getID() == GEO_ITEM)
					{
						checkoutList.push_back(static_cast<CItem*>(hands[1]));
						// when in game1 - checking for correct item picked
						if(inGame == 1 && static_cast<CItem*>(hands[1])->getItem() == meshList[randomItem -10])
						{
							pickCorrect = true;
						}
						hands[1] = NULL;
					}
					if (keypressed[K_LEFT_PICK] && hands[0] == NULL && checkoutList.size() > 0)
					{
						hands[0] = static_cast<CObj*>(checkoutList[checkoutList.size() - 1 ]);
						checkoutList.pop_back();
					}
					if (keypressed[K_RIGHT_PICK] && hands[1] == NULL && checkoutList.size() > 0)
					{
						hands[1] = static_cast<CObj*> (checkoutList[checkoutList.size() - 1]);
						checkoutList.pop_back();
					}
				}
			}
		}
	}

	if (hands[0] != NULL && hands[1] != NULL)
	{
		if (hands[0]->getID() == GEO_CAR && hands[1]->getID() == GEO_CAR)
		{
			updateCar(dt);
		}
		else if (hands[0]->getID() == GEO_TROLLEY && hands[1]->getID() == GEO_TROLLEY)
		{
			updateTrolley(dt);
		}
	}

	if(inGame == 0)
		updateHuman(dt);
	updateSuperMarket(dt);
	updateHands(dt);
	updateCamera(dt);
	updateGame(dt);
	if(Application::IsKeyPressed('Z'))
	{
		togglelight = true;
	}
	if(Application::IsKeyPressed('X'))
	{
		togglelight = false;
	}
	static double fpsRefresh;
	fpsRefresh += dt;
	if (fpsRefresh >= 1)
	{
		fps = 1 / dt;
		fpsRefresh = 0;
	}

}

void SP2::updateCamera(double dt)
{
	if(cam == true)
	{
		glEnable(GL_CULL_FACE);
		camera = cameraList[camNum]->camera;
		if(Application::IsKeyPressed('1')) // toggle floor 1 cam 1
		{
			floorNum = 1;
			camNum = 0;
		}
		if(Application::IsKeyPressed('2')) // toggle floor 1 cam 2
		{
			floorNum = 1;
			camNum = 1;
		}
		if(Application::IsKeyPressed('3')) // toggle floor 2 cam 1
		{
			floorNum = 2;
			camNum = 0;
		}
		if(Application::IsKeyPressed('4')) // toggle floor 2 cam 2
		{
			floorNum = 2;
			camNum = 1;
		}
	}
	if(keypressed[K_EXIT_CAM] && cam == true && game3 == false)
	{
		floorNum = 2;
		cam = false;
		camera = saved;
	}
	if(cam == false)
	{
		camera.Update(dt, outerSkyboxMaxBound, outerSkyboxMinBound, objList, hands, floorNum, objList2);
	}
}

void SP2::updateGame(double dt)
{
	static const float ROTATE_SPEED = 100.f;
	// tresure hunt game start bound
	if(camera.position.x < game1MaxBound.x && camera.position.x > game1MinBound.x && camera.position.z < game1MaxBound.z && camera.position.z > game1MinBound.z)
	{
		if(keypressed[K_START_STORY] && inGame == 0)// check if want to start game + no game involved currently
		{
			inGame = 1;
			timeFrame = 30;
			playerScore[0] = 0;
		}
	}
	// cashier game start bound
	if(camera.position.x < game2MaxBound.x && camera.position.x > game2MinBound.x && camera.position.z < game2MaxBound.z && camera.position.z > game2MinBound.z)
	{
		if(keypressed[K_START_STORY] && inGame == 0)
		{
			CItem *pItem;
			inGame = 2;
			timeFrame = 0;
			itemLeft = 10;
			playerScore[1] = 0;
			// init items for game 2 - cashier table one 
			for(int i = 0 ; i < 10 ; ++i)
			{
				int a = rand() % 10 + GEO_ITEM_1;
				pItem = new CItem(GEO_ITEM, Vector3(0,0,0), Vector3(0,0,0), Vector3(1,1,1), Vector3(1,1,1), meshList[a]);
				checkoutList.push_back(pItem);
			}
			delete pItem;
		}
	}
	//guard game start bound
	if(camera.position.x < game3MaxBound.x && camera.position.x > game3MinBound.x && camera.position.z < game3MaxBound.z && camera.position.z > game3MinBound.z)
	{
		if(keypressed[K_START_STORY] && inGame == 0)
		{
			game3 = true;
			saved = camera;
			cam = true;
			inGame = 3;
		}
	}
	if(inGame == 1) // in treasure hunt mode aka game 1
	{
		//constant countdown
		timeFrame -= dt;
		// getting out of game 1
		if(timeFrame <= 0)
		{
			// return items to correct shelf
			for(int i  = 0 ; i < checkoutList.size() ; ++i) //checks items in cashier table
			{
				for(int j = 0 ; j < objList.size() ; ++j) 
				{
					pObj = objList[j];
					if(pObj->getID() == GEO_SHELF && static_cast<CShelf*>(pObj)->itemList[1]->getItem() == checkoutList[i]->getItem()) // check through obj list for shelfs and check if item belongs to shelf
					{
						static_cast<CShelf*>(objList[j])->itemList.push_back(checkoutList[i]);
					}
				}
			}
			for(int i = 0 ; i < checkoutList.size() ; ++i)
			{
				checkoutList.pop_back();
			}
			inGame = 0;
		}
	}
	if(inGame == 2)
	{
		// constant increase
		timeFrame += dt;
		// getting out of game 2
		if( itemLeft == 0 && inGame == 2)
		{
			playerScore[1] = timeFrame;
			CItem *pItem;
			inGame = 0;
			for(int i = 0 ; i < checkoutList.size(); ++i)
			{
				pItem = checkoutList[i];
				delete pItem;
			}
		}
	}
	if(inGame == 3)
	{
		//note to all - this story own time own target
		// no points in this story though
		// using WASD to move security guard got bound check - using referance from camera3 code
		tempBobMoveX = bobMoveX ;
		tempBobMoveZ = bobMoveZ ;

		if(Application::IsKeyPressed('W'))
		{
			bobMoveX += 1;
			if(updateBoundCheckGame3())
			{
				bobMoveX = tempBobMoveX;
				bobMoveZ = tempBobMoveZ;
			}
		}
		if(Application::IsKeyPressed('S'))
		{
			bobMoveX -= 1;
			if(updateBoundCheckGame3())
			{
				bobMoveX = tempBobMoveX;
				bobMoveZ = tempBobMoveZ;
			}
		}
		if(Application::IsKeyPressed('D'))
		{
			bobMoveZ += 1;
			if(updateBoundCheckGame3())
			{
				bobMoveX = tempBobMoveX;
				bobMoveZ = tempBobMoveZ;
			}
		}
		if(Application::IsKeyPressed('A'))
		{
			bobMoveZ -= 1;
			if(updateBoundCheckGame3())
			{
				bobMoveX = tempBobMoveX;
				bobMoveZ = tempBobMoveZ;
			}
		}

		if(keypressed[K_EXIT_CAM] && game3 == true)
		{ 
			floorNum = 1;
			camera = saved;
			game3 = false;
			cam = false;
			inGame = 0;
		}
	}
}

bool SP2::updateBoundCheckGame3()
{
	for(int i = 0 ; i < objList.size(); ++i)
	{
		pObj = objList[i];
		if(pObj->getRender())
		{
			if(bobMoveX < pObj->getMaxBound().x && bobMoveX > pObj->getMinBound().x && bobMoveZ < pObj->getMaxBound().z && bobMoveZ > pObj->getMinBound().z )
			{
				return true;
			}
		}
	}
	return false;
}

void SP2::updateTrolley(double dt)
{
	static const float ROTATE_SPEED = 100.f;
	if (keypressed[K_EXIT_TROLLEY])
	{
		static_cast<CTrolley*>(hands[0])->updatePosition();
		hands[0]->calcBound();
		camera = saved;
		camera.position = static_cast<CTrolley*>(hands[0])->camera.position;
		camera.target = static_cast<CTrolley*>(hands[0])->camera.target;
		camera.up = static_cast<CTrolley*>(hands[0])->camera.up;
		rotateHandY = hands[0]->getRotate().y;
		trolleyRotateHandX = rotateHandX;
		hands[0] = hands[1] = NULL;
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
		if (Application::IsKeyPressed(VK_UP) && rotateHandX < 50 && (hands[0] == NULL || hands[0]->getID() != GEO_CAR))
		{
			rotateHandX += ROTATE_SPEED*dt;
		}
		if (Application::IsKeyPressed(VK_DOWN) && rotateHandX > -50 && (hands[0] == NULL || hands[0]->getID() != GEO_CAR))
		{
			rotateHandX -= ROTATE_SPEED*dt;
		}
		if(Application::IsKeyPressed('R') && (hands[0] == NULL || hands[0]->getID() != GEO_CAR || hands[0]->getID() != GEO_TROLLEY))
		{
			rotateHandX = 0;
			rotateHandY = 0;
		}
	}
}

void SP2::updateShelf()
{
	// Pick up item for left hand
	if (keypressed[K_LEFT_PICK] && hands[0] == NULL && static_cast<CShelf*>(pObj)->itemList.size() > 0)
	{
		hands[0] = static_cast<CObj*>(static_cast<CShelf*>(pObj)->itemList[static_cast<CShelf*>(pObj)->itemList.size() - 1]);
		static_cast<CShelf*>(pObj)->itemList.pop_back();
	}

	// Place item for left hand
	if (keypressed[K_LEFT_PLACE] && hands[0] != NULL && hands[0]->getID() == GEO_ITEM && static_cast<CShelf*>(pObj)->itemList.size() < static_cast<CShelf*>(pObj)->limit )
	{
		hands[0]->setTranslate(static_cast<CShelf*>(pObj)->itemPosition[static_cast<CShelf*>(pObj)->itemList.size()]);
		static_cast<CShelf*>(pObj)->itemList.push_back(static_cast<CItem*>(hands[0]));
		hands[0] = NULL;
	}

	// Pick up item for right hand
	if (keypressed[K_RIGHT_PICK] && hands[1] == NULL && static_cast<CShelf*>(pObj)->itemList.size() > 0)
	{
		hands[1] = static_cast<CObj*>(static_cast<CShelf*>(pObj)->itemList[static_cast<CShelf*>(pObj)->itemList.size() - 1]);
		static_cast<CShelf*>(pObj)->itemList.pop_back();
	}

	// Place item for right hand
	if (keypressed[K_RIGHT_PLACE] && hands[1] != NULL && hands[1]->getID() == GEO_ITEM && static_cast<CShelf*>(pObj)->itemList.size() < static_cast<CShelf*>(pObj)->limit)
	{
		hands[1]->setTranslate(static_cast<CShelf*>(pObj)->itemPosition[static_cast<CShelf*>(pObj)->itemList.size()]);
		static_cast<CShelf*>(pObj)->itemList.push_back(static_cast<CItem*>(hands[1]));
		hands[1] = NULL;
	}
}

void SP2::updateSuperMarket(double dt)
{
	static const float LIFT_SPEED = 0.1 * supermarketScale.x;
	//lift door interaction (needed for both floors) [ closes when selected floor to go]
	if(camera.position.x < supermarketLiftDoorMaxBound.x && camera.position.x > supermarketLiftDoorMinBound.x && camera.position.z < supermarketLiftDoorMaxBound.z && camera.position.z > supermarketLiftDoorMinBound.z)
	{
		if(disableLiftDoor == false)
		{
			if(translateLiftX < 2)
			{
				liftRightDoor->setTranslateX(liftRightDoor->getTranslate().x + LIFT_SPEED);
				liftRightDoor->calcBound();
				liftLeftDoor->setTranslateX(liftLeftDoor->getTranslate().x - LIFT_SPEED);
				liftLeftDoor->calcBound();
				translateLiftX += 0.1;
			}
		}
	}
	else
	{
		if(disableLiftDoor == false)
		{
			if(translateLiftX > 0)
			{
				liftRightDoor->setTranslateX(liftRightDoor->getTranslate().x - LIFT_SPEED);
				liftRightDoor->calcBound();
				liftLeftDoor->setTranslateX(liftLeftDoor->getTranslate().x + LIFT_SPEED);
				liftLeftDoor->calcBound();
				translateLiftX -= 0.1;
			}
		}
	}
	if(disableLiftDoor == true)
	{
		if(translateLiftX > 0)
		{
			liftRightDoor->setTranslateX(liftRightDoor->getTranslate().x - LIFT_SPEED);
			liftRightDoor->calcBound();
			liftLeftDoor->setTranslateX(liftLeftDoor->getTranslate().x + LIFT_SPEED);
			liftLeftDoor->calcBound();
			translateLiftX -= 0.1;
		}
	}
	// lift interaction - bring them to 2nd floor/ 1st floor
	static float doorTimer = 0;
	if(disableLiftDoor && translateLiftX <= 0) // Swap between floors after door closes
	{
		doorTimer += dt;
		if (doorTimer >= 1)
		{
			floorNum = newFloor;
			disableLiftDoor = false;
			doorTimer = 0;
		}
	}
	if(camera.position.x < supermarketLiftMaxBound.x && camera.position.x > supermarketLiftMinBound.x && camera.position.z < supermarketLiftMaxBound.z && camera.position.z > supermarketLiftMinBound.z)
	{
		if(keypressed[K_FIRST_FLOOR] && !disableLiftDoor)
		{
			if (floorNum != 1)
			{
				disableLiftDoor = true;
				newFloor = 1;
			}
		}
		if(keypressed[K_SECOND_FLOOR] && !disableLiftDoor)
		{
			if (floorNum != 2)
			{
				disableLiftDoor = true;
				newFloor = 2;
			}
		}
	}
	if(floorNum == 1) //1st floor
	{
		for(int a = 0;a<CharacterList.size();++a)
		{

			if (camera.position.x < supermarketDoorMaxBound.x && camera.position.x > supermarketDoorMinBound.x && camera.position.z < supermarketDoorMaxBound.z && camera.position.z > supermarketDoorMinBound.z||
				CharacterList[a]->getTranslate().x < supermarketDoorMaxBound.x && CharacterList[a]->getTranslate().x > supermarketDoorMinBound.x && CharacterList[a]->getTranslate().z < supermarketDoorMaxBound.z && CharacterList[a]->getTranslate().z > supermarketDoorMinBound.z)
			{
				if(translateX<2)
				{
					translateX+=0.1;
					--a;
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
	}
	if(floorNum == 2)
	{
		if(camera.position.x < supermarketSecurityDoorMaxBound.x && camera.position.x > supermarketSecurityDoorMinBound.z && camera.position.z > supermarketSecurityDoorMinBound.z && camera.position.z < supermarketSecurityDoorMaxBound.z)
		{
			if(translateSecurityZ<2)
			{
				translateSecurityZ+=0.1;
			}
		}
		else
		{		
			if(translateSecurityZ>0)
			{
				translateSecurityZ-=0.1;
			}
		}
	}
}

void SP2::updateCar(double dt)//updating car
{
	static const float ROTATE_SPEED = 100.f;
	if (keypressed[K_EXIT_CAR])
	{
		static_cast<CCar*>(hands[0])->setRender(true);
		static_cast<CCar*>(hands[0])->carCamera = camera;
		camera = saved;
		Vector3 right = ((static_cast<CCar*>(hands[0])->carCamera.target - static_cast<CCar*>(hands[0])->carCamera.position).Cross(static_cast<CCar*>(hands[0])->carCamera.up)).Normalized();
		Mtx44 Rotation;
		Rotation.SetToRotation(90,0,1,0);
		camera.target = ((static_cast<CCar*>(hands[0])->carCamera.position - (right * 35)) + ((Rotation * (static_cast<CCar*>(hands[0])->carCamera.position - static_cast<CCar*>(hands[0])->carCamera.target))));
		camera.position = (static_cast<CCar*>(hands[0])->carCamera.position - (right * 35));
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
	for(int a = 0; a < objList.size(); ++a)
	{
		if(objList[a]->getID() == GEO_HUMAN)
		{

			static_cast <CCharacter*>(objList[a])->UpdateMovement(30);
			static_cast <CCharacter*>(objList[a])->WalkTo(static_cast <CCharacter*>(objList[a])->AiRouteLocation[static_cast <CCharacter*>(objList[a])->getRouteID()]);

			if(static_cast<CCashier*>(objList[a])->getRole()==1) // Cashier
			{
				static_cast<CCashier*> (objList[a])->setInteractionBound(camera.position,50);

				if(static_cast<CCashier*>(objList[a])->getInteractionBound()==true)
				{
					cout<<"Cashier says hi"<<endl;
				}

			}
			else if(static_cast<CSecurityGuard*>(objList[a])->getRole()==2)  //Security Guard
			{    
				static_cast<CSecurityGuard*> (objList[a])->setInteractionBound(camera.position,50);

				static_cast<CShopper*> (objList[a])->setInteractionBound(camera.position,50);

				if(static_cast<CSecurityGuard*>(objList[a])->getRouteID()==static_cast<CSecurityGuard*>(objList[a])->AiRouteLocation.size()-1)
				{
					static_cast<CSecurityGuard*>(objList[a])->setRouteID(0);
				}

				if(static_cast <CCharacter*>(objList[a])->getTranslate().x == static_cast <CCharacter*>(objList[a])->AiRouteLocation[static_cast <CCharacter*>(objList[a])->getRouteID()].x && static_cast <CCharacter*>(objList[a])->getTranslate().z == static_cast <CCharacter*>(objList[a])->AiRouteLocation[static_cast <CCharacter*>(objList[a])->getRouteID()].z)
				{
					static_cast <CCharacter*>(objList[a])->setRouteID(static_cast<CSecurityGuard*>(objList[a])->getRouteID()+1);
				}



				if(static_cast<CSecurityGuard*>(objList[a])->getInteractionBound()==true)
				{
					static_cast<CSecurityGuard*>(objList[a])->setMovement(0);
					cout<<"SecurityGuard says hi"<<endl; 
				}

			}
			else if(static_cast<CShopper*>(objList[a])->getRole()==3)//Shopper
			{
				if(static_cast <CCharacter*>(objList[a])->getRouteID()==0)
				{
					static_cast <CCharacter*>(objList[a])->setRouteID(1);
				}
				if(static_cast <CCharacter*>(objList[a])->getTranslate().x == static_cast <CCharacter*>(objList[a])->AiRouteLocation[static_cast <CCharacter*>(objList[a])->getRouteID()].x && static_cast <CCharacter*>(objList[a])->getTranslate().z == static_cast <CCharacter*>(objList[a])->AiRouteLocation[static_cast <CCharacter*>(objList[a])->getRouteID()].z)
				{
					static_cast <CCharacter*>(objList[a])->setRouteID(rand()%static_cast <CCharacter*>(objList[a])->AiRouteLocation.size());
				}
				static_cast<CShopper*> (objList[a])->setInteractionBound(camera.position,50);

				if(static_cast<CShopper*>(objList[a])->getInteractionBound()==true)
				{
					static_cast<CCashier*>(objList[a])->setMovement(0);
					cout<<"Shopper says: You're near me"<<endl;
				}
			}


			else if(static_cast<CPromoter*>(objList[a])->getRole()==4)
			{
				static_cast<CPromoter*> (objList[a])->setInteractionBound(camera.position,50);
				if(static_cast<CPromoter*>(objList[a])->getInteractionBound()==true)
				{
					static_cast<CPromoter*>(objList[a])->setMovement(0);
					cout<<"Promoter says hi"<<endl;
				}
			}

		}
	}
}

void SP2::updateCabinet(double dt)
{
	for(int a = 0; a < objList.size(); ++a)
	{
		if(objList2[a]->getID()== GEO_DISPLAY1 && floorNum == 2)
		{
			//static_cast<CObj*> (objList2[a])->setInteractionBound(camera.position,50);


			if(objList2[a]->getID()==GEO_HUMAN  && floorNum == 2)
			{
				if(static_cast<CPromoter*>(objList2[a])->getRole()==4)
				{
					static_cast<CPromoter*> (objList2[a])->setInteractionBound(camera.position,50);
					if(static_cast<CPromoter*>(objList2[a])->getInteractionBound()==true)
						cout<<"Promoter says hi"<<endl;
				}

				else if( objList2[a]->getID()== GEO_DISPLAY2 && floorNum == 2)
				{}
				else if(objList2[a]->getID()== GEO_DISPLAY3 && floorNum == 2)
				{}
				else if( objList2[a]->getID()== GEO_DISPLAY4 && floorNum == 2)
				{}
			}
		}
	}
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

	std::vector<CObj*> list;
	if (floorNum == 1)
	{
		list = objList;
	}
	else if (floorNum == 2)
	{
		list = objList2;
	}
	// Render objList
	for (int i = 0; i < list.size(); ++i)
	{
		pObj = list[i];
		if (pObj->getRender())
		{
			if (pObj->getID() == GEO_CAR)
			{
				renderCar();
			}
			else if(pObj->getID() == GEO_SHELF)
			{
				renderShelf();
			}
			else if(pObj->getID() == GEO_HUMAN)
			{
				renderHuman();
			}
			else if (pObj->getID() != GEO_SUPERMARKET_WALL)
			{
				modelStack.PushMatrix();
				modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y, pObj->getTranslate().z);
				modelStack.Rotate(pObj->getRotate().x, 1,0,0);
				modelStack.Rotate(pObj->getRotate().y, 0,1,0);
				modelStack.Rotate(pObj->getRotate().z, 0,0,1);
				modelStack.PushMatrix();
				modelStack.Scale(pObj->getScale().x, pObj->getScale().y, pObj->getScale().z);
				RenderMesh(meshList[pObj->getID()], togglelight);
				modelStack.PopMatrix();

				if (pObj->getID() == GEO_TROLLEY)
				{
					if (static_cast<CTrolley*>(pObj)->itemList.size() > 0)
					{
						modelStack.PushMatrix();
						modelStack.Translate(0,((pObj->getScale().y * pObj->getSize().y) / 5) * 3.5,0);
						modelStack.Scale(static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]->getScale().x, static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]->getScale().y, static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]->getScale().z);
						RenderMesh(static_cast<CTrolley*>(pObj)->itemList[static_cast<CTrolley*>(pObj)->itemList.size() - 1]->getItem(), togglelight);
						modelStack.PopMatrix();
					}
				}
				modelStack.PopMatrix();
			}
		}
	}

	if (hands[0] == NULL || hands[1] == NULL || hands[0]->getID() == GEO_ITEM || hands[1]->getID() == GEO_ITEM || (hands[0]->getID() == GEO_TROLLEY && hands[1]->getID() == GEO_TROLLEY))
	{
		renderHands();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
		modelStack.Rotate(hands[0]->getRotate().y - 90, 0, 1, 0);
		modelStack.Scale(17, 15, 1);
		RenderMesh(meshList[GEO_CAR_SCREEN], togglelight);
		modelStack.PopMatrix();
	}

	//// Target test
	//modelStack.PushMatrix();
	//modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	//modelStack.Scale(1,1,1);
	//RenderMesh(meshList[GEO_CUBE], togglelight);
	//modelStack.PopMatrix();

	RenderMesh(meshList[GEO_AXES], false);
	if (floorNum == 1)
	{
		for (int i = 0; i < trolleyList.size(); ++i)
		{
			pObj = trolleyList[i];
			for (int j = 0; j < 4; ++j)
			{
				modelStack.PushMatrix();
				modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y + (pObj->getScale().y * pObj->getSize().y * 1.3),pObj->getTranslate().z);
				modelStack.Rotate(0, 0,1,0);
				modelStack.Scale(5,5,5);
				RenderText(meshList[GEO_TEXT], std::to_string(static_cast<long long>(static_cast<CTrolley*>(pObj)->itemList.size())), Color(1,0,0));
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y + (pObj->getScale().y * pObj->getSize().y * 1.3),pObj->getTranslate().z);
				modelStack.Rotate(180, 0,1,0);
				modelStack.Scale(5,5,5);
				RenderText(meshList[GEO_TEXT], std::to_string(static_cast<long long>(static_cast<CTrolley*>(pObj)->itemList.size())), Color(1,0,0));
				modelStack.PopMatrix();
			}
		}
	}
	renderGame(inGame);
	if (hands[0] != NULL && hands[0]->getID() == GEO_ITEM)
	{
		if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_1])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_1],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_2])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_2],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_3])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_3],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_4])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_4],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_5])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_5],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_6])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_6],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_7])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_7],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_8])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_8],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_9])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_9],10,7.5,5);
		}
		else if (static_cast<CItem*>(hands[0])->getItem() == meshList[GEO_ITEM_10])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_10],10,7.5,5);
		}
	}
	if (hands[1] != NULL && hands[1]->getID() == GEO_ITEM)
	{
		if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_1])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_1],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_2])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_2],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_3])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_3],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_4])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_4],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_5])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_5],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_6])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_6],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_7])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_7],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_8])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_8],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_9])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_9],10,7.5,4);
		}
		else if (static_cast<CItem*>(hands[1])->getItem() == meshList[GEO_ITEM_10])
		{
			Render2D(meshList[GEO_INVENTORY_ITEM_10],10,7.5,4);
		}
	}
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

	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 0, 0), 2, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], sFPS.str(), Color(0, 0, 0), 2, 6, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "Orientation: ", Color(0, 0, 0), 2, 1, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], sOrient.str(), Color(0, 0, 0), 2, 20, 5);
	RenderTextOnScreen(meshList[GEO_TEXT], "Pitch: ", Color(0, 0, 0), 2, 1, 6);
	RenderTextOnScreen(meshList[GEO_TEXT], sPitch.str(), Color(0, 0, 0), 2, 10, 6);  
	RenderTextOnScreen(meshList[GEO_TEXT], "X: ", Color(0, 0, 0), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], sX.str(), Color(0, 0, 0), 2, 4, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y: ", Color(0, 0, 0), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], sY.str(), Color(0, 0, 0), 2, 4, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z: ", Color(0, 0, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], sZ.str(), Color(0, 0, 0), 2, 4, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], ">o<", Color(1,0,0), 2, 19.2, 15);

	if(aiTalk == true  && timer < 500)
	{
		for(int a = 0; a < objList.size(); ++a)
		{
			if(static_cast<CCashier*>(objList[a])->getRole()==1)
			{
				int textNum = rand() % 10;
				switch(textNum)
				{
				case 1:
					RenderTextOnScreen(meshList[GEO_TEXT], "Hi There!",Color(0,0,0), 2, 0, -2);
					break;
				case 2:
					RenderTextOnScreen(meshList[GEO_TEXT], "Can I have your Items?", Color(0,0,0), 2, 0, -2);
					break;
				case 3:
					RenderTextOnScreen(meshList[GEO_TEXT], "That would be $420.69 Sir", Color(0,0,0), 2, 0, -2);
					break;
				case 4:
					RenderTextOnScreen(meshList[GEO_TEXT], "Would you like some of our home grown and cultured weed?", Color(0,0,0), 2, 0,-2);
					break;
				case 5:
					RenderTextOnScreen(meshList[GEO_TEXT], "You must be under 18 to buy cigarettes Sir!", Color(0,0,0), 2, 0, -2);
					break;
				case 6: 
					RenderTextOnScreen(meshList[GEO_TEXT], "Do you want to build a MeshMan?", Color (0,0,0), 2, 0, -2);
					break;
				case 7:
					RenderTextOnScreen(meshList[GEO_TEXT], "I used to be a shopper JUST like you, then i got broke", Color(0,0,0), 2, 0, -2);
					break;
				case 8:
					RenderTextOnScreen(meshList[GEO_TEXT], " Everything used to be peacful around here, then the Great Singapore Sales atacked", Color(0,0,0), 1, 0, -2);
					break;
				case 9: 
					RenderTextOnScreen(meshList[GEO_TEXT], "The art of slicing is very delicate, don't you think?", Color(0,0,0), 2, 0, -2);
				}
			}
			if(static_cast<CSecurityGuard*>(objList[a])->getRole()==2)
			{
				int textNum = rand() % 10;
				switch(textNum)
				{
				case 1:
					RenderTextOnScreen(meshList[GEO_TEXT], "Hi There!",Color(0,0,0), 2, 0, -2);
					break;
				case 2:
					RenderTextOnScreen(meshList[GEO_TEXT], "Can I have your Items?", Color(0,0,0), 2, 0, -2);
					break;
				case 3:
					RenderTextOnScreen(meshList[GEO_TEXT], "That would be $420.69 Sir", Color(0,0,0), 2, 0, -2);
					break;
				case 4:
					RenderTextOnScreen(meshList[GEO_TEXT], "Would you like some of our home grown and cultured weed?", Color(0,0,0), 2, 0,-2);
					break;
				case 5:
					RenderTextOnScreen(meshList[GEO_TEXT], "You must be under 18 to buy cigarettes Sir!", Color(0,0,0), 2, 0, -2);
					break;
				case 6: 
					RenderTextOnScreen(meshList[GEO_TEXT], "Do you want to build a MeshMan?", Color (0,0,0), 2, 0, -2);
					break;
				case 7:
					RenderTextOnScreen(meshList[GEO_TEXT], "I used to be a shopper JUST like you, then i got broke", Color(0,0,0), 2, 0, -2);
					break;
				case 8:
					RenderTextOnScreen(meshList[GEO_TEXT], " Everything used to be peacful around here, then the Great Singapore Sales atacked", Color(0,0,0), 1, 0, -2);
					break;
				case 9: 
					RenderTextOnScreen(meshList[GEO_TEXT], "The art of slicing is very delicate, don't you think?", Color(0,0,0), 2, 0, -2);
				}
			}
			if(static_cast<CShopper*>(objList[a])->getRole()==3)
			{
				int textNum = rand() % 10;
				switch(textNum)
				{
				case 1:
					RenderTextOnScreen(meshList[GEO_TEXT], "Hi There!",Color(0,0,0), 2, 0, -2);
					break;
				case 2:
					RenderTextOnScreen(meshList[GEO_TEXT], "Can I have your Items?", Color(0,0,0), 2, 0, -2);
					break;
				case 3:
					RenderTextOnScreen(meshList[GEO_TEXT], "That would be $420.69 Sir", Color(0,0,0), 2, 0, -2);
					break;
				case 4:
					RenderTextOnScreen(meshList[GEO_TEXT], "Would you like some of our home grown and cultured weed?", Color(0,0,0), 2, 0,-2);
					break;
				case 5:
					RenderTextOnScreen(meshList[GEO_TEXT], "You must be under 18 to buy cigarettes Sir!", Color(0,0,0), 2, 0, -2);
					break;
				case 6: 
					RenderTextOnScreen(meshList[GEO_TEXT], "Do you want to build a MeshMan?", Color (0,0,0), 2, 0, -2);
					break;
				case 7:
					RenderTextOnScreen(meshList[GEO_TEXT], "I used to be a shopper JUST like you, then i got broke", Color(0,0,0), 2, 0, -2);
					break;
				case 8:
					RenderTextOnScreen(meshList[GEO_TEXT], " Everything used to be peacful around here, then the Great Singapore Sales atacked", Color(0,0,0), 1, 0, -2);
					break;
				case 9: 
					RenderTextOnScreen(meshList[GEO_TEXT], "The art of slicing is very delicate, don't you think?", Color(0,0,0), 2, 0, -2);
				}
			}
			if(static_cast<CPromoter*>(objList[a])->getRole()==4)
			{
				int textNum = rand() % 10;
				switch(textNum)
				{
				case 1:
					RenderTextOnScreen(meshList[GEO_TEXT], "Hi There!",Color(0,0,0), 2, 0, -2);
					break;
				case 2:
					RenderTextOnScreen(meshList[GEO_TEXT], "Can I have your Items?", Color(0,0,0), 2, 0, -2);
					break;
				case 3:
					RenderTextOnScreen(meshList[GEO_TEXT], "That would be $420.69 Sir", Color(0,0,0), 2, 0, -2);
					break;
				case 4:
					RenderTextOnScreen(meshList[GEO_TEXT], "Would you like some of our home grown and cultured weed?", Color(0,0,0), 2, 0,-2);
					break;
				case 5:
					RenderTextOnScreen(meshList[GEO_TEXT], "You must be under 18 to buy cigarettes Sir!", Color(0,0,0), 2, 0, -2);
					break;
				case 6: 
					RenderTextOnScreen(meshList[GEO_TEXT], "Do you want to build a MeshMan?", Color (0,0,0), 2, 0, -2);
					break;
				case 7:
					RenderTextOnScreen(meshList[GEO_TEXT], "I used to be a shopper JUST like you, then i got broke", Color(0,0,0), 2, 0, -2);
					break;
				case 8:
					RenderTextOnScreen(meshList[GEO_TEXT], " Everything used to be peacful around here, then the Great Singapore Sales atacked", Color(0,0,0), 1, 0, -2);
					break;
				case 9: 
					RenderTextOnScreen(meshList[GEO_TEXT], "The art of slicing is very delicate, don't you think?", Color(0,0,0), 2, 0, -2);
				}
			}
		}
	}
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
		/*if (hands[0] == NULL)
		{
		modelStack.Scale(.4,.4,1.5);
		}
		else if (hands[0]->getID() == GEO_ITEM)
		{
		modelStack.Scale(hands[0]->getScale().x, hands[0]->getScale().y, hands[0]->getScale().z);
		}*/
		modelStack.Scale(.4,.4,1.5);
		modelStack.PushMatrix();

		/*if (hands[0] == NULL)
		{
		modelStack.Translate(-1.5,-1.5,-1);
		RenderMesh(meshList[GEO_HAND], togglelight);
		}
		else if (hands[0]->getID() == GEO_ITEM)
		{
		modelStack.Translate(-1.5, -1.5, -4);
		RenderMesh(static_cast<CItem*>(hands[0])->getItem(), togglelight);
		}*/
		modelStack.Translate(-1.5,-1.5,-1);
		RenderMesh(meshList[GEO_HAND], togglelight);
		modelStack.PopMatrix();

		modelStack.PopMatrix();

		// Right hands
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);

		modelStack.Rotate(rotateHandY, 0, 1, 0);
		modelStack.Rotate(rotateHandX,1,0,0);
		/*if (hands[1] == NULL)
		{
		modelStack.Scale(.4,.4,1.5);
		}
		else if (hands[1]->getID() == GEO_ITEM)
		{
		modelStack.Scale(hands[1]->getScale().x, hands[1]->getScale().y, hands[1]->getScale().z);
		}*/
		modelStack.Scale(.4,.4,1.5);
		modelStack.PushMatrix();

		/*if (hands[1] == NULL)
		{
		modelStack.Translate(1.5,-1.5,-1);
		RenderMesh(meshList[GEO_HAND], togglelight);
		}
		else if (hands[1]->getID() == GEO_ITEM)
		{
		modelStack.Translate(1.5, -1.5, -4);
		RenderMesh(static_cast<CItem*>(hands[1])->getItem(), togglelight);
		}*/
		modelStack.Translate(1.5,-1.5,-1);
		RenderMesh(meshList[GEO_HAND], togglelight);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
}

void SP2::renderCabinet()
{
	//Tardis Display Shelf
	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y , pObj->getTranslate().z );
	modelStack.Scale(pObj->getScale().x * .75, pObj->getScale().y * .75, pObj->getScale().z * .5 );
	RenderMesh(meshList[GEO_DISPLAY1], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .75, pObj->getScale().y * .75, pObj->getScale().z * .5 );
	RenderMesh(meshList[GEO_DISPLAY2], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .75, pObj->getScale().y * .75, pObj->getScale().z * .5 );
	RenderMesh(meshList[GEO_DISPLAY3], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .75, pObj->getScale().y * .75, pObj->getScale().z * .5 );
	RenderMesh(meshList[GEO_DISPLAY4], togglelight);
	modelStack.PopMatrix();
}

void SP2::renderSpecialItems()
{
	//POTATO
	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_POTATO], togglelight);
	modelStack.PopMatrix();
	//HAMMERTIME
	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_THOR], togglelight);
	modelStack.PopMatrix();
	//WUKONG
	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_WUKONG], togglelight);
	modelStack.PopMatrix();
	//--------------------------------TARDIS------------------------------
	modelStack.PushMatrix();

	//modelStack.Translate(0,tardisY,0);
	modelStack.Rotate(rotTardis,0,1,0);


	//modelStack.Rotate(tardisPitch,1,0,0);

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_TARDIS_TOP], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Rotate(rotTardis, 0 , 1, 0);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_TARDIS_MID], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_TARDIS_SIGN], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(pObj->getTranslate().x,pObj->getTranslate().y, pObj->getTranslate().z);
	modelStack.Scale(pObj->getScale().x * .1, pObj->getScale().y * .1, pObj->getScale().z * .1);
	RenderMesh(meshList[GEO_TARDIS_BOT], togglelight);
	modelStack.PopMatrix();


	modelStack.PopMatrix();

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

void SP2::renderSuperMarket()
{

	modelStack.PushMatrix();
	modelStack.Translate(0,-4,0);
	modelStack.Translate(supermarketPosition.x,supermarketPosition.y,supermarketPosition.z);
	modelStack.Scale(supermarketScale.x,supermarketScale.y,supermarketScale.z);

	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_SUPERMARKET], togglelight);
	modelStack.PopMatrix();

	if(floorNum == 1)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-1.55-translateX,0,10);
		modelStack.Scale(0.6,0.5,0.5);
		RenderMesh(meshList[GEO_SUPERMARKET_DOOR], togglelight);//right Door
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Translate(1.55+translateX,0,10);
		modelStack.Scale(0.6,0.5,0.5);
		RenderMesh(meshList[GEO_SUPERMARKET_DOOR], togglelight);//left Door
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate( 5 , 0,translateSecurityZ);
		modelStack.Scale(1,0.7,0.5);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_SUPERMARKET_DOOR] , togglelight);
		modelStack.PopMatrix();
	}
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

void SP2::renderGame(int a)// 1- treasure hunt 
{
	//** NOTE : ALL GAME ON FIRST FLOOR **//
	if(floorNum == 1)
	{
		switch (a)
		{
		case 1 :
			{
				std::ostringstream sTF, sPS;
				sTF << (int)timeFrame;//time given / time taken CHANGE IN UPDATE GAME
				sPS << playerScore[0]; 
				if(pickCorrect == false)
				{
					// display item to be picked up 
					modelStack.PushMatrix();
					modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
					modelStack.Rotate(rotateHandY,0,1,0);
					modelStack.Rotate(rotateHandX,1,0,0);
					modelStack.Translate(4,2.5,4);
					modelStack.Scale(2,2,2);
					RenderMesh(meshList[randomItem] , false);
					modelStack.PopMatrix();	
				}
				else
				{
					//if found correct , gain point plus new item to find
					playerScore[0] += 1;
					randomItem = rand() % 10 + GEO_INVENTORY_ITEM_1;
					pickCorrect = false;
				}
				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_TEXT] ,"Time:", Color(1,0,0), 2 , 30, 20);
				RenderTextOnScreen(meshList[GEO_TEXT] , sTF.str(), Color(1,0,0), 2 , 38 , 20);
				RenderTextOnScreen(meshList[GEO_TEXT], "Score:", Color (1,0,0), 2, 30, 18);
				RenderTextOnScreen(meshList[GEO_TEXT] ,sPS.str(), Color(1,0,0), 2, 38 , 18);
				modelStack.PopMatrix();
			}
			break;
		case 2:
			{
				std::ostringstream sTF , sIL;
				sIL << itemLeft;
				sTF << timeFrame;
				if(itemLeft != 0)
				{
					modelStack.PushMatrix();
					modelStack.Translate(supermarketPosition.x + 45, supermarketPosition.y + 22, supermarketPosition.z + 55);
					modelStack.Scale(3,3,3);
					if(checkoutList.size() > 0)
					{
						RenderMesh(checkoutList[checkoutList.size() - 1]->getItem(),togglelight);
					}
					modelStack.PopMatrix();
				}
				modelStack.PushMatrix();
				RenderTextOnScreen(meshList[GEO_TEXT] ,"Time:", Color(1,0,0), 2 , 30, 20);
				RenderTextOnScreen(meshList[GEO_TEXT] , sTF.str(), Color(1,0,0), 2 , 38 , 20);
				RenderTextOnScreen(meshList[GEO_TEXT], "Item Left:", Color (1,0,0), 2, 28, 18);
				RenderTextOnScreen(meshList[GEO_TEXT] ,sIL.str(), Color(1,0,0), 2, 38 , 18);
				modelStack.PopMatrix();
			}
			break;
		case 3: // guard control game - will render bob, all movement is in update game
			{
				modelStack.PushMatrix();
				modelStack.Translate(supermarketPosition.x + bobMoveX , supermarketPosition.y + 5, supermarketPosition.z + bobMoveZ);
				modelStack.Scale(supermarketScale.x/2 , supermarketScale.y/2 + 0.1, supermarketScale.z/4);	

				RenderMesh(meshList[GEO_GAME3_BOB_BODY],false); // ======= BOB's BODY
				modelStack.PushMatrix();
				modelStack.Translate(1.5,2.8,0);
				RenderMesh(meshList[GEO_GAME3_BOB_ARM],false); // ========= BOB's RIGHT ARM
				modelStack.Translate(0,-0.95,0);
				RenderMesh(meshList[GEO_GAME3_BOB_HAND],false); // ========= BOB's Right Hand
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(-1.5,2.8,0);
				RenderMesh(meshList[GEO_GAME3_BOB_ARM],false); // ========= BOB's LEFT ARM
				modelStack.Translate(0,-0.95,0);
				RenderMesh(meshList[GEO_GAME3_BOB_HAND],false);// ========== BOB's left Hand
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(0.6,0.5,0);
				modelStack.Scale(0.9,1.2,1);
				RenderMesh(meshList[GEO_GAME3_BOB_LEG],false);// =========== BOB's right leg
				modelStack.PopMatrix();
				modelStack.PushMatrix();
				modelStack.Translate(-0.6,0.5,0);
				modelStack.Scale(0.9,1.2,1);
				RenderMesh(meshList[GEO_GAME3_BOB_LEG],false);// =========== BOB's left leg
				modelStack.PopMatrix();

				modelStack.PopMatrix();
			}
			break;
		case 0: // show story/game starting areas
			{
				glDisable(GL_CULL_FACE);
				//============= GAME 1 : TREASURE HUNT ==========================
				modelStack.PushMatrix();
				glDisable(GL_CULL_FACE);
				modelStack.Translate(game1MaxBound.x - 2 * supermarketScale.x , camera.position.y, game1MaxBound.z - 2 * supermarketScale.z);
				modelStack.Scale(supermarketScale.x, supermarketScale.y, supermarketScale.z);
				RenderText(meshList[GEO_TEXT],"[T]" ,Color(1,0,0));
				modelStack.Translate(0,-1,0);
				RenderText(meshList[GEO_TEXT]," V " ,Color(1,0,0));
				modelStack.PopMatrix();

				//============ GAME 2 : CASHIER ==========================
				modelStack.PushMatrix();
				modelStack.Translate(game2MaxBound.x - (2 * supermarketScale.x) , camera.position.y, game2MaxBound.z - (2 * supermarketScale.z));
				modelStack.Scale(supermarketScale.x ,supermarketScale.y, supermarketScale.z);
				RenderText(meshList[GEO_TEXT],"[C]",Color(1,0,0));
				modelStack.Translate(1,-1,0);
				RenderText(meshList[GEO_TEXT] ,"V " , Color(1,0,0));
				modelStack.PopMatrix();

				//============== GAME 3 : GUARD =========================
				modelStack.PushMatrix();
				modelStack.Translate(game3MaxBound.x - (2*supermarketScale.x) , camera.position.y ,game3MaxBound.z - (2 * supermarketScale.z));
				modelStack.Scale(supermarketScale.x , supermarketScale.y, supermarketScale.z);
				RenderText(meshList[GEO_TEXT] ,"[S]" ,Color(1,0,0));
				modelStack.Translate(1,-1,0);
				RenderText(meshList[GEO_TEXT],"V",Color(1,0,0));
				modelStack.PopMatrix();
				glEnable(GL_CULL_FACE);			
			}
			break;
		}
	}
}

void SP2::renderHuman() 
{
	pObj->calcBound();

	if(static_cast<CCharacter*>(pObj)->getRole()==1) // Cashier
	{
		modelStack.PushMatrix();
		modelStack.Translate(pObj->getTranslate().x, pObj->getTranslate().y,pObj->getTranslate().z);
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
		modelStack.Translate(-0.6,1,0);
		modelStack.PushMatrix();
		modelStack.Translate(0,-.25,0);
		//modelStack.Translate(-0.6,0.75,0);
		RenderMesh(meshList[GEO_HUMAN_STAFF_LEG] , togglelight);
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		// =========================== L_LEGS ==============================
		modelStack.PushMatrix();
		modelStack.PushMatrix();
		modelStack.Translate(0.6,0.75,0);
		RenderMesh(meshList[GEO_HUMAN_STAFF_LEG], togglelight);
		modelStack.PopMatrix();

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
		modelStack.Rotate(-(static_cast<CCharacter*>(pObj)->getMovement()),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_LEG] , togglelight);
		modelStack.PopMatrix();

		// =========================== L_LEGS ==============================
		modelStack.PushMatrix();
		modelStack.Translate(0.6,0.75,0);
		modelStack.Rotate(static_cast<CCharacter*>(pObj)->getMovement(),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_SECURITYGUARD_LEG], togglelight);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else if(static_cast<CCharacter*>(pObj)->getRole()==3)
	{
		modelStack.PushMatrix();
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
		modelStack.Rotate(-(static_cast<CCharacter*>(pObj)->getMovement()),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG] , togglelight);
		modelStack.PopMatrix();

		// =========================== L_LEGS ==============================
		modelStack.PushMatrix();
		modelStack.Translate(0.6,0.75,0);
		modelStack.Rotate(static_cast<CCharacter*>(pObj)->getMovement(),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG], togglelight);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
	else if(static_cast<CCharacter*>(pObj)->getRole()==4)
	{
		modelStack.PushMatrix();
		modelStack.Translate(pObj->getTranslate().x+5, pObj->getTranslate().y, pObj->getTranslate().z);
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
		modelStack.Rotate(-(static_cast<CCharacter*>(pObj)->getMovement()),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_STAFF_LEG] , togglelight);
		modelStack.PopMatrix();

		// =========================== L_LEGS ==============================
		modelStack.PushMatrix();
		modelStack.Translate(0.6,0.75,0);
		modelStack.Rotate(static_cast<CCharacter*>(pObj)->getMovement(),1,0,0);
		RenderMesh(meshList[GEO_HUMAN_STAFF_LEG], togglelight);
		modelStack.PopMatrix();
		modelStack.PopMatrix();
	}
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
	for (int i = 0; i < objList.size(); ++i)
	{
		pObj = objList[i];
		delete pObj;
	}
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

	//glDisable(GL_DEPTH_TEST);
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
void SP2::Render2D(Mesh* mesh, float size, float x, float y)
{
	//if(!mesh || mesh->textureID <= 0) //Proper error check
	//return;

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
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);

	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
