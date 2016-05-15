/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __PRIMITIVEWIRECLASS_H_
#define __PRIMITIVEWIRECLASS_H_

#include "RE\Mesh\MeshClass.h"

namespace ReEng
{

class ReEngDLL PrimitiveWireClass : public MeshClass
{
	typedef MeshClass super;

	float m_fSpotCount; // To be used with the grid;

public:
	/*
	 PrimitiveWireClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	PrimitiveWireClass();
	/* Copy Constructor */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	PrimitiveWireClass(const PrimitiveWireClass& other);
	/* Copy Assignment Operator */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	virtual PrimitiveWireClass& operator=(const PrimitiveWireClass& other);

	/* Destructor */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~PrimitiveWireClass(void);

	/* Generates an Axis shape */
	/*
	 USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void GenerateAxis(void);
	/* Generates a cube shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateCube(float a_fSize, vector3 a_v3Color);
	/* Generates a cone shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a cylinder shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a Tube shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a Torus shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionHeigh, int a_nSubdivisionAxis, vector3 a_v3Color);
	/* Generates a sphere shape */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color);
	/* Generates a Grid object */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateGrid(float a_fReticuleSpots = 1000.0f, vector3 a_v3Color = vector3(0.7f, 0.7f, 0.7f));
	/* Generates a Line object */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void GenerateLine(vector3 a_v3StartColor = REWHITE, vector3 a_v3EndColor = REWHITE);

	///* Renders the primitive asking for its position in the world and a color */
	//virtual void Render(matrix4 a_m4ToWorld, vector3 a_v3Color);
	///* Renders the primitive asking for its position in the world */
	//virtual void Render(matrix4 a_m4ToWorld);

private:
	/* Compiles the object with an specific color and name */
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void CompileObject(vector3 a_v3Color, String a_sName);
	/* Adds a quad to the list points in the buffer to be compiled*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight);
	/* Adds a tri to the list points in the buffer to be compiled*/
	/*
	 USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTop);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveWireClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<PrimitiveWireClass*>;

}

#endif //__PRIMITIVEWIRECLASS_H_