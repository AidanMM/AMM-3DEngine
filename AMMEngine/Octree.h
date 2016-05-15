#pragma once
#include "Model.h"
#include "GameObject.h"

enum SECTION {
	TOP_FRONT_LEFT = 0,
	TOP_FRONT_RIGHT = 1,
	TOP_BACK_LEFT = 2,
	TOP_BACK_RIGHT = 3,
	BOTTOM_FRONT_LEFT = 4,
	BOTTOM_FRONT_RIGHT = 5,
	BOTTOM_BACK_LEFT = 6,
	BOTTOM_BACK_RIGHT = 7
};

class Octree {
private:
	Octree();
	Octree(std::vector<GameObject*> contained, int subdivisions, glm::vec3 min, glm::vec3 max, glm::vec3 position, glm::vec3 size);
	Model* m_cube;
	glm::vec3 m_position;
	glm::vec3 m_size;
	glm::vec3 m_max;
	glm::vec3 m_min;
	Octree* m_parent = nullptr;
	Camera* worldCamera = nullptr;

	void ReBound(Octree* oct);
	void CalcBounds(std::vector<GameObject*> objects);
	void CheckMinMax(glm::vec3 checkAgainst);
	void CheckMinMax(std::vector<glm::vec3> points);
	bool Overlaps(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2);
	void AdjustObject(GameObject* obj);
	void PlaceObject(GameObject* obj);
	void AdjustOctree();
	void AdjustSize(glm::vec3 size);
public:
	std::vector<Octree*> m_children;
	std::vector<GameObject*> m_gameObjects;
	int section = -1; 

	/// <summary>
	/// When you create an Octree, you need to pass it a list of game objects for it to contain.
	/// It will then attempt to place and subdivide accordingly.
	/// <summary>
	Octree(std::vector<GameObject*> contained, int subdivisions);
	Octree(std::vector<GameObject*> contained, int subdivisions, glm::vec3 size);

	void AddNode(GameObject* object);

	void SubDivide(std::vector<GameObject*> contained, int subdivisions);

	void Render();

	void CheckCollisions();

	~Octree();
};