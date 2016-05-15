/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __GROUP_H_
#define __GROUP_H_

#include "RE\Materials\MaterialManagerSingleton.h"
#include "RE\Animation\FrameClass.h"
#include "RE\Animation\AnimationClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"
#include "RE\Physics\BoundingObjectClass.h"

namespace ReEng
{

class ReEngDLL GroupClass
{	
	bool m_bVisible = true;		//Visibility flag
	bool m_bVisibleAxis = false;	//Debug flag
	bool m_bCollidable = false;	//Collision flag
	bool m_bGlobalized = false;	//Global coordinates flag
	bool m_bModified = false;	//Modified flag

	int m_nHP = 0;			//Hit Points of this group
	uint m_uShapeCount = 0; //number of shapes in this group
	uint m_uFrameCount = 0; //Frames in this group
	
	SystemSingleton* m_pSystem = nullptr; //System pointer
	MaterialManagerSingleton* m_pMatMngr = nullptr; //Material Manager Pointer
	MeshDrawerSingleton* m_pMeshDrawer = nullptr; //Mesh Manager Pointer
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //Mesh Manager Pointer
	BoundingObjectClass* m_pBOFrame = nullptr; //Bounding Object of the group per frame
	GroupClass* m_pParent = nullptr; //Parent group pointer
	FrameClass* m_pFrame = nullptr; //List of frames of animation in the group
		
	String m_sName = "NULL";	//Name of the group
	String m_sParent = "NULL";	//Name of the parent of the group

	vector3 m_v3Pivot;		//Point in which the point is going to rotate around
	matrix4* m_pHierarchy = nullptr;	//Matrix for all Meshes that compose the hierarchy of a group
	matrix4 m_m4ToWorld;	//Model to world matrix

	std::vector<MeshClass*> m_lMeshList;//List of Meshes that compose the group
	std::vector<int> m_lMesh; //List of Meshes that compose a group
	std::vector<int> m_lMeshM; //List of Meshes that compose a group when modified

public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	GroupClass(void);
	/*
	USAGE: Copy constructor
	ARGUMENTS: class object
	OUTPUT: class object
	*/
	GroupClass(const GroupClass& other);
	/*
	USAGE: Copy Assignment operator
	ARGUMENTS: class object
	OUTPUT: class object
	*/
	GroupClass& operator=(const GroupClass& other);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~GroupClass(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE:
	ARGUMENTS: class object
	OUTPUT: ---
	*/
	void Swap(GroupClass& other);
	/*
	USAGE: Returns the number of shapes in the vector of shapes
	ARGUMENTS: ---
	OUTPUT: number of shapes
	*/
	int GetShapeCount(void);
	/*
	USAGE: Return the name of the group
	ARGUMENTS: ---
	OUTPUT: name of the group
	*/
	String GetName(void);
	/*
	USAGE: Sets the name of the group
	ARGUMENTS:
	- String a_sName -> name of the group
	OUTPUT: ---
	*/
	void SetName(String a_sName);
	/*
	USAGE: Gets the pointer to all the BOs of the group (one per frame)
	ARGUMENTS: ---
	OUTPUT: the array of BOs of the model
	*/
	BoundingObjectClass* GetBOArray(void);
	/*
	USAGE: Gets the mesh pointer specified by index
	ARGUMENTS: 
	- uint a_nIndex -> index in the list of meshes
	OUTPUT: Mesh in the index
	*/
	MeshClass* GetMesh(uint a_nIndex);
	/*
	USAGE: Removes the empty meshes in the group
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void RemoveEmptyMeshes(void);
	/*
	USAGE: Creates a new mesh and adds it to the list of meshes (name required)
	ARGUMENTS: 
	- String a_sName -> Name of the new mesh to create
	OUTPUT: ---
	*/
	void AddMesh(String a_sName);
	/*
	USAGE: Reserves the OpenGL buffers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);
	/*
	USAGE: Identifies a mesh by the material name and returns its list index
	ARGUMENTS: 
	- String a_sName -> name in the material manager
	OUTPUT: index of the list (-1 if not found)
	*/
	int IdentifyMeshByMaterial(String a_sName);
	/*
	USAGE: Creates a copy of a provided group in this group
	ARGUMENTS: instance object to copy
	OUTPUT: was this cloned successfully?
	*/
	bool CloneFromGroup(const GroupClass& other);
	/*
	USAGE: Releases the OpenGL Buffers allocated
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReleaseOpenGL(void);
	/*
	USAGE: Completes all the necessary information before binding
	ARGUMENTS:
	- bool a_bAverageNormals = false -> asks if the faces are to be smoothed
	OUTPUT: ---
	*/
	void CompleteMissingShapeInfo(bool a_bAverageNormals = false);
	/*
	USAGE: Changes the material of a mesh for a new one, materials needs to exist
	ARGUMENTS:
	- String a_sOldMaterialName -> Previous material
	- String a_sNewMaterialName -> new material to add
	OUTPUT: ---
	*/
	void SwapMaterial(String a_sOldMaterialName, String a_sNewMaterialName);
	/*
	USAGE: Sets shader program to this group, will load the new shader if it doesn't exist
	ARGUMENTS:
	- String a_sVertexShaderName -> vertex shader file name
	- String a_sFragmentShaderName -> fragment shader file name
	- String a_sShaderName -> shader name
	- vector3 a_v3Tint = REDEFAULT -> tint of the group
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets shader program to this group, shader needs to be previously loaded
	ARGUMENTS:
	- String a_sShaderName -> shader name
	- vector3 a_v3Tint = REDEFAULT -> tint of the group
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the material for all objects in the group
	ARGUMENTS:
	- String a_sMaterialName -> name of the previously loaded material
	OUTPUT: ---
	*/
	void SetMaterial(String a_sMaterialName);
	/*
	USAGE: Return the pivot point of the group
	ARGUMENTS: ---
	OUTPUT: pivot
	*/
	vector3 GetPivot(void);
	/*
	USAGE: Sets the pivot point for the group
	ARGUMENTS:
	- vector3 a_v3Pivot -> pivot point
	OUTPUT: ---
	*/
	void SetPivot(vector3 a_v3Pivot);
	/*
	USAGE:
	ARGUMENTS:
	- GroupClass* a_pParent -> 
	OUTPUT: ---
	*/
	void SetParent(GroupClass* a_pParent);
	/*
	USAGE:
	ARGUMENTS:
	- int a_nHP -> 
	OUTPUT: ---
	*/
	void SetHP(int a_nHP);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	int GetHP(void);
	/*
	USAGE:
	ARGUMENTS:
	- bool a_bCollidable -> 
	OUTPUT: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	bool GetCollidable(void);
	/*
	USAGE:  Sets the group visible
	ARGUMENTS:
	- bool a_bVisible -> visibility flag
	OUTPUT: ---
	*/
	void SetVisible(bool a_bVisible);
	/*
	USAGE:  Sets the axis of the group group visible
	ARGUMENTS:
	- bool a_bVisible -> visibility flag
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible);
	/*
	USAGE: Asks if the group is visible
	ARGUMENTS: ---
	OUTPUT: bool -> visibility flag
	*/
	bool GetVisible(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	String GetParentName(void);
	/*
	USAGE:
	ARGUMENTS:
	- String a_sParent -> 
	OUTPUT: ---
	*/
	void SetParentName(String a_sParent);
	/*
	USAGE:
	ARGUMENTS:
	- uint nFrame -> 
	OUTPUT: ---
	*/
	FrameClass GetFrame(uint nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- bool a_bGlobalized -> 
	OUTPUT: ---
	*/
	void SetGlobalized(bool a_bGlobalized);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	uint GetFrameCount(void);
	/*
	USAGE:
	ARGUMENTS:
	- int a_nFrames -> 
	OUTPUT: ---
	*/
	void GenerateFrames(int a_nFrames);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ReleaseFrames(void);
	/*
	USAGE:
	ARGUMENTS:
	- int a_nFrame -> 
	- vector3 a_v3Translation -> 
	- vector3 a_v3Rotation -> 
	- vector3 a_v3Scale -> 
	- bool a_bVisible -> 
	- bool a_bKeyframe -> 
	OUTPUT: ---
	*/
	void SetFrame(int a_nFrame, vector3 a_v3Translation, vector3 a_v3Rotation, vector3 a_v3Scale, bool a_bVisible, bool a_bKeyframe);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set
	- int a_nFrame -> frame to set value to
	OUTPUT: ---
	*/
	void SetPosX(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to
	OUTPUT: ---
	*/
	void SetPosY(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetPosZ(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetAngX(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetAngY(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetAngZ(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetSizeX(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetSizeY(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetSizeZ(float a_fValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetVisible(bool a_bValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- float a_fValue -> value to set 
	- int a_nFrame -> frame to set value to 
	OUTPUT: ---
	*/
	void SetKeyframe(bool a_bValue, int a_nFrame);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ComputeMatrix(void);
	/*
	USAGE:
	ARGUMENTS:
	- int a_nFrames -> 
	OUTPUT: ---
	*/
	void Interpolate(int a_nFrames);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	matrix4& GetModelMatrix(void);
	/*
	USAGE:
	ARGUMENTS:
	- GroupClass* a_Group -> 
	- int a_nFrame = 0 -> 
	OUTPUT: ---
	*/
	matrix4 TraverseHierarchy(GroupClass* a_Group, int a_nFrame = 0);
	/*
	USAGE:
	ARGUMENTS: 
	- int a_nShape = -1 -> 
	OUTPUT: ---
	*/
	std::vector<vector3> GetVertexList(int a_nShape = -1);
	/*
	USAGE:
	ARGUMENTS: 
	- uint a_nFrame -> 
	- matrix4 a_mToWorld -> 
	OUTPUT: ---
	*/
	void Update(uint a_nFrame);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DisconectAnimationFrames(void);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	matrix4 GetHierarchyMatrix(uint a_nFrame);
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void UpdateBOForFrame(uint a_nFrame);
	/*
	USAGE:
	ARGUMENTS:
	- matrix4 a_nMatrix -> 
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_nMatrix);
	/*
	USAGE:
	ARGUMENTS:
	- uint a_nFrame = 0 -> 
	OUTPUT: ---
	*/
	void AddToRenderList(uint a_nFrame = 0);//Add all shapes to the render list
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = REBODISPLAY::BD_NONE -> Display options BD_NONE | BD_BO | BD_OB | BD_AB
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = REBODISPLAY::BD_NONE);

	/*
	USAGE: Will check if the group is colliding with the ray specified by the origin and directional vector and store
	- the distance from the origin till the collision in a_fDistance
	ARGUMENTS:
	- vector3 a_v3RayOrigin -> start of the ray
	- vector3 a_v3RayDirection -> direction of the ray
	- float& a_fDistance -> distance for origin
	OUTPUT: Is it colliding?
	*/
	bool IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance, int a_nCurrentFrame);

private:
	/*
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<GroupClass*>;

}
#endif //__GROUP_H__