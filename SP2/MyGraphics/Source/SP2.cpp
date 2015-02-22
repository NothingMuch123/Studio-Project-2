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

using namespace std;

int GetMagnitude(int CamPos,int ObjPos);

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
	camera.Init(Vector3(0,50,0), Vector3(0,50,-15), Vector3(0,1,0));

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
	initCar();

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");

	meshList[GEO_CUBE] = MeshBuilder::GenerateOBJ("cube" , "OBJ//Wall.obj");
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//MazeWall.tga");

	meshList[GEO_PLAYER] = MeshBuilder::GenerateOBJ( "player" , "OBJ//Wall.obj");
	meshList[GEO_PLAYER]->textureID = LoadTGA("Image//player_texture.tga");

	initHuman(); 
	initOuterSkybox();
	initSuperMarket();
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

	inCar = NULL;
	pObj = new CCar(OBJ_CAR, Vector3(-200,0,0), Vector3(0,0,0), Vector3(5,5,5), Vector3(17,8,17));
	pObj->calcBound();
	static_cast<CCar*>(pObj)->setCamera();
	objList.push_back(pObj);
	carList.push_back(static_cast<CCar*>(pObj));
}

void SP2::initSuperMarket()
{
	// Supermarket
	supermarketSize.Set(30,20,20);
	supermarketPosition.Set(0,0,0);
	supermarketScale.Set(10,10,10);
	// Door
	Vector3 doorPosition(supermarketPosition.x, supermarketPosition.y, supermarketPosition.z + ((supermarketScale.z * supermarketSize.z) / 2));
	supermarketDoorMaxBound.Set(doorPosition.x + (3 * supermarketScale.x), doorPosition.y, doorPosition.z + (5 * supermarketScale.z));
	supermarketDoorMinBound.Set(doorPosition.x - (3 * supermarketScale.x), doorPosition.y, doorPosition.z - (5 * supermarketScale.z));
	isDoorOpen = false;
	translateX = 0;
	
	meshList[GEO_SM] = MeshBuilder::GenerateOBJ("SuperMarket", "OBJ//supermarket.obj");
	meshList[GEO_SM]->textureID = LoadTGA("Image//SuperMarketTexture.tga");

	meshList[GEO_CASHIERT] = MeshBuilder::GenerateOBJ("CashierTable" , "OBJ//cashiertable.obj");
	meshList[GEO_CASHIERT]->textureID = LoadTGA("Image//cashier table.tga");

	meshList[GEO_CAMERA] = MeshBuilder::GenerateOBJ("Camera" , "OBJ//camera.obj");
	meshList[GEO_CAMERA]->textureID = LoadTGA("Image//camera_texture.tga");

	meshList[GEO_SCREEN] = MeshBuilder::GenerateOBJ("Camera Screen" , "OBJ//cameraScreen.obj");
	meshList[GEO_SCREEN]->textureID = LoadTGA("Image//cameraScreen_texture.tga");

	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ( "Shelf" ,"OBJ//shelf.obj");
	meshList[GEO_SHELF]->textureID = LoadTGA("Image//shelf.tga");
		
	meshList[GEO_SMD] = MeshBuilder::GenerateOBJ( "Shelf" ,"OBJ//SuperMarketDoor.obj");
	meshList[GEO_SMD]->textureID = LoadTGA("Image//SuperMarketDoorTexture.tga");
	//======================================================= ITEMS ====================================================================
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

void SP2::initHuman()
{
	meshList[GEO_HUMAN_SHOPPER_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	meshList[GEO_HUMAN_SHOPPER_BODY]->textureID = LoadTGA("Image//shopper_texture.tga");

	meshList[GEO_HUMAN_SHOPPER_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	meshList[GEO_HUMAN_SHOPPER_ARM]->textureID = LoadTGA ("Image//shopper_texture.tga");

	meshList[GEO_HUMAN_SHOPPER_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	meshList[GEO_HUMAN_SHOPPER_HAND]->textureID = LoadTGA ("Image//shopper_texture.tga");

	meshList[GEO_HUMAN_SHOPPER_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	meshList[GEO_HUMAN_SHOPPER_LEG]->textureID = LoadTGA ("Image//shopper_texture.tga");

	meshList[GEO_HUMAN_POLICE_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	meshList[GEO_HUMAN_POLICE_BODY]->textureID = LoadTGA("Image//police_texture.tga");

	meshList[GEO_HUMAN_POLICE_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	meshList[GEO_HUMAN_POLICE_ARM]->textureID = LoadTGA ("Image//police_texture.tga");

	meshList[GEO_HUMAN_POLICE_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	meshList[GEO_HUMAN_POLICE_HAND]->textureID = LoadTGA ("Image//police_texture.tga");

	meshList[GEO_HUMAN_POLICE_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	meshList[GEO_HUMAN_POLICE_LEG]->textureID = LoadTGA ("Image//police_texture.tga");

	meshList[GEO_HUMAN_STAFF_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	meshList[GEO_HUMAN_STAFF_BODY]->textureID = LoadTGA("Image//staff_texture.tga");

	meshList[GEO_HUMAN_STAFF_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	meshList[GEO_HUMAN_STAFF_ARM]->textureID = LoadTGA ("Image//staff_texture.tga");

	meshList[GEO_HUMAN_STAFF_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	meshList[GEO_HUMAN_STAFF_HAND]->textureID = LoadTGA ("Image//staff_texture.tga");

	meshList[GEO_HUMAN_STAFF_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	meshList[GEO_HUMAN_STAFF_LEG]->textureID = LoadTGA ("Image//staff_texture.tga");
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
	fps = 60;
	togglelight = false;
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

	meshList[GEO_OUTER_BOTTOM] = MeshBuilder::GenerateQuad("Outer skybox bottom", Color(1,1,1), TexCoord(1,1));
	meshList[GEO_OUTER_BOTTOM]->textureID = LoadTGA("Image//OuterSkybox//bottom.tga");

	outerSkyboxSize.Set(1000,1000,1000);
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
	for (int i = 0; i < objList.size(); ++i)
	{
		pObj = objList[i];
		if (pObj->getRender())
		{
			if (camera.target.x < pObj->getMaxBound().x && camera.target.x > pObj->getMinBound().x && camera.target.y < pObj->getMaxBound().y && camera.target.y > pObj->getMinBound().y && camera.target.z < pObj->getMaxBound().z && camera.target.z > pObj->getMinBound().z)
			{
				if (pObj->getID() == OBJ_CAR)
				{
					if (Application::IsKeyPressed('C') && inCar == NULL)
					{
						inCar = static_cast<CCar*>(pObj);
						pObj->setRender(false);
						camera = static_cast<CCar*>(pObj)->carCamera;
					}
				}
			}
		}
	}
	if (inCar != NULL)
	{
		updateCar(dt);
	}

	camera.Update(dt, outerSkyboxMaxBound, outerSkyboxMinBound, objList);
	updateHuman(dt);
	updateSuperMarket(dt);

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
void SP2::updateSuperMarket(double dt)
{
	/*cout<<camera.position.x<<" "<<camera.position.z<<" x:"<<GetMagnitude(camera.position.x,0)<<" z:"<<GetMagnitude(camera.position.z,100);
*/
	//if(GetMagnitude(camera.position.x,0)<((supermarketPosition.x+2.5)*supermarketScale.x) && GetMagnitude(camera.position.z,(supermarketPosition.z+3)*supermarketScale.z)<((supermarketPosition.z - (supermarketScale.z*supermarketSize.z))*supermarketScale.z))
	if (camera.position.x < supermarketDoorMaxBound.x && camera.position.x > supermarketDoorMinBound.x && camera.position.z < supermarketDoorMaxBound.z && camera.position.z > supermarketDoorMinBound.z)
	{
		isDoorOpen = true;
		if(translateX<2)
		{
			translateX+=0.1;
		}
	}
	else
	{
		isDoorOpen = false;
	
		if(translateX>0)
		{
			translateX-=0.1;
		}
	}
}

void SP2::updateCar(double dt)
{
	if (Application::IsKeyPressed('V'))
	{
		inCar->setRender(true);
		inCar->carCamera = camera;
		Vector3 right = ((inCar->carCamera.target - inCar->carCamera.position).Cross(inCar->carCamera.up)).Normalized();
		Mtx44 Rotation;
		Rotation.SetToRotation(90,0,1,0);
		camera.Init(camera.position - (right * 65), (camera.position - (right * 65)) + ((Rotation * (camera.position - camera.target))), Vector3(0,1,0));
		inCar->updatePosition();
		inCar->calcBound();
		inCar = NULL;
	}
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float rotateY = inCar->getRotate().y + (75*dt);
		inCar->setRotateY(rotateY);
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float rotateY = inCar->getRotate().y - (75*dt);
		inCar->setRotateY(rotateY);
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
		}
	}

	// Car screen
	if (inCar != NULL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
		modelStack.Rotate(inCar->getRotate().y - 90, 0, 1, 0);
		modelStack.Scale(3.4 * inCar->getScale().x, 3 * inCar->getScale().y, 1);
		RenderMesh(meshList[GEO_CAR_SCREEN], togglelight);
		modelStack.PopMatrix();
	}

	// Target test
	/*
	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x, camera.target.y, camera.target.z);
	modelStack.Scale(5,5,5);
	RenderMesh(meshList[GEO_CUBE], togglelight);
	modelStack.PopMatrix();*/
	
	RenderMesh(meshList[GEO_AXES], false);

	//renderHuman(1);
	//renderHuman(2);
	//renderHuman(3);

	// Please do the proper modelStack method, else anything below it will be ruined -Fang Shu
	/*RenderMesh(meshList[GEO_ITEM_4] , togglelight);
	modelStack.Translate(0,0,0);
	modelStack.Scale(0.2,0.3,0.2);
	RenderMesh(meshList[GEO_CUBE] , togglelight);*/

	std::ostringstream sFPS, sX, sY, sZ;
	sFPS << fps;
	sX << camera.position.x;
	sY << camera.position.y;
	sZ << camera.position.z;
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 1, 0), 2, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], sFPS.str(), Color(0, 1, 0), 2, 4, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "X: ", Color(0, 1, 0), 2, 1, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], sX.str(), Color(0, 1, 0), 2, 4, 4);
	RenderTextOnScreen(meshList[GEO_TEXT], "Y: ", Color(0, 1, 0), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], sY.str(), Color(0, 1, 0), 2, 4, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z: ", Color(0, 1, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], sZ.str(), Color(0, 1, 0), 2, 4, 2);
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

void SP2::renderHuman(int type)// 1- shopper , 2 - police, 3 - staff
{
	if( type == 1)
	{
		modelStack.PushMatrix();
		{
			//===================================== BODY ===========================
			modelStack.Translate(0,0,0);
			RenderMesh(meshList[GEO_HUMAN_SHOPPER_BODY], togglelight); 
			modelStack.PushMatrix();
			{
				// ================================ L_SHOULDERs =======================
				modelStack.Translate(1.5,2.8,0);
				RenderMesh(meshList[GEO_HUMAN_SHOPPER_ARM], togglelight); 
				modelStack.PushMatrix();
				{
					//=============================== L_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_SHOPPER_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================ R_SHOULDER =======================
				modelStack.Translate(-1.5,2.8, 0);
				RenderMesh(meshList[GEO_HUMAN_SHOPPER_ARM], togglelight);
				modelStack.PushMatrix();
				{
					//=============================== R_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_SHOPPER_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================== R_LEGS ========================
				modelStack.Translate(-0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG] , togglelight);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// =========================== L_LEGS ==============================
				modelStack.Translate(0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_SHOPPER_LEG], togglelight);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	if(type == 2)
	{
		modelStack.PushMatrix();
		{
			//===================================== BODY ===========================
			modelStack.Translate(0,0,0);
			RenderMesh(meshList[GEO_HUMAN_POLICE_BODY], togglelight); 
			modelStack.PushMatrix();
			{
				// ================================ L_SHOULDERs =======================
				modelStack.Translate(1.5,2.8,0);
				RenderMesh(meshList[GEO_HUMAN_POLICE_ARM], togglelight); 
				modelStack.PushMatrix();
				{
					//=============================== L_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_POLICE_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================ R_SHOULDER =======================
				modelStack.Translate(-1.5,2.8, 0);
				RenderMesh(meshList[GEO_HUMAN_POLICE_ARM], togglelight);
				modelStack.PushMatrix();
				{
					//=============================== R_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_POLICE_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================== R_LEGS ========================
				modelStack.Translate(-0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_POLICE_LEG] , togglelight);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// =========================== L_LEGS ==============================
				modelStack.Translate(0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_POLICE_LEG], togglelight);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
	}
	if(type == 3)
	{
		modelStack.PushMatrix();
		{
			//===================================== BODY ===========================
			modelStack.Translate(0,0,0);
			RenderMesh(meshList[GEO_HUMAN_STAFF_BODY], togglelight); 
			modelStack.PushMatrix();
			{
				// ================================ L_SHOULDERs =======================
				modelStack.Translate(1.5,2.8,0);
				RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight); 
				modelStack.PushMatrix();
				{
					//=============================== L_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================ R_SHOULDER =======================
				modelStack.Translate(-1.5,2.8, 0);
				RenderMesh(meshList[GEO_HUMAN_STAFF_ARM], togglelight);
				modelStack.PushMatrix();
				{
					//=============================== R_HANDS =========================
					modelStack.Translate(0,-0.9,0);
					RenderMesh(meshList[GEO_HUMAN_STAFF_HAND], togglelight);
				}
				modelStack.PopMatrix();
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// ================================== R_LEGS ========================
				modelStack.Translate(-0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_STAFF_LEG] , togglelight);
			}
			modelStack.PopMatrix();
			modelStack.PushMatrix();
			{
				// =========================== L_LEGS ==============================
				modelStack.Translate(0.6,0.75,0);
				RenderMesh(meshList[GEO_HUMAN_STAFF_LEG], togglelight);
			}
			modelStack.PopMatrix();
		}
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

int GetMagnitude(int CamPos,int ObjPos)
{
	int Magnitude = CamPos - ObjPos;

	if(Magnitude<0)
	{
		Magnitude = Magnitude*-1;
	}

	return Magnitude;
}
