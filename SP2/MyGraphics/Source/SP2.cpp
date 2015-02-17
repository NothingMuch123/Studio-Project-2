#include "SP2.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include <sstream>
#include <fstream>

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
	camera.Init(Vector3(0,50,0), Vector3(0,50,-5), Vector3(0,1,0));

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
	meshList[GEO_CUBE]->textureID = LoadTGA("Image//Wall.tga");

	human.InitStaff();
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
}

void SP2::initSuperMarket()
{
	meshList[GEO_SM] = MeshBuilder::GenerateOBJ("SuperMarket", "OBJ//supermarket.obj");
	meshList[GEO_SM]->textureID = LoadTGA("Image//SuperMarketTexture.tga");
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
	skyboxSize.Set(1000,1000,1000);
	skyboxOffset = 10;
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
}

void SP2::Update(double dt)
{
	updateCar();
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	camera.Update(dt);
	UpdateHuman(dt);

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

void SP2::updateCar()
{

}

void SP2::RenderHuman()
{
	modelStack.PushMatrix();
	{
		//===================================== BODY ===========================
		modelStack.Translate(0,5,20);
		RenderMesh(human.GetHuman(0), false); 
		modelStack.PushMatrix();
		{
			// ================================ L_SHOULDERs =======================
			modelStack.Translate(1.5,2.8,0);
			RenderMesh(human.GetHuman(1), false); 
			modelStack.PushMatrix();
			{
				//=============================== L_HANDS =========================
				modelStack.Translate(0,-0.9,0);
				RenderMesh(human.GetHuman(2), false);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			// ================================ R_SHOULDER =======================
			modelStack.Translate(-1.5,2.8, 0);
			RenderMesh(human.GetHuman(1), false);
			modelStack.PushMatrix();
			{
				//=============================== R_HANDS =========================
				modelStack.Translate(0,-0.9,0);
				RenderMesh(human.GetHuman(2), false);
			}
			modelStack.PopMatrix();
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			// ================================== R_LEGS ========================
			modelStack.Translate(-0.6,0.75,0);
			RenderMesh(human.GetHuman(3) , false);
		}
		modelStack.PopMatrix();
		modelStack.PushMatrix();
		{
			// =========================== L_LEGS ==============================
			modelStack.Translate(0.6,0.75,0);
			RenderMesh(human.GetHuman(3), false);
		}
		modelStack.PopMatrix();
	}
	modelStack.PopMatrix();

}

void SP2::UpdateHuman(double dt)
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

	renderCar();

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	{
		modelStack.Translate(0,0,20);
		RenderHuman();
	}
	modelStack.PopMatrix();

	std::ostringstream sFPS;
	sFPS << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], "FPS: ", Color(0, 1, 0), 2, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], sFPS.str(), Color(0, 1, 0), 2, 6, 1);
}
void SP2::renderSuperMarket()
{
	modelStack.PushMatrix();
	modelStack.Scale(5,5,5);
	modelStack.Translate(0,0,0);
	RenderMesh(meshList[GEO_SM], false);
	modelStack.PopMatrix();
}
void SP2::renderCar()
{
	modelStack.PushMatrix();
	modelStack.Scale(4,4,4);
	modelStack.Translate(25,1,0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_CAR], false);
	modelStack.PopMatrix();
	for(int x = -5;x<11;x+=10)
	{
		for(int y = -3;y<4;y+=6)
		{
			modelStack.PushMatrix();
			modelStack.Translate(x,0,y);
			RenderMesh(meshList[GEO_CAR_TYRE], false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();

}
void SP2::renderOuterSkybox()
{
	float translateY = 10;
	modelStack.PushMatrix();
	modelStack.Translate(0, translateY, -skyboxSize.z/2 + skyboxOffset);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_FRONT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, translateY, skyboxSize.z/2 - skyboxOffset);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_BACK], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-skyboxSize.z/2 + skyboxOffset, translateY, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_LEFT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(skyboxSize.z/2 - skyboxOffset, translateY, 0);
	modelStack.Rotate(-90,0,1,0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_RIGHT], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, skyboxSize.y/2 + translateY - skyboxOffset, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
	RenderMesh(meshList[GEO_OUTER_TOP], togglelight);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(skyboxSize.x, skyboxSize.y, 1);
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