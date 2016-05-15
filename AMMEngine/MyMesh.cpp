#include "MyMesh.h"

//  MyMesh
void MyMesh::Init(void)
{
	m_bBinded = false;
	m_nVertexCount = 0;

	m_vao = 0;
	m_VertexBuffer = 0;
	m_ColorBuffer = 0;

	m_modelCollisionData = new CollisionData;
}
void MyMesh::Swap(MyMesh& other)
{
	std::swap(m_bBinded, other.m_bBinded);
	std::swap(m_nVertexCount, other.m_nVertexCount);

	std::swap(m_vao, other.m_vao);
	std::swap(m_VertexBuffer, other.m_VertexBuffer);
	std::swap(m_ColorBuffer, other.m_ColorBuffer);

	std::swap(m_lVertexPos, other.m_lVertexPos);
	std::swap(m_lVertexCol, other.m_lVertexCol);
}
void MyMesh::Release(void)
{
	if (m_ColorBuffer > 0)
		glDeleteBuffers(1, &m_ColorBuffer);

	if (m_VertexBuffer > 0)
		glDeleteBuffers(1, &m_VertexBuffer);

	if (m_vao > 0)
		glDeleteVertexArrays(1, &m_vao);

	m_lVertexPos.clear();
	m_lVertexCol.clear();
}
//The big 3
MyMesh::MyMesh(){ Init(); }
MyMesh::MyMesh(MyMesh const& other)
{
	m_bBinded = other.m_bBinded;
	m_nVertexCount = other.m_nVertexCount;

	m_vao = other.m_vao;
	m_VertexBuffer = other.m_VertexBuffer;
	m_ColorBuffer = other.m_ColorBuffer;

	m_lVertexPos = other.m_lVertexPos;
	m_lVertexCol = other.m_lVertexCol;
}
MyMesh& MyMesh::operator=(MyMesh const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		MyMesh temp(other);
		Swap(temp);
	}
	return *this;
}
MyMesh::~MyMesh(){ Release(); };
//Accessors
int MyMesh::GetVertexTotal(void){ return m_nVertexCount; }
void MyMesh::AddVertexPosition(glm::vec3 input){ m_lVertexPos.push_back(input); m_nVertexCount++; }
void MyMesh::AddVertexColor(glm::vec3 input){ m_lVertexCol.push_back(input); }
//Methods
void MyMesh::CompleteMesh(void)
{
	int nColorTotal = static_cast<int>(m_lVertexCol.size());
	for (int nColor = nColorTotal; nColor < m_nVertexCount; nColor++)
		m_lVertexCol.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
}
void MyMesh::CompileCollisionData()
{
	//Remove doubled points in the vertex list
	for (int i = 0; i < m_lVertexPos.size(); i++)
	{
		glm::vec3 a = m_lVertexPos[i];
		for (int k = 0; k < m_lVertexPos.size(); k++)
		{
			glm::vec3 b = m_lVertexPos[k];
			if (i != k && a == b)
			{
				m_lVertexPos.erase(m_lVertexPos.begin() + k);
				k--;
			}
		}
	}
	m_lVertexPos.resize(m_lVertexPos.size());
	if (m_compileSAT)
		return;
	//Remove interior edges
	for (int i = 0; i < m_modelCollisionData->m_SATRemovalEdges.size(); i++)
	{
		m_modelCollisionData->m_SATRemovalEdges[i] = glm::normalize(m_modelCollisionData->m_SATRemovalEdges[i]);
		for (int k = 0; k < m_modelCollisionData->m_SATEdges.size(); k++)
		{
			if (i != k)
			{
				if (glm::abs(m_modelCollisionData->m_SATRemovalEdges[i]) == glm::abs(m_modelCollisionData->m_SATEdges[k]))
				{
					m_modelCollisionData->m_SATEdges.erase(m_modelCollisionData->m_SATEdges.begin() + k);
					k--;
				}
			}
		}
	}
	//Remove double and superflous edges in the SATEdges list
	for (int i = 0; i < m_modelCollisionData->m_SATEdges.size(); i++)
	{
		glm::vec3 a = m_modelCollisionData->m_SATEdges[i];
		for (int k = 0; k < m_modelCollisionData->m_SATEdges.size(); k++)
		{
			glm::vec3 b = m_modelCollisionData->m_SATEdges[k];
			float dot = abs(glm::dot(a, b));
			if (i != k)
			{
				if (glm::abs(a) == glm::abs(b))
				{
					m_modelCollisionData->m_SATEdges.erase(m_modelCollisionData->m_SATEdges.begin() + k);
					k--;
				}
			}
		}
	}
	//Now loop through and reslolve the surface normals
	for (int i = 0; i < m_modelCollisionData->m_SATNormals.size(); i++)
	{
		glm::vec3 a = m_modelCollisionData->m_SATNormals[i];
		for (int k = 0; k < m_modelCollisionData->m_SATNormals.size(); k++)
		{
			glm::vec3 b = m_modelCollisionData->m_SATNormals[k];
			float dot = abs(glm::dot(a, b));
			if (i != k)
			{
				if (glm::abs(a) == glm::abs(b))
				{
					m_modelCollisionData->m_SATNormals.erase(m_modelCollisionData->m_SATNormals.begin() + k);
					k--;
				}
			}
		}
	}
	m_modelCollisionData->m_SATNormals.resize(m_modelCollisionData->m_SATNormals.size());
	m_modelCollisionData->m_SATRemovalEdges.resize(m_modelCollisionData->m_SATRemovalEdges.size());
}
void MyMesh::CompileOpenGL3X(void)
{
	if (m_bBinded)
		return;

	if (m_nVertexCount == 0)
		return;

	CompleteMesh();

	// Create a vertex array object
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	// Create and initialize a buffer object for each shape.
	glGenBuffers(1, &m_VertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nVertexCount * sizeof(glm::vec3), &m_lVertexPos[0], GL_STATIC_DRAW);

	//Initialize the color buffer for the object.
	glGenBuffers(1, &m_ColorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_ColorBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_nVertexCount * sizeof(glm::vec3), &m_lVertexCol[0], GL_STATIC_DRAW);

	m_bBinded = true;

	return;
}
void MyMesh::CompileMesh()
{
	CompileOpenGL3X();
	CompileCollisionData();
}

void MyMesh::AddTri(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3, glm::vec3 color1, glm::vec3 color2, glm::vec3 color3)
{
	AddVertexPosition(point1);
	AddVertexPosition(point2);
	AddVertexPosition(point3);

	AddVertexColor(color1);
	AddVertexColor(color2);
	AddVertexColor(color3);
	Face f = Face(point1, point2, point3);
	m_faces.push_back(f);
	if (!m_compileSAT)
		return;
	for (int i = 0; i < m_faces.size(); i++)
	{
		if (f.surfaceNormal == m_faces[i].surfaceNormal)
		{
			Face other = m_faces[i];
			if (f.point1 == other.point1)
			{
				if (f.point2 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point3 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
			}
			else if (f.point1 == other.point2)
			{
				if (f.point2 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point3 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
			}
			else if (f.point1 == other.point3)
			{
				if (f.point2 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point1);
				if (f.point3 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point1);
			}

			if (f.point2 == other.point1)
			{
				if (f.point1 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point3 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
			}
			else if (f.point2 == other.point2)
			{
				if (f.point1 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point3 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
			}
			else if (f.point2 == other.point3)
			{
				if (f.point1 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point2);
				if (f.point3 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
				if (f.point3 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point3 - f.point2);
			}

			if (f.point3 == other.point1)
			{
				if (f.point2 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point1 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
			}
			else if (f.point3 == other.point2)
			{
				if (f.point2 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point1 == other.point1) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
			}
			else if (f.point3 == other.point3)
			{
				if (f.point2 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point2 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point2 - f.point3);
				if (f.point1 == other.point2) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
				if (f.point1 == other.point3) m_modelCollisionData->m_SATRemovalEdges.push_back(f.point1 - f.point3);
			}
		}
	}
	m_modelCollisionData->m_SATEdges.push_back(glm::normalize(f.edge1));
	m_modelCollisionData->m_SATEdges.push_back(glm::normalize(f.edge2));
	m_modelCollisionData->m_SATEdges.push_back(glm::normalize(f.edge3));
	m_modelCollisionData->m_SATNormals.push_back(f.surfaceNormal);
}

Face::Face(glm::vec3 point1, glm::vec3 point2, glm::vec3 point3)
{
	this->point1 = point1;
	this->point2 = point2;
	this->point3 = point3;
	this->edge1 = point2 - point1;
	this->edge2 = point3 - point2;
	this->edge3 = point1 - point3;
	surfaceNormal = glm::cross(point2 - point1, point3 - point1);
	if(glm::length(surfaceNormal) > 0)
		surfaceNormal = glm::normalize(surfaceNormal);
}
