/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@rit.edu)
Date: 2015/09
Notes: This is a simplified version of MeshClass
inside of ReEng.dll, its stripped out of a lot
of functionality in order to focuss on important
concepts of OpenGL, please use a MeshClass object
for better functionality.
----------------------------------------------*/
#pragma once

#include <vector>
#include <iostream>

// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "OpenGL-Tutorials\shader.hpp"

#include "GLM\glm.hpp"
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include "CollisionData.h"
class CollisionData;

struct Face {
	glm::vec3 point1;
	glm::vec3 point2;
	glm::vec3 point3;
	glm::vec3 edge1;
	glm::vec3 edge2;
	glm::vec3 edge3;
	glm::vec3 surfaceNormal;

	Face(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

private:
	Face();
};

//System Class
class MyMesh
{
	friend class Model;
protected:
	std::vector<glm::vec3> m_lVertexPos;	//List of Vertices
	std::vector<glm::vec3> m_lVertexCol;	//List of Colors

	glm::vec3 color = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 tint = glm::vec3(0.9f, 1.0f, 0.1f);

	std::vector<Face> m_faces;

public:
	/* Constructor */
	MyMesh(void);
	/* Copy Constructor */
	MyMesh(MyMesh const& other);
	/* Copy Assignment Operator*/
	MyMesh& operator=(MyMesh const& other);
	/* Destructor */
	~MyMesh(void);

	/* Swaps the contents of the object with another object's content */
	void Swap(MyMesh& other);

	/* Compiles the Mesh for OpenGL 3.X use*/
	void CompileOpenGL3X(void);

	/*Compiles the mesh and its collision data.  Final step in shape creation*/
	void CompileMesh();

	/* Returns the total number of vertices in this Mesh */
	int GetVertexTotal(void);

	/* Adds a new point to the vector of vertices */
	void AddVertexPosition(glm::vec3 a_v3Input);

	/* Adds a new color to the vector of vertices */
	void AddVertexColor(glm::vec3 a_v3Input);

	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3);

	std::vector<glm::vec3> GetVertices() { return m_lVertexPos; }

	CollisionData* m_modelCollisionData;

	std::vector<Face> GetFaces() { return m_faces; }

	bool m_bBinded = false; //Binded flag
	int m_nVertexCount = 0; //Number of Vertices in this Mesh

	bool m_compileSAT = true;

	GLuint m_vao = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)

protected:
	/* Initialize the object's fields */
	virtual void Init(void);
	/* Releases the object from memory */
	virtual void Release(void);
	/* Completes the information missing to create the mesh */
	void CompleteMesh(void);

public:
	/* Completes the triangle information */
	void CompleteTriangleInfo(void);

	void CompileCollisionData();
};