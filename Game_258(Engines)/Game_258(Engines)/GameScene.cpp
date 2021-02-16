#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	shape = nullptr;
	shape2 = nullptr;
}

GameScene::~GameScene()
{
	delete shape;
	shape = nullptr;

	delete shape2;
	shape2 = nullptr;
}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);
	Vertex v;
	std::vector<Vertex>vertexList;
	vertexList.reserve(3);
	v.pos = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = glm::vec3(0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	Vertex v2;
	std::vector<Vertex>vertexList;
	vertexList.reserve(3);
	v.pos = glm::vec3(-0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = glm::vec3(0.5f, 0.5f, 0.0f);
	vertexList.push_back(v);
	v.pos = glm::vec3(-0.5f, -0.5f, 0.0f);
	vertexList.push_back(v);

	Model* model = new Model();
	model->AddMesh(new Mesh(vertexList));
	shape = new GameObject(model);
	shape2 = new GameObject(model);
	return true;
}

void GameScene::Update(const float deltaTime_)
{
}

void GameScene::Render()
{
	shape->Render();
	shape2->Render();
}
