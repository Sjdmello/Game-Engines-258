#include "CoreEngine.h"
#include "Game1.h"



int main(int argc, char* argv[]) {

	CoreEngine::GetInstance()->SetGameInterface(new Game1);
	
	if (!CoreEngine::GetInstance()->OnCreate("Game Engines 4", 800, 600)) {
		std::cout << "failed to create engine" << std::endl;
		return 0;
	}
	CoreEngine::GetInstance()->Run();
	return 0;
	
}