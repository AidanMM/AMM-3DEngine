#pragma once
#include <iostream>

#include "GameManager.h"
#include "SimpleObjects.h"
#include "Automota.h"
#include "KinectUtilites.h"

class AestheticsScene : public Scene {
	Colony* colony;
	int counter = 0;
	KinectUtilities* kinect;
	float lowX, highX, lowY, highY, lowZ, highZ;

	virtual void Init();

	virtual void Update(float dt);
	float MapRange(float value, float low1, float high1, float low2, float high2);
	void HandleInput(Camera* camera);
};