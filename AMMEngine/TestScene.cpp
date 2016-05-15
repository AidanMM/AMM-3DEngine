#include "TestScene.h"
#include "SimpleObjects.h"

void TestScene::Init()
{
	BoxObject* box = new BoxObject(1.0f, 2.0f, 3.0f);
	box->m_name = "Box";
	Model* myModel = new Model();
	myModel->GenCube(1.0f);
	box->SetModel(myModel);

	AddObject(box);
}

void TestScene::Update(float dt)
{
}
