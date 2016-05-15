/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/11
----------------------------------------------*/
#ifndef __OCTANTCLASS_H_
#define __OCTANTCLASS_H_

#include "RE\Physics\BOManagerSingleton.h"

namespace ReEng
{

//System Class
class ReEngDLL OctantClass
{
	static uint m_uOctantCount; //will store the number of octants instantiated
	static uint m_uMaxLevel;//will store the maximum level an octant can go to
	static uint m_uIdealBOCount; //will tell how many ideal BOs this object will contain

	uint m_uID = 0; //Will store the current ID for this octant
	uint m_uLevel = 0; //Will store the current level of the octant
	uint m_uChildren = 0;// Number of children on the octant (either 0 or 8)

	float m_fSize = 0.0f; //Radius of the Bounding Object

	BOManagerSingleton* m_pBOMngr = nullptr;//Bounding Object Manager Singleton
	MeshManagerSingleton* m_pMeshMngr = nullptr;//Mesh Manager singleton

	vector3 m_v3Center = vector3(0.0f); //Will store the center point of the octant
	vector3 m_v3Min = vector3(0.0f); //Will store the minimum vector of the octant
	vector3 m_v3Max = vector3(0.0f); //Will store the maximum vector of the octant
	
	OctantClass* m_pParent = nullptr;// Will store the parent of current octant
	OctantClass* m_pChild[8];//Will store the children of the current octant

	std::vector<uint> m_lBOs; //stores all the BOs under this octant
	OctantClass* m_pRoot = nullptr;//Bounding Object Manager Singleton
	std::vector<OctantClass*> m_lChild; //list of nodes that contain objects

public:
	/*
	USAGE: Constructor, will create an octant containing all MagnaBOs Instances in the Mesh 
	manager	currently contains
	ARGUMENTS:
	- uint a_nMaxLevel = 3 -> Sets the maximum level of subdivision
	- uint nIdealBOCount = 5 -> Sets the ideal level of objects per octant
	OUTPUT: class object
	*/
	OctantClass(uint a_nMaxLevel = 3, uint a_nIdealBOCount = 5);
	/*
	USAGE: Constructor
	ARGUMENTS:
	- vector3 a_v3Center -> Center of the octant in global space
	- float a_fSize -> size of each side of the octant volume
	OUTPUT: class object
	*/
	OctantClass(vector3 a_v3Center, float a_fSize);
	/*
	USAGE: Copy Constructor
	ARGUMENTS: class object to copy
	OUTPUT: class object instance
	*/
	OctantClass(OctantClass const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS: class object to copy
	OUTPUT: ---
	*/
	OctantClass& operator=(OctantClass const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~OctantClass(void);
	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- OctantClass& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(OctantClass& other);
	/*
	USAGE: Gets this octant's size
	ARGUMENTS: ---
	OUTPUT: size of octant
	*/
	float GetSize(void);
	/*
	USAGE: Gets the center of the octant in global scape
	ARGUMENTS: ---
	OUTPUT: Center of the octant in global space
	*/
	vector3 GetCenterGlobal(void);
	/*
	USAGE: Gets the min corner of the octant in global space
	ARGUMENTS: ---
	OUTPUT: Minimum in global space
	*/
	vector3 GetMinGlobal(void);
	/*
	USAGE: Gets the max corner of the octant in global space
	ARGUMENTS: ---
	OUTPUT: Maximum in global space
	*/
	vector3 GetMaxGlobal(void);
	/*
	USAGE: Asks if there is a collision with the BO specified by index from
	the Bounding Object Manager
	ARGUMENTS:
	- int a_nBOIndex -> Index of the BO in the BO Manager
	OUTPUT: check of the collision
	*/
	bool IsColliding(uint a_nBOIndex);
	/*
	USAGE: Displays the Octant volume specified by index including the objects underneath
	ARGUMENTS:
	- uint a_nIndex -> Octant to be displayed.
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void Display(uint a_nIndex, vector3 a_v3Color = REYELLOW);
	/*
	USAGE: Displays the Octant volume in the color specified
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void Display(vector3 a_v3Color = REYELLOW);
	/*
	USAGE: Displays the non empty leafs in the octree
	ARGUMENTS:
	- vector3 a_v3Color = REYELLOW -> Color of the volume to display.
	OUTPUT: ---
	*/
	void DisplayLeafs(vector3 a_v3Color = REYELLOW);
	/*
	USAGE: Clears the BO list for each node
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ClearBOList(void);
	/*
	USAGE: allocates 8 smaller octants in the child pointers
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Subdivide(void);
	/*
	USAGE: returns the child specified in the index
	ARGUMENTS: uint a_nChild -> index of the child (from 0 to 7)
	OUTPUT: OctantClass object (child in index)
	*/
	OctantClass* GetChild(uint a_nChild);
	/*
	USAGE: returns the parent of the octant
	ARGUMENTS: ---
	OUTPUT: OctantClass object (parent)
	*/
	OctantClass* GetParent(void);
	/*
	USAGE: Asks the Octant if it does not contain any children (its a leaf)
	ARGUMENTS: ---
	OUTPUT: It contains no children
	*/
	bool IsLeaf(void);
	/*
	USAGE: Asks the Octant if it contains more than this many Bounding Objects
	ARGUMENTS:
	- uint a_nBOs -> Number of BOs to query
	OUTPUT: It contains at least this many BOs
	*/
	bool ContainsMoreThan(uint a_nBOs);
	/*
	USAGE: Deletes all children and the children of their children (almost sounds apocalyptic)
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void KillBranches(void);
	/*
	USAGE: Creates a tree using subdivisions, the max number of objects and levels
	ARGUMENTS: 
	- uint a_nMaxLevel = 3 -> Sets the maximum level of the tree while constructing it
	OUTPUT: ---
	*/
	void ConstructTree(uint a_nMaxLevel = 3);
	/*
	USAGE: Traverse the tree up to the leafs and sets the objects in them to the index
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void AssignIDtoBO(void);
	/*
	USAGE: Check the collision in objects under them, if they are colliding a flag can be enabled for display
	ARGUMENTS:
	- int a_nBODisplay = BD_NONE -> display collisions option
	OUTPUT: ---
	*/
	void CheckCollisions(int a_nBODisplay = BD_NONE);
private:
	/*
	USAGE: Deallocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Allocates member fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
	/*
	USAGE: Traverse the tree up to the leafs and check the collision in objects under them
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void TraverseForCollisions(int a_nBODisplay);
	/*
	USAGE: creates the list of all leafs that contains objects.
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ConstructList(void);
};

}

#endif //__OCTANTCLASS_H_