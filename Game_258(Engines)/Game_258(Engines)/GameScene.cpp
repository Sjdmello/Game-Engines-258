#include "GameScene.h"

GameScene::GameScene() : Scene()
{
	shape = nullptr;
	
}

GameScene::~GameScene()
{
	model = nullptr;
	delete shape;
	shape = nullptr;

}

bool GameScene::OnCreate()
{
	Debug::Info("Creating GameScene", "GameScene.cpp", __LINE__);
	CoreEngine::GetInstance()->SetCamera(new Camera());
	CoreEngine::GetInstance()->GetCamera()->SetPosition(glm::vec3(0.0f, 0.0f, 4.0f));
	CoreEngine::GetInstance()->GetCamera()->AddLightSource(new LightSource(glm::vec3(0.0f, 0.0f, 2.0f), 0.1f, 0.5f, 0.5f,
		glm::vec3(1.0f, 1.0f, 1.0f)));

	
	

    model = new Model("Resources/Models/Dice.obj",
		"Resources/Models/Dice.mtl",ShaderHandler::GetInstance()->GetShader("basicShader"));
	//model->SetScale(glm::vec3(0.5f));
	shape = new GameObject(model);
	
	return true;
}

void GameScene::Update(const float deltaTime_)
{
	shape->Update(deltaTime_);
}

void GameScene::Render()
{
	shape->Render(CoreEngine::GetInstance()->GetCamera());

}
