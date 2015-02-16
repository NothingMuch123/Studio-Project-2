#ifndef _ASSIGNMENT03_H_
#define _ASSIGNMENT03_H_

#include "Scene.h"
#include "Camera.h"
#include "Camera2.h"
#include "Camera3.h"
#include "MeshBuilder.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "Obj.h"

class Assignment03 : public Scene
{
	enum GEOMETRY_TYPE
	{
		// Shapes
		GEO_AXES,
		GEO_LIGHTBALL,
		GEO_LIGHTBALL2,

		// Model
		// Stan
		GEO_HEAD,
		GEO_EYES,
		GEO_EYEBALL,
		GEO_MOUTH,

		GEO_HELMET,
		GEO_HELMETTORUS,
		GEO_HELMETTOP,
		GEO_HELMETBORDER_H,
		GEO_HELMETBORDER_V,
		GEO_HELMETDIAMOND,
		GEO_HELMETSPHERE,

		GEO_BODY,
		GEO_BELT,
		GEO_BELT2,
		GEO_BELTBUCKLE,
		GEO_BELTSPHERE,
		GEO_BELTSTRIP,

		GEO_ARM,
		GEO_BAND,
		GEO_FIST,

		GEO_MODELBOTTOM,
		GEO_LEGS,
		GEO_FEET,

		// Item
		GEO_HANDLE,
		GEO_MIDDLE,
		GEO_BLADE,
		GEO_TIP,

		// Skybox
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_TEXT,

		GEO_WALL,		// Maze wall
		GEO_MONSTER,	// Monster
		GEO_CHEST,		// Chest
		GEO_TROPHY,		// Trophy

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
	Assignment03();
	~Assignment03();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	unsigned m_vertexArrayID;
	Mesh *meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	Camera3 camera;
	MS modelStack, viewStack, projectionStack;
	Light lights[2];

	std::vector<CObj*> objList;
	CObj *pObj;
	float skyboxOffset, monsterMaxJump, monsterMinJump, tiltUpDown, lightHeight;
	Vector3 SkyBoxBoundMax, SkyBoxBoundMin, skyboxSize;
	Vector3 modelPosition, modelTarget, modelUp, modelView;
	double fps;
	bool togglelight, togglecamera;
	bool startText, endText;
	Vector3 startMaxBound, startMinBound, endMaxBound, endMinBound;

	bool boundCheck(Vector3 BoundMax, Vector3 BoundMin);
	bool skyboxCheck();
	void InitMap();
	void InitSkybox();
	void RenderSkybox();
	void InitObj(Mesh* _obj, float _translateX, float _translateY, float _translateZ, float _rotateX, float _rotateY, float _rotateZ, float _scaleX, float _scaleY, float _scaleZ, int _shape);
	void RenderObj(CObj *_obj);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	// Model
	// Animation variables
	float bodyTranslateY;
	float bodyTranslateX;
	float bodyRotateAngleX;
	float bodyRotateAngleY;
	bool move;

	void charInit();
	void charUpdate(double dt);

	// Stan
	void RenderStan(); // Main function
	void RenderHelmet();
	void RenderHead();
	void RenderBody();
	void RenderArms(bool Left_OR_Right); // False = Right arm | True = Left arm
	void RenderLegs();

	// Item
	void RenderSword(); // Main function
	void RenderHandle();
	void RenderBlade();
};

#endif