#include "Human.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "Vertex.h"
#include "LoadTGA.h"
#include "LoadOBJ.h"

CHuman::CHuman(void)
{
}

CHuman::~CHuman(void)
{
}

void CHuman::InitShopper()
{
	human[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	human[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//shopper_texture.tga");
	human[GEO_HUMAN_BODY]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_BODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kShininess = 1.f;

	human[GEO_HUMAN_LARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_LARM]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_LARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_LHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_LHAND]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_LHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LLEG]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_LLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kShininess = 1.f;
	
	
	human[GEO_HUMAN_RARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_rightshoulder.obj");
	human[GEO_HUMAN_RARM]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_RARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_RHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_righthand.obj");
	human[GEO_HUMAN_RHAND]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_RHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_RLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_rightleg.obj");
	human[GEO_HUMAN_RLEG]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_RLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kShininess = 1.f;
}

void CHuman::InitPolice()
{
	human[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	human[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//police_texture.tga");
	human[GEO_HUMAN_BODY]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_BODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kShininess = 1.f;

	human[GEO_HUMAN_LARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_LARM]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_LARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_LHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_LHAND]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_LHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LLEG]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_LLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kShininess = 1.f;
	
	
	human[GEO_HUMAN_RARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_rightshoulder.obj");
	human[GEO_HUMAN_RARM]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_RARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_RHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_righthand.obj");
	human[GEO_HUMAN_RHAND]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_RHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_RLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_rightleg.obj");
	human[GEO_HUMAN_RLEG]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_RLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kShininess = 1.f;
}

void CHuman::InitStaff()
{
	human[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	human[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//staff_texture.tga");
	human[GEO_HUMAN_BODY]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_BODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kShininess = 1.f;

	human[GEO_HUMAN_LARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_LARM]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_LARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_LHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_LHAND]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_LHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LLEG]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_LLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LLEG]->material.kShininess = 1.f;
	
	
	human[GEO_HUMAN_RARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_rightshoulder.obj");
	human[GEO_HUMAN_RARM]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_RARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_RHAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_righthand.obj");
	human[GEO_HUMAN_RHAND]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_RHAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RHAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RHAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_RLEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_rightleg.obj");
	human[GEO_HUMAN_RLEG]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_RLEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_RLEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_RLEG]->material.kShininess = 1.f;
}

Mesh *CHuman::GetHuman(int a)
{
	return human[a];
}