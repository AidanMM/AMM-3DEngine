#pragma once
#include "LSystem.h"
#include "Model.h"

#define PI 3.14159265359f

class MeshGenerator {
public:
	LSytem m_system;
	Model* m_model;
	float rotationOffset = PI / 8;
	float scaleOffset = 1.5f;
	float translationOffset = 1.0f;
	void GenerateModel(std::string system, int iterations, std::string modelName, glm::vec3 startingPoint, float radius, int pointsPerLevel);

private:

};