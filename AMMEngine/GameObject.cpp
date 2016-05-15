#include "GameObject.h"
#include "Model.h"

GameObject::GameObject()
{
	m_worldCamera = Camera::GetInstance();
	m_data = new std::map<std::string, int>();
}

GameObject::~GameObject()
{	
	if (m_model != nullptr)
	{
		delete m_model;
		m_model = nullptr;
	}
	if (m_data != nullptr)
	{
		delete m_data;
		m_data = nullptr;
	}

	if (m_worldCamera != nullptr)
	{
		//delete m_worldCamera;
		m_worldCamera = nullptr;
	}
}

Model * GameObject::GetModel()
{
	return m_model;
}

void GameObject::SetModel(Model* model)
{
	if (m_model != nullptr)
	{
		delete m_model;
	}
	m_model = model;
	if (m_model != nullptr)
	{
		delete m_collisionData;
	}
	m_collisionData = new CollisionData(*model->GetMesh()->m_modelCollisionData);
	m_collisionData->BindToObject(this);
}

void GameObject::SetColor(glm::vec3 color)
{
	m_model->m_color = color;
}

void GameObject::Draw()
{
	m_oldTransformations = m_transformations;
	m_transformations = glm::mat4(1.0f);
	m_transformations *= glm::translate(m_translations);
	m_transformations *= m_rotations;
	m_transformations *= glm::scale(m_scales);
	if (m_oldTransformations != m_transformations)
		m_transformationsModified = true;
	else
		m_transformationsModified = false;
	if (m_visible)
	{
		m_model->Render(m_transformations, m_worldCamera->GetView(), m_worldCamera->GetProjection());
	}
}

void GameObject::DrawDebug()
{
	//The reason this wraps only one function is for future additions of drawing 
	//vector information and any other possible information.
	m_collisionData->DrawBoundingBox();
}

void GameObject::EnableCollision()
{
	m_collisionData = new CollisionData(*m_model->GetMesh()->m_modelCollisionData);
	m_collisionData->BindToObject(this);
	m_collisionData->SetModel(m_model->GetMesh());
}

void GameObject::CreateModel(std::string name)
{
	if (m_model != nullptr)
	{
		delete m_model;
	}

	m_model = new Model(name);
}

void GameObject::Delete()
{
	CleanUp();
	isDelete = true;
	m_visible = false;
	m_collisionData->m_collisionMask = 0;
}
