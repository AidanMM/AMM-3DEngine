/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __BOMANAGERSINGLETON_H_
#define __BOMANAGERSINGLETON_H_

#include "RE\Physics\BoundingObjectClass.h"
#include "RE\Mesh\MeshManagerSingleton.h"
namespace ReEng
{

//System Class
class ReEngDLL BOManagerSingleton
{
	uint m_uBOCount = 0; //number of BOs in the list
	static BOManagerSingleton* m_pInstance; // Singleton pointer
	std::vector<BoundingObjectClass*> m_lObject; //list of BOs
	std::vector<std::vector<std::vector<int>>> m_lCollisions;
	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager Singleton
public:
	/*
	USAGE: Gets the static instance of the class
	ARGUMENTS: ---
	OUTPUT: static pointer to class
	*/
	static BOManagerSingleton* GetInstance();
	/*
	USAGE: releases the static pointer to class
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Adds a Bounding Object to the list and returns its index.
	ARGUMENTS:
	- BoundingObjectClass* a_pObject -> Object to Add
	OUTPUT: Index of the object, -1 if not added
	*/
	int AddBO(BoundingObjectClass* a_pObject);

	/*
	USAGE: Adds all object currently in the Mesh Manager
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Initialize(void);

	/*
	USAGE: Sets the visibility of the bounding object.
	ARGUMENTS:
	- int a_nIndex -> Index of the object
	- int a_nRenderOptions = BD_NONE -> Render options BS | OB | AB
	- vector3 a_v3Color = REDEFAULT -> color to render
	OUTPUT: ---
	*/
	void SetVisible(uint a_nIndex, int a_nRenderOptions = BD_NONE, vector3 a_v3Color = REDEFAULT);
	
	/*
	USAGE: Returns the number of BOs currently on the manager
	ARGUMENTS: ---
	OUTPUT: Number of BOs
	*/
	uint GetBOCount(void);
	/*
	USAGE: returns the element specified by the index
	ARGUMENTS:
	- uint a_nIndex -> Index of the object in the manager
	OUTPUT: BoundingObjectClass* from the list
	*/
	BoundingObjectClass* GetBoundingObject(uint a_nIndex);
	/*
	USAGE: Checks if there is a collision between these 2 objects and marks it in their lists
	ARGUMENTS:
	- uint a_nIndexA -> Index of the first object
	- uint a_nIndexB -> Index of the second object
	OUTPUT: ---
	*/
	void CheckCollisionBetween(uint a_nIndexA, uint a_nIndexB);
	/*
	USAGE: Calculates the intermediary states of all the members in the variables
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Update(void);

private:
	/*
	USAGE: instantiates the object
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	BOManagerSingleton(void);
	/*
	USAGE: does nothing (singleton behavior)
	ARGUMENTS: other instance to copy
	OUTPUT: ---
	*/
	BOManagerSingleton(BOManagerSingleton const& other);
	/*
	USAGE: does nothing (singleton behavior)
	ARGUMENTS: other instance to copy
	OUTPUT: ---
	*/
	BOManagerSingleton& operator=(BOManagerSingleton const& other);
	/*
	USAGE: releases the instance
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~BOManagerSingleton(void);
	/*
	USAGE: deallocates the memory of the method
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: allocates the members of the method
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Calculates the collision between all OBs
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CheckCollisions(void);
};

}

#endif //__BOMANAGERSINGLETON_H__