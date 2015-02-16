#include "Assignment03.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <sstream>
#include <fstream>

Assignment03::Assignment03()
{
}

Assignment03::~Assignment03()
{
}

void Assignment03::Init()
{
	startText = endText = false;
	lightHeight = -10;
	tiltUpDown = 0;
	monsterMaxJump = -19.5;
	monsterMinJump = -29.5;
	fps = 60;
	togglelight = true;
	togglecamera = false;
	// Init VBO here
	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

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
	
	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
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
	lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));

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

	Mtx44 projection;
	projection.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	projectionStack.LoadMatrix(projection);

	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 1, 0);
	//meshList[GEO_LIGHTBALL2] = MeshBuilder::GenerateSphere("lightball2", Color(1, 1, 1), 1, 0);

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Courier.tga");

	InitMap();
	
	//Initialize camera settings
	camera.Init(modelPosition, modelTarget, modelUp);

	// Init skybox
	InitSkybox();

	// Init model
	charInit();
}

void Assignment03::InitMap()
{
	std::vector<std::string> map;
	std::string data;
	std::ifstream fMap;
	fMap.open("map.txt");
	while(!fMap.eof())
	{
		fMap >> data;
		map.push_back(data);
	}
	map.pop_back();
	skyboxSize.Set(map[0].length() * 100, 60, map.size() * 100);
	skyboxOffset = 5;

	meshList[GEO_WALL] = MeshBuilder::GenerateOBJ("Wall", "OBJ\\wall.obj");
	meshList[GEO_WALL]->textureID = LoadTGA("Image\\MazeWall.tga");
	meshList[GEO_WALL]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_WALL]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALL]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WALL]->material.kShininess = 1.f;

	meshList[GEO_MONSTER] = MeshBuilder::GenerateOBJ("Monster", "OBJ\\Monster.obj");
	meshList[GEO_MONSTER]->textureID = LoadTGA("Image\\Monster.tga");
	meshList[GEO_MONSTER]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MONSTER]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MONSTER]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MONSTER]->material.kShininess = 1.f;

	meshList[GEO_CHEST] = MeshBuilder::GenerateOBJ("Chest", "OBJ\\Chest.obj");
	meshList[GEO_CHEST]->textureID = LoadTGA("Image\\Chest.tga");
	meshList[GEO_CHEST]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_CHEST]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CHEST]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CHEST]->material.kShininess = 1.f;

	meshList[GEO_TROPHY] = MeshBuilder::GenerateOBJ("Trophy", "OBJ\\Trophy.obj");
	meshList[GEO_TROPHY]->textureID = LoadTGA("Image\\Trophy.tga");
	meshList[GEO_TROPHY]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TROPHY]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TROPHY]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TROPHY]->material.kShininess = 1.f;

	float startX = -(skyboxSize.x / 2) + 50, startZ = -(skyboxSize.z / 2) + 50; // X starts from left and Z starts from top
	for (int row = 0; row < map.size(); row++)
	{
		for (int col = 0; col < map[0].length(); col++)
		{
			if (map[row][col] == '#') // Only change translate X & Z
			{
				InitObj(meshList[GEO_WALL], startX + (col * 100), 0, startZ + (row * 100), 0, 0, 0, 100, skyboxSize.y, 100, CObj::SHAPES::S_CUBE);
			}
			else if (map[row][col] == 'M')
			{
				InitObj(meshList[GEO_MONSTER], startX + (col * 100), (-7.5 * 2.5) - 22, startZ + (row * 100), 0, 180, 0, 2.5, 2.5, 2.5, CObj::SHAPES::S_MONSTER);
			}
			else if (map[row][col] == 'C')
			{
				InitObj(meshList[GEO_CHEST], startX + (col * 100), -skyboxSize.y / 2, startZ + (row * 100), 0, 180, 0, 20, 20, 20, CObj::SHAPES::S_CHEST);
			}
			else if (map[row][col] == 'S')
			{
				modelPosition.Set(startX + (col * 100), 10, startZ + (row * 100));
				modelTarget.Set(modelPosition.x - 1, modelPosition.y, modelPosition.z);
				modelUp.Set(0, 1, 0);
				modelView = (modelTarget - modelPosition).Normalized();
				startMaxBound.Set(startX + (col * 100) + 50, 30, startZ + (row * 100) + 50);
				startMinBound.Set(startX + (col * 100) - 50, -30, startZ + (row * 100) - 50);
			}
			else if (map[row][col] == 'E')
			{
				InitObj(meshList[GEO_TROPHY], startX + (col * 100), -skyboxSize.y / 2, startZ + (row * 100), 0, 0, 0, 1, 1, 1, CObj::SHAPES::S_TROPHY);
				endMaxBound.Set(startX + (col * 100) + 50, 30, startZ + (row * 100) + 50);
				endMinBound.Set(startX + (col * 100) - 50, -30, startZ + (row * 100) - 50);
			}
		}
	}
}

void Assignment03::InitSkybox()
{
	// Skybox
	SkyBoxBoundMax.Set(skyboxSize.x/2 - skyboxOffset, skyboxSize.y/2 - skyboxOffset, skyboxSize.z/2 - skyboxOffset);
	SkyBoxBoundMin.Set(-skyboxSize.x/2 + skyboxOffset, -skyboxSize.y/2 + skyboxOffset, -skyboxSize.z/2 + skyboxOffset);

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.y/60));
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_FRONT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FRONT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_FRONT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_FRONT]->material.kShininess = 1.f;

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.y/60));
	meshList[GEO_BACK]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_BACK]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BACK]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BACK]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BACK]->material.kShininess = 1.f;

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.y/60));
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_LEFT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEFT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEFT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_LEFT]->material.kShininess = 1.f;

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.y/60));
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_RIGHT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_RIGHT]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RIGHT]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RIGHT]->material.kShininess = 1.f;

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.z/100));
	meshList[GEO_TOP]->textureID = LoadTGA("Image//Wall.tga");
	meshList[GEO_TOP]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TOP]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TOP]->material.kSpecular.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TOP]->material.kShininess = 1.f;

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), TexCoord(skyboxSize.x/100, skyboxSize.z/100));
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//Floor.tga");
	meshList[GEO_BOTTOM]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BOTTOM]->material.kDiffuse.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BOTTOM]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_BOTTOM]->material.kShininess = 1.f;
}

void Assignment03::charInit()
{	
	// Body
	bodyRotateAngleX = 0;
	bodyRotateAngleY = 0;
	bodyTranslateX = 0;
	bodyTranslateY = 0;
	move = false;

	// Stan
	int headSize = 10;
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Head", Color(0.9, 0.8, 0.6), headSize, 0);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HEAD]->material.kShininess = 8.f;

	meshList[GEO_HELMET] = MeshBuilder::GenerateSphere("Helmet", Color(0.09, 0.32, 0.63), headSize, 1);
	meshList[GEO_HELMET]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_HELMET]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HELMET]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMET]->material.kShininess = 8.f;

	meshList[GEO_HELMETTORUS] = MeshBuilder::GenerateTorus("Helmet torus", Color(0.6, 0.6, 0.6), 36, 36, 1, 1);
	meshList[GEO_HELMETTORUS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HELMETTORUS]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HELMETTORUS]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETTORUS]->material.kShininess = 1.f;
	
	meshList[GEO_HELMETTOP] = MeshBuilder::GenerateCone("Helmet top", Color(1, 0, 0), 0.5, 2);
	meshList[GEO_HELMETTOP]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_HELMETTOP]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HELMETTOP]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETTOP]->material.kShininess = 1.f;

	meshList[GEO_HELMETBORDER_H] = MeshBuilder::GenerateCylinder("Helmet border horizontal", Color(0.6, 0.6, 0.6), headSize, headSize / 4);
	meshList[GEO_HELMETBORDER_H]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETBORDER_H]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HELMETBORDER_H]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETBORDER_H]->material.kShininess = 8.f;

	meshList[GEO_HELMETBORDER_V] = MeshBuilder::GenerateCylinder("Helmet border vertical", Color(0.6, 0.6, 0.6), headSize, headSize / 4, 1);
	meshList[GEO_HELMETBORDER_V]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETBORDER_V]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HELMETBORDER_V]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETBORDER_V]->material.kShininess = 8.f;

	meshList[GEO_HELMETDIAMOND] = MeshBuilder::GenerateCube("Helmet diamond", Color(0.4, 0.4, 0.4));
	meshList[GEO_HELMETDIAMOND]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETDIAMOND]->material.kDiffuse.Set(0.4f, 0.4f, 0.4f);
	meshList[GEO_HELMETDIAMOND]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETDIAMOND]->material.kShininess = 8.f;

	meshList[GEO_HELMETSPHERE] = MeshBuilder::GenerateSphere("Helmet sphere", Color(0.4, 0.4, 0.4), 1, 0);
	meshList[GEO_HELMETSPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETSPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HELMETSPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HELMETSPHERE]->material.kShininess = 8.f;

	meshList[GEO_EYES] = MeshBuilder::GenerateSphere("Eyes", Color(1, 1, 1), 1, 0);
	meshList[GEO_EYES]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYES]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYES]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYES]->material.kShininess = 8.f;

	meshList[GEO_EYEBALL] = MeshBuilder::GenerateSphere("Eye ball", Color(0, 0, 0), 1, 0);
	meshList[GEO_EYEBALL]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYEBALL]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYEBALL]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_EYEBALL]->material.kShininess = 8.f;
	
	meshList[GEO_MOUTH] = MeshBuilder::GenerateSphere("Mouth", Color(0, 0, 0), 1, 1);
	meshList[GEO_MOUTH]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUTH]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MOUTH]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MOUTH]->material.kShininess = 8.f;

	meshList[GEO_BODY] = MeshBuilder::GenerateSphere("Body", Color(0.85, 0.34, 0.21), 8, 1);
	meshList[GEO_BODY]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BODY]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BODY]->material.kShininess = 8.f;

	meshList[GEO_BELT] = MeshBuilder::GenerateCylinder("Belt", Color(0.5, 0.2, 0.04), 8, 1);
	meshList[GEO_BELT]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELT]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BELT]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELT]->material.kShininess = 8.f;

	meshList[GEO_BELT2] = MeshBuilder::GenerateCube("Belt 2", Color(0.5, 0.2, 0.04));
	meshList[GEO_BELT2]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELT2]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BELT2]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELT2]->material.kShininess = 8.f;

	meshList[GEO_BELTBUCKLE] = MeshBuilder::GenerateCube("Belt buckle", Color(0.72, 0.72, 0.72));
	meshList[GEO_BELTBUCKLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTBUCKLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BELTBUCKLE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTBUCKLE]->material.kShininess = 8.f;

	meshList[GEO_BELTSTRIP] = MeshBuilder::GenerateCube("Belt strip", Color(0.72, 0.72, 0.72));
	meshList[GEO_BELTSTRIP]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTSTRIP]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BELTSTRIP]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTSTRIP]->material.kShininess = 8.f;

	meshList[GEO_BELTSPHERE] = MeshBuilder::GenerateSphere("Belt sphere", Color(0, 0, 0), 1);
	meshList[GEO_BELTSPHERE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTSPHERE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BELTSPHERE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BELTSPHERE]->material.kShininess = 8.f;

	meshList[GEO_ARM] = MeshBuilder::GenerateSphere("Arm", Color(0.9, 0.8, 0.6), 1);
	meshList[GEO_ARM]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_ARM]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_ARM]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_ARM]->material.kShininess = 8.f;

	meshList[GEO_BAND] = MeshBuilder::GenerateCylinder("Arm band", Color(0.7, 0.7, 0.7), 1, 1);
	meshList[GEO_BAND]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BAND]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BAND]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BAND]->material.kShininess = 8.f;

	meshList[GEO_FIST] = MeshBuilder::GenerateSphere("Fist", Color(0.9, 0.8, 0.6), 1);
	meshList[GEO_FIST]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FIST]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FIST]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FIST]->material.kShininess = 8.f;

	meshList[GEO_MODELBOTTOM] = MeshBuilder::GenerateSphere("Bottom", Color(0.09, 0.32, 0.63), 1, 1);
	meshList[GEO_MODELBOTTOM]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MODELBOTTOM]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODELBOTTOM]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MODELBOTTOM]->material.kShininess = 8.f;

	meshList[GEO_LEGS] = MeshBuilder::GenerateCylinder("Leg", Color(0.09, 0.32, 0.63), 4, 3);
	meshList[GEO_LEGS]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEGS]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_LEGS]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_LEGS]->material.kShininess = 8.f;

	meshList[GEO_FEET] = MeshBuilder::GenerateSphere("Feet", Color(0, 0, 0), 1, 1);
	meshList[GEO_FEET]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FEET]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEET]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_FEET]->material.kShininess = 8.f;

	meshList[GEO_HANDLE] = MeshBuilder::GenerateCylinder("Sword handle", Color(0.82, 0.7, 0.54), 0.5, 5);
	meshList[GEO_HANDLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HANDLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HANDLE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_HANDLE]->material.kShininess = 8.f;

	meshList[GEO_MIDDLE] = MeshBuilder::GenerateCube("Sword middle", Color(0.82, 0.7, 0.54));
	meshList[GEO_MIDDLE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MIDDLE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MIDDLE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_MIDDLE]->material.kShininess = 8.f;

	meshList[GEO_BLADE] = MeshBuilder::GenerateCube("Sword middle", Color(0.82, 0.7, 0.54));
	meshList[GEO_BLADE]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLADE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BLADE]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_BLADE]->material.kShininess = 8.f;

	meshList[GEO_TIP] = MeshBuilder::GenerateCube("Sword tip", Color(0.82, 0.7, 0.54));
	meshList[GEO_TIP]->material.kAmbient.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TIP]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TIP]->material.kSpecular.Set(0.2f, 0.2f, 0.2f);
	meshList[GEO_TIP]->material.kShininess = 8.f;
}

void Assignment03::Update(double dt)
{
	lights[0].position.Set(modelPosition.x, modelPosition.y + lightHeight, modelPosition.z); // Follow model
	lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
	lights[1].position.Set(modelPosition.x, modelPosition.y - 20, modelPosition.z); // Follow model

	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	// Text print check
	if (objList.size() != 0)
	{
		for (int i = 0; i < objList.size(); i++)
		{
			pObj = objList[i];
		}
	}
	
	// Interaction check
	float monsterJumpSpeed = 30;
	if (objList.size() != 0)
	{
		for (int i = 0; i < objList.size(); i++)
		{
			pObj = objList[i];
			if (pObj->getShape() != CObj::SHAPES::S_CUBE)
			{
				if (pObj->getShape() == CObj::SHAPES::S_MONSTER)
				{
					if (modelPosition.x < pObj->getInteractMaxBound().x && modelPosition.x > pObj->getInteractMinBound().x && modelPosition.z < pObj->getInteractMaxBound().z && modelPosition.z > pObj->getInteractMinBound().z)
					{
						if (pObj->getTranslateY() < monsterMinJump)
						{
							pObj->setMonsterJump(false);
						}
						if (pObj->getTranslateY() < monsterMaxJump && pObj->getMonsterJump() == false)
						{
							pObj->setTranslateY(pObj->getTranslateY() + (float)(monsterJumpSpeed * dt));
						}
						else
						{
							pObj->setMonsterJump(true);
							pObj->setTranslateY(pObj->getTranslateY() - (float)(monsterJumpSpeed * dt));
						}
					}
					else
					{
						if (pObj->getTranslateY() < monsterMinJump)
						{
							pObj->setTranslateY(pObj->getTranslateY() + (float)(monsterJumpSpeed * dt));
							if (pObj->getTranslateY() >= monsterMinJump)
							{
								pObj->setTranslateY(monsterMinJump);
							}
						}
						else
						{
							pObj->setTranslateY(pObj->getTranslateY() - (float)(monsterJumpSpeed * dt));
							if (pObj->getTranslateY() <= monsterMinJump)
							{
								pObj->setTranslateY(monsterMinJump);
							}
						}
					}
				}
			}
		}
	}
	// Toggle start text
	if (modelPosition.x < startMaxBound.x && modelPosition.x > startMinBound.x && modelPosition.z < startMaxBound.z && modelPosition.z > startMinBound.z)
	{
		startText = true;
	}
	else
	{
		startText = false;
	}
	// Toggle end text
	if (modelPosition.x < endMaxBound.x && modelPosition.x > endMinBound.x && modelPosition.z < endMaxBound.z && modelPosition.z > endMinBound.z)
	{
		endText = true;
	}
	charUpdate(dt);
	if (togglecamera == true)
	{
		camera.Update(dt, objList, SkyBoxBoundMax, SkyBoxBoundMin);
	}

	if(Application::IsKeyPressed('Z'))
	{
		togglelight = true;
	}
	if(Application::IsKeyPressed('X'))
	{
		togglelight = false;
	}
	if (Application::IsKeyPressed('C'))
	{
		togglecamera = true;
		camera.position = modelPosition;
		camera.target = modelTarget;
		camera.up = modelUp;
	}
	if (Application::IsKeyPressed('V'))
	{
		togglecamera = false;
	}
	static double fpsRefresh;
	fpsRefresh += dt;
	if (fpsRefresh >= 1)
	{
		fps = 1 / dt;
		fpsRefresh = 0;
	}
}

void Assignment03::charUpdate(double dt)
{
	if (Application::IsKeyPressed('W') || Application::IsKeyPressed('A') || Application::IsKeyPressed('S') || Application::IsKeyPressed('D'))
	{
		move = true;
	}
	const float rotateSpeed = 50;
	if (move == true && togglecamera == false) // Move character
	{
		// Body movement
		static bool bodyRotate = false; // False = Rotate positively (Anti-clockwise) | True = Rotate negatively (Clockwise)
		const float maxBodyAngle = 5, minBodyAngle = -5, moveSpeed = 50;
		if (bodyRotateAngleX <= minBodyAngle)
		{
			bodyRotate = false;
		}
		if (bodyRotateAngleX < maxBodyAngle && bodyRotate == false)
		{
			bodyRotateAngleX += (float) (rotateSpeed * dt);
		}
		else
		{
			bodyRotate = true;
			bodyRotateAngleX -= (float) (rotateSpeed * dt);
		}
		if (bodyRotateAngleX >= 0)
		{
			bodyTranslateY = bodyRotateAngleX / maxBodyAngle;
		}
		else
		{
			bodyTranslateY = -bodyRotateAngleX / maxBodyAngle;
		}
		if (Application::IsKeyPressed('W')) // Move forward
		{
			Vector3 tempTarget = modelTarget, tempPosition = modelPosition;
			float yaw = (float)(moveSpeed * dt);
			Vector3 zeroTarget = modelTarget;
			zeroTarget.y = modelPosition.y;
			modelView = (zeroTarget - modelPosition).Normalized();
			modelPosition += (modelView * yaw);
			modelTarget += (modelView * yaw);

			if (objList.size() != 0)
			{
				for (int i = 0; i < objList.size(); i++)
				{
					pObj = objList[i];
					if(boundCheck(pObj->getMaxBound(), pObj->getMinBound()))
					{
						modelTarget = tempTarget;
						modelPosition = tempPosition;
					}
				}
			}
			else
			{
				if (skyboxCheck())
				{
					modelTarget = tempTarget;
					modelPosition = tempPosition;
				}
			}
			lights[0].position.Set(modelPosition.x, modelPosition.y + lightHeight, modelPosition.z);
			lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
		}
		if (Application::IsKeyPressed('S')) // Move backward
		{
			Vector3 tempTarget = modelTarget, tempPosition = modelPosition;
			float yaw = (float)(-moveSpeed * dt);
			Vector3 zeroTarget = modelTarget;
			zeroTarget.y = modelPosition.y;
			modelView = (zeroTarget - modelPosition).Normalized();
			modelPosition += (modelView * yaw);
			modelTarget += (modelView * yaw);
			

			if (objList.size() != 0)
			{
				for (int i = 0; i < objList.size(); i++)
				{
					pObj = objList[i];
					if(boundCheck(pObj->getMaxBound(), pObj->getMinBound()))
					{
						modelTarget = tempTarget;
						modelPosition = tempPosition;
					}
				}
			}
			else
			{
				if (skyboxCheck())
				{
					modelTarget = tempTarget;
					modelPosition = tempPosition;
				}
			}
			lights[0].position.Set(modelPosition.x, modelPosition.y + lightHeight, modelPosition.z);
			lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
		}
		if(Application::IsKeyPressed('A'))
		{
			Vector3 tempTarget = modelTarget, tempPosition = modelPosition;
			float yaw = (float)(-moveSpeed * dt);
			modelView = (modelTarget - modelPosition).Normalized();
			modelPosition += (modelView.Cross(modelUp) * yaw);
			modelTarget += (modelView.Cross(modelUp) * yaw);

			if (objList.size() != 0)
			{
				for (int i = 0; i < objList.size(); i++)
				{
					pObj = objList[i];
					if(boundCheck(pObj->getMaxBound(), pObj->getMinBound()))
					{
						modelTarget = tempTarget;
						modelPosition = tempPosition;
					}
				}
			}
			else
			{
				if (skyboxCheck())
				{
					modelTarget = tempTarget;
					modelPosition = tempPosition;
				}
			}
			lights[0].position.Set(modelPosition.x, modelPosition.y + lightHeight, modelPosition.z);
			lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
		}
		if(Application::IsKeyPressed('D'))
		{
			Vector3 tempTarget = modelTarget, tempPosition = modelPosition;
			float yaw = (float)(moveSpeed * dt);
			modelView = (modelTarget - modelPosition).Normalized();
			modelPosition += (modelView.Cross(modelUp) * yaw);
			modelTarget += (modelView.Cross(modelUp) * yaw);

			if (objList.size() != 0)
			{
				for (int i = 0; i < objList.size(); i++)
				{
					pObj = objList[i];
					if(boundCheck(pObj->getMaxBound(), pObj->getMinBound()))
					{
						modelTarget = tempTarget;
						modelPosition = tempPosition;
					}
				}
			}
			else
			{
				if (skyboxCheck())
				{
					modelTarget = tempTarget;
					modelPosition = tempPosition;
				}
			}
		}
		lights[0].position.Set(modelPosition.x, modelPosition.y + lightHeight, modelPosition.z);
		lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
	}
	else
	{
		if (bodyRotateAngleX < 0) // Smaller than or equal to 0
		{
			bodyRotateAngleX += (float) (rotateSpeed * dt);
			if (bodyRotateAngleX >= 0)
			{
				bodyRotateAngleX = 0;
			}
		}
		else if (bodyRotateAngleX > 0)
		{
			bodyRotateAngleX -= (float) (rotateSpeed * dt);
			if (bodyRotateAngleX <= 0)
			{
				bodyRotateAngleX = 0;
			}
		}
	}
	move = false; // Forces move to false for next check

	// Rotation
	if (togglecamera == false)
	{
		if(Application::IsKeyPressed(VK_LEFT))
		{
			Mtx44 rotation;
			float pitch = (float)(50 * dt);
			modelView = (modelTarget - modelPosition).Normalize();
			rotation.SetToRotation(pitch, 0, 1, 0);
			modelView = rotation * modelView;
			modelTarget = (modelPosition + modelView);
			modelUp = rotation * modelUp;
			bodyRotateAngleY += pitch;
			lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
		}
		if(Application::IsKeyPressed(VK_RIGHT))
		{
			Mtx44 rotation;
			float pitch = (float)(-50 * dt);
			modelView = (modelTarget - modelPosition).Normalize();
			rotation.SetToRotation(pitch, 0, 1, 0);
			modelView = rotation * modelView;
			modelTarget = (modelPosition + modelView);
			modelUp = rotation * modelUp;
			bodyRotateAngleY += pitch;
			lights[0].spotDirection.Set(cos(Math::DegreeToRadian(-bodyRotateAngleY)), 0, sin(Math::DegreeToRadian(-bodyRotateAngleY)));
		}
		if(Application::IsKeyPressed(VK_UP) && tiltUpDown < 80)
		{
			Mtx44 rotation;
			float pitch = (float)(50 * dt);
			modelView = (modelTarget - modelPosition).Normalized();
			Vector3 right = modelView.Cross(modelUp);
			right.y = 0;
			right.Normalize();
			modelUp = right.Cross(modelView).Normalized();
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			modelView = rotation * modelView;
			modelTarget = (modelPosition + modelView);
			tiltUpDown += pitch;
		}
		if(Application::IsKeyPressed(VK_DOWN) && tiltUpDown > -10)
		{
			Mtx44 rotation;
			float pitch = (float)(-50 * dt);
			modelView = (modelTarget - modelPosition).Normalized();
			Vector3 right = modelView.Cross(modelUp);
			right.y = 0;
			right.Normalize();
			modelUp = right.Cross(modelView).Normalized();
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			modelView = rotation * modelView;
			modelTarget = (modelPosition + modelView);
			tiltUpDown += pitch;
		}
	}
}

bool Assignment03::boundCheck(Vector3 BoundMax, Vector3 BoundMin)
{
	if ((modelPosition.x < BoundMax.x && modelPosition.x > BoundMin.x && modelPosition.y < BoundMax.y && modelPosition.y > BoundMin.y && modelPosition.z < BoundMax.z && modelPosition.z > BoundMin.z) || (modelPosition.x >= SkyBoxBoundMax.x || modelPosition.x <= SkyBoxBoundMin.x || modelPosition.y >= SkyBoxBoundMax.y || modelPosition.y <= SkyBoxBoundMin.y || modelPosition.z >= SkyBoxBoundMax.z || modelPosition.z <= SkyBoxBoundMin.z))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Assignment03::skyboxCheck()
{
	if (modelPosition.x >= SkyBoxBoundMax.x || modelPosition.x <= SkyBoxBoundMin.x || modelPosition.y >= SkyBoxBoundMax.y || modelPosition.y <= SkyBoxBoundMin.y || modelPosition.z >= SkyBoxBoundMax.z || modelPosition.z <= SkyBoxBoundMin.z)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Assignment03::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
	viewStack.LoadIdentity();
	if (togglecamera == true)
	{
		viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	}
	else
	{
		viewStack.LookAt(modelPosition.x, modelPosition.y, modelPosition.z, modelTarget.x, modelTarget.y, modelTarget.z, modelUp.x, modelUp.y, modelUp.z);
	}
	modelStack.LoadIdentity();

	// Light 1
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
	}

	//RenderMesh(meshList[GEO_AXES], false);

	RenderSkybox();

	// Render obj
	for (int i = 0; i < objList.size(); i++)
	{
		RenderObj(objList[i]);
	}

	// Stan
	modelStack.PushMatrix();
	RenderStan();
	modelStack.PopMatrix();

	std::ostringstream sFPS, sX, sZ;
	sFPS << fps;
	sX << modelPosition.x;
	sZ << modelPosition.z;
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 1, 0), 2, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], sFPS.str(), Color(0, 1, 0), 2, 6, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], "X: ", Color(0, 1, 0), 2, 1, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], sX.str(), Color(0, 1, 0), 2, 3, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "Z: ", Color(0, 1, 0), 2, 1, 2);
	RenderTextOnScreen(meshList[GEO_TEXT], sZ.str(), Color(0, 1, 0), 2, 3, 2);
	if (endText)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "You win", Color(1, 0, 0), 4, 7, 8);
	}
	else if (startText)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Find the trophy", Color(1, 0, 0), 4, 3, 8);
		RenderTextOnScreen(meshList[GEO_TEXT], "To win", Color(1, 0, 0), 3, 10.5, 9);
	}
}

void Assignment03::Exit()
{
	// Cleanup VBO here
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}

void Assignment03::RenderMesh(Mesh *mesh, bool enableLight)
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

void Assignment03::RenderText(Mesh* mesh, std::string text, Color color)
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

void Assignment03::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void Assignment03::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -skyboxSize.z/2);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_FRONT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, skyboxSize.z/2);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_BACK], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-skyboxSize.x/2, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_LEFT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(skyboxSize.x/2, 0, 0);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_RIGHT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, skyboxSize.y/2, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(skyboxSize.x, skyboxSize.x, 1);
	RenderMesh(meshList[GEO_TOP], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -skyboxSize.y/2, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(skyboxSize.x, skyboxSize.x, 1);
	RenderMesh(meshList[GEO_BOTTOM], togglelight);
	modelStack.PopMatrix();
}

void Assignment03::RenderObj(CObj *_obj)
{
	modelStack.PushMatrix();
	modelStack.Translate(_obj->getTranslateX(), _obj->getTranslateY(), _obj->getTranslateZ());
	modelStack.Rotate(_obj->getRotateX(), 1, 0, 0);
	modelStack.Rotate(_obj->getRotateY(), 0, 1, 0);
	modelStack.Rotate(_obj->getRotateZ(), 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Scale(_obj->getScaleX(), _obj->getScaleY(), _obj->getScaleZ());
	RenderMesh(_obj->getObj(), togglelight);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void Assignment03::InitObj(Mesh* _obj, float _translateX, float _translateY, float _translateZ, float _rotateX, float _rotateY, float _rotateZ, float _scaleX, float _scaleY, float _scaleZ, int _shape)
{
	pObj = new CObj(_obj, _translateX, _translateY, _translateZ, _rotateX, _rotateY, _rotateZ, _scaleX, _scaleY, _scaleZ, _shape);
	objList.push_back(pObj);
	pObj->init();
}

void Assignment03::RenderStan()
{
	modelStack.PushMatrix();	// Start of body
	modelStack.Translate(bodyTranslateX + modelPosition.x, -25 + bodyTranslateY, modelPosition.z);
	modelStack.Rotate(bodyRotateAngleX, 1, 0, 0);
	modelStack.Rotate(bodyRotateAngleY + 180, 0, 1, 0);
	RenderBody();
	modelStack.PushMatrix();	// Start of head
	modelStack.Translate(0, 20, 0);			// DO NOT CHANGE | Controls the location of head relevant to the body
	RenderHead();

	modelStack.PushMatrix();	// Start of helmet
	RenderHelmet();
	modelStack.PopMatrix();		// End of helmet
	modelStack.PopMatrix();		// End of head

	modelStack.PushMatrix();	// Start of arm (Right)
	modelStack.Translate(0, 8, -7.5);		// DO NOT CHANGE | Controls the location of the upper limb of the right arm
	RenderArms(0); // 0 to tell function it is right arm
	modelStack.PopMatrix();		// End of arm (Right)

	modelStack.PushMatrix();	// Start of arm (Left)
	modelStack.Translate(0, 8, 7.5);		// DO NOT CHANGE | Controls the location of the upper limb of the left arm
	modelStack.Rotate(180, 0, 1, 0);		// DO NOT CHANGE | Rotates the right arm to form the left arm with the same function
	RenderArms(1); // 1 to tell function it is left arm
	modelStack.PopMatrix();		// End of arm (Left)

	modelStack.PushMatrix();	// Start of leg (Right)
	modelStack.Translate(0, 0, -3.5);
	RenderLegs();
	modelStack.PopMatrix();		// End of leg (Right)

	modelStack.PushMatrix();	// Start of leg (Left)
	modelStack.Translate(0, 0, 3.5);
	RenderLegs();
	modelStack.PopMatrix();		// End of leg (Left)

	modelStack.PopMatrix();		// End of body
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for model's helmet
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderHelmet()
{
	modelStack.PushMatrix();	// Start of helmet
	modelStack.PushMatrix();	// Start scaling for helmet
	modelStack.Scale(1.01, 1, 1.01);
	RenderMesh(meshList[GEO_HELMET], togglelight);
	modelStack.PopMatrix();		// End scaling for helmet

	modelStack.PushMatrix();	// Start of helmet border (Horizontal)
	modelStack.Translate(0, 1, 0);
	modelStack.PushMatrix();	// Start scaling for helmet border (Horizontal)
	modelStack.Scale(1.05, 1, 1.05);
	RenderMesh(meshList[GEO_HELMETBORDER_H], togglelight);
	modelStack.PopMatrix();		// End scaling for helmet border (Horizontal)

	modelStack.PushMatrix();	// Start of helmet sphere overall for horizontal
	modelStack.PushMatrix();	// Start of helmet sphere 1 (Left)
	modelStack.Translate(6.5, 0, 8);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 1
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 1
	modelStack.PopMatrix();		// End of helmet sphere 1 (Left)

	modelStack.PushMatrix();	// Start of helmet sphere 2 (Left)
	modelStack.Translate(8.375, 0, 6.125);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 2
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 2
	modelStack.PopMatrix();		// End of helmet sphere 2 (Left)

	modelStack.PushMatrix();	// Start of helmet sphere 3 (Left)
	modelStack.Translate(9.5, 0, 4);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 3
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 3
	modelStack.PopMatrix();		// End of helmet sphere 3 (Left)

	// Right
	modelStack.PushMatrix();	// Start of helmet sphere 1 (Right)
	modelStack.Translate(6.5, 0, -8);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 1
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 1

	modelStack.PopMatrix();		// End of helmet sphere 1 (Right)

	modelStack.PushMatrix();	// Start of helmet sphere 2 (Right)
	modelStack.Translate(8.375, 0, -6.125);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 2
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 2
	modelStack.PopMatrix();		// End of helmet sphere 2 (Right)

	modelStack.PushMatrix();	// Start of helmet sphere 3 (Right)
	modelStack.Translate(9.5, 0, -4);
	modelStack.PushMatrix();	// Start scaling for helmet sphere 3
	modelStack.Scale(0.6, 0.6, 0.6);
	RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
	modelStack.PopMatrix();	// End scaling for helmet sphere 3
	modelStack.PopMatrix();		// End of helmet sphere 3 (Right)
	modelStack.PopMatrix();		// End of helmet sphere overall for horizontal

	modelStack.PopMatrix();		// End of helmet border (Horizontal)

	modelStack.PushMatrix();	// Start of helmet border (Vertical)
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.PushMatrix();	// Start scaling for helmet border (Vertical)
	modelStack.Scale(1.05, 1, 1.05);
	RenderMesh(meshList[GEO_HELMETBORDER_V], togglelight);
	modelStack.PushMatrix();	// Start of helmet torus
	modelStack.Translate(0, 0, 10);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();	// Start scaling for helmet torus
	modelStack.Scale(0.5, 0.5, 0.5);
	RenderMesh(meshList[GEO_HELMETTORUS], togglelight);
	modelStack.PopMatrix();		// End scaling for helmet torus
	/*modelStack.PushMatrix();	// Start of helmet top
	modelStack.Translate(0, 1, 0);
	RenderMesh(meshList[GEO_HELMETTOP], togglelight);
	modelStack.PopMatrix();		// End of helmet top*/
	modelStack.PopMatrix();		// End of helmet torus
	modelStack.PopMatrix();	// End scaling for helmet border (Vertical)
	modelStack.PushMatrix();	// Start of helmet sphere overall (Vertical)
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(8 -(j * 1.5), -0.5 + (i * 1), 6.5 + (j * 1.5));
			modelStack.PushMatrix();	// Start of scaling for helmet sphere (Vertical)
			modelStack.Scale(0.4, 0.4, 0.4);
			RenderMesh(meshList[GEO_HELMETSPHERE], togglelight);
			modelStack.PopMatrix();	// End of scaling for helmet sphere (Vertical)
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();		// End of helmet sphere overall (Vertical)

	modelStack.PopMatrix();		// End of helmet border (Vertical)

	modelStack.PushMatrix();	// Start of helmet diamond
	modelStack.Translate(9.01, 2, 0);
	modelStack.Rotate(45, 1, 0, 0);
	modelStack.Scale(4, 4, 4);
	RenderMesh(meshList[GEO_HELMETDIAMOND], togglelight);
	modelStack.PopMatrix();		// End of helmet diamond

	modelStack.PopMatrix();		// End of helmet
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for model's head
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderHead()
{
	modelStack.PushMatrix();	// Start of head
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[GEO_HEAD], togglelight);

	modelStack.PushMatrix();	// Start of eyes (Right)
	modelStack.Translate(9, 3, 2);
	modelStack.Rotate(30, 1, 0, 1);
	modelStack.Scale(1, 2.5, 2);
	RenderMesh(meshList[GEO_EYES], togglelight);

	modelStack.PushMatrix();	// Start of eye ball (Right)
	modelStack.Translate(0.8, -0.25, -0.25);
	modelStack.Scale(0.5, 0.2, 0.25);
	RenderMesh(meshList[GEO_EYEBALL], togglelight);
	modelStack.PopMatrix();		// End of eye ball (Right)
	modelStack.PopMatrix();		// End of eyes (Right)

	modelStack.PushMatrix();	// Start of eyes (Left)
	modelStack.Translate(9, 3, -2);
	modelStack.Rotate(-30, 1, 0, -1);
	modelStack.Scale(1, 2.5, 2);
	RenderMesh(meshList[GEO_EYES], togglelight);

	modelStack.PushMatrix();	// Start of eye ball (Left)
	modelStack.Translate(0.8, -0.3, 0.3);
	modelStack.Scale(0.5, 0.2, 0.25);
	RenderMesh(meshList[GEO_EYEBALL], togglelight);
	modelStack.PopMatrix();		// End of eye ball (Left)
	modelStack.PopMatrix();		// End of eyes (Left)

	modelStack.PushMatrix();	// Start of mouth
	modelStack.Translate(6.5, 7, 0);
	modelStack.Rotate(180, 1, 0, 0);
	RenderMesh(meshList[GEO_MOUTH], togglelight);
	modelStack.PopMatrix();		// End of mouth

	modelStack.PopMatrix();		// End of head
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for model's body
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderBody()
{
	modelStack.PushMatrix();	// Start of body
	modelStack.Scale(1, 1.5, 1);
	RenderMesh(meshList[GEO_BODY], togglelight);

	modelStack.PushMatrix();	// Start of belt
	modelStack.Translate(0, 1, 0);
	RenderMesh(meshList[GEO_BELT], togglelight);

	modelStack.PushMatrix();	// Start of belt buckle
	modelStack.Translate(8, 0, 0);
	modelStack.Scale(1, 1.5, 4);
	RenderMesh(meshList[GEO_BELTBUCKLE], togglelight);

	modelStack.PushMatrix();	// Start of belt 2
	modelStack.Translate(0.01, 0, 0);
	modelStack.Scale(1, 0.7, 0.7);
	RenderMesh(meshList[GEO_BELT2], togglelight);

	modelStack.PushMatrix();	// Start of belt strip
	modelStack.Translate(0.01, 0, 0.5);
	modelStack.Scale(1, 0.25, 0.3);
	RenderMesh(meshList[GEO_BELTSTRIP], togglelight);
	modelStack.PopMatrix();		// End of belt strip
	modelStack.PopMatrix();		// End of belt 2
	modelStack.PopMatrix();		// End of belt buckle

	modelStack.PushMatrix();	// Start of belt sphere (overall)

	modelStack.PushMatrix();	// Start of belt sphere 1 (left)
	modelStack.Translate(6.2, 0, 5);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 1 (left)

	modelStack.PushMatrix();	// Start of belt sphere 2 (left)
	modelStack.Translate(6.9, 0, 4);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 2 (left)

	modelStack.PushMatrix();	// Start of belt sphere 3 (left)
	modelStack.Translate(7.4, 0, 3);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 3 (left)

	for (int i = 0; i < 3; i++)
	{
		modelStack.PushMatrix();	// Start of belt sphere (middle)
		modelStack.Translate(8.5, 0, 1 - (i * 1));
		modelStack.Scale(0.2, 0.12, 0.2);
		RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
		modelStack.PopMatrix();		// End of belt sphere (middle)
	}

	modelStack.PushMatrix();	// Start of belt sphere 1 (right)
	modelStack.Translate(6.2, 0, -5);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 1 (right)

	modelStack.PushMatrix();	// Start of belt sphere 2 (right)
	modelStack.Translate(6.9, 0, -4);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 2 (right)

	modelStack.PushMatrix();	// Start of belt sphere 3 (right)
	modelStack.Translate(7.4, 0, -3);
	modelStack.Scale(0.2, 0.12, 0.2);
	RenderMesh(meshList[GEO_BELTSPHERE], togglelight);
	modelStack.PopMatrix();		// End of belt sphere 3 (right)

	modelStack.PopMatrix();		// End of belt sphere (overall)

	modelStack.PopMatrix();		// End of belt

	modelStack.PushMatrix();	// Start of bottom
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.PushMatrix();	// Start scaling for bottom
	modelStack.Scale(8, 1, 8);
	RenderMesh(meshList[GEO_MODELBOTTOM], togglelight);
	modelStack.PopMatrix();		// End scaling for bottom
	modelStack.PopMatrix();		// End of bottom

	modelStack.PopMatrix();		// End of body
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for model's arm
\param		Left_OR_Right - Tells the function to render left or right arm
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderArms(bool Left_OR_Right)
{
	modelStack.PushMatrix();	// Start of upper arm
	modelStack.Rotate(35, 1, 0, 0);	// Shoulder rotate angle on x axis [Fixed]
	modelStack.PushMatrix();	// Start scaling for upper arm
	modelStack.Scale(2, 3, 2);
	RenderMesh(meshList[GEO_ARM], togglelight);
	modelStack.PopMatrix();		// End scaling for upper arm

	modelStack.PushMatrix();	// Start of lower arm
	modelStack.PushMatrix();	// Start scaling for lower arm
	modelStack.Scale(1.8, 2.5, 1.8);
	RenderMesh(meshList[GEO_ARM], togglelight);
	modelStack.PopMatrix();		// End scaling for lower arm

	modelStack.PushMatrix();	// Start of band
	modelStack.Translate(0, -2, 0);
	modelStack.PushMatrix();	// Start scaling for band
	modelStack.Scale(1.8, 1, 1.8);
	RenderMesh(meshList[GEO_BAND], togglelight);
	modelStack.PopMatrix();		// End scaling for band

	modelStack.PushMatrix();	// Start of fist
	modelStack.Translate(0, -1.5, 0);
	modelStack.PushMatrix();	// Start scaling for fist
	modelStack.Scale(1.8, 1.8, 1.8);
	RenderMesh(meshList[GEO_FIST], togglelight);
	modelStack.PopMatrix();		// End scaling for fist

	if (Left_OR_Right == false) // Renders sword on right hand
	{
		modelStack.PushMatrix();	// Start of sword
		RenderSword();
		modelStack.PopMatrix();		// End of sword
	}

	modelStack.PopMatrix();		// End of fist

	modelStack.PopMatrix();		// End of band

	modelStack.PopMatrix();		// End of lower arm

	modelStack.PopMatrix();		// End of upper arm
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for model's leg
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderLegs()
{
	modelStack.PushMatrix();	// Start of leg
	modelStack.Translate(0, -1.5, 0);
	RenderMesh(meshList[GEO_LEGS], togglelight);

	modelStack.PushMatrix();	// Start of feet
	modelStack.Translate(1, -2.5, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();	// Start scaling for feet
	modelStack.Scale(4, 2, 5);
	RenderMesh(meshList[GEO_FEET], togglelight);
	modelStack.PopMatrix();		// End scaling for feet
	modelStack.PopMatrix();		// End of feet

	modelStack.PopMatrix();		// End of leg
}

// Item
/******************************************************************************/
/*!
\brief		Hierarchical modelling for entire item
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderSword()
{
	modelStack.PushMatrix();	// Start of handle
	RenderHandle();
	modelStack.PushMatrix();	// Start of blade
	RenderBlade();
	modelStack.PopMatrix();		// End of blade
	modelStack.PopMatrix();		// End of handle
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for item's handle
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderHandle()
{
	modelStack.PushMatrix();	// Start of sword handle
	modelStack.Rotate(90, 0, 0, 1);
	RenderMesh(meshList[GEO_HANDLE], togglelight);
	modelStack.PushMatrix();	// Start of sword middle
	modelStack.Translate(0, -3, 0);
	modelStack.PushMatrix();	// Start scaling for sword middle
	modelStack.Scale(1, 1, 5);
	RenderMesh(meshList[GEO_MIDDLE], togglelight);
	modelStack.PopMatrix();		// End scaling for sword middle
	modelStack.PopMatrix();		// End of sword middle

	modelStack.PopMatrix();		// End of sword handle
}

/******************************************************************************/
/*!
\brief		Hierarchical modelling for item's blade
\param		None
\exception	None
*/
/******************************************************************************/
void Assignment03::RenderBlade()
{
	modelStack.PushMatrix();	// Start of sword blade
	modelStack.Translate(6, 0, 0);
	modelStack.PushMatrix();	// Start scaling for sword blade
	modelStack.Scale(10, 1, 2);
	RenderMesh(meshList[GEO_BLADE], togglelight);
	modelStack.PopMatrix();		// End scaling for sword blade

	modelStack.PushMatrix();	// Start of sword tip
	modelStack.Translate(5, 0, 0);
	modelStack.Rotate(45, 0, 0, 1);
	modelStack.Scale(0.8, 0.8, 2);
	RenderMesh(meshList[GEO_TIP], togglelight);
	modelStack.PopMatrix();		// End of sword tip
	modelStack.PopMatrix();		// End of sword blade
}