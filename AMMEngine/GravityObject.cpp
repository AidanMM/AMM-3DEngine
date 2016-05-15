#include "GravityObject.h"

GravityObject::GravityObject(float density, float mass)
{
	m_model = new Model("Sphere");
	m_model->GenSphere(1.0f, 6);
	EnableCollision();
	m_collisionData->m_collisionMask = 0;
	float volume = mass / density;
	float radius = cbrtf(volume * 3 / 4 / PI);
	m_scales = glm::vec3(radius, radius, radius);
	m_mass = mass;
	m_density = density;

	max = glm::vec3(0, 0, 0);
	min = max;
}

void GravityObject::Update(float dt)
{
	m_acceleration = m_netForce / m_mass;
	m_velocity += m_acceleration;
	m_position += m_velocity * dt;

	m_translations = m_position;

	m_netForce = glm::vec3(0, 0, 0);

	if (m_name == "BlackHole")
	{
		float volume = m_mass / m_density;
		float radius = cbrtf(volume * 3 / 4 / PI);
		m_scales = glm::vec3(radius, radius, radius);
	}
	else 
	{
		if (m_position.x < min.x)
			min.x = m_position.x;
		else if (m_position.x > max.x)
			max.x = m_position.x;

		if (m_position.y < min.y)
			min.y = m_position.y;
		else if (m_position.y > max.y)
			max.y = m_position.y;

		if (m_position.z < min.z)
			min.z = m_position.z;
		else if (m_position.z > max.z)
			max.z = m_position.z;

		glm::vec3 color;
		color.x = MapRange(m_position.x, min.x, max.x, 0.4f, .6f);
		//color.y = MapRange(m_position.y, min.y, max.y, 0.4f, .6f);
		color.z = MapRange(m_position.z, min.z, max.z, 0, 1);
		SetColor(color);
	}
}

void GravityObject::applyForce(glm::vec3 force)
{
	m_netForce += force;
}

void GravityObject::onCollision(GameObject * other)
{
	if (other->m_name == "indicator")
	{
		SetColor(m_model->m_color * .999f);
		m_mass += 1000;
	}
}

float GravityObject::MapRange(float value, float low1, float high1, float low2, float high2)
{
	return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}
