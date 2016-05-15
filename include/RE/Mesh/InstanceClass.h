/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __INSTANCECLASS_H_
#define __INSTANCECLASS_H_

#include "RE\Mesh\ModelClass.h"
#include "RE\Mesh\PrimitiveManagerSingleton.h"

namespace ReEng
{

class ReEngDLL InstanceClass
{
	bool m_binstantiated = false;	//RE_DONE instantiated flag
	bool m_bVisible = true;			//Visibility flag
	bool m_bVisibleAxis = false;	//Visible Axis flag
	bool m_bCollidable = false;		//Collidable flag

	bool m_bFirstRun = true;
	
	uint m_uGroupCount = 0;		//Number of groups
	uint m_uFrameCount = 0;		//Number of frames
	int m_nStateLast = 0;		//Last state visited
	int m_nStateCurrent = 0;	//Current state
	int m_nStateNext = 0;		//Next state to visit
	int m_nHP = 1;				//Hit Points of the Instance
	uint m_uCurrentFrame = 0;	//Current frame to be rendered

	float m_fLastFrameDrawn = 0.0f; //Last frame rendered

	SystemSingleton* m_pSystem = nullptr;		//System pointer
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr; //Mesh Manager Pointer
	ModelClass* m_pModel = nullptr;				//Model from which this instance was instantiated
	GroupClass* m_pGroup = nullptr;				//List of group pointers of the instance

	DWORD m_dLastRenderCall = 0;	//Last render call

	String m_sName = "NULL";		//Name of the instance

	matrix4 m_m4ToWorld;		//Model to world matrix

	std::map<String, int> m_map;	//For indexing the groups

	SequenceClass* m_pSequence = nullptr; //Sequence played outside of state
	BoundingObjectClass* m_pBO = nullptr; //pointer to a BO that contains all frames BO
	BoundingObjectClass* m_pBOFrame = nullptr; //pointer to an array of per frame BOs

public:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	InstanceClass(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass(const InstanceClass& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass& operator=(const InstanceClass& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~InstanceClass(void);

	//Accessors
	/*
	USAGE: Sets the Shader program
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName, vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the shader program to a program already compiled
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sShaderName = "Original", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Sets the Model to World matrix of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(const matrix4 a_m4ToWorld = matrix4(1.0f));
	/*
	USAGE: Gets the model to World matrix from the instance
	ARGUMENTS: ---
	OUTPUT:
	*/
	matrix4& GetModelMatrix(void);
	/*
	USAGE: Set the name of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetName(String a_sName);
	/*
	USAGE: Gets the name of the specified group
	ARGUMENTS:
	OUTPUT:
	*/
	String GetName(int nGroup = -1);
	/*
	USAGE: Sets the Hit Points of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetHP(int a_nHP);
	/*
	USAGE: Gets the Hit Points of the instance
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetHP(void);
	/*
	USAGE: Gets the pointer to all the BOs of the index (one per frame)
	ARGUMENTS: ---
	OUTPUT: the array of BOs of the model
	*/
	BoundingObjectClass* GetBOArray(void);
	/*
	USAGE: Sets the instance to be collidable
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/*
	USAGE: Asks the instance if its collidable
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetCollidable(void);
	/*
	USAGE: Sets the visibility flag
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisible(bool a_bVisible);
	/*
	USAGE: Gets the visibility flag
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetVisible(void);
	/*
	USAGE: Gets the current state of the instance
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetCurrentState(void);
	/*
	USAGE: Asks if the model is in the last frame for its current state
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsInLastFrame(void);
	/*
	USAGE: Plays the specified animation sequence
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PlayAnimation(int a_nSequenceIndex = -1);
	/*
	USAGE: Sets the next state of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetNextState(uint a_nNext);
	/*
	USAGE: Sets the current state of the instance (it forces the switch)
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetCurrentSate(uint a_nState);
	/*
	USAGE: Change the shader program of a group finding it by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetGroupShaderByName(String a_sProgramName = "Original", String a_sGroupName = "ALL", vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Change the shader program of a group finding it by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetGroupShaderByNumber(String a_sProgramName = "Original", int nGroup = -1, vector3 a_v3Tint = REDEFAULT);
	/*
	USAGE: Change the material of a group finding it by name, the material needs to be already compiled
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetGroupMaterial(String a_sMaterialName, String a_sGroupName = "ALL");
	/*
	USAGE: Asks the instance what is the last drawn frame
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetLastFrameDrawn(void);
	/*
	USAGE: Asks the instance what is its the number of groups
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetGroupCount(void);
	/*
	USAGE: Asks the instance what is its number of frames
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetFrameCount(void);
	/*
	USAGE: Asks the instance for the vertices of the whole model
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(void);
	/*
	USAGE: Asks the instance for the Model for which it was instantiated from
	ARGUMENTS: ---
	OUTPUT:
	*/
	ModelClass* GetModelInstanced(void);
	/*
	USAGE: Creates an Instance of a previously loaded model
	ARGUMENTS:
	OUTPUT: ---
	*/
	void InstanceModel(ModelClass& a_Model);
	/*
	USAGE: Updates all the internal structures of the instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Adds all groups of the instance to the render list
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AddToRenderList(void);
	/*
	USAGE: Asks the instance if its already RE_DONE instantiated
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsInstanced(void);
	/*
	USAGE: Identifies a group by name, the return will be -1 if the name is not found
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyGroup(String a_sName);
	/*
	USAGE: Swap the materials of the instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SwapMaterials(String a_sOldMaterialName, String a_sNewMaterialName);
	/*
	USAGE: We need to disconnect all the pointers that are shared among the instances and the model
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void DisconectPointers(void);
	/*
	USAGE: Sets the visibility of the Axis of the instance
	ARGUMENTS:
	- bool a_bEnable = false -> Enable or disable
	- int a_nIndex = -2 -> Group index -1 will affect all groups, less than that will affect none
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bEnable = false, int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = REBODISPLAY::BD_NONE -> Display options BD_NONE | BD_BO | BD_OB | BD_AB
	- String a_sInstanceName = "ALL" -> Instance to apply to
	- int a_nIndex = -2 -> Group index -1 will affect all groups, less than that will affect none
	OUTPUT: ---
	*/
	void SetVisibleBO(int a_nOption = REBODISPLAY::BD_NONE, int a_nGroupIndex = -2);
	/*
	USAGE: Gets a group by name
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass* GetGroup(String a_sName);
	/*
	USAGE: Gets a group by index
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass* GetGroup(uint a_nIndex);
	/*
	USAGE: Gets the current frame 
	ARGUMENTS: ---
	OUTPUT: Current Frame
	*/
	uint GetCurrentFrame(void);
	/*
	USAGE: Gets the current frame BO
	ARGUMENTS: ---
	OUTPUT: Bounding Object of the current frame
	*/
	BoundingObjectClass* GetCurrentBO(void);
	/*
	USAGE: Gets the BO that contains all frameBO
	ARGUMENTS: ---
	OUTPUT: Bounding Object 
	*/
	BoundingObjectClass* GetMagnaBO(void);
	/*
	USAGE: Will check if an Instance is colliding with the ray specified by the origin and directional vector and store
	- the distance from the origin till the collision in a_fDistance, the output will be the index of the the group 
	- is first colliding with, -1 if not colliding with anything
	ARGUMENTS:
	- vector3 a_v3RayOrigin -> start of the ray
	- vector3 a_v3RayDirection -> direction of the ray
	- float& a_fDistance -> distance for origin
	OUTPUT: group index
	*/
	int IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);

private:
	
	/*
	USAGE: Initializes the variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Release the fields in the class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Swaps Content with other Instance class
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(InstanceClass& other);
	/*
	USAGE: Identifies a state by name
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyState(StateClass* a_pState);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<InstanceClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<InstanceClass*>;

}

#endif //_INSTANCECLASS_H
