/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MESHMANAGERSINGLETON_H_
#define __MESHMANAGERSINGLETON_H_
#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Mesh\ModelManagerSingleton.h"
#include "RE\Mesh\TextSingleton.h"

namespace ReEng
{
//MeshManagerSingleton
class ReEngDLL MeshManagerSingleton
{
	static MeshManagerSingleton* m_pInstance; // Singleton pointer
	TextSingleton* m_pText; //Text Singleton

public:
	MeshDrawerSingleton* m_pMeshDrawer = nullptr;//pointer to the Mesh Drawer singleton
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //pointer to the Primitive Manager singleton
	ModelManagerSingleton* m_pModelMngr = nullptr; //pointer to the Model Manager singleton
	
	//Singleton Methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static MeshManagerSingleton* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	//Gets/Sets
	/*
	USAGE: Gets the Instance by an index number
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByIndex(int a_nIndex);
	/*
	USAGE: Gets the Instance by a name
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByName(String a_sInstanceName);
	/*
	USAGE: Asks the Manager for the number of instances
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetInstanceCount(void);
	/*
	USAGE: Asks for the name of the group in the specified instance
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	- uint a_nGroupIndex -> Index of the group
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceGroupName(uint a_nInstanceIndex, uint a_nGroupIndex);
	/*
	USAGE: Asks for the name of the instance stored in the specified index
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceName(uint a_nInstanceIndex);
	/*
	USAGE: Asks the Manager for the number of models
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetModelCount(void);
	/*
	USAGE: Asks the manager for an specific instance's model to world matrix
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 GetModelMatrix(String a_sInstance);
	/*
	USAGE: Asks the name of the specified instance by its index returns empty if not found
	ARGUMENTS:
	OUTPUT:
	*/
	String GetNameOfInstanceByIndex(int a_nIndex);
	/*
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(String a_sInstanceName);
	/*
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(uint a_nIndex);
	/*
	USAGE: Sets the model matrix of an specific instance finding it by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, String a_sInstance = "ALL");
	/*
	USAGE: Sets the model matrix of an specific instance finding it by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld, int a_nIndex);
	/*
	USAGE: Sets the shader program of an specific instance by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByName(String a_sInstanceName = "ALL", String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the shader program of an specific instance by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgramByNumber(int a_nInstance = -1, int a_nGroup = -1, String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the visibility of the axis of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible = false, String a_sInstanceName = "ALL", int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = REBODISPLAY::BD_NONE -> Display options BD_NONE | BD_BS | BD_OB | BD_AB
	- String a_sInstanceName = "ALL" -> Instance to apply to
	- bool a_bAllGroups = false -> Apply to all groups
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = REBODISPLAY::BD_NONE, String a_sInstanceName = "ALL", int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = REBODISPLAY::BD_NONE -> Display options BD_NONE | BD_BS | BD_OB | BD_AB
	- int a_nInstanceIndex = -1 -> Instance index if less than 0 applies it to all
	- int a_nGroupIndex = -1 -> Group index if less than 0 applies it to all
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = REBODISPLAY::BD_NONE, int a_nInstanceIndex = -1, int a_nGroupIndex = -1);
	/*
	USAGE: Updates the model manager
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Update(void);
	//Methods
	/*
	USAGE: Render the axis on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddAxisToQueue(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the a Camera Mesh on the specified camera's position, -1 for active camera
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCameraToQueue(int a_nID = -1, vector3 a_v3Color = REWHITE);
	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddConeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCylinderToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddGridToQueue(float a_fSize = 1.0f, int a_Axis = REAXIS::XY, vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Renders a hexagon tile on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	MeshClass* AddHexagonTileToQueue(matrix4 a_m4ToWorld, vector2 a_v2Size, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders a hexagon on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddHexagonToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Adds an instance to the render list specified by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(uint a_nInstance);
	/*
	USAGE: Renders the specified instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(String a_sInstance = "ALL");
	/*
	USAGE: Renders a line on with the specified vectors and color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddLineToRenderList(vector3 a_v3Origin, vector3 a_v3Ending, vector3 a_v3StartColor = REDEFAULT, vector3 a_v3EndColor = REDEFAULT);
	/*
	USAGE: Renders a mesh on the specified space
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(MeshClass* a_pMesh, matrix4& a_m4ToWorld);
	/*
	USAGE: Renders a mesh on the specified space
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddMeshToRenderList(int a_nIndex, matrix4& a_m4ToWorld);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddPlaneToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddSphereToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders a char array in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextLineToQueue(vector3 a_v3Color, const char * _Format, ...);
	/*
	USAGE: Renders a char array in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTextToQueue(vector3 a_v3Color, const char * _Format, ...);
	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTorusToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Returns the index of the specified instance name, -1 if not found
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyInstance(String a_sInstanceName);
	/*
	USAGE: Will check if an Instance is colliding with the ray specified by the origin and directional vector and store
	- the distance from the origin till the collision in a_fDistance, the output will be an std::pair containing the index
	- of the instance and the index of the group is first colliding with, -1 if not colliding with anything
	ARGUMENTS:
	- vector3 a_v3RayOrigin -> start of the ray
	- vector3 a_v3RayDirection -> direction of the ray
	- float& a_fDistance -> distance for origin
	OUTPUT: <Instance index, group index>
	*/
	std::pair<int, int> IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);
	/*
	USAGE: Asks the manager if an instance with this name has been created
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsInstanceCreated(String a_sInstanceName);
	/*
	USAGE: Loads an add-on file for the specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadAddOn(String a_sInstanceName, String a_sFileName);
	/*
	USAGE: Loads the specified level file
	ARGUMENTS:
	OUTPUT: ---
	*/
	void LoadLevel(String a_sFileName);
	/*
	USAGE: Loads the specified model file
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadModel(String a_sFileName,
		String a_sInstanceName,
		bool a_bAbsoluteRoute = false,
		matrix4 a_m4ToWorld = matrix4(1.0),
		int a_nVisibility = 1,
		int a_nCollidable = 1,
		int a_nState = 0);
	/*
	USAGE: Renders a String in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Print(String a_sInput, vector3 a_v3Color = REWHITE);
	/*
	USAGE: Renders a String Line in the specified color
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PrintLine(String a_sInput, vector3 a_v3Color = REWHITE);
	/*
	USAGE: Renders the list of meshes
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Render(void);
	/*
	USAGE: Saves the specified model file, needs to specify the file extension (ATO or BTO)
	ARGUMENTS:
	String a_sFileName -> Name of the file
	FORMAT a_Format -> Extension of the file FORMAT::ATO or FORMAT::BTO
	String a_sInstanceName -> Name of the instance to save
	bool a_bAbsoluteRoute = false -> whether the filename specifies an absolute route or not
	OUTPUT: REERRORS -> RERROR_FREE if everything went right, reason for failure otherwise
	*/
	REERRORS SaveModel(String a_sFileName,
		FORMAT a_Format,
		String a_sInstanceName,
		bool a_bAbsoluteRoute = false);
	/*
	USAGE: Sets the texture for the font
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetFont(String a_sTextureName);

private:
	//Rule of 3
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	MeshManagerSingleton(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton(MeshManagerSingleton const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	MeshManagerSingleton& operator=(MeshManagerSingleton const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~MeshManagerSingleton(void);
	//Other methods
	/*
	USAGE: Initializes the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
};

}

#endif //__MESHMANAGERSINGLETON_H_