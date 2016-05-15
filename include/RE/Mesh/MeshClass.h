/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHCLASS_H_
#define __MESHCLASS_H_

#include "RE\System\SystemSingleton.h"
#include "RE\System\ShaderManagerSingleton.h"
#include "RE\Materials\MaterialManagerSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL MeshClass
{
protected:

	bool m_bCopy = false;	//Checks to see if this Mesh is a copy or the original
	bool m_bWire = false;	//Checks to see if the Mesh is going to be drawn in wires
	bool m_bBinded = false; //Binded flag

	uint m_uMaterialIndex = 0; //Material index of this mesh
	uint m_uVertexCount = 0; //Number of vertices in this Mesh

	GLuint m_VAO = 0;			//OpenGL Vertex Array Object
	GLuint m_VBO = 0;			//OpenGL Vertex Array Object
	GLuint m_VertexBuffer = 0;	//OpenGL Buffer (Will hold the vertex buffer pointer)
	GLuint m_ColorBuffer = 0;	//OpenGL Buffer (Will hold the color buffer pointer)
	GLuint m_UVBuffer = 0;		//OpenGL Buffer (Will hold the UV buffer pointer)
	GLuint m_NormalBuffer = 0;	//OpenGL Buffer (will hold the Normal Buffer)
	GLuint m_TangentBuffer = 0;	//OpenGL Buffer (will hold the Tangent Buffer)
	GLuint m_BinormalBuffer = 0;//OpenGL Buffer (will hold the Binormal Buffer)

	GLuint m_nShader = 0;	//Index of the shader
	GLuint m_nShaderO = 0;	//Index of the original shader

	ShaderManagerSingleton* m_pShaderMngr = nullptr;	//Shader Manager
	MaterialManagerSingleton* m_pMatMngr = nullptr;		//Material Manager

	String m_sName = "NULL";	//Identifier of the Mesh
	vector3 m_v3Tint; //Color modifier

	std::vector<vector3> m_lVertex; //Composed vertex array
	std::vector<vector3> m_lVertexPos;	//List of Vertices
	std::vector<vector3> m_lVertexCol;	//List of Colors
	std::vector<vector3> m_lVertexNor;	//List of Normals
	std::vector<vector3> m_lVertexTan;	//List of Tangents
	std::vector<vector3> m_lVertexBin;	//List of Binormals
	std::vector<vector3> m_lVertexUV;	//List of UVS
	
public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	MeshClass(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object (to copy)
	OUTPUT: class object
	*/
	MeshClass(MeshClass const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object (to copy)
	OUTPUT: class object
	*/
	MeshClass& operator=(MeshClass const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshClass(void);
	/*
	USAGE: Swaps the contents of the object with another object's content
	ARGUMENTS: class object  (to swap with)
	OUTPUT: ---
	*/
	void Swap(MeshClass& other);
	/*
	USAGE: Compiles the Mesh for OpenGL 3.X use
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);
	/*
	USAGE: Asks the Mesh if it has been binded
	ARGUMENTS: ---
	OUTPUT: Whether its being binded or not
	*/
	bool GetBinded(void);
	/*
	USAGE: Set the shader to the newly loaded shader
	ARGUMENTS:
	- String a_sVertexShaderName -> file name
	- String a_sFragmentShaderName -> file name
	- String a_sShaderName -> name of the shader
	- vector3 a_v3Tint = REDEFAULT -> tint color
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the shader of the Shape to a loaded shader
	ARGUMENTS:
	- String a_sShaderName = "Original" -> Name of the previously loaded shader
	- vector3 a_v3Tint = REDEFAULT -> color tint
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the material of the shape by name
	ARGUMENTS:
	- String a_sMaterialName -> Name of the previously loaded material
	OUTPUT: ---
	*/
	void SetMaterial(String a_sMaterialName);
	/*
	USAGE: Returns the total number of vertices in this Mesh
	ARGUMENTS: ---
	OUTPUT: Number of vertices
	*/
	int GetVertexCount(void);
	/*
	USAGE: Sets the material index by index in the material manager
	ARGUMENTS:
	- int a_nIndex -> index of the previously loaded material
	OUTPUT: ---
	*/
	void SetMaterialIndex(int a_nIndex);
	/*
	USAGE: Gets the material used in the shape by index of the material manager
	ARGUMENTS: ---
	OUTPUT: index of the material used
	*/
	int GetMaterialIndex(void);
	/*
	USAGE: Asks the mesh for the Shader program used
	ARGUMENTS: ---
	OUTPUT: index of the shader
	*/
	GLuint GetShaderIndex(void);
	/*
	USAGE: Adds a new point to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexPosition(vector3 a_v3Input);
	/*
	USAGE: Adds a new lists of points to the vector of vertices
	ARGUMENTS:
	- std::vector<vector3> a_v3Input -> list of vertices
	- matrix4 a_m4ModelToWorld = IDENTITY_M4 -> vertices modifiers
	OUTPUT: ---
	*/
	void AddVertexPositionList(std::vector<vector3> a_lInput, matrix4 a_m4ModelToWorld = IDENTITY_M4);
	/*
	USAGE: Adds a new color to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexColor(vector3 a_v3Input);
	/*
	USAGE: Adds a new color list to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexColorList(std::vector<vector3> a_lInput);
	/*
	USAGE: Adds a new normal to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexNormal(vector3 a_v3Input);
	/*
	USAGE: Adds a new normal list to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexNormalList(std::vector<vector3> a_v3Input);
	/*
	USAGE: Adds a new binormal to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexBinormal(vector3 a_v3Input);
	/*
	USAGE: Adds a new binormal list to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexBinormalList(std::vector<vector3> a_v3Input);
	/*
	USAGE: Adds a new tangent to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexTangent(vector3 a_v3Input);
	/*
	USAGE: Adds a new tangent list to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexTangentList(std::vector<vector3> a_v3Input);
	/*
	USAGE: Adds a new uv to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexUV(vector3 a_v3Input);
	/*
	USAGE: Adds a new uv to the vector of vertices
	ARGUMENTS:
	- vector3 a_v3Input -> vector input
	OUTPUT: ---
	*/
	void AddVertexUVList(std::vector<vector3> a_v3Input);
	/*
	USAGE: Replaces the list of vertices with the incoming one
	ARGUMENTS: 
	- std::vector<vector3> a_lVertex -> list of vertices
	OUTPUT: ---
	*/
	void SetVertexList(std::vector<vector3> a_lVertex);
	/*
	USAGE: Asks the shape for the list of vertices
	ARGUMENTS: ---
	OUTPUT: list of vertices of this mesh
	*/
	std::vector<vector3> GetVertexList(void);
	/*
	USAGE: Asks the shape for the list of Color vertices
	ARGUMENTS: ---
	OUTPUT: color list
	*/
	std::vector<vector3> GetColorList(void);
	/*
	USAGE: Asks the shape for the list of UV vertices
	ARGUMENTS: ---
	OUTPUT: uv list
	*/
	std::vector<vector3> GetUVList(void);
	/*
	USAGE: Asks the shape for the list of Normal vertices
	ARGUMENTS: ---
	OUTPUT: normal list
	*/
	std::vector<vector3> GetNormalList(void);
	/*
	USAGE: Asks the shape for the list of tangents
	ARGUMENTS: ---
	OUTPUT: tangent list
	*/
	std::vector<vector3> GetTangentList(void);
	/*
	USAGE: Asks the shape for the list of bitangents
	ARGUMENTS: ---
	OUTPUT: bitangent list
	*/
	std::vector<vector3> GetBitangetList(void);
	/*
	USAGE: Return the tint applied to the mesh
	ARGUMENTS: ---
	OUTPUT: tint applied to this shape
	*/
	vector3 GetTint(void);
	/*
	USAGE: Sets the open gl buffer identifier
	ARGUMENTS:
	- GLuint a_nIndex -> OpenGL buffer index
	OUTPUT: ---
	*/
	void SetVertexBuffer(GLuint a_nIndex);
	/*
	USAGE: Returns the OpenGL vertex buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL vertex buffer index
	*/
	GLuint GetVertexBuffer(void);
	/*
	USAGE: Returns the OpenGL UV buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL UV buffer index
	*/
	GLuint GetUVBuffer(void);
	/*
	USAGE: Returns the OpenGL color buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL color buffer index
	*/
	GLuint GetColorBuffer(void);
	/*
	USAGE: Returns the OpenGL normal buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL normal buffer index
	*/
	GLuint GetNormalBuffer(void);
	/*
	USAGE: Returns the OpenGL tangent buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL tangent buffer index
	*/
	GLuint GetTangentBuffer(void);
	/*
	USAGE: Returns the OpenGL binormal buffer index of this shape
	ARGUMENTS: ---
	OUTPUT: OpenGL binormal buffer index
	*/
	GLuint GetBinormalBuffer(void);

	/*
	USAGE: Asks if this shape is made for wireframe use
	ARGUMENTS: ---
	OUTPUT: wireframe use?
	*/
	bool IsWire(void);
	/*
	USAGE: Gets the number of colors applied to this shape
	ARGUMENTS: ---
	OUTPUT: number of colors
	*/
	uint GetColorSize(void);
	/*
	USAGE: Returns the first color used for the shape
	ARGUMENTS: ---
	OUTPUT: first color vertex
	*/
	vector3 GetFirstColor(void);
	/*
	USAGE: Asks the Mesh for its name
	ARGUMENTS: ---
	OUTPUT: Name of the mesh
	*/
	String GetName(void);
	/*
	USAGE: Sets the Mesh's name
	ARGUMENTS:
	- String a_sName -> new name to add
	OUTPUT: ---
	*/
	virtual void SetName(String a_sName);

	/*
	USAGE: returns the VAO of the mesh
	ARGUMENTS: ---
	OUTPUT: VAO
	*/
	GLuint GetVAO(void);
	
	/*
	USAGE: returns the VBO of the mesh
	ARGUMENTS: ---
	OUTPUT: VAO
	*/
	GLuint GetVBO(void);

protected:
	/*
	USAGE: Initialize the object's fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Completes the information missing to create the mesh
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompleteMesh(void);
	/*
	USAGE: Disconnects OpenGL3.x from the Mesh without releasing the buffers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DisconnectOpenGL3X(void);

public:
	/*
	USAGE: Completes the triangle information
	ARGUMENTS:
	- bool a_bAverageNormals = false -> soften the edges of the model
	OUTPUT: ---
	*/
	void CompleteTriangleInfo(bool a_bAverageNormals = false);

	/*
	USAGE: Calculates the missing tangents
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateTangents(void);

	/*
	USAGE: renders the object in wireframe mode
	ARGUMENTS:
	matrix4 a_mViewProjection -> View * Projection matrix
	matrix4 a_mToWorld -> to world matrix
	vector3 a_v3Color -> Color to render
	OUTPUT: ---
	*/
	virtual void Render(matrix4 a_mProjection, matrix4 a_mView, matrix4 a_mWorld);

	/*
	USAGE: renders the object in wireframe mode
	ARGUMENTS:
	matrix4 a_mViewProjection -> View * Projection matrix
	matrix4 a_mToWorld -> to world matrix
	vector3 a_v3Color -> Color to render
	OUTPUT: ---
	*/
	virtual void RenderList(matrix4 a_mProjectionMatrix, matrix4 a_mViewMatrix, float* a_fMatrixArray, int a_nInstances);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<MeshClass*>;

}

#endif //__MESHCLASS_H_