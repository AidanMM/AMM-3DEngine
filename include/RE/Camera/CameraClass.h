/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/10
----------------------------------------------*/
#ifndef __CAMERACLASS_H_
#define __CAMERACLASS_H_

#include "RE\system\SystemSingleton.h"

namespace ReEng
{
	//Camera Class
	class ReEngDLL CameraClass
	{
		bool m_bFPS = true; //If set to false will behave like a flight simulator camera

		CAMERAMODE m_nMode = CAMERAMODE::CAMPERSP; //Sets the mode the camera will display

		float m_fFOV = 45.0f;

		vector2 m_v2NearFar = vector2(0.001f, 1000.0f);

		vector3 m_v3Position = vector3(0.0f, 0.0f, 5.0f);
		vector3 m_v3Target = vector3(0.0f, 0.0f, 0.0f);
		vector3 m_v3Top = vector3(0.0f, 1.0f, 0.0f);

		vector3 m_v3Forward = vector3(0.0f, 0.0f, -1.0f);
		vector3 m_v3Upward = vector3(0.0f, 1.0f, 0.0f);
		vector3 m_v3Rightward = vector3(1.0f, 0.0f, 0.0f);

		vector3 m_v3PitchYawRoll = vector3(0.0f);

		matrix4 m_m4Projection = matrix4(1.0f);
		matrix4 m_m4View = matrix4(1.0f);

	public:
		/*
		USAGE: Constructor
		ARGUMENTS: ---
		OUTPUT: class object
		*/
		CameraClass(void);
		/*
		USAGE: Constructor with parameters
		ARGUMENTS:
		OUTPUT:
		*/
		CameraClass(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
		/*
		USAGE: Copy Constructor
		ARGUMENTS:
		OUTPUT:
		*/
		CameraClass(CameraClass const& other);
		/*
		USAGE: Copy Assignment Operator
		ARGUMENTS:
		OUTPUT:
		*/
		CameraClass& operator=(CameraClass const& other);
		/*
		USAGE: Destructor
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		~CameraClass(void);
		/*
		USAGE: Gets the View matrix from the camera
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetViewMatrix(void);
		/*
		USAGE: Gets the Projection matrix from the camera
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetProjectionMatrix(void);
		/*
		USAGE: Gets the ModelViewProjection matrix from the camera
		ARGUMENTS:
		OUTPUT:
		*/
		matrix4 GetMVP(matrix4 a_m4ModelToWorld);
		/*
		USAGE: Gets the ViewProjection matrix from the camera
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetVP(void);
		/*
		USAGE:  Gets the position of the camera
		ARGUMENTS: ---
		OUTPUT:
		*/
		vector3 GetPosition(void);
		/*
		USAGE: Changes the near and far planes
		ARGUMENTS:
		OUTPUT:
		*/
		void SetNearFarPlanes(float a_fNear, float a_fFar);
		/*
		USAGE: Calculates the projection based on the camera values
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CalculateProjection(void);
		/*
		USAGE: Calculates the view based on the camera values
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void CalculateView(void);
		/*
		USAGE: Set Field of View
		ARGUMENTS:
		OUTPUT:
		*/
		void SetFOV(float a_fFOV);
		/*
		USAGE: Sets the camera at the specified position
		ARGUMENTS:
		OUTPUT:
		*/
		void SetPosition(vector3 a_v3Position);
		/*
		USAGE: Sets the target of the camera to the specified position
		ARGUMENTS:
		- vector3 a_vTarget -> point to look at
		OUTPUT:
		*/
		void SetTarget(vector3 a_v3Target);
		/*
		USAGE: Sets the camera at the specified position and target
		ARGUMENTS:
		OUTPUT:
		*/
		void SetPositionTargetAndView(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
		/*
		USAGE: Translates from mouse coordinates (inside of window) to world space
		ARGUMENTS: 
		- uint a_nMouseX
		- uint a_nMouseY
		OUTPUT: Click Position in World space
		*/
		vector3 GetClickOnWorldSpace(uint a_nMouseX, uint a_nMouseY);
		/*
		USAGE: Get where in the window you clicked and the direction that click would take you
		ARGUMENTS:
		- uint a_nMouseX
		- uint a_nMouseY
		OUTPUT: pair of start and direction
		*/
		std::pair<vector3,vector3> GetClickAndDirectionOnWorldSpace(uint a_nMouseX, uint a_nMouseY);
		/*
		USAGE: Gets the space on which the camera is located on the global space
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetCameraSpace(void);
		/*
		USAGE: Gets the space just in front of the camera in global space
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetCameraSpaceAdjusted(void);
		/*
		USAGE: Gets the plane space just in front of the camera
		ARGUMENTS: ---
		OUTPUT:
		*/
		matrix4 GetCameraPlane(void);
		/*
		USAGE: Translates the camera forward or backward
		ARGUMENTS: 
		OUTPUT: ---
		*/
		void MoveForward(float a_fDistance = 0.1f);
		/*
		USAGE: Translates the camera Upward or downward
		ARGUMENTS: 
		OUTPUT: ---
		*/
		void MoveVertical(float a_fDistance = 0.1f);
		/*
		USAGE: Translates the camera right or left
		ARGUMENTS:
		OUTPUT: ---
		*/
		void MoveSideways(float a_fDistance = 0.1f);
		/*
		USAGE: Rotates the camera Pitch
		ARGUMENTS: 
		OUTPUT: ---
		*/
		void ChangePitch(float a_fDegree = 0.01f);
		/*
		USAGE: Rotates the camera Yaw
		ARGUMENTS:
		OUTPUT: ---
		*/
		void ChangeYaw(float a_fDegree = 0.01f);
		/*
		USAGE: Rotates the camera Roll
		ARGUMENTS:
		OUTPUT: ---
		*/
		void ChangeRoll(float a_fDegree = 0.01f);
		/*
		USAGE: Sets the camera in First Person Shooter mode, if false it will work like an aircraft
		ARGUMENTS:
		OUTPUT: ---
		*/
		void SetFPS(bool a_bFPS = true);
		/*
		USAGE: Sets the camera in Perspective mode, if false it will work as an orthographic camera
		ARGUMENTS:
		OUTPUT:
		*/
		void SetCameraMode(CAMERAMODE a_nMode = CAMERAMODE::CAMPERSP);
		/*
		USAGE: Returns the current value for the camera mode
		ARGUMENTS: ---
		OUTPUT:
		*/
		CAMERAMODE GetCameraMode(void);
		/*
		USAGE: Resets the value of the camera
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void ResetCamera(void);

	private:
		/*
		USAGE: Releases the object from memory
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Release(void);
		/*
		USAGE: Initialize the object's fields
		ARGUMENTS: ---
		OUTPUT: ---
		*/
		void Init(vector3 a_v3Position, vector3 a_v3Target, vector3 a_v3Upward);
		/*
		USAGE: Swaps the contents of the object with another object's content
		ARGUMENTS:
		OUTPUT: ---
		*/
		void Swap(CameraClass& other);
	};

	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass>;
	EXPIMP_TEMPLATE template class ReEngDLL std::vector<CameraClass*>;
}
#endif //__CAMERACLASS_H_