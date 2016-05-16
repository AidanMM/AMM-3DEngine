#include "TestScene.h"
#include "MeshGenerator.h"

void TestScene::Init()
{
	GameManager::GetInstance()->m_collisionType = BRUTE_FORCE;
	BoxObject* box = new BoxObject(1000.0f, 1.0f, 1000.0f);
	box->m_name = "Ground";
	Model* myModel = new Model();
	myModel->GenCube(1.0f);
	box->SetModel(myModel);
	box->defaultColor = glm::vec3(125.0f / 255.0f, 68.0f / 255.0f, 23.0f / 255.0f);
	box->m_collisionData->m_collisionMask = 0;
	AddObject(box);

	camera = Camera::GetInstance();
	camera->SetPosition(glm::vec3(0.0f, 5.0f, 200.0f));

	
	MeshGenerator* mesh = new MeshGenerator();

	std::cout << "Generating Tree1..." << std::endl;
	mesh->rotationOffset = 0.3926991f;
	mesh->translationOffset = 5.0f;
	mesh->m_system.AddAxiom('F', "F[Fz[zFZXFZYF]Z[ZFxzFyzF]C+]");
	mesh->GenerateModel("+TT+F", 4, "Tree1", glm::vec3(0, 0, 0), 1.0f, 6);

	std::cout << "Generating Tree2..." << std::endl;
	mesh->m_system.ClearAxioms();
	mesh->rotationOffset = 0.4485496f;
	mesh->translationOffset = 1.0f;
	mesh->m_system.AddAxiom('R', "F[ZxR][zR]FR");
	mesh->m_system.AddAxiom('F', "FF");
	//mesh->GenerateModel("R", 7, "Tree2", glm::vec3(0, 0, 0), .1f, 5);

	std::cout << "Generating Tree3..." << std::endl;
	mesh->m_system.ClearAxioms();
	mesh->rotationOffset = 0.3f;
	mesh->translationOffset = 4.0f;
	mesh->m_system.AddAxiom('R', "FFF[FXYZ[FxRxF[zFRzXFC]R[ZFZyFC]]yFRyF]");
	mesh->GenerateModel("+TT+R", 5, "Tree3", glm::vec3(0, 0, 0), 1.0f, 5);

	std::cout << "Generating Tree4..." << std::endl;
	mesh->m_system.ClearAxioms();
	mesh->rotationOffset = 0.1f;
	mesh->translationOffset = 1.0f;
	mesh->m_system.AddAxiom('R', "F[[yyBBzB]XB]");
	mesh->m_system.AddAxiom('B', "XXYYYYYYYYFRFzzFRRC");
	mesh->GenerateModel("+TT+R", 7, "Tree4", glm::vec3(0, 0, 0), 1.0f, 6);

	std::cout << "Generating Tree5..." << std::endl;
	mesh->m_system.ClearAxioms();
	mesh->rotationOffset = .4f;
	mesh->translationOffset = .2f;
	mesh->m_system.AddAxiom('R', "YYTF[xFR]C[XFRFR]");
	mesh->GenerateModel("+TT+R", 7, "Tree5", glm::vec3(0, 0, 0), .2f, 3);

	std::cout << "All trees generated!" << std::endl;
	std::cout << "Building a forest..." << std::endl;
	for (int x = -5; x < 5; x++)
	{
		for (int z = -5; z < 5; z++)
		{
			BoxObject* temp = new BoxObject(1.0f, 1.0f, 1.0f);
			int treeType = rand() % 4;
			//int treeType = 4;
			switch (treeType)
			{
			case 0:
				temp->SetModel(new Model("Tree1"));
				temp->m_scales = glm::vec3(.1f, .1f, .1f);
				break;
			case 4: {
				Model* foo = new Model("Cube");
				foo->GenBox(1.0f, 1.0f, 1.0f);
				temp->SetModel(foo);
				temp->m_scales = glm::vec3(5.0f, 5.0f, 5.0f);
			}
				break;
			case 1:
				temp->SetModel(new Model("Tree3"));
				temp->m_scales = glm::vec3(.3f, .3f, .3f);
				break;
			case 2:
				temp->SetModel(new Model("Tree4"));
				temp->m_scales = glm::vec3(.5f, .5f, .5f);
				break;
			case 3:
				temp->SetModel(new Model("Tree5"));
				temp->m_scales = glm::vec3(.5f, .5f, .5f);
			default:
				break;
			}
			temp->m_translations = glm::vec3(x * (rand() % 30 + 5), 0, z * (rand() % 25 + 20));
			glm::vec3 color = glm::vec3(rand() % 80 / 255.0f,
										rand() % 100 / 255.0f + .3f,
										rand() % 10 / 255.0f);
			temp->m_rotations *= glm::rotate((float)(rand() % 180), glm::vec3(0, 1, 0));
			temp->defaultColor = color;
			temp->m_scales *= (float)(rand() % 10 + 10) / 10.0f;
			temp->m_collisionData->m_collisionMask = 0;
			AddObject(temp);
		}
	}
}

void TestScene::Update(float dt)
{
	HandleInput(camera);
}

void TestScene::HandleInput(Camera * camera)
{
	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		camera->ChangeYaw(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		camera->ChangeYaw(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		camera->ChangePitch(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		camera->ChangePitch(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A))
	{
		camera->MoveSideways(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_D))
	{
		camera->MoveSideways(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		camera->MoveForward(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_S))
	{
		camera->MoveForward(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_Q))
	{
		camera->MoveVertical(1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_E))
	{
		camera->MoveVertical(-1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_J))
	{
		cube->m_rotations *= glm::rotate(.5f, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_L))
	{
		cube->m_rotations *= glm::rotate(-.5f, glm::vec3(0, 1, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_I))
	{
		cube->m_rotations *= glm::rotate(-.5f, glm::vec3(1, 0, 0));
	}
	if (glfwGetKey(window, GLFW_KEY_K))
	{
		cube->m_rotations *= glm::rotate(.5f, glm::vec3(1, 0, 0));
	}
}
