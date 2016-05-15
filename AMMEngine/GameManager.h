#pragma once
#include "GameObject.h"
#include "Octree.h"

class Scene {
public:
	Scene() { };
	~Scene();
	std::vector<GameObject*> m_dynamicAdditionQueue;
	std::map<std::string, std::vector<GameObject*>> m_objectsDictionary;
	std::vector<GameObject*> m_objects;
	bool initialized = false;

	virtual void Init() = 0;

	virtual void Update(float dt) = 0;

	void AddObject(GameObject* object);

	GameObject* GetObjectByName(std::string name);
	std::vector<GameObject*> GetAllObjectsByName(std::string name);
};

enum COLLISION_TYPE {
	BRUTE_FORCE,
	OCTREE
};

class GameManager {
private:
	bool m_isDebug = false;

	static GameManager* instance;
	GameManager();
	GameManager(GameManager const* other) {};
	GameManager& operator=(GameManager const& other) {};
	void BruteForceCollision();
	void OctreeCollision();
	std::vector<int> deleteQueue;
	Octree* m_octree = nullptr;
	int m_currentSubdivisions = m_subdivisions;
	void AddObjectToCurrentScene(GameObject* object);
public:
	static GameManager* GetInstance();
	static void ReleaseInstance();

	static GLFWwindow* window;
	int m_subdivisions = 1;
	int m_collisionType = OCTREE;

	std::vector<Scene*> m_sceneStack;
	Scene* m_currentScene;

	void SetCurrentScene(Scene* scene);
	void PopCurrentScene();

	void Update(float deltaTime);
	//void Update();

	void Draw();
	void DrawDebug();

	void DetectCollisions();
};