#include "MeshBuilder.h"
#include <GL\glew.h>

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-1000, 0, 0);			// 1
	v.color = Color(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0);			// 2
	v.color = Color(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0);			// 3
	v.color = Color(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0);			// 4
	v.color = Color(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000);			// 5
	v.color = Color(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000);			// 6
	v.color = Color(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	for (int i = 0; i < 6; i++)
	{
		index_buffer_data.push_back(i);
	}
	
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, TexCoord _texCoord)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	v.pos.Set(-0.5, -0.5, 0);		// 1
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5, -0.5, 0);		// 2
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(_texCoord.u, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5, 0.5, 0);			// 3
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(_texCoord.u, _texCoord.v);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5, 0.5, 0);		// 4
	v.color = color;
	v.normal.Set(0, 0, 1);
	v.texCoord.Set(0, _texCoord.v);
	vertex_buffer_data.push_back(v);

	index_buffer_data.push_back(0);	// 1
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);	// 2
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color)
{
	// An array of 3 vectors which represents 3 vertices
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	
	v.pos.Set(-0.5f, 0.5f, 0.5f);		// 8
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		// 5
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);		// 7
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);		// 6
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, 0.5f);		// 7
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, 0.5f);		// 5
	v.color = color;
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(0.5f, 0.5f, 0.5f);		// 7
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		// 6
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		// 3
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(0.5f, -0.5f, -0.5f);		// 2
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		// 3
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		// 6
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, -0.5f);		// 4
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		// 8
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		// 3
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(0.5f, 0.5f, 0.5f);		// 7
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, 0.5f, -0.5f);		// 3
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		// 8
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(0.5f, 0.5f, -0.5f);		// 3
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		// 2
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);		// 4
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, -0.5f);		// 1
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, -0.5f);		// 4
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, -0.5f);		// 2
	v.color = color;
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(-0.5f, 0.5f, -0.5f);		// 4
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		// 1
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		// 8
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(-0.5f, -0.5f, 0.5f);		// 5
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, 0.5f, 0.5f);		// 8
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		// 1
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(0.5f, -0.5f, -0.5f);		// 2
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		// 6
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		// 1
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	
	v.pos.Set(-0.5f, -0.5f, 0.5f);		// 5
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(-0.5f, -0.5f, -0.5f);		// 1
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0.5f, -0.5f, 0.5f);		// 6
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, int radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for (float theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, int iRadius, int oRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for (float theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(oRadius * cos(Math::DegreeToRadian(theta)), 0, oRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(iRadius * cos(Math::DegreeToRadian(theta)), 0, iRadius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, double radius, bool hemisphere)
{
	float phi;
	if (hemisphere == true)
	{
		phi = 0;
	}
	else
	{
		phi = -90;
	}
	
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for (; phi < 90; phi +=10)
	{
		for (float theta = 0; theta <= 360; theta += 10)
		{
			v.pos.Set(radius * (cos(Math::DegreeToRadian(phi))) * (cos(Math::DegreeToRadian(theta))), radius * (sin(Math::DegreeToRadian(phi))), radius * (cos(Math::DegreeToRadian(phi))) * (sin(Math::DegreeToRadian(theta))));
			v.color = color;
			v.normal.Set(radius * (cos(Math::DegreeToRadian(phi))) * (cos(Math::DegreeToRadian(theta))), radius * (sin(Math::DegreeToRadian(phi))), radius * (cos(Math::DegreeToRadian(phi))) * (sin(Math::DegreeToRadian(theta))));
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * (cos(Math::DegreeToRadian(phi + 10))) * (cos(Math::DegreeToRadian(theta))), radius * (sin(Math::DegreeToRadian(phi + 10))), radius * (cos(Math::DegreeToRadian(phi + 10))) * (sin(Math::DegreeToRadian(theta))));
			v.color = color;
			v.normal.Set(radius * (cos(Math::DegreeToRadian(phi + 10))) * (cos(Math::DegreeToRadian(theta))), radius * (sin(Math::DegreeToRadian(phi + 10))), radius * (cos(Math::DegreeToRadian(phi + 10))) * (sin(Math::DegreeToRadian(theta))));
			vertex_buffer_data.push_back(v);
		}
	}
	
	if (hemisphere == true) // Creates the base for hemisphere
	{
		for (float theta = 0; theta <= 360; theta += 10)
		{
			v.pos.Set(0, 0, 0);
			v.color = color;
			vertex_buffer_data.push_back(v);

			v.pos.Set(radius * (cos(Math::DegreeToRadian(theta))), 0, radius * (sin(Math::DegreeToRadian(theta))));
			v.color = color;
			vertex_buffer_data.push_back(v);
		}
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, double radius, double height, bool hemicylinder)
{
	float degree;
	if (hemicylinder == false)
	{
		degree = 360;
	}
	else
	{
		degree = 180;
	}
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for (float theta = 0; theta <= degree; theta += 10)
	{
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), (-height / 2) + height, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(radius * cos(Math::DegreeToRadian(theta)), (-height / 2) + height, radius * sin(Math::DegreeToRadian(theta)));
		vertex_buffer_data.push_back(v);
	}

	for (float theta = 0; theta <= degree; theta += 10) // Top
	{
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(0, height / 2, 0);
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}
	for (float theta = 0; theta <= degree; theta += 10) // Bottom
	{
		v.pos.Set(0, -height / 2, 0);
		v.color = color;
		v.normal.Set(0, -1, 0);
		vertex_buffer_data.push_back(v);

		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), -height / 2, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a torus; Use color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - color of mesh
\param numStack - number of stacks for torus
\param numSlice - number of slices for torus
\param iRadius - Inner radius of torus
\param oRadius - Outer radius of torus
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateTorus(const std::string &meshName, Color color, unsigned int numStack, unsigned int numSlice, float oRadius, float iRadius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerStack = 360.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;
	float x1, z1; // y1 is always zero
	float x2, y2, z2;

	for(unsigned int stack = 0; stack < numStack + 1; stack++)
	{
		for (unsigned int slice = 0; slice < numSlice + 1; slice++)
		{
			z1 = oRadius * cos(Math::DegreeToRadian(stack * degreePerStack));
			x1 = oRadius * sin(Math::DegreeToRadian(stack * degreePerStack));
			z2 = (oRadius + iRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * cos(Math::DegreeToRadian(stack * degreePerStack));
			y2 = iRadius * sin(Math::DegreeToRadian(slice * degreePerStack));
			x2 = (oRadius + iRadius * cos(Math::DegreeToRadian(slice * degreePerSlice))) * sin(Math::DegreeToRadian(stack * degreePerStack));
			v.pos.Set(x2, y2, z2);
			v.color = color;
			v.normal.Set(x2 - x1, y2, z2 - z1);
			v.normal.Normalize();
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned int stack = 0; stack < numStack; stack++)
	{
		for (unsigned slice = 0; slice < numSlice + 1; slice++)
		{
			index_buffer_data.push_back((numSlice + 1) * stack + slice + 0);
			index_buffer_data.push_back((numSlice + 1) * (stack + 1) + slice + 0);
		}
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cone; Use color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - color of mesh
\param radius - radius of cone
\param height - height of cone
\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, double radius, double height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	for(int theta = 0; theta <= 360; theta += 10)
	{
		v.pos.Set(radius *cos(Math::DegreeToRadian(theta)), -height /2, radius *sin(Math::DegreeToRadian(theta)));
		v.color=color;
		v.normal.Set(height *cos(Math::DegreeToRadian(theta)), radius, height *sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);

		v.pos.Set(0,height/2,0);
		v.color=color;
		v.normal.Set(height *cos(Math::DegreeToRadian(theta)), radius, height *sin(Math::DegreeToRadian(theta)));
		v.normal.Normalize();
		vertex_buffer_data.push_back(v);
	}

	for (int i = 0; i < vertex_buffer_data.size(); i++)
	{
		index_buffer_data.push_back(i);
	}

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path)
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);
	//Create the mesh and call glBindBuffer, glBufferData
	//Use triangle list and remember to set index size

	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	float offset = 0;
	for(unsigned i = 0; i < numRow; ++i)
	{
		for(unsigned j = 0; j < numCol; ++j)
		{
			//Task: Add 4 vertices into vertex_buffer_data
			v.pos.Set(-0.5, -0.5, 0);		// 1
			v.texCoord.Set(j * width, 1.f - height - i * height);
			vertex_buffer_data.push_back(v);
			v.pos.Set(0.5, -0.5, 0);		// 2
			v.texCoord.Set(j * width + width, 1.f - height - i * height);
			vertex_buffer_data.push_back(v);
			v.pos.Set(0.5, 0.5, 0);			// 3
			v.texCoord.Set(j * width + width, 1.f - height - i * height + height);
			vertex_buffer_data.push_back(v);
			v.pos.Set(-0.5, 0.5, 0);		// 4
			v.texCoord.Set(j * width, 1.f - height - i * height + height);
			vertex_buffer_data.push_back(v);

			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(offset + 0);	// 1
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 3);
			index_buffer_data.push_back(offset + 1);	// 2
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);

			offset += 4;
		}
	}


	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer); // Bind index buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}