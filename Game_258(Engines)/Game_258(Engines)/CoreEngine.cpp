#include "CoreEngine.h"

std::unique_ptr<CoreEngine> CoreEngine::engineInstance = nullptr;

CoreEngine::CoreEngine()
{
	window = nullptr;
	isRunning = false;
	fps = 60;
	gameInterface = nullptr;
	currentSceneNum = 0;
}

CoreEngine::~CoreEngine()
{
}

CoreEngine* CoreEngine::GetInstance() {
	if(engineInstance.get() == nullptr){
		engineInstance.reset(new CoreEngine);
	}
	return engineInstance.get();
}

bool CoreEngine::OnCreate(std::string name_, int width_, int height_)
{
	Debug::OnCreate();
	window = new Window();
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Window failed to initialize", "CoreEngine.cpp", __LINE__);
		OnDestroy();
		return isRunning = false;
	}

	SDL_WarpMouseInWindow(window->GetWindow(), window->GetWidth() / 2, window->GetHeight() / 2);
	MouseEventListener::RegisterEngineObject(this);

	ShaderHandler::GetInstance()->CreateProgram("colourShader", "ColourVertexShader.glsl", "ColourFragmentShader.glsl");
	ShaderHandler::GetInstance()->CreateProgram("basicShader", "VertexShader.glsl", "FragmentShader.glsl");

	if (gameInterface) {
		if (!gameInterface->OnCreate()) {
			Debug::FatalError("Failed to load game", "CoreEngine.cpp", __LINE__);
			OnDestroy();
			return isRunning = false;
		}
	}

	Debug::Info("Everthing worked", "CoreEngine.cpp",__LINE__);
	timer = new Timer();
	timer->Start();
	return isRunning = true;
}

void CoreEngine::Run()
{
	while (isRunning) {
		timer->UpdateFrameTicks();
		EventListener::Update();
		Update(timer->GetDeltaTime());
		Render();
		SDL_Delay(timer->GetSleepTime(fps));
	}
	if (!isRunning) {
		OnDestroy();
	}
}

void CoreEngine::Exit()
{
	isRunning = false;
}

bool CoreEngine::GetIsRunning() const
{
	return isRunning;
}

int CoreEngine::GetCurrentScene() const
{
	return currentSceneNum;
}

float CoreEngine::GetScreenWidth() const
{
	return static_cast<float>(window->GetWidth());
}

float CoreEngine::GetScreenHeight() const
{
	return static_cast<float>(window->GetHeight());
}

Camera* CoreEngine::GetCamera() const
{
	return camera;
}

void CoreEngine::SetGameInterface(GameInterface* gameInterface_)
{
	gameInterface = gameInterface_;
}

void CoreEngine::SetCurrentScene(int sceneNum_)
{
	currentSceneNum = sceneNum_;
}

void CoreEngine::SetCamera(Camera* camera_)
{
	camera = camera_;
}

void CoreEngine::NotifyOfMousePressed(glm::ivec2 mouse_, int buttonType_)
{
}

void CoreEngine::NotifyOfMouseReleased(glm::ivec2 mouse_, int buttonType_)
{
	CollisionHandler::GetInstance()->MouseUpdate(mouse_, buttonType_);

}

void CoreEngine::NotifyOfMouseMove(glm::ivec2 mouse_)
{
	if (camera) {
		camera->ProcessMouseMovement(MouseEventListener::GetMouseOffSet());
	}
}

void CoreEngine::NotifyOfMouseScroll(int y_)
{
	if (camera) {
		camera->ProcessMouseZoom(y_);
	}
}

void CoreEngine::Update(const float deltaTime_)
{
	if (gameInterface) {
		gameInterface->Update(deltaTime_);
	
	}
	
}

void CoreEngine::Render()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		if (gameInterface) {
			gameInterface->Render();
	 }
		SDL_GL_SwapWindow(window->GetWindow());
}

void CoreEngine::OnDestroy()
{
	Texturehandler::GetInstance()->OnDestroy();
	ShaderHandler::GetInstance()->OnDestroy();
	SceneGraph::GetInstance()->OnDestroy();
	MaterialHandler::GetInstance()->OnDestroy();
	CollisionHandler::GetInstance()->OnDestroy();
	delete gameInterface;
	gameInterface = nullptr;

	delete camera;
	camera = nullptr;

	delete window;
	window = nullptr;
	SDL_Quit;
	exit(0);
}
