/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MODELCLASS_H_
#define __MODELCLASS_H_

#include <thread>
#include "RE\Mesh\GroupClass.h"
#include "RE\System\FileReaderClass.h"
#include "RE\Animation\SequenceClass.h"
#include "RE\Animation\StateClass.h"
#include "RE\physics\BoundingObjectClass.h"

#ifdef FBXSDK_SHARED
#include <fbxsdk.h>
#ifdef IOS_REF
#undef  IOS_REF
#define IOS_REF (*(pManager->GetIOSettings()))
#endif
#endif

namespace ReEng
{

class ReEngDLL ModelClass
{	
	bool m_bLoaded = false; //Loaded flag
	bool m_bBinded = false; //Binded flag
	bool m_bVisible = true;	//Visibility flag
	bool m_bCollidable = false;	//Collidable flag
#ifdef FBXSDK_SHARED
	bool m_bUsingFBXSDK = true; //FBX flag
#else
	bool m_bUsingFBXSDK = false; //FBX flag
#endif
	uint m_uMaterialCount = 0; //number of materials
	uint m_uGroupCount = 0; //Number of groups
	uint m_uFrameCount = 0; //Number of frames
	uint m_uStateCount = 0; //Number of states
	uint m_uSequenceCount = 0; //Number of sequences
	int m_nHP = 1; //Hit point of the model

	SystemSingleton* m_pSystem = nullptr;	//Pointer to the system
	MaterialManagerSingleton* m_pMatMngr = nullptr;	//Pointer to the Material Manager
	std::thread* m_Thread = nullptr;	//Thread on which the model is loading

	String m_sName = "NULL";	//Name of the Model
		
	std::vector<GroupClass*> m_lGroup;	//List of groups
	std::vector<SequenceClass*> m_lSequence;	//List of sequences
	std::vector<StateClass*> m_lState;	//List of states

	std::map<String,int> m_map;//Indexer of Groups
	std::map<String,int> m_mapStates;//Indexer of states
public:
	/*
	 ModelClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	ModelClass(void);
	/* Copy Constructor */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ModelClass(const ModelClass& other);
	/* Copy Assignment operator*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	ModelClass& operator=(const ModelClass& other);
	/* Destructor */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~ModelClass(void);
	
	/* Releases the object from memory */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);

	/* Loads an obj file in memory */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS CreateLoadOBJThread(String a_sFileName, bool a_bAbsoluteRoute);

	/* Swaps the information of one model object into another */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(ModelClass& other);

	/* Asks the model for its number of groups */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetGroupCount(void);
	/* Asks the model for its name */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	String GetName(void);
	/* Property GetName*/
	//__declspec(property(get = GetName)) String Name;

	/* Asks the Model for a Group by index */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass* GetGroup(uint a_nIndex);
	/* Asks the model identify the index of a group by name, -1 if not found*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyGroup(String a_sName);

	/* Asks the model if its RE_DONE loading */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsLoaded(void);

	/* Create a copy of a group by index */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool InstanceGroup(GroupClass* a_TargetGroup, uint a_nIndex);

	/* Binds the Model for opengl 3.x*/
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CompileOpenGL3X(void);

	/* Sets the Hit Points of the model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetHP(int a_nHP);
	/* Asks the model for its Hit Points*/
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	int GetHP(void);

	/* Sets the model to be collidable */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetCollidable(bool a_bCollidable);
	/* Asks the model if its collidable */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool GetCollidable(void);

	/* Sets the model to be visible */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetVisible(bool a_bVisible);
	/* Asks the model if its visible */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool GetVisible(void);

	/* 
	Asks the model for a list of vertices for a particular group's shape 
		Args:
			a_nGroup -> -1 for all groups
			a_nMesh -> -1 for all shapes
	*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	std::vector<vector3> GetVertexList(int a_nGroup = -1, int a_nMesh = -1);

	/* Get the number of frames of animation in this model */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetFrameCount(void);

	/* Asks the model for its sequence List */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	std::vector<SequenceClass*> GetSequenceList(void);

	/* Asks the model for a sequence from its List of sequences */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	SequenceClass* GetSequence(uint a_nSequence);

	/* Asks the model for its number of states*/
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetStateCount(void);
	/* Asks the model for its number of states*/
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	uint GetSequenceCount(void);
	/* Asks the model for a state by index */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass* GetState(uint a_nState);

	/* Asks the model the index of the provided state, -1 if not found */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyState(StateClass* a_pState);

	/* Asks the model the index of the provided state, -1 if not found */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	int IdentifyState(String a_sName);

	/* Loads a model from an OBJ file*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadOBJ(String a_sFileName, bool a_bAbsoluteRoute = false);

	/* Loads a model from an ATO file*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadATO(String a_sFileName, bool a_bAbsoluteRoute = false);

	/* Loads a model from an BTO file*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadBTO(String a_sFileName, bool a_bAbsoluteRoute = false);

#ifdef FBXSDK_SHARED
	/* Loads a model from an BTO file*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadFBX(String a_sFileName, bool a_bAbsoluteRoute = false);
#endif

	/* Saves a loaded model as an ATO file do not add the extension unless absolute route*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveATO(String a_sFileName, bool a_bAbsoluteRoute);

	/* Saves a loaded model as an BTO file do not add the extension unless absolute route*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS SaveBTO(String a_sFileName, bool a_bAbsoluteRoute);

private:
	/* Initializates the model object */
	/*
	 
	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/* Loads the material file for this model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadMTL(String a_sFileName);
	/* Loads the hierarchy file for this model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadHIE(String a_sFileName);
	/* Loads the animation file for this model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadANIM(String a_sFileName);
	/* Loads the sequence file for this model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadSEQ(String a_sFileName);
	/* Loads the state file for this model */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	REERRORS LoadSTA(String a_sFileName);

	/* Asks the model for a group by name*/
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	GroupClass* GetGroup(String a_sName);

	/* Asks the model for a state by name */
	/*
	 
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	StateClass* GetState(String a_sName);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	vector3 RoundVector(vector3 a_v3Vector, float fMargin = 0.0001f);

#ifdef FBXSDK_SHARED
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXGetExtremeFrames(FbxNode* pNode, int& nStart, int& nEnd);

	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessGroupAnimation(FbxNode* pNode, GroupClass* pGroup);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessEmpty(FbxNode* pNode);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessMesh(FbxNode* pNode);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void FBXProcessNode(FbxNode* pNode);
	/*
	
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	bool FBXProcessScene(FbxScene* pScene);
#endif
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<ModelClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<ModelClass*>;

}

#endif //_MODEL_H