/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MODELMANAGERSINGLETON_H_
#define __MODELMANAGERSINGLETON_H_

#include <string>
#include "RE\Mesh\InstanceClass.h"

namespace ReEng
{

class ReEngDLL ModelManagerSingleton
{
	//Member variables
	uint m_uInstanceCount = 0;		//Number of instances
	uint m_uModelCount = 0;			//Number of models

	static ModelManagerSingleton* m_pInstance;
	MaterialManagerSingleton* m_pMatMngr = nullptr; //Material Manager pointer

	std::vector<vector4> m_lCollidingGroup; //List of colliding Objects
	std::vector<ModelClass*> m_lModel; //Vector of Models
	std::vector<InstanceClass*> m_lInstance; //Vetor of Model Instances

	std::map<String,int> m_mapModel;
	std::map<String,int> m_mapInstance;
public:
	//Singleton methods
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static ModelManagerSingleton* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS:
	OUTPUT: ---
	*/
	static void ReleaseInstance();
	//Accessors
	/*
	USAGE: Will check the collision between two objects if they are colliding it will return a pair, each member
	- will be the list of group indices (of the other object) each group is colliding with.
	ARGUMENTS:
	- String a_sName1 -> Index Instance one
	- String a_sName2 -> Index Instance two
	- int a_nBODisplay -> Activates the display for the BO
	OUTPUT: Instance<GroupIndex<OtherGroupIndex>>, Instance<GroupIndex<OtherGroupIndex>>
	*/
	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
		GetCollisionPair(String a_sIndex1, String a_sIndex2, int a_nBODisplay = BD_NONE);
	/*
	USAGE: Will check the collision between two objects if they are colliding it will return a pair, each member
	- will be the list of group indices (of the other object) each group is colliding with.
	ARGUMENTS:
	- uint nIndex1 -> Index Instance one
	- uint nIndex2 -> Index Instance two
	- int a_nBODisplay -> Activates the display for the BO
	OUTPUT: Instance<GroupIndex<OtherGroupIndex>>, Instance<GroupIndex<OtherGroupIndex>>
	*/
	std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
		GetCollisionPair(uint a_nIndex1, uint a_nIndex2, int a_nBODisplay = BD_NONE);
	/*
	USAGE: Gets the current state of the model
	ARGUMENTS:
	- a_sInstanceName: Name of the model to look
	OUTPUT: -1 if model does not exist
	*/
	int GetCurrentState(String a_sInstanceName);
	/*
	USAGE: Gets the current state of the model
	ARGUMENTS:
	- a_nInstanceIndex: Index of the model to look
	OUTPUT: -1 if model does not exist
	*/
	int GetCurrentState(uint a_nInstanceIndex);
	/*
	USAGE: Asks for the name of the group in the specified instance
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	- uint a_nGroupIndex -> Index of the group
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceGroupName(uint a_nInstanceIndex, uint a_nGroupIndex);
	/*
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	InstanceClass* GetInstanceByIndex(uint a_nIndex);
	/*
	USAGE: Asks the Manager for an instance using the provided name, nullptr if not found
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
	USAGE: Asks for the name of the instance stored in the specified index
	ARGUMENTS:
	- uint a_nInstanceIndex -> Index of the instance
	OUTPUT: Name in the index, empty if not found
	*/
	String GetInstanceName(uint a_nInstanceIndex);
	/*
	USAGE: Asks the Manager for an instance using the provided index, nullptr if not found
	ARGUMENTS:
	OUTPUT:
	*/
	ModelClass* GetModelByIndex(uint a_nIndex);
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
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(uint a_nIndex);
	/*
	USAGE: Asks the manager for the list of vertices of an specified instance
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(String a_sInstanceName);
	/*
	USAGE: Sets the model matrix of an specific instance finding it by name
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_mMatrix, String a_sInstance = "ALL");
	/*
	USAGE: Sets the model matrix of an specific instance finding it by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_mMatrix, int a_nInstance = -1);
	/*
	USAGE: Sets the next state of the specified instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetNextState(String a_sIntance, int a_nNextState);
	/*
	USAGE: Sets the shader program of an specific instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetShaderProgram(String a_sInstanceName, String a_sVertexShaderName, String a_sFragmentShaderName, String a_sShaderName);
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
	USAGE: Sets the visibility of an specified instance axis
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisibleAxis(bool a_bVisible = false, String a_sInstanceName = "ALL", int a_nGroupIndex = -1);
	/*
	USAGE: Sets the visibility of the Bounding Object of the instance
	ARGUMENTS:
	- int a_nOption = REBODISPLAY::BD_NONE -> Display options BD_NONE | BD_BS | BD_OB | BD_AB
	- String a_sInstanceName = "ALL" -> Instance to apply to
	- int a_nGroupIndex = -1 -> Group index if less than 0 applies it to all
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
	//Other methods
	/*
	USAGE: Renders the specified instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(String a_sInstance = "ALL");
	/*
	USAGE: Adds an instance to the render list specified by index
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddInstanceToRenderList(uint a_nInstance);
	/*
	USAGE: Check for the collisions in the list by brute force
	ARGUMENTS:
	- int a_nBODisplay = BD_NONE -> Bounding Object Display Option
	OUTPUT: ---
	*/
	void CheckCollisions(int a_nBODisplay = BD_NONE);
	/*
	USAGE: Removes the specified instance from the list
	ARGUMENTS:
	OUTPUT: ---
	*/
	void DeleteInstance(String a_sInstance = "ALL");
	/*
	USAGE: Asks the manager for the index of the instance in the instance list, -1 if the instance is not part of it
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyInstance(String a_sName);
	/*
	USAGE: Asks the manager for the index of the model in the model list, -1 if the model is not part of it
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyModel(String a_sFileName);
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
	USAGE: Checks if the instance in RE_DONE animating
	ARGUMENTS:
	OUTPUT:
	*/
	bool IsInstanceInLastFrame(String a_sInstanceName);
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
	REERRORS LoadLevel(String a_sFileName);
	/*
	USAGE: Loads the specified model file in a separate thread
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
	USAGE: Modifies the material of the specified instance
	ARGUMENTS:
	OUTPUT: ---
	*/
	void ModifyMaterial(String a_sInstance,
		String a_sOldMaterialName,
		String a_sNewMaterialName,
		String a_sDiffuseTexture = "Original",
		String a_sNormalTexture = "Original",
		String a_sSpecularTexture = "Original");
	/*
	USAGE: Plays the specified animation
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PlayAnimation(String a_sInstanceName, int a_nSequenceIndex = -1);
	/*
	USAGE: Pushes an Instance into the Instance list
	ARGUMENTS:
	OUTPUT: ---
	*/
	void PushInstance(InstanceClass* a_pInstance);
	/*
	USAGE: Saves the model as a ATO do not add the extension unless it's an absolute route
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveATO(String a_sFileName, bool a_bAbsoluteRoute, String a_sInstance);
	/*
	USAGE: Saves the model as a BTO do not add the extension unless it's an absolute route
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveBTO(String a_sFileName, bool a_bAbsoluteRoute, String a_sInstance);
	/*
	USAGE: Updates the model manager
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Update(void);
	/*
	USAGE: Updates the model map
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void UpdateMap(void);
private:
	//Rule of Three
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	ModelManagerSingleton(void);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	ModelManagerSingleton(const ModelManagerSingleton& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	ModelManagerSingleton& operator=(const ModelManagerSingleton& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ModelManagerSingleton(void);
	//Member Functions
	/*
	USAGE: Releases the object from memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initializes the object's fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	
};

}

#endif //__MODELMANAGERSINGLETON_H_