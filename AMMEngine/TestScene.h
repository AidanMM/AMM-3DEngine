#pragma once
#include "GameManager.h"
#include "SimpleObjects.h"

class TestScene : public Scene {
	Camera* camera;
	BoxObject* cube;
	virtual void Init();

	virtual void Update(float dt);

	void HandleInput(Camera* camera);
};