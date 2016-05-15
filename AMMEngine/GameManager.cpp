#include "GameManager.h"

GameManager* GameManager::instance = nullptr;
GLFWwindow* GameManager::window = nullptr;

GameManager::GameManager()
{
}

void GameManager::BruteForceCollision()
{
	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		GameObject* first = m_currentScene->m_objects[i];
		if (first->m_collisionData->m_collisionMask == 0)
			continue;
		for (int p = 0; p < m_currentScene->m_objects.size(); p++)
		{
			if (i == p)
				continue;
			GameObject* second = m_currentScene->m_objects[p];
			if (first->m_collisionData->m_collisionMask == 0 || second->m_collisionData->m_collisionMask == 0)
				continue;
			if (first->m_collisionData->m_collisionMask & second->m_collisionData->m_collisionMask == 0)
				continue;
			if (CollisionData::AreColliding(CollisionData::CollisionDetectionType::AxisRealignedBoundingBox, first, second))
			{
				//TODO: This is slow as they are both going to check for collision against each other
				//there should be logic to prevent this v
				first->onCollision(second);
			}
		}
	}
}

void GameManager::OctreeCollision()
{
	if (m_currentSubdivisions != m_subdivisions)
	{
		m_currentSubdivisions = m_subdivisions;
		if (m_octree != nullptr)
			delete m_octree;
		m_octree = new Octree(m_currentScene->m_objects, m_currentSubdivisions);
	}
	if (m_octree == nullptr)
	{
		m_octree = new Octree(m_currentScene->m_objects, m_currentSubdivisions);
	}
	m_octree->CheckCollisions();
}

void GameManager::AddObjectToCurrentScene(GameObject* object)
{
	if (m_currentScene->m_objectsDictionary.find(object->m_name) != m_currentScene->m_objectsDictionary.end())
	{
		m_currentScene->m_objects.push_back(object);
		m_currentScene->m_objectsDictionary[object->m_name].push_back(object);
	}
	else {
		std::vector<GameObject*> objects;
		objects.push_back(object);
		m_currentScene->m_objects.push_back(object);
		m_currentScene->m_objectsDictionary[object->m_name] = objects;
	}
}

GameManager * GameManager::GetInstance()
{
	if (instance != nullptr)
	{
		return instance;
	}
	else
	{
		//Create a new Cube model as the default model
		Model* model = new Model("Cube");
		model->GenCube(1.0f);
		return instance = new GameManager();
	}
}

void GameManager::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

void GameManager::SetCurrentScene(Scene* scene)
{
	if (scene->initialized == false)
	{
		scene->Init();
		scene->initialized = true;
	}
	//m_sceneStack.clear();
	m_sceneStack.push_back(scene);
	m_currentScene = scene;
	m_octree = nullptr;
}

void GameManager::PopCurrentScene()
{
	Scene* oldScene = m_sceneStack.back();
	m_sceneStack.pop_back();
	SetCurrentScene(m_sceneStack.back());
	delete oldScene;
}

void GameManager::Update(float deltaTime)
{
	if (glfwGetKey(GameManager::window, GLFW_KEY_LEFT_SHIFT))
	{
		if (glfwGetKey(GameManager::window, GLFW_KEY_T))
		{
			m_isDebug = false;
		}
	}
	else
	{
		if (glfwGetKey(GameManager::window, GLFW_KEY_T))
		{
			m_isDebug = true;
		}
	}

	//Delete anything in the delete Queue
	for (int i = 0; i < deleteQueue.size(); i++)
	{
		int index = deleteQueue[i] - i;
		GameObject* obj = m_currentScene->m_objects[index];
		m_currentScene->m_objects.erase(m_currentScene->m_objects.begin() + index);
		delete obj;
	}
	
	deleteQueue.clear();

	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		GameObject* go = m_currentScene->m_objects[i];
		go->Update(deltaTime);

		// For now, check to see if collision is enabled. If so, update bounding boxes.
		if (go->m_collisionData != nullptr && go->m_collisionData->m_collisionMask != 0)
		{
			go->m_collisionData->UpdateBoundingBoxes();
		}
	}

	m_currentScene->Update(deltaTime);

	DetectCollisions();

	//Add all of the objects that are currently in the dynamic addition queue
	for (int i = 0; i < m_currentScene->m_dynamicAdditionQueue.size(); i++)
	{
		if (m_octree != nullptr)
		{
			m_octree->AddNode(m_currentScene->m_dynamicAdditionQueue[i]);
		}
		AddObjectToCurrentScene(m_currentScene->m_dynamicAdditionQueue[i]);
		m_currentScene->m_dynamicAdditionQueue.erase(m_currentScene->m_dynamicAdditionQueue.begin() + i);
		i--;
	}
	m_currentScene->m_dynamicAdditionQueue.clear();
}

void GameManager::Draw()
{
	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		if (m_currentScene->m_objects[i]->IsDelete())
		{
			deleteQueue.push_back(i);
			continue;
		} 
		
		m_currentScene->m_objects[i]->Draw();
	}
}

void GameManager::DrawDebug()
{
	if (!m_isDebug)
	{
		return;
	}

	for (int i = 0; i < m_currentScene->m_objects.size(); i++)
	{
		m_currentScene->m_objects[i]->DrawDebug();
	}
	if (m_octree != nullptr && m_collisionType == OCTREE) 
	{
		m_octree->Render();
	}
}

void GameManager::DetectCollisions()
{
	switch (m_collisionType)
	{
	case OCTREE:
		OctreeCollision();
		break;
	case BRUTE_FORCE:
	default:
		BruteForceCollision();
		break;
	}
	
}

Scene::~Scene()
{
	delete &m_objects;
	delete &m_objectsDictionary;
}

void Scene::AddObject(GameObject* object)
{
	if (initialized == false)
	{
		if (m_objectsDictionary.find(object->m_name) != m_objectsDictionary.end())
		{
			m_objects.push_back(object);
			m_objectsDictionary[object->m_name].push_back(object);
		}
		else {
			std::vector<GameObject*> objects;
			objects.push_back(object);
			m_objects.push_back(object);
			m_objectsDictionary[object->m_name] = objects;
		}
	}
	else
	{
		m_dynamicAdditionQueue.push_back(object);
	}
}

GameObject * Scene::GetObjectByName(std::string name)
{
	if (m_objectsDictionary.find(name) != m_objectsDictionary.end())
	{
		return m_objectsDictionary[name].front();
	}
	else 
		return nullptr;
}

std::vector<GameObject*> Scene::GetAllObjectsByName(std::string name)
{
	if (m_objectsDictionary.find(name) != m_objectsDictionary.end())
	{
		return m_objectsDictionary[name];
	}
	else
		return std::vector<GameObject*>();
}
