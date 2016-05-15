#include "Octree.h"

void Octree::ReBound(Octree* oct)
{
	//Not implmeneted currently.  Stub implementation
	/*
	if (m_gameObjects.size() == 0)
	{
		for (int i = 0; i < m_children.size(); i++) 
		{
			ReBound(m_children[i]);
		}
	}
	else {
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			CheckMinMax(m_gameObjects[i]->m_translations);
		}
	}*/
}

void Octree::CalcBounds(std::vector<GameObject*> objects)
{
	if (objects.size() >= 1)
	{
		m_min = objects[0]->m_translations;
		m_max = m_min;
	}
	for (int i = 0; i < objects.size(); i++)
	{
		CheckMinMax(objects[i]->m_collisionData->m_reBoundingPoints);
	}
	m_size = (m_max - m_min);
	m_position = (m_max + m_min) / 2.0f;
}

void Octree::CheckMinMax(glm::vec3 checkAgainst)
{
	if (checkAgainst.x > m_max.x)
		m_max.x = checkAgainst.x;
	if (checkAgainst.x < m_min.x)
		m_min.x = checkAgainst.x;

	if (checkAgainst.y > m_max.y)
		m_max.y = checkAgainst.y;
	if (checkAgainst.y < m_min.y)
		m_min.y = checkAgainst.y;

	if (checkAgainst.z > m_max.z)
		m_max.z = checkAgainst.z;
	if (checkAgainst.z < m_min.z)
		m_min.z = checkAgainst.z;
}

void Octree::CheckMinMax(std::vector<glm::vec3> points)
{
	for (int i = 0; i < points.size(); i++)
	{
		CheckMinMax(points[i]);
	}
}

bool Octree::Overlaps(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2)
{
	bool areColliding = true;

	if (max1.x < min2.x)
		areColliding = false;
	if (min1.x > max2.x)
		areColliding = false;

	if (max1.y < min2.y)
		areColliding = false;
	if (min1.y > max2.y)
		areColliding = false;

	if (max1.z < min2.z)
		areColliding = false;
	if (min1.z > max2.z)
		areColliding = false;

	return areColliding;
}

void Octree::AdjustObject(GameObject * obj)
{	
	if (obj->IsDelete())
		return;
	if (Overlaps(obj->m_collisionData->m_min + obj->m_translations, obj->m_collisionData->m_max + obj->m_translations, m_min, m_max))
	{
		if (m_children.size() == 0)
		{
			m_gameObjects.push_back(obj);
		} 
		else
		{
			for (int i = 0; i < m_children.size(); i++)
			{
				m_children[i]->PlaceObject(obj);
			}
		}
	} 
	else if (m_parent != nullptr)
	{
		m_parent->AdjustObject(obj);
	}
	else if (m_parent == nullptr)
	{
		//Resizing code not functioning as intended
		/*for (int i = 0; i < m_children.size(); i++)
		{
			for (int i = 0; i < obj->m_collisionData->m_boundingPoints.size(); i++)
			{
				CheckMinMax(obj->m_collisionData->m_boundingPoints[i]);
			}
			m_size = (m_max - m_min);
			m_children[i]->AdjustSize(m_size / 2.0f);
		}*/
	}
}

void Octree::PlaceObject(GameObject * obj)
{
	if (Overlaps(obj->m_collisionData->m_min + obj->m_translations, obj->m_collisionData->m_max + obj->m_translations, m_min, m_max))
	{ 
		if (m_children.size() != 0)
		{
			for (int i = 0; i < m_children.size(); i++)
			{
				m_children[i]->PlaceObject(obj);
			}
		}
		else
		{
			m_gameObjects.push_back(obj);
		}
	}
}

Octree::Octree(std::vector<GameObject*> contained, int subdivisions)
{	
	m_cube = new Model("cube");
	m_cube->GenCube(1.0f);
	CalcBounds(contained);
	SubDivide(contained, subdivisions);
}

Octree::Octree(std::vector<GameObject*> contained, int subdivisions, glm::vec3 size)
{
	m_cube = new Model("cube");
	m_cube->GenCube(1.0f);
	CalcBounds(contained);
	m_size = size;
	m_min = m_position - size;
	m_max = m_position + size;
	SubDivide(contained, subdivisions);
}

Octree::Octree(std::vector<GameObject*> contained, int subdivisions, glm::vec3 min, glm::vec3 max, glm::vec3 position, glm::vec3 size)
{
	m_min = min;
	m_max = max;
	m_position = position;
	m_size = size;
	m_cube = new Model("cube");
	m_cube->GenCube(1.0f);
	SubDivide(contained, subdivisions);
}

void Octree::AddNode(GameObject * object)
{
	if (m_children.size() != 0)
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->PlaceObject(object);
		}
	}
}

void Octree::SubDivide(std::vector<GameObject*> contained, int subdivisions)
{
	if (subdivisions > 0)
	{
		for (int i = 0; i < 8; i++)
		{
			glm::vec3 size = m_size / 2.0f;
			glm::vec3 offset = size / 2.0f;
			glm::vec3 position;
			switch (i)
			{
			case TOP_BACK_LEFT:
				position = glm::vec3(m_position.x - offset.x, m_position.y + offset.y, m_position.z - offset.z);
				break;
			case TOP_BACK_RIGHT:
				position = glm::vec3(m_position.x + offset.x, m_position.y + offset.y, m_position.z - offset.z);
				break;
			case TOP_FRONT_LEFT:
				position = glm::vec3(m_position.x - offset.x, m_position.y + offset.y, m_position.z + offset.z);
				break;
			case TOP_FRONT_RIGHT:
				position = glm::vec3(m_position.x + offset.x, m_position.y + offset.y, m_position.z + offset.z);
				break;
			case BOTTOM_BACK_LEFT:
				position = glm::vec3(m_position.x - offset.x, m_position.y - offset.y, m_position.z - offset.z);
				break;
			case BOTTOM_BACK_RIGHT:
				position = glm::vec3(m_position.x + offset.x, m_position.y - offset.y, m_position.z - offset.z);
				break;
			case BOTTOM_FRONT_LEFT:
				position = glm::vec3(m_position.x - offset.x, m_position.y - offset.y, m_position.z + offset.z);
				break;
			case BOTTOM_FRONT_RIGHT:	
			default:
				position = glm::vec3(m_position.x + offset.x, m_position.y - offset.y, m_position.z + offset.z);
				break;
			}	
			glm::vec3 max = position + size;
			glm::vec3 min = position - size;

			std::vector<GameObject*> collection;
			for (int i = 0; i < contained.size(); i++)
			{
				if (Overlaps(contained[i]->m_collisionData->m_min + contained[i]->m_translations, contained[i]->m_collisionData->m_max + contained[i]->m_translations, min, max))
				{
					collection.push_back(contained[i]);
				}
			}
			Octree* octree = new Octree(collection, subdivisions - 1, min, max, position, size);
			octree->m_parent = this;
			m_children.push_back(octree);
		}
	}
	else
	{
		for (int i = 0; i < contained.size(); i++)
		{
			if (Overlaps(contained[i]->m_collisionData->m_min + contained[i]->m_translations, contained[i]->m_collisionData->m_max + contained[i]->m_translations, m_min, m_max))
			{
				m_gameObjects.push_back(contained[i]);
			}
		}
	}
}

void Octree::Render()
{
	if (m_children.size() != 0)
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->Render();
		}
		return;
	}
	if (worldCamera == nullptr)
	{
		worldCamera = Camera::GetInstance();
	}
	glm::mat4 transformations = glm::mat4(1.0f);
	transformations *= glm::translate(m_position);
	transformations *= glm::scale(m_size);
	m_cube->Render(transformations, worldCamera->GetView(), worldCamera->GetProjection());
	
}

void Octree::CheckCollisions()
{
	AdjustOctree();
	if (m_gameObjects.size() == 0)
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->CheckCollisions();
		}
	}
	else
	{
		for (int i = 0; i < m_gameObjects.size(); i++)
		{
			GameObject* first = m_gameObjects[i];
			if (first->IsDelete())
			{
				m_gameObjects.erase(m_gameObjects.begin() + i);
				i--;
				continue;
			}
			for (int k = 0; k < m_gameObjects.size(); k++)
			{
				if (i == k)
					continue;
				GameObject* second = m_gameObjects[k];
				if (second->IsDelete())
				{
					m_gameObjects.erase(m_gameObjects.begin() + k);
					k--;
					continue;
				}
				if (first->m_collisionData->m_collisionMask == 0 || second->m_collisionData->m_collisionMask == 0)
					continue;
				if (first->m_collisionData->m_collisionMask & second->m_collisionData->m_collisionMask == 0)
					continue;
				if (CollisionData::AreColliding(CollisionData::CollisionDetectionType::AxisRealignedBoundingBox, first, second))
				{
					//TODO: This is slow as they are both going to check for collision against each other
					//there should be logic to prevent this
					first->onCollision(second);
				}
			}
		}
	}
}

void Octree::AdjustOctree()
{
	if (m_gameObjects.size() == 0)
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->AdjustOctree();
		}
	}
	else
	{
		int curSize = m_gameObjects.size();
		for (int i = 0; i < curSize; i++)
		{
			if (m_gameObjects[i]->DidModifyTransformations())
			{
				AdjustObject(m_gameObjects[i]);
				m_gameObjects.erase(m_gameObjects.begin() + i);
				i--;
				curSize--;
			}
		}
	}
}

void Octree::AdjustSize(glm::vec3 size)
{
	if (m_parent == nullptr)
		return;
	glm::vec3 vecFromParent = m_position - m_parent->m_position;
	vecFromParent = glm::normalize(vecFromParent);
	m_position = vecFromParent * glm::length(size);
	m_min = m_position - size;
	m_max = m_position + size;
	if (m_children.size() != 0)
	{
		for (int i = 0; i < m_children.size(); i++)
		{
			m_children[i]->AdjustSize(size / 2.0f);
		}
	}
	
}

Octree::~Octree()
{
	for (int i = 0; i < m_children.size(); i++)
	{
		delete m_children[i];
	}
	worldCamera = nullptr;
	delete m_cube;
}
