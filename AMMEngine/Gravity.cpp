#include "Gravity.h"

#define distanceScalar 200
#define earthMass 1
#define sunMass 100000
#define REARPROJECTED true

void Gravity::AddAstralBody(GravityObject* toAdd)
{
	astralBodies.push_back(toAdd);
	AddObject(toAdd);
}

glm::vec3 Gravity::CalculateGravitationalForce(GravityObject * first, GravityObject * second)
{
	float force = 0.0f;
	glm::vec3 toSecond = second->m_position - first->m_position;
	float distance = glm::length(toSecond) * distanceScalar;
	if (distance != 0)
		force = (first->m_mass + second->m_mass) / (distance * distance);
	else
		force = 0;
	return toSecond * force;
}

void Gravity::Init()
{
	GameManager::GetInstance()->m_collisionType = BRUTE_FORCE;
	int tries = 0;
	while ((kinect = KinectUtilities::GetInstance()) == nullptr || tries > 100) {
		tries++;
		fprintf(stderr, "Attempting to initializse the kinect...\n");
	}
	kinectIndicator = new BoxObject(5, 5, 5);
	kinectIndicator->m_name = "indicator";
	kinectIndicator->EnableCollision();
	AddObject(kinectIndicator);
	kinectIndicator->m_visible = false;
	kinectIndicator->m_collisionData->m_collisionMask = 0;

	glClearColor(0, 0, 0, 0);
	Camera::GetInstance()->SetPositionAndTarget(glm::vec3(0, 0, 100.0f), glm::vec3(0, 0, 0));
	for (int x = -5; x <= 5; x++)
	{
		if (x == 0)
			continue;
		for (int y = -5; y <= 5; y++)
		{
			if (y == 0)
				continue;
			for (int z = -10; z <= 10; z++)
			{
				if (z == 0)
					continue;
				GravityObject* obj = new GravityObject(8.0, earthMass);
				obj->m_position = glm::vec3(x * 5, y * 5, z * 5);
				AddAstralBody(obj);
			}
		}
	}
	/*GravityObject* obj = new GravityObject(1000.0f, 100.0f);
	obj->m_position = glm::vec3(0,0,0);
	obj->SetColor(glm::vec3(1, 1, 0));
	obj->m_name = "Sun";
	AddAstralBody(obj);*/
	for (int x = -1; x <= 1; x++)
	{
		for (int y = -1; y <= 1; y++)
		{
			if (x == 0 && y == 0)
				continue;
			GravityObject* obj = new GravityObject(sunMass / 4, sunMass);
			obj->m_name = "BlackHole";
			obj->SetColor(glm::vec3(0, 1, 1));
			obj->m_position = glm::vec3(-40.5 * x, 20.5 * y, 0);
			obj->m_collisionData->m_collisionMask = 1;
			AddAstralBody(obj);
		}
	}
}

void Gravity::Update(float dt)
{
	std::vector<GameObject*> blackHoles = GetAllObjectsByName("BlackHole");
	for (int i = 0; i < astralBodies.size(); i++)
	{
		for (int p = 0; p < blackHoles.size(); p++)
		{
			if (i == p)
				continue;
			astralBodies[i]->applyForce(CalculateGravitationalForce(astralBodies[i], dynamic_cast<GravityObject*>(blackHoles[p])));
		}
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_DOWN))
	{
		Camera::GetInstance()->MoveForward(-10.0f);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_UP))
	{
		Camera::GetInstance()->MoveForward(10.0f);
	}
	if (glfwGetKey(GameManager::window, GLFW_KEY_1))
	{
		GameManager::GetInstance()->SetCurrentScene(new Gravity);
	}

	for (int i = 0; i < blackHoles.size(); i++)
	{
		dynamic_cast<GravityObject*>(blackHoles[i])->m_netForce = glm::vec3(0, 0, 0);
	}
	/*
	if (kinect != nullptr)
	{
		kinect->GetKinectData();
		if (kinect->m_tracked == false)
		{
			kinectIndicator->m_visible = false;
			kinectIndicator->m_collisionData->m_collisionMask = 0;
		}
		else {
			kinectIndicator->m_visible = true;
			kinectIndicator->m_collisionData->m_collisionMask = 1;
			if (!REARPROJECTED)
			{
				const CameraSpacePoint& rightHand = kinect->joints[JointType_HandRight].Position;
				kinectIndicator->m_translations = glm::vec3(rightHand.X * 50, rightHand.Y * 40, -1);
			}
			else {
				const CameraSpacePoint& rightHand = kinect->joints[JointType_HandRight].Position;
				kinectIndicator->m_translations = glm::vec3((-rightHand.Z + 2) * 50, rightHand.Y * 40, -1);
			}
		}
	} 
	*/
}
