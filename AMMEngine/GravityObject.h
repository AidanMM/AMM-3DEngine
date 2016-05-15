#pragma once
#include "GameObject.h"
#define PI 3.14159265359f

class GravityObject : public GameObject {
public:
	glm::vec3 m_velocity;
	glm::vec3 m_acceleration;
	glm::vec3 m_position;
	glm::vec3 m_netForce;
	glm::vec3 max;
	glm::vec3 min;
	float m_mass;
	float m_density;
	float m_radius;

	GravityObject(float density, float mass);

	float MapRange(float value, float low1, float high1, float low2, float high2);

	virtual void Update(float dt) override;

	void applyForce(glm::vec3 force);

	virtual void onCollision(GameObject* other);
};