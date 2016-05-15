#pragma once
#include "GameManager.h"
#include "GameObject.h"
#include "XboxControls.h"


extern GLFWwindow* window;

class CubeObject : public GameObject {
public:
	CubeObject() { m_model->GenCube(1.0f); EnableCollision(); }

	CubeObject(float size) { m_model->GenCube(size); EnableCollision(); }

	void Update(float dt)
	{
		//m_collisionData->UpdateBoundingBoxes();
	};
};

class BoxObject : public GameObject {
public:
	BoxObject() { BoxObject(1.0f, 2.0f, 1.0f); }
	BoxObject(float length, float width, float height) 
	{
		m_name = "Box";
		m_model = new Model(m_name);
		m_model->GenCube(1.0);
		m_scales = glm::vec3(length, width, height);
		EnableCollision();
	}

	void Update(float dt)
	{
		//TODO: Discuss whether or not calling this should be an "option" of those inheriting form GameObject
		//m_collisionData->UpdateBoundingBoxes();
		SetColor(glm::vec3(0.0f, 0.0f, 1.0f));
	};

	virtual void onCollision(GameObject* other) override
	{
		SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	}
};

class SphereObject : public GameObject {
public:
	SphereObject() : SphereObject(1.0f) {};
	SphereObject(float radius)
	{
		m_name = "Sphere";
		m_model = new Model(m_name);
		m_model->GenSphere(radius, 6);
		EnableCollision();
	}

	void Update(float dt)
	{

	}
};

class PlayerBox : public BoxObject {
public:
	XboxControls* Controller = new XboxControls(1);
	PlayerBox() : BoxObject(1.0f, 1.0f, 1.0f) { }
	void Update(float dt)
	{
		float velocity = 5.0f * dt;
		SetColor(glm::vec3(1.0f, 0.0f, 0.0f));

		if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT))
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_I))
			{
				m_translations += glm::vec3(0.0f, -velocity, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_K))
			{
				m_translations += glm::vec3(0.0f, velocity, 0.01f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_U))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, -1.0f, 0.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_O))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			}
		}
		else
		{
			if (glfwGetKey(GameManager::window, GLFW_KEY_J) || (Controller->GetState().Gamepad.sThumbLX < 0))
			{
				m_translations += glm::vec3(-velocity, 0.0f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_L) || (Controller->GetState().Gamepad.sThumbLX > 0))
			{
				m_translations += glm::vec3(velocity, 0.0f, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_I) || (Controller->GetState().Gamepad.sThumbLY > 0))
			{
				m_translations += glm::vec3(0.0f, velocity, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_K) || (Controller->GetState().Gamepad.sThumbLY < 0))
			{
				m_translations += glm::vec3(0.0f, -velocity, 0.0f);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_N))
			{
				m_translations += glm::vec3(0.0f, 0.0f, -velocity);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_M))
			{
				m_translations += glm::vec3(0.0f, 0.0f, velocity);
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_U))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, 1.0f));
			}
			if (glfwGetKey(GameManager::window, GLFW_KEY_O))
			{
				m_rotations *= glm::rotate(1.0f, glm::vec3(0.0f, 0.0f, -1.0f));
			}
		}
	}

	void onCollision(GameObject* other) {
		SetColor(glm::vec3(1.0f, 1.0f, 0.0f));
	}
};