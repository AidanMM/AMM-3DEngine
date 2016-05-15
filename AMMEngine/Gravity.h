#pragma once
#include "GameManager.h"
#include "GravityObject.h"
#include "KinectUtilites.h"
#include "SimpleObjects.h"

class Gravity : public Scene {
	std::vector<GravityObject*> astralBodies;
	KinectUtilities* kinect;
	BoxObject* kinectIndicator;

	void AddAstralBody(GravityObject* toAdd);

	glm::vec3 CalculateGravitationalForce(GravityObject* first, GravityObject* second);

	virtual void Init();

	virtual void Update(float dt);
};