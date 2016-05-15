/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVEMANAGERSINGLETON_H_
#define __PRIMITIVEMANAGERSINGLETON_H_

#include "RE\Mesh\PrimitiveClass.h"
#include "RE\Mesh\PrimitiveWireClass.h"
#include "RE\Mesh\MeshDrawerSingleton.h"


namespace ReEng
{

//System Class
class ReEngDLL PrimitiveManagerSingleton
{
	static PrimitiveManagerSingleton* m_pInstance; // Singleton of the class

	MeshClass* m_pAxis = nullptr; //Axis primitive
	MeshClass* m_pGrid = nullptr; //Grid primitive
	MeshClass* m_pLine = nullptr; //Line primitive
	MeshClass* m_pPlane = nullptr; //Plane primitive
	MeshClass* m_pCube = nullptr; //Cube primitive
	MeshClass* m_pCubeWire = nullptr; //Cube Wire primitive
	MeshClass* m_pCone = nullptr; //Cone primitive
	MeshClass* m_pConeWire = nullptr; //Cone Wire primitive
	MeshClass* m_pCylinder = nullptr; //Cylinder primitive
	MeshClass* m_pCylinderWire = nullptr; //Cylinder Wire primitive
	MeshClass* m_pTube = nullptr; //Tube primitive
	MeshClass* m_pTubeWire = nullptr; //Tube Wire primitive
	MeshClass* m_pTorus = nullptr; //Torus primitive
	MeshClass* m_pTorusWire = nullptr; //Torus Wire primitive
	MeshClass* m_pSphere = nullptr;//Sphere primitive
	MeshClass* m_pSphereWire = nullptr;//Sphere Wire primitive
	MeshClass* m_pHexagon = nullptr;//Hexagon primitive
	MeshClass* m_pHexagonWire = nullptr;//Hexagon Wire primitive

	MeshDrawerSingleton* m_pMeshDrawer = nullptr;

public:
	/*
	USAGE: Gets/Constructs the singleton pointer
	ARGUMENTS:
	OUTPUT:
	*/
	static PrimitiveManagerSingleton* GetInstance();
	/*
	USAGE: Destroys the singleton
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/*
	USAGE: Render the axis on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddAxisToQueue(matrix4 a_m4ToWorld);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddPlaneToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Renders the cube on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddCubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the cone on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddConeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the cylinder on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddCylinderToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the tube on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddTubeToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the torus on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddTorusToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders a hexagon on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddHexagonToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	MeshClass* AddSphereToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT, int a_RenderOption = RERENDER::SOLID | RERENDER::WIRE);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	void AddGridToQueue(float a_fSize = 1.0f, int a_Axis = REAXIS::XY, vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Renders the sphere on the specified position
	ARGUMENTS:
	OUTPUT: returns the pointer to mesh used in the queue
	*/
	void AddLineToQueue(vector3 a_v3Start, vector3 a_v3End, vector3 a_v3StartColor = REDEFAULT, vector3 a_v3EndColor = REDEFAULT);
	/*
	USAGE: Renders a camera shape on the specified position
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddCameraToQueue(matrix4 a_m4ToWorld, vector3 a_v3Color = REDEFAULT);
	
private:
	/*
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	PrimitiveManagerSingleton(void);
	/*
	USAGE: Copy constructor
	ARGUMENTS:
	OUTPUT:
	*/
	PrimitiveManagerSingleton(PrimitiveManagerSingleton const& other);
	/*
	USAGE: Copy Assignment operator
	ARGUMENTS:
	OUTPUT:
	*/
	PrimitiveManagerSingleton& operator=(PrimitiveManagerSingleton const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~PrimitiveManagerSingleton(void);
	/*
	USAGE: Releases the objects memory
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Release(void);
	/*
	USAGE: Initializates the objects fields
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void Init(void);
};

}

#endif //__PRIMITIVEMANAGERSINGLETON_H_