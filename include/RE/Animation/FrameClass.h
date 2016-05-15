/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __FRAMECLASS_H_
#define __FRAMECLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{

class ReEngDLL FrameClass
{
	bool m_bKeyframe = true;
	bool m_bVisible = true;
	vector3 m_v3Translation = vector3(0.0f);
	vector3 m_v3Rotation = vector3(0.0f);
	vector3 m_v3Scale = vector3(1.0f);
	matrix4 m_m4Transformation = matrix4(1.0f);
public:
	
	/*
	 FrameClass
	USAGE: constructor
	ARGUMENTS: ---
	OUTPUT:
	*/
	FrameClass();
	/*
	 FrameClass
	USAGE: Copy Constructor
	ARGUMENTS:
	OUTPUT:
	*/
	FrameClass(const FrameClass& other);
	/*
	 operator=
	USAGE: Copy Assignment Operator
	ARGUMENTS:
	OUTPUT:
	*/
	virtual FrameClass& operator=(const FrameClass& other);
	/*
	 ~FrameClass
	USAGE: Destructor
	ARGUMENTS:  ---
	OUTPUT: ---
	*/
	~FrameClass(void);
	/*
	 GetTransformation
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	matrix4 GetTransformation(void);
	/*
	 ComputeTransformation
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 ComputeTransformation(	vector3 a_v3Translation,
									vector3 a_v3Pivot,
									vector3 a_v3Rotation,
									vector3 a_v3Scale,
									bool a_bVisible,
									bool a_bKeyFrame,
									matrix4 a_m4ToParent = matrix4(1.0f));
	/*
	 ComputeTransformation
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 ComputeTransformation(matrix4 a_m4ToParent);
	/*
	 ComputeTransformation
	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	matrix4 ComputeTransformation(vector3 a_v3Pivot);
	/*
	 IsKeyframe
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsKeyframe(void);
	/*
	 SetVisible
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	void SetVisible(bool a_bVisible);
	/*
	 IsVisible
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	bool IsVisible(void);
	/*
	 SetKeyframe
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	void SetKeyframe(bool a_bKeyframe);
	/*
	 SetPosX
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosX( float a_fValue );
	/*
	 SetPosY
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosY( float a_fValue );
	/*
	 SetPosZ
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetPosZ( float a_fValue );
	/*
	 SetAngX
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngX( float a_fValue );
	/*
	 SetAngY
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngY( float a_fValue );
	/*
	 SetAngZ
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetAngZ( float a_fValue );
	/*
	 SetSizeX
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeX( float a_fValue );
	/*
	 SetSizeY
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeY( float a_fValue );
	/*
	 SetSizeZ
	USAGE:
	ARGUMENTS:
	OUTPUT: ---
	*/
	void SetSizeZ( float a_fValue );
	/*
	 GetPos
	USAGE: Gets the Position
	ARGUMENTS:
	OUTPUT: ---
	*/
	vector3 GetPos(void);
	/*
	 GetAng
	USAGE: Gets the Rotation
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetAng(void);
	/*
	 GetSize
	USAGE: Gets the Scale
	ARGUMENTS: ---
	OUTPUT:
	*/
	vector3 GetSize(void);
	/*
	 GetPosX
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetPosX( void );
	/*
	 GetPosY
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetPosY( void );
	/*
	 GetPosZ
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetPosZ( void );
	/*
	 GetAngX
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetAngX( void );
	/*
	 GetAngY
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetAngY( void );
	/*
	 GetAngZ
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetAngZ( void );
	/*
	 GetSizeX
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetSizeX( void );
	/*
	 GetSizeY
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetSizeY( void );
	/*
	 GetSizeZ
	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	float GetSizeZ( void );
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<FrameClass*>;

}
#endif //__ANIMATIONFRAMECLASS_H_