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

	human[GEO_HUMAN_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_ARM]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_ARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_ARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_HAND]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_HAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_HAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LEG]->textureID = LoadTGA ("Image//shopper_texture.tga");
	human[GEO_HUMAN_LEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kShininess = 1.f;
}

void CHuman::InitPolice()
{
	human[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	human[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//police_texture.tga");
	human[GEO_HUMAN_BODY]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_BODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kShininess = 1.f;

	human[GEO_HUMAN_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_ARM]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_ARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_ARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_HAND]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_HAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_HAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LEG]->textureID = LoadTGA ("Image//police_texture.tga");
	human[GEO_HUMAN_LEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kShininess = 1.f;
}

void CHuman::InitStaff()
{
	human[GEO_HUMAN_BODY] = MeshBuilder::GenerateOBJ( "body" , "OBJ//humanModel_bodyNhead.obj");
	human[GEO_HUMAN_BODY]->textureID = LoadTGA("Image//staff_texture.tga");
	human[GEO_HUMAN_BODY]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_BODY]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_BODY]->material.kShininess = 1.f;

	human[GEO_HUMAN_ARM] = MeshBuilder::GenerateOBJ( "l_arm" , "OBJ//humanModel_leftshoulder.obj");
	human[GEO_HUMAN_ARM]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_ARM]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_ARM]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_ARM]->material.kShininess = 1.f;

	human[GEO_HUMAN_HAND] = MeshBuilder::GenerateOBJ ( "l_hand" , "OBJ//humanModel_lefthand.obj");
	human[GEO_HUMAN_HAND]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_HAND]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_HAND]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_HAND]->material.kShininess = 1.f;

	human[GEO_HUMAN_LEG] = MeshBuilder::GenerateOBJ( "l_leg" , "OBJ//humanModel_leftleg.obj");
	human[GEO_HUMAN_LEG]->textureID = LoadTGA ("Image//staff_texture.tga");
	human[GEO_HUMAN_LEG]->material.kAmbient.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kDiffuse.Set(0.2f, 0.2f, 0.2f);
	human[GEO_HUMAN_LEG]->material.kSpecular.Set(1.f, 1.f, 1.f);
	human[GEO_HUMAN_LEG]->material.kShininess = 1.f;
}

Mesh *CHuman::GetHuman(int a)
{
	return human[a];
}