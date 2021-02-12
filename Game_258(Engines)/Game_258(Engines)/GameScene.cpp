#include "GameScene.h"

GameScene::GameScene() : Scene()
{

}

GameScene::~GameScene()
{
}

bool GameScene::OnCreate()
{
	std::cout << "game scene" << std::endl;
	return true;
}

void GameScene::Update(const float deltaTime_)
{
}

void GameScene::Render()
{
}
