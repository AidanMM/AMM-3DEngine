/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __BoundingObjectCLASS_H_
#define __BoundingObjectCLASS_H_

#include "RE\Mesh\PrimitiveManagerSingleton.h"
using namespace ReEng;
//System Class
class ReEngDLL BoundingObjectClass 
{
	PrimitiveManagerSingleton* m_pPrimitiveMngr = nullptr;

	bool m_bVisibleOBB = false;		//Visibility of the Oriented Bounding Box
	bool m_bVisibleAABB = false;	//Visibility of the Axis Aligned Bounding Box
	bool m_bVisibleBS = false;		//Visibility of the Bounding Sphere

	float m_fRadius = 0.0f; //Radius of the Bounding Object

	vector3 m_v3ColorAABB;	//Color of the Axis (Re)Aligned Bounding Box
	vector3 m_v3ColorOBB;	//Color of the Oriented Bounding Box
	vector3 m_v3ColorBS;	//Color of the Bounding Sphere

	vector3 m_v3CenterL = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinL = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxL = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3CenterG = vector3(0.0f); //Will store the center point of the Object Class
	vector3 m_v3MinG = vector3(0.0f); //Will store the minimum vector of the Object Class
	vector3 m_v3MaxG = vector3(0.0f); //Will store the maximum vector of the Object Class

	vector3 m_v3HalfWidth = vector3(0.0f);//Will store half the size of all sides
	vector3 m_v3HalfWidthG = vector3(0.0f);//Will store half the size of all sides

	matrix4 m_m4ToWorld = IDENTITY_M4; //Matrix that will take us from local to world coordinate

public:
	/*
	USAGE: Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass(void);
	/*
	USAGE: Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass(std::vector<vector3> a_lVertex);
	/*
	USAGE: Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass(vector3 a_v3Center, float a_fSize);
	/*
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass(BoundingObjectClass const& other);
	/*
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	BoundingObjectClass& operator=(BoundingObjectClass const& other);
	/*
	USAGE: Destructor
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~BoundingObjectClass(void);
	/*
	USAGE: Gets the "ModelToWorld" matrix associated with the bounding box
	ARGUMENTS: ---
	OUTPUT:
	*/
	matrix4 GetModelMatrix(void);
	/*
	USAGE: Sets the Bounding Object into world coordinates
	ARGUMENTS:
	- matrix4 a_m4ToWorld -> Model to World matrix
	OUTPUT: ---
	*/
	void SetModelMatrix(matrix4 a_m4ToWorld);
	/*
	USAGE: Sets the visibility of the OBB the AABB and the BS
	ARGUMENTS:
	- int a_nRenderOption = REBODISPLAY::BD_NONE \ Options BD_BS | BD_OB | BD_AB
	OUTPUT: ---
	*/
	void SetVisible(int a_nRenderOption = REBODISPLAY::BD_NONE);
	/*
	USAGE: Sets the visibility of the OBB
	ARGUMENTS:
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT: ---
	*/
	void SetVisibleOBB(bool a_bVisible);
	/*
	USAGE: Gets the visibility of the OBB
	ARGUMENTS:
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT:
	*/
	bool GetVisibleOBB(void);
	/*
	USAGE: Sets the visibility of the AABB
	ARGUMENTS:
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT: ---
	*/
	void SetVisibleAABB(bool a_bVisible);
	/*
	USAGE: Gets the visibility of the AABB
	ARGUMENTS: 
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT:
	*/
	bool GetVisibleAABB(void);
	/*
	USAGE: Sets the visibility of the BS
	ARGUMENTS:
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT: ---
	*/
	void SetVisibleBS(bool a_bVisible);
	/*
	USAGE: Gets the visibility of the OBB
	ARGUMENTS:
	- bool a_bVisible -> true for draw false for not draw
	OUTPUT:
	*/
	bool GetVisibleBS(void);
	/*
	USAGE: Gets the color vector of the AABB
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetColorAABB(void);
	/*
	USAGE: Sets the color vector of the AABB
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetColorAABB(vector3 a_v3Color);
	/*
	USAGE: Gets the color vector of the OBB
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetColorOBB(void);
	/*
	USAGE: Sets the color vector of the OBB
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetColorOBB(vector3 a_v3Color);
	/*
	USAGE: Gets the color vector of the BS
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetColorBS(void);
	/*
	USAGE: Sets the color vector of the BS
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetColorBS(vector3 a_v3Color);
	/*
	USAGE: Gets the centroid of the Bounding object in Local coordinates
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetCentroidLocal(void);
	/*
	USAGE: Gets the centroid of the Bounding object in Global coordinates
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetCentroidGlobal(void);
	/*
	USAGE: Gets the HalfWidth vector of the object (half the size of each side)
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetHalfWidth(void);
	/*
	USAGE: Gets the Radius size of the Bounding Sphere
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetRadius(void);
	/*
	USAGE: Calculates the Oriented Bounding Box, Axis Alligned Bounding Box and the Bounding Sphere from the instance
	ARGUMENTS:
	- std::vector<vector3> a_lVertex -> The vertices for which we want to create the BO from
	OUTPUT: ---
	*/
	void Initializate(std::vector<vector3> a_lVertex);
	/*
	USAGE: Determines the collision with an incoming object using the SAT
	ARGUMENTS:
	- MyBOClass* const a_pOther -> Other object to check collision with
	OUTPUT: result of the collision
	*/
	bool SAT(BoundingObjectClass* const a_pOther);
	/*
	USAGE: Asks if there is a collision with another Bounding Object object
	ARGUMENTS:
	- MyBOClass* const a_pOther -> Other object to check collision with
	OUTPUT: check of the collision
	*/
	bool IsColliding(BoundingObjectClass* const a_pOther);
	/*
	 USAGE: Test against a ray
	ARGUMENTS:
	- vector3 a_v3RayOrigin -> The origin of the ray
	- vector3 a_v3RayDirection -> The direction in which the ray is moving
	- float& a_fDistance -> the distance in which the collision is happening from the origin
	OUTPUT:
	*/
	bool IsColliding(vector3 a_v3RayOrigin, vector3 a_v3RayDirection, float& a_fDistance);
	/*
	USAGE:Renders the bounding box
	ARGUMENTS:
	- a_v3Color -> determinate the color of the box to be rendered, if REDEFAULT
	-- it will render the shape in the constructed color (white)
	OUTPUT: ---
	*/
	void AddToRenderList(bool bForceDraw = false);
	/*
	USAGE: Gets the Max vector of the AABB in global space
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetAABBMax(void);
	/*
	USAGE: Gets the Min vector of the AABB in global space
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetAABBMin(void);
	/*
	USAGE: Displays the Bounding Sphere of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void AddBOToRenderList(vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Displays the Oriented Bounding Box of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void AddOBToRenderList(vector3 a_v3Color = REDEFAULT);
	/*
	USAGE: Displays the ReAlligned Bounding Box of the BO in the specified color
	ARGUMENTS:
	- vector3 a_v3Color = REDEFAULT -> Color of the Object to display if the value is REDEFAULT it
	-- will display Objects in white and colliding ones in red.
	OUTPUT: ---
	*/
	void AddABToRenderList(vector3 a_v3Color = REDEFAULT);

	/*
	USAGE: Changes object contents for other object's
	ARGUMENTS:
	- BOClass& other -> object to swap content from
	OUTPUT: ---
	*/
	void Swap(BoundingObjectClass& other);

private:
	/*
	USAGE: Released Memory and objects allocated.
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
	USAGE: Calculates the Axis Aligned Bounding Box from the instance from the OBB
	ARGUMENTS:
	OUTPUT: ---
	*/
	void CalculateAABB(void);
};

//EXPIMP_TEMPLATE template class ReEngDLL std::vector<BoundingObjectClass>;
//EXPIMP_TEMPLATE template class ReEngDLL std::vector<BoundingObjectClass*>;

#endif //__BoundingObjectClass_H__