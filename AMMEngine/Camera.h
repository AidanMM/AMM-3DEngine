#pragma once

#include <glm\gtc\matrix_transform.hpp>
#include <SFML\Graphics.hpp>
#include <glm\gtx\quaternion.hpp>

/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Programmer: Tal Cohen (tsc1510@rit.edu)
Date: 2015/10
----------------------------------------------*/

//Camera Class
class Camera
{
	bool m_bFPS = false; //If set to false will behave like a flight simulator camera

	float m_fFOV = 45.0f;

	glm::vec2 m_v2NearFar = glm::vec2(0.001f, 1000.0f);

	glm::vec3 m_v3Position = glm::vec3(0.0f, 0.0f, 5.0f);
	glm::vec3 m_v3Target = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 m_v3Top = glm::vec3(0.0f, 1.0f, 0.0f);

	glm::vec3 m_v3Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 m_v3Upward = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 m_v3Rightward = glm::vec3(1.0f, 0.0f, 0.0f);

	glm::vec3 m_v3PitchYawRoll = glm::vec3(0.0f);

	glm::mat4 m_m4Projection = glm::mat4(1.0f);
	glm::mat4 m_m4View = glm::mat4(1.0f);

	static Camera* m_pInstance; // Singleton pointer

private:
	/*
	CameraClass
	USAGE: Constructor
	ARGUMENTS: ---
	OUTPUT: class object
	*/
	Camera(void);
	/* Copy Constructor */
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Camera(Camera const& other);
	/* Copy Assignment Operator*/
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	Camera& operator=(Camera const& other);
	/* Destructor */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	~Camera(void);

public:
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	static Camera* GetInstance();
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	static void ReleaseInstance(void);
	/* Gets the View matrix from the camera */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::mat4 GetView(void);
	/* Gets the Projection matrix from the camera */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::mat4 GetProjection(void);
	/* Gets the ModelViewProjection matrix from the camera */
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	glm::mat4 GetMVP(glm::mat4 a_m4ModelToWorld);
	/* Gets the ViewProjection matrix from the camera */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::mat4 GetVP(void);

	/* Gets the position of the camera */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::vec3 GetPosition(void);

	/* Changes the near and far planes */
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetNearFarPlanes(float a_fNear, float a_fFar);
	/* Calculates the projection based on the camera values */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateProjection(void);
	/* Calculates the view based on the camera values */
	/*

	USAGE:
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void CalculateView(void);
	/* Set Field of View */
	/*

	USAGE:
	ARGUMENTS:
	OUTPUT:
	*/
	void SetFOV(float a_fFOV);

	/*

	USAGE: Sets the camera at the specified position
	ARGUMENTS:
	OUTPUT:
	*/
	void SetPosition(glm::vec3 a_v3Position);
	/*

	USAGE: Sets the target of the camera to the specified position
	ARGUMENTS:
	glm::vec3 a_vTarget -> point to look at
	OUTPUT:
	*/
	void SetTarget(glm::vec3 a_v3Target);
	/*

	USAGE: Sets the camera at the specified position and target
	ARGUMENTS:
	OUTPUT:
	*/
	void SetPositionAndTarget(glm::vec3 a_v3Position, glm::vec3 a_v3Target);

	/*

	USAGE: Gets the camera space just in front of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::mat4 GetCameraSpaceAdjusted(void);

	/*

	USAGE: Gets the camera plane of the camera
	ARGUMENTS: ---
	OUTPUT:
	*/
	glm::mat4 GetCameraPlane(void);

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
	void SetFPS(bool a_bFPS = false);
	
	/*

	USAGE: Resets the value of the camera
	ARGUMENTS: ---
	OUTPUT: ---
	*/
	void ResetCamera(void);

	glm::vec3 GetForward(void) { return m_v3Forward; }
	glm::vec3 GetRightward(void) { return m_v3Rightward; }
	glm::vec2 GetNearFarPlanes(void) { return m_v2NearFar; }

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
	void Init(void);

	/*

	USAGE: Swaps the contents of the object with another object's content
	ARGUMENTS:
	OUTPUT: ---
	*/
	void Swap(Camera& other);
};
