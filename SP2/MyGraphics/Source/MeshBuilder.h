/******************************************************************************/
/*!
\file	MeshBuilder.h
\author Team 8
\par	
\brief
Header file for MeshBuilder Class
*/
/******************************************************************************/
#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"
#include <vector>
#include "LoadOBJ.h"

/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color, TexCoord _texCoord);
	static Mesh* GenerateCube(const std::string &meshName, Color color);
	static Mesh* GenerateCircle(const std::string &meshName, Color color, int radius);
	static Mesh* GenerateRing(const std::string &meshName, Color color, int iRadius, int oRadius);
	static Mesh* GenerateSphere(const std::string &meshName, Color color, double radius, bool hemisphere = false);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, double radius, double height, bool hemicylinder = false);
	static Mesh* GenerateTorus(const std::string &meshName, Color color, unsigned int numStack, unsigned int numSlice, float oRadius, float iRadius);
	static Mesh* GenerateCone(const std::string &meshName, Color color, double radius, double height);
	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);
	static Mesh* GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif