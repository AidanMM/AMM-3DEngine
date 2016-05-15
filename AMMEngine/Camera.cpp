#include "Camera.h"

// Camera
Camera* Camera::m_pInstance = nullptr;

Camera* Camera::GetInstance()
{
	if (m_pInstance == nullptr)
	{
		m_pInstance = new Camera();
	}
	return m_pInstance;
}
void Camera::ReleaseInstance()
{
	if (m_pInstance != nullptr)
	{
		delete m_pInstance;
		m_pInstance = nullptr;
	}
}

void Camera::Init(void)
{
	m_bFPS = true;

	m_fFOV = 45.0f;

	m_v2NearFar = glm::vec2(0.001f, 1000.0f);

	m_v3Position = glm::vec3(0.0f, 0.0f, 5.0f);
	m_v3Target = glm::vec3(0.0f, 0.0f, 0.0f);
	m_v3Top = glm::vec3(0.0f, 1.0f, 0.0f);

	m_v3Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_v3Upward = glm::vec3(0.0f, 1.0f, 0.0f);
	m_v3Rightward = glm::vec3(1.0f, 0.0f, 0.0f);

	m_v3PitchYawRoll = glm::vec3(0.0f);

	m_m4Projection = glm::mat4(1.0f);
	m_m4View = glm::mat4(1.0f);
}
void Camera::Swap(Camera& other)
{
	std::swap(m_bFPS, other.m_bFPS);

	std::swap(m_fFOV, other.m_fFOV);

	std::swap(m_v2NearFar, other.m_v2NearFar);

	std::swap(m_v3Position, other.m_v3Position);
	std::swap(m_v3Target, other.m_v3Target);
	std::swap(m_v3Top, other.m_v3Top);

	std::swap(m_v3Forward, other.m_v3Forward);
	std::swap(m_v3Upward, other.m_v3Upward);
	std::swap(m_v3Rightward, other.m_v3Rightward);

	std::swap(m_v3PitchYawRoll, other.m_v3PitchYawRoll);

	std::swap(m_m4Projection, other.m_m4Projection);
	std::swap(m_m4View, other.m_m4View);
}
void Camera::Release(void) {}
//The big 3
Camera::Camera()
{
	Init();
	CalculateProjection();
}
Camera::Camera(Camera const& other)
{
	m_bFPS = other.m_bFPS;

	m_fFOV = other.m_fFOV;

	m_v2NearFar = other.m_v2NearFar;

	m_v3Position = other.m_v3Position;
	m_v3Target = other.m_v3Target;
	m_v3Top = other.m_v3Top;

	m_v3Forward = other.m_v3Forward;
	m_v3Upward = other.m_v3Upward;
	m_v3Rightward = other.m_v3Rightward;

	m_v3PitchYawRoll = other.m_v3PitchYawRoll;

	m_m4Projection = other.m_m4Projection;
	m_m4View = other.m_m4View;
}
Camera& Camera::operator=(Camera const& other)
{
	if (this != &other)
	{
		Release();
		Init();
		Camera temp(other);
		Swap(temp);
	}
	return *this;
}
Camera::~Camera() { Release(); };
//Accessors
glm::vec3 Camera::GetPosition(void) { return m_v3Position; }
glm::mat4 Camera::GetView(void) { CalculateView(); return m_m4View; }
glm::mat4 Camera::GetProjection(void) { CalculateProjection(); return m_m4Projection; }
void Camera::SetNearFarPlanes(float a_fNear, float a_fFar) { m_v2NearFar = glm::vec2(a_fNear, a_fFar); }
void Camera::SetFOV(float a_fFOV) { m_fFOV = a_fFOV; }
void Camera::SetFPS(bool a_bFPS) { m_bFPS = a_bFPS; }
void Camera::SetPosition(glm::vec3 a_v3Position)
{
	m_v3Position = a_v3Position;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(glm::cross(m_v3Rightward, m_v3Forward));
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));

	m_v3Top = m_v3Position + m_v3Upward;
	m_v3Target = m_v3Position + glm::normalize(m_v3Forward);

	CalculateProjection();
}
void Camera::SetTarget(glm::vec3 a_v3Target)
{
	m_v3Target = a_v3Target;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(glm::cross(m_v3Rightward, m_v3Forward));
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));

	m_v3Top = m_v3Position + m_v3Upward;
	m_v3Target = m_v3Position + glm::normalize(m_v3Forward);

	CalculateProjection();
}
glm::mat4 Camera::GetMVP(glm::mat4 a_m4ModelToWorld)
{
	CalculateView();
	CalculateProjection();
	return m_m4Projection * m_m4View * a_m4ModelToWorld;
}
glm::mat4 Camera::GetVP(void)
{
	CalculateView();
	CalculateProjection();
	return m_m4Projection * m_m4View;
}
//--- Non Standard Singleton Methods
void Camera::CalculateProjection(void)
{
	float fRatio = 1920.0f / 1080.0f;
	float fPos = 0;
	m_m4Projection = glm::perspective(m_fFOV, fRatio, m_v2NearFar.x, m_v2NearFar.y);
}
void Camera::CalculateView(void)
{
	//Calculate the Forward again
	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	//Determine axis for pitch rotation
	m_v3Rightward = glm::cross(m_v3Forward, m_v3Upward);
	//Compute glm::quat for pitch based on the camera pitch angle
	glm::quat qPitch = glm::angleAxis(m_v3PitchYawRoll.x, m_v3Rightward);
	//Compute glm::quat for Yaw based on the camera pitch angle
	glm::quat qYaw = glm::angleAxis(m_v3PitchYawRoll.y, m_v3Upward);
	//Compute glm::quat for Roll based on the camera pitch angle
	glm::quat qRoll = glm::angleAxis(m_v3PitchYawRoll.z, m_v3Forward);

	//Add the glm::quats
	glm::quat qTemp = glm::cross(qPitch, qYaw);
	//update the direction from the glm::quat
	m_v3Forward = glm::rotate(qTemp, m_v3Forward);


	//This will affect all of the other directions, generally speaking you do not want that other than in flight games
	if (m_bFPS == false)
	{
		qTemp = glm::cross(qRoll, qPitch);
		m_v3Upward = glm::rotate(qTemp, m_v3Upward);

		qTemp = glm::cross(qYaw, qRoll);
		m_v3Rightward = glm::rotate(qTemp, m_v3Rightward);
	}

	//set the look at to be in front of the camera
	m_v3Target = m_v3Position + m_v3Forward;
	m_v3Top = m_v3Position + m_v3Upward;

	//Damping for a smooth camera
	m_v3PitchYawRoll *= 0.5f;

	//Calculate the look at
	m_m4View = glm::lookAt(m_v3Position, m_v3Target, m_v3Upward);
}
void Camera::MoveForward(float a_fDistance)
{
	m_v3Position += m_v3Forward * a_fDistance;
	m_v3Target += m_v3Forward * a_fDistance;
	m_v3Top += m_v3Forward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Top - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
}
void Camera::MoveVertical(float a_fDistance)
{
	m_v3Position += m_v3Upward * a_fDistance;
	m_v3Target += m_v3Upward * a_fDistance;
	m_v3Top += m_v3Upward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Top - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
}
void Camera::MoveSideways(float a_fDistance)
{
	m_v3Position += m_v3Rightward * a_fDistance;
	m_v3Target += m_v3Rightward * a_fDistance;
	m_v3Top += m_v3Rightward * a_fDistance;

	m_v3Forward = glm::normalize(m_v3Target - m_v3Position);
	m_v3Upward = glm::normalize(m_v3Top - m_v3Position);
	m_v3Rightward = glm::normalize(glm::cross(m_v3Forward, m_v3Upward));
}
void Camera::ChangePitch(float a_fDegree)
{
	m_v3PitchYawRoll.x += a_fDegree;
}
void Camera::ChangeYaw(float a_fDegree)
{
	m_v3PitchYawRoll.y += a_fDegree;
}
void Camera::ChangeRoll(float a_fDegree)
{
	m_v3PitchYawRoll.z += a_fDegree;
}
void Camera::SetPositionAndTarget(glm::vec3 a_v3Position, glm::vec3 a_v3Target)
{
	SetPosition(a_v3Position);
	SetTarget(a_v3Target);
}
void Camera::ResetCamera(void)
{
	m_v3PitchYawRoll = glm::vec3(0.0f);

	m_v3Position = glm::vec3(0.0f, 0.0f, 10.0f);
	m_v3Target = glm::vec3(0.0f, 0.0f, 9.0f);
	m_v3Top = glm::vec3(0.0f, 1.0f, 10.0f);

	m_v3Forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_v3Upward = glm::vec3(0.0f, 1.0f, 0.0f);
	m_v3Rightward = glm::vec3(1.0f, 0.0f, 0.0f);
}
//glm::mat4 Camera::GetCameraSpaceAdjusted(void)
//{
//	CalculateView();
//	return glm::inverse(m_m4Projection) * glm::translate(glm::vec3(0.0f, 0.0f, -1.2085f));
//}
//glm::mat4 Camera::GetCameraPlane(void)
//{
//	SystemSingleton* pSystem = SystemSingleton::GetInstance();
//	float fSize = pSystem->GetWindowWidth() / static_cast<float>(pSystem->GetWindowHeight());
//	return GetCameraSpaceAdjusted() * glm::translate(glm::vec3(0.0f, 0.0f, -1.2085f)) * glm::scale(glm::vec3(fSize, 1.0f, 0.0f));
//}