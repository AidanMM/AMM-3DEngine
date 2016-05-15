#include "Model.h"

std::map<std::string, MyMesh*>* Model::s_MeshCollection = new std::map<std::string, MyMesh*>();
GLuint SHADER_TYPES::DEFAULT_LOCATION = -1;

void Model::compileShape()
{
	m_needsCompilation = false;
	if (Exists(m_modelName) != nullptr) return;

	m_model->CompileMesh();
	s_MeshCollection->insert(std::pair<std::string, MyMesh*>(m_modelName, m_model));
}

MyMesh* Model::Exists(std::string meshName)
{
	if (s_MeshCollection->find(meshName) != s_MeshCollection->end())
	{
		return s_MeshCollection->at(meshName);
	}
	else
		return nullptr;
}

Model::Model(std::string modelName, GLuint shaderType)
{
	m_modelName = modelName;
	m_color = glm::vec3(1.0f, 0.0f, 0.0f);
	
	if (Exists(modelName) == nullptr)
	{
		m_model = new MyMesh();
		
		m_needsCompilation = true;
	}
	else
	{
		m_model = s_MeshCollection->at(modelName);
		m_needsCompilation = false;
	}
	
	//Compile Color shader
	switch (m_shaderType)
	{
	default:
		if (SHADER_TYPES::DEFAULT_LOCATION == -1)
		{
			SHADER_TYPES::DEFAULT_LOCATION = LoadShaders("shaders\\Color.vs", "shaders\\Color.fs");
		}
		m_shaderProgram = SHADER_TYPES::DEFAULT_LOCATION;
		break;
	}

}

void Model::Render(glm::mat4 toWorld, glm::mat4 view, glm::mat4 persp)
{
	if (m_needsCompilation) {
		compileShape();
	}
	
	if (!m_model->m_bBinded)
		return;

	if (m_model->m_nVertexCount == 0)
		return;

	// Use the buffer and shader
	glUseProgram(m_shaderProgram);

	// Get the GPU variables by their name and hook them to CPU variables
	GLuint MVP = glGetUniformLocation(m_shaderProgram, "MVP");
	GLuint v4Position = glGetAttribLocation(m_shaderProgram, "Position_b");
	GLuint v3Color = glGetUniformLocation(m_shaderProgram, "Color");
	GLuint v3Tint = glGetUniformLocation(m_shaderProgram, "Tint");
	//GLuint v4Color = glGetAttribLocation(m_nShaderProgram, "Color_b");

	//Final Projection of the Camera is going to be hard coded
	glm::mat4 m4Projection = persp;
	glm::mat4 m4View = view;
	glUniformMatrix4fv(MVP, 1, GL_FALSE, glm::value_ptr(m4Projection * m4View * toWorld));

	//position
	glEnableVertexAttribArray(v4Position);
	glBindBuffer(GL_ARRAY_BUFFER, m_model->m_VertexBuffer);
	glVertexAttribPointer(v4Position, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//Color & tint
	float c[3] = { m_color.x, m_color.y, m_color.z };
	glUniform3fv(v3Color, 1, c);
	glUniform3fv(v3Tint, 1, c);
	/*glEnableVertexAttribArray(v4Color);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glVertexAttribPointer(v4Color, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);*/

	//Color and draw
	glDrawArrays(GL_TRIANGLES, 0, m_model->m_nVertexCount);

	glDisableVertexAttribArray(v4Position);
	//glDisableVertexAttribArray(v4Color);
}

void Model::AddVertex(glm::vec3 position)
{
	m_model->AddVertexPosition(position);
	m_needsCompilation = true;
}

void Model::AddVertex(glm::vec3 position, glm::vec3 color)
{
	AddVertex(position);
	m_model->AddVertexColor(color);
}

void Model::AddColor(glm::vec3 color)
{
	m_model->AddVertexColor(color);
	m_needsCompilation = true;
}

void Model::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3)
{
	m_model->AddTri(point1,point2,point3,color1,color2,color3);
	m_needsCompilation = true;
}

void Model::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color)
{
	AddTri(point1, point2, point3, color, color, color);
}

void Model::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	AddTri(point1, point2, point3, m_color, m_color, m_color);
}

void Model::AddQuad(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 point4)
{
	AddTri(point1, point2, point3);
	AddTri(point4, point3, point2);
}

void Model::GenCube(float size, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	GenBox(size, size, size, front, left, right, bottom, top, back);
}

void Model::GenCube(float size, glm::vec3 color)
{
	GenCube(size, color, color, color, color, color, color);
}

void Model::GenCube(float size)
{
	GenCube(size, m_color);
}

void Model::GenBox(std::vector<glm::vec3> points, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	if (m_needsCompilation == false)
		return;
	if (points.size() < 8)
	{
		return;
	}
	
	//Front
	AddTri(points[1], points[3], points[0], front);
	AddTri(points[2], points[3], points[1], front);

	//Left
	AddTri(points[0], points[3], points[7], left);
	AddTri(points[4], points[0], points[7], left);

	//Right
	AddTri(points[1], points[5], points[6], right);
	AddTri(points[6], points[2], points[1], right);

	//Bottom
	AddTri(points[0], points[4], points[5], bottom);
	AddTri(points[5], points[1], points[0], bottom);

	//Top
	AddTri(points[2], points[6], points[7], top);
	AddTri(points[3], points[2], points[7], top);

	//Back
	AddTri(points[6], points[7], points[4], back);
	AddTri(points[5], points[6], points[4], back);

	compileShape();
}

void Model::GenBox(std::vector<glm::vec3> points, glm::vec3 color)
{
	GenBox(points, color, glm::vec3(0.0f,1.0f,0.0f), color, color ,color, color);
}

void Model::GenBox(std::vector<glm::vec3> points)
{
	GenBox(points, m_color);
}

void Model::GenBox(float width, float height, float length, glm::vec3 front, glm::vec3 left, glm::vec3 right, glm::vec3 bottom, glm::vec3 top, glm::vec3 back)
{
	//Create the eight points that will map out to the cube
	//remember counterclockwise to the tri is where the face will be visible

	width *= .5f;
	height *= .5f;
	length *= .5f;

	std::vector<glm::vec3> points(8, glm::vec3(0.0f));

	//Top points
	points[0] = glm::vec3(-width, -height, length);
	points[1] = glm::vec3(width, -height, length);
	points[2] = glm::vec3(width, height, length);
	points[3] = glm::vec3(-width, height, length);

	//Bottom points
	points[4] = glm::vec3(-width, -height, -length);
	points[5] = glm::vec3(width, -height, -length);
	points[6] = glm::vec3(width, height, -length);
	points[7] = glm::vec3(-width, height, -length);

	GenBox(points, front, left, right, bottom, top, back);
}

void Model::GenBox(float width, float height, float length, glm::vec3 color)
{
	GenBox(width, height, length, color, color, color, color, color, color);
}

void Model::GenBox(float width, float height, float length)
{
	GenBox(width, height, length, m_color);
}

void Model::GenSphere(float radius, int subdivisions)
{
	if (m_needsCompilation == false)
		return;
	//Sets minimum and maximum of subdivisions
	if (subdivisions < 1)
	{
		GenCube(radius * 2);
		return;
	}

	float value = 1.0f;
	glm::vec3 pointA(-value, -value, value); //0
	glm::vec3 pointB(value, -value, value); //1
	glm::vec3 pointC(-value, value, value); //2

	//left to right List of vector3
	std::vector<glm::vec3> vectorAB;
	vectorAB.push_back(pointA);
	for (int i = 0; i < subdivisions; i++)
	{
		glm::vec3 temp(pointB - pointA);
		temp /= subdivisions + 1;
		temp *= (i + 1);
		vectorAB.push_back(temp + pointA);
	}
	vectorAB.push_back(pointB);

	//height increments
	float fHeight = pointC.y - pointA.y;
	fHeight /= subdivisions + 1;

	//List of Lists
	std::vector<std::vector<glm::vec3>> list;
	list.push_back(vectorAB);
	for (int j = 0; j < subdivisions + 1; j++)
	{
		std::vector<glm::vec3> temp = list[0];
		float increment = fHeight * (j + 1);
		for (int i = 0; i < subdivisions + 2; i++)
		{
			temp[i].y += increment;
		}
		list.push_back(temp);
	}

	//Creating the patch of quads
	for (int j = 0; j < subdivisions + 1; j++)
	{
		for (int i = 0; i < subdivisions + 1; i++)
		{
			AddQuad(list[j][i], list[j][i + 1], list[j + 1][i], list[j + 1][i + 1]);
		}
	}

	//normalizing the vectors to make them round
	for (int i = 0; i < m_model->GetVertexTotal(); i++)
	{
		m_model->m_lVertexPos[i] = glm::normalize(m_model->GetVertices()[i]);
		m_model->m_lVertexPos[i] *= radius;
	}

	//RightSideFace
	int nVert = m_model->GetVertexTotal();
	std::vector<glm::vec3> right;
	for (int i = 0; i < nVert; i++)
	{
		glm::mat4 rotation;
		rotation = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		right.push_back(static_cast <glm::vec3> (rotation * glm::vec4(m_model->m_lVertexPos[i], 1.0f)));
	}


	for (int i = 0; i < nVert; i++)
	{
		AddVertex(right[i]);
	}

	//LeftSideFace
	std::vector<glm::vec3> left;
	for (int i = 0; i < nVert; i++)
	{
		glm::mat4 rotation;
		rotation = glm::rotate(glm::mat4(1.0f), -90.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		left.push_back(static_cast <glm::vec3>(rotation * glm::vec4(m_model->m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertex(left[i]);
	}

	//BackSideFace
	std::vector<glm::vec3> back;
	for (int i = 0; i < nVert; i++)
	{
		glm::mat4 rotation;
		rotation = glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
		back.push_back(static_cast <glm::vec3>(rotation * glm::vec4(m_model->m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertex(back[i]);
	}

	//TopSideFace
	std::vector<glm::vec3> top;
	for (int i = 0; i < nVert; i++)
	{
		glm::mat4 rotation;
		rotation = glm::rotate(glm::mat4(1.0f), -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		top.push_back(static_cast <glm::vec3>(rotation * glm::vec4(m_model->m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertex(top[i]);
	}

	//BottomSideFace
	std::vector<glm::vec3> bottom;
	for (int i = 0; i < nVert; i++)
	{
		glm::mat4 rotation;
		rotation = glm::rotate(glm::mat4(1.0f), 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		bottom.push_back(static_cast <glm::vec3>(rotation * glm::vec4(m_model->m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertex(bottom[i]);
	}

	compileShape();
}

void Model::AssignModel(Model * model)
{
	m_model = model->GetMesh();
}

std::vector<glm::vec3> Model::GetVertices()
{
	return m_model->GetVertices();
}

MyMesh * Model::GetMesh()
{
	return m_model;
}
