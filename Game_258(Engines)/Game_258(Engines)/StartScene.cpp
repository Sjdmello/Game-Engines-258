#include "StartScene.h"

StartScene::StartScene() : Scene()
{
}

StartScene::~StartScene()
{
}

bool StartScene::OnCreate()
{
	//std::cout << "start scene" << std::endl;
	CoreEngine::GetInstance()->SetCurrentScene(1);
	return true;
}

void StartScene::Update(const float deltaTime_)
{
}

void StartScene::Render()
{
}
