#pragma once
#include <map>

#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "OpenGL-Tutorials\shader.hpp"

#include "MyMesh.h"
class MyMesh;

static struct SHADER_TYPES {
	static const GLuint DEFAULT = 0;
	static const GLuint PHONG = 1;

	static GLuint DEFAULT_LOCATION;
};

class Model{
private:
	bool m_needsCompilation = true;

	static std::map<std::string, MyMesh*>* s_MeshCollection;
	std::string m_modelName;
	MyMesh* m_model = nullptr;

	MyMesh* Exists(std::string meshName);

	GLuint m_shaderType;
	GLuint m_shaderProgram;

public:
	Model() : Model("Default Cube", SHADER_TYPES::DEFAULT) {};
	Model(std::string modelName) : Model(modelName, SHADER_TYPES::DEFAULT) {};
	Model(std::string modelName, GLuint shaderType);

	//<summary>
	//When color is unspecied, defaultColor is used. default is set to red when unset.
	//</summary>
	glm::vec3 m_color; 

	void compileShape();

	void Render(glm::mat4 toWorld, glm::mat4 view, glm::mat4 persp);

	void AddVertex(glm::vec3 position);
	void AddVertex(glm::vec3 position, glm::vec3 color);

	void AddColor(glm::vec3 color);

	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3);
	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color);
	void AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3);

	void AddQuad(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4);

	//Creates a cube with the designated colors for the faces
	void GenCube(float size, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenCube(float size, glm::vec3 color);
	void GenCube(float size);

	//Creates a box with the designated colors for the faces
	void GenBox(std::vector<glm::vec3> points, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenBox(std::vector<glm::vec3> points, glm::vec3 color);
	void GenBox(std::vector<glm::vec3> points);
	void GenBox(float width, float length, float height, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back);
	void GenBox(float width, float length, float height, glm::vec3 color);
	void GenBox(float width, float length, float height);

	void GenSphere(float radius, int subdivisions);

	void AssignModel(Model* model);

	std::vector<glm::vec3> GetVertices();

	MyMesh* GetMesh();
};